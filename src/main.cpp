//******************************************************************************
// File name:   main.cpp
// Author:      Dawson Hose'
// Date:        09/16/2024 (Replace xx/xx/xxxx with month/day/year)
// Class:       CS200-01 (Replace xx with your section number)
// Assignment:  Base Converter
// Purpose:     Change an input string into either decimal, binary or hexidecimal
// Hours:       0.25
//******************************************************************************

#include <iostream>
#include <math.h>

using namespace std;

int hexCharToInt (char hexDigit);
char getBase (const string& strNumber);
string getNumber (const string& prompt);
void printTitle (const string& myTitle);
string binaryToDecimal (const string& strNumber);
string decimalToBinary (const string& strNumber);
string decimalToHex (const string& strNumber);
string hexToDecimal (const string& strNumber);
string hexToBinary (const string& strNumber);
string binaryToHex (const string& strNumber);

int main () {
  const char DECIMAL = 'D', BINARY = 'B', HEX = 'H';
  const string DECIMAL_TITLE = "The decimal conversion is: ", 
               BINARY_TITLE = "The binary conversion is: ", 
               HEX_TITLE = "The hexadecimal conversion is: ";
  string input;

  do {
    input = getNumber("Enter your string to convert (q to quit): ");
    switch (getBase(input)){
      case DECIMAL:
        printTitle(BINARY_TITLE);
        cout << decimalToBinary(input) << endl;
        printTitle(HEX_TITLE);
        cout << decimalToHex(input) << endl;
        break;
      case BINARY:
        printTitle(DECIMAL_TITLE);
        cout << binaryToDecimal(input) << endl;
        printTitle(HEX_TITLE);
        cout << binaryToHex(input) << endl;
        break;
      case HEX:
        printTitle(DECIMAL_TITLE);
        cout << hexToDecimal(input) << endl;
        printTitle(BINARY_TITLE);
        cout << hexToBinary(input) << endl;
        break;
    }
  } while (input != "q");
  
  return EXIT_SUCCESS;
}

int hexCharToInt (char hexDigit) {
  int integer = static_cast<int>(hexDigit);

  if (integer >= 48 && integer <= 57){
    integer = integer % 48;
  } else {
    integer = 10 + (integer % 65);
  }
  return integer;
}

char getBase (const string& strNumber){
  char baseType;

  
  if (strNumber[0] == 'q'){
    baseType = 'Q';
  } else if (strNumber.length() == 1){
    baseType = 'D';
  } else if (strNumber[0] != '0'){
    baseType = 'D';
  } else {
    if (strNumber[1] == 'x'){
      baseType = 'H';
    } else {
      baseType = 'B';
    }
  } 

  return baseType;
}

string getNumber (const string& prompt){
  string input;

  cout << prompt;
  cin >> input;

  return input;
}

void printTitle (const string& myTitle){
  cout << myTitle;
}

string binaryToDecimal (const string& strNumber){
  const char ON = '1';
  int decimal = 0, length = strNumber.length();

  for (int i = length; i > 1; i--){
    if (strNumber[i] == ON){
      decimal += pow(2 ,length - i);
    }
  }

  return to_string(decimal);
}

string decimalToBinary (const string& strNumber){
  int decimalValue = stoi(strNumber), places = 0;
  string binary = "0b";


  while (pow(2, places) <= decimalValue) {
      places++;
  }

  for (int i = places - 1; i >= 0; i--){
    if (decimalValue - pow(2, i) >= 0){
      binary.append("1");
      decimalValue -= pow(2,i);
    } else {
      binary.append("0");
    }
  }

  return binary;
}

string decimalToHex (const string& strNumber){
  const int DIVISOR = 16;
  int decimalValue = stoi(strNumber), remainder = 0, count = 0;
  char ch = '\0';
  string hex = "0x";

  do {
    remainder = decimalValue % DIVISOR;
    if (remainder < 10 && count != 0){
      hex.append(to_string(remainder));
    } else if (remainder >= 10){
      switch (remainder){
        case 10:
          ch = 'A';
          break;
        case 11:
          ch = 'B';
          break;
        case 12:
          ch = 'C';
          break;
        case 13:
          ch = 'D';
          break;
        case 14:
          ch = 'E';
          break;
        case 15:
          ch = 'F';
          break;
      }
      hex = hex + ch;
    }
    decimalValue /= DIVISOR;
    count++;
  } while(decimalValue != 0 && remainder != 16);

  return hex;
}

string hexToDecimal (const string& strNumber){
  int hexValue = 0, hexCharValue = 0;

  for (int i = 0; i < strNumber.length(); i++){
    hexCharValue += hexCharToInt(strNumber[i]);
    hexValue += hexCharValue * pow(16, strNumber.length() - (1 + i));
  }

  return to_string(hexValue);
}

string hexToBinary (const string& strNumber){
  return decimalToBinary((hexToDecimal(strNumber)));
}

string binaryToHex (const string& strNumber){
  return decimalToHex(binaryToDecimal(strNumber));
}