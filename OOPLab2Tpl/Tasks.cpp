#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
#include "Tasks.h"
#include "Examples.h"

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Task2  \n";
    cout << "    2.  Task2 \n";
    cout << "    3.  Examples \n";
    cout << "    4.  Exit \n";
}
void task1() {
    int a, b, c, d;
    cin>> a >> b >> c >> d;
    double defaultNum = (12 * a + ((d*15+12*b)/1024) - 12 * c + d * 15);
    double customNum = ((a << 3) + (a << 2)) + ((((d << 4) - d) + ((b << 3) + (b << 2))) >> 10) - ((c << 3) + (c << 2)) + ((d << 4) - d);
    cout<< defaultNum << endl << customNum <<endl;
    cout << " Calculation of expressions using bitwise operations  \n";
    return;
}


bool parityBit(short num) {
    bool result = false;
    for (int i = 1; i < 14; i++) {
        if ((num >> i) & 1)
            result = !result;
    }
    return result;
}
void task2() {
  cout << "1. Encode.\n2. Decode.\nChoose: ";
  int choose = 0;
  cin >> choose;
  switch (choose) {
  case 1: {
      char a[4][32];
      short res[4][32] = { 0 };
      cin.ignore(32, '\n');
      for (int i = 0; i < 4; i++) {
          cin.getline(a[i], 32);
      }
      for (int i = 0; i < 4; i++) {
          if (strlen(a[i]) < 32) {
              for (int c = strlen(a[i]); c < 32; c++) {
                  a[i][c] = ' ';
              }
              a[i][31] = '\0';
          }
      }
      for (int i = 0; i < 4; i++) {
          cout << a[i] << ";" << endl;
      }
      for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 32; j++) {
              // cout << bitset<16>(a[i][j]) << endl;
              // cout << bitset<16>(res[i][j]) << endl;
              res[i][j] |= j;
              // cout << bitset<16>(res[i][j]) << endl;
              res[i][j] <<= 11;
              // cout << bitset<16>(res[i][j]) << endl;
              res[i][j] |= i << 9;
              // cout << bitset<16>(res[i][j]) << endl;
              res[i][j] |= a[i][j] << 1;
              // cout << bitset<16>(res[i][j]) << endl;
              res[i][j] |= parityBit(res[i][j]);
              cout << "coded symbol '" << a[i][j] << "' in pos [" << i << "][" << j
                  << "]:" << endl;
              cout << bitset<16>(res[i][j]) << endl;
          }
      }
      ofstream resBinFile("/Users/admin/Documents/oop/lab2/lab2/out", ios::out | ios::binary);
      resBinFile.write((char*)&res, (4 * 32) * sizeof(short));
  };
  case 2: {
    short fromBinary[4][32];
    char result[4][32];
    std::ifstream input("/Users/admin/Documents/oop/lab2/lab2/out", ios::binary);
    input.read((char *)&fromBinary, 4 * 32 * sizeof(short));
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 32; j++) {
        cout << bitset<16>(fromBinary[i][j]) << endl;
        bool readParityBit = fromBinary[i][j] & 1;
        if (parityBit(fromBinary[i][j] != readParityBit)) {
          cout << "Parity bits not matched" << endl;
        }
        char letter = (fromBinary[i][j] >> 1) & 255;
        int readRyadok = (fromBinary[i][j] >> 9) & 3;
        if (readRyadok != i) {
          cout << "String position not matched" << endl;
        }
        int posSymbol = (fromBinary[i][j] >> 11) & 31;
        if (posSymbol != j) {
          cout << "Position symbol not matched" << endl;
        }
        cout << "Letter: " << letter << endl;
        result[i][j] = letter;
      }
      cout << endl;
    }
    cout << "Result:" << endl;
    for (int i = 0; i < 4; i++) {
      cout << result[i] << ";" << endl;
    }
  } break;
  default: {
    cout << "Invalid input\n";
    break;
  }
  }
}
