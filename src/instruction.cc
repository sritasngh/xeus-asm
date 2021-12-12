/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    instruction.cc
 * @brief   contains implementation for all the 8085 instructions
 */

#include "xasm/instruction.hpp"

void ADD(string arg1, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {

  int length = arg1.length();
  if (length == 1) {

    if (validityRegisters(arg1) || validityRegisterPair(arg1)) {

      if (arg1 != "M") {

        /*Fetches index of register to access array string registers[]*/
        int registerID = registerNumber(arg1);
        /*Converting decimal value to string format and storing in accumulator*/
        registers[0] = hexAdd(registers[registerID], registers[0], flag, true);

      } else {

        /*Fetches data of HL pair*/
        string address = "";
        address = address + registers[5] + registers[6];
        if (address >= "0000" && address <= "FFFF") {

          /*Converting decimal value to string format and storing in
           * accumulator*/
          registers[0] = hexAdd(memory[address], registers[0], flag, true);
        } else {
          last_error = "Error: " + arg1 +
                       "Address out of bounds\nThe program will quit\n";
          return;
          /*error message of address out of bounds*/
        }
      }
    } else {
      last_error = "Error: " + arg1 +
                   "\nInvalid register details\nThe program will quit\n";
      return;
      /*error of invalid register details*/
    }
  } else {
    last_error =
        "Error: " + arg1 + "\nInvalid arguments\nThe program will quit\n";
    return;
    /*Error message of invalid arguments*/
  }
}

void ADI(string arg, string registers[], bool flag[], string &last_error) {

  int length = arg.length();
  if (length == 2) {

    if (validityData(arg)) {

      /*Performs immediate addition and stores in accumulator*/
      registers[0] = hexAdd(arg, registers[0], flag, true);
    } else {

      last_error =
          "Error: " + arg + "\nInvalid data content\nThe program will quit\n";
      return;
      /*Error message of invalid data content*/
    }
  } else {

    last_error =
        "Error: " + arg + "\nInvalid data size\nThe program will quit\n";
    return;
    /*Error message of invalid data size*/
  }
}

void DAD(string arg, string registers[], bool flag[], string &last_error) {

  int length = arg.length();
  if (length == 1) {

    if (validityRegisters(arg)) {

      int registerID = registerNumber(arg);
      if (registerID == 1 || registerID == 3 || registerID == 5) {

        string data16bit = "";
        string data16bitHL = "";
        string resultant = "";
        if (validityData(registers[registerID]) &&
            validityData(registers[registerID + 1]) &&
            validityData(registers[5]) && validityData(registers[6])) {

          data16bit = data16bit + registers[registerID] + registers[registerID];
          data16bitHL = data16bitHL + registers[5] + registers[6];
          int value16bit[4];
          int value16bitHL[4];
          int carry = 0;
          hexToDecimal(arg, value16bit);
          hexToDecimal(arg, value16bitHL);
          for (int i = 3; i >= 0; i--) {

            int value = value16bit[i] + value16bitHL[i] + carry;
            if (value >= 16)
              flag[0] = true;
            else
              flag[0] = false;
            carry = value / 16;
            value = value % 16;
            if (value >= 0 && value <= 9)
              resultant = (char)('0' + value) + resultant;
            else {
              switch (value) {

              case 10:
                resultant = "A" + resultant;
                break;
              case 11:
                resultant = "B" + resultant;
                break;
              case 12:
                resultant = "C" + resultant;
                break;
              case 13:
                resultant = "D" + resultant;
                break;
              case 14:
                resultant = "E" + resultant;
                break;
              case 15:
                resultant = "F" + resultant;
                break;
              }
            }
          }

          registers[5] = resultant[0] + resultant[1];
          registers[6] = resultant[2] + resultant[3];
        } else {
          last_error =
              "Error: " + arg +
              "\nInvalid data content in registet\nThe program will quit\n";
          return;
          /*Error:Invalid data content in registers*/
        }
      } else {
        last_error = "Error: " + arg +
                     "\nInvalid register pair\nThe program will quit\n";
        return;
        /*Error:Invaid register pair*/
      }
    } else {
      last_error = "Error: " + arg +
                   "\nInvalid register content\nThe program will quit\n";
      return;
      /*Error:Invalid register content*/
    }
  } else {
    last_error =
        "Error: " + arg + "\nInvalid arguments\nThe program will quit\n";
    return;
    /*Error:Invalid Input Argument*/
  }
}

void SUB(string arg1, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {

  int length = arg1.length();
  if (length == 1) {

    if (validityRegisters(arg1)) {

      if (arg1 != "M") {

        /*Fetches index of register to access array string registers[]*/
        int registerID = registerNumber(arg1);
        /*Converting decimal value to string format and storing in accumulator*/
        registers[0] = hexSub(registers[registerID], registers[0], flag, true);

      } else {

        /*Fetches data of HL pair*/
        string address = "";
        address = address + registers[5] + registers[6];
        if (address >= "0000" && address <= "FFFF") {

          /*Converting decimal value to string format and storing in
           * accumulator*/
          registers[0] = hexSub(memory[address], registers[0], flag, true);

        } else {
          last_error = "Error: " + arg1 +
                       "Address out of bounds\nThe program will quit\n";
          return;
          /*error message of address out of bounds*/
        }
      }
    } else {
      last_error = "Error: " + arg1 +
                   "\nInvalid register details\nThe program will quit\n";
      return;
      /*error of invalid register details*/
    }
  } else {
    last_error =
        "Error: " + arg1 + "\nInvalid arguments\nThe program will quit\n";
    return;
    /*Error message of invalid arguments*/
  }
}

void SUI(string arg, string registers[], bool flag[], string &last_error) {

  int length = arg.length();
  if (length == 2) {

    if (validityData(arg)) {

      /*Performs immediate subtraction and stores in accumulator*/
      registers[0] = hexSub(arg, registers[0], flag, true);
    } else {

      last_error = "Error: " + arg + "\n This is an invalid data\n";
      return;
      /*Error message of invalid data content*/
    }
  } else {

    last_error =
        "Error: " + arg + "\nThis is an invalid data\nThe program will quit\n";
    return;
    /*Error message of invalid data size*/
  }
}

void MOV(string argument1, string argument2, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {
  int l1 = argument1.length();
  int l2 = argument2.length();
  if (l1 == 1 && l2 == 1) {
    if (argument1 == "M" && argument2 != "M" && validityRegisters(argument2)) {
      string address = registers[5] + registers[6];
      memory[address] = registers[registerNumber(argument2)];
    } else if (argument1 != "M" && argument2 == "M" &&
               validityRegisters(argument1)) {
      string address = registers[5] + registers[6];
      registers[registerNumber(argument1)] = memory[address];
    } else if (argument1 != "M" && argument2 != "M" &&
               validityRegisters(argument2) && validityRegisters(argument1)) {
      registers[registerNumber(argument1)] =
          registers[registerNumber(argument2)];
    } else {
      last_error = "Error: Invalid content\nThe program will quit\n";
      return;
    }
  }
}

void MVI(string arg1, string arg2, string registers[], bool flags[],
         map<string, string> &memory, string &last_error) {
  int l1 = arg1.length();
  int l2 = arg2.length();
  if (l1 == 1 && l2 == 2) {
    if (arg1 == "M") {
      string address = registers[5] + registers[6];
      if (validityData(arg2))
        memory[address] = arg2;
      else {
        last_error = "Error: Invalid content\nThe program will quit\n";
        return;
      }
    } else if (validityRegisters(arg1) && validityData(arg2)) {
      registers[registerNumber(arg1)] = arg2;
    } else {
      last_error = "Error: Invalid content\nThe program will quit\n";
      return;
    }
  } else {
    last_error = "Error: Invalid content\nThe program will quit\n";
    return;
  }
}

void INR(string arg, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {

  int length = arg.length();
  if (length == 1) {

    if (validityRegisters(arg)) {

      if (arg != "M") {

        /*Performs INR on a register*/
        int registerID = registerNumber(arg);
        registers[registerID] =
            hexAdd(registers[registerID], "01", flag, false);
      } else {
        /*Performs DCR on HL pair*/
        string address = "";
        address = address + registers[5] + registers[6];
        if (validityAddress(address)) {

          memory[address] = hexAdd(memory[address], "01", flag, false);
        } else {

          last_error = "Error: " + arg +
                       "Address out of bounds\nThe program will quit\n";
          return;
        }
      }
    } else {

      last_error = "Error: " + arg +
                   "\nInvalid register details\nThe program will quit\n";
      return;
      /*Error:Invalid Register*/
    }
  } else {
    last_error =
        "Error: " + arg + "\nInvalid argument type\nThe program will quit\n";
    return;
    /*Error: Invalid argument type*/
  }
}

void INX(string arg, string registers[], bool flag[], string &last_error) {

  int length = arg.length();
  if (length == 1) {

    if (validityRegisters(arg)) {

      int registerID = registerNumber(arg);
      if (registerID == 1 || registerID == 3 || registerID == 5) {

        string data16bit = "";
        string temporary = "";
        string s1 = "";
        string s2 = "";
        if (validityData(registers[registerID]) == true &&
            validityData(registers[registerID + 1]) == true) {

          data16bit =
              data16bit + registers[registerID] + registers[registerID + 1];
          // temporary =  hexAdd16bit(data16bit,"0001",flag,false);
          temporary = increaseAddress(data16bit);
          s1 = s1 + temporary[0] + temporary[1];
          s2 = s2 + temporary[2] + temporary[3];
          registers[registerID] = s1;
          registers[registerID + 1] = s2;
        } else {

          last_error =
              "Error: " + arg +
              "\nInvalid data content in registers\nThe program will quit\n";
          return;
          /*Error:Invalid data content in registers*/
        }
      } else {
        last_error = "Error: " + arg +
                     "\nInvalid register pair\nThe program will quit\n";
        return;
        /*Error:Invaid register pair*/
      }
    } else {
      last_error = "Error: " + arg +
                   "\nInvalid register content\nThe program will quit\n";
      return;
      /*Error:Invalid register content*/
    }
  } else {
    last_error =
        "Error: " + arg + "\nInvalid input arguments\nThe program will quit\n";
    return;
    /*Error:Invalid Input Argument*/
  }
}

void DCR(string arg, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {

  int length = arg.length();
  if (length == 1) {

    if (validityRegisters(arg)) {

      if (arg != "M") {

        /*Performs INR on a register*/
        int registerID = registerNumber(arg);
        registers[registerID] =
            hexSub(registers[registerID], "01", flag, false);
      } else {
        /*Performs DCR on HL pair*/
        string address = "";
        address = address + registers[5] + registers[6];
        if (validityAddress(address)) {

          memory[address] = hexSub(memory[address], "01", flag, false);
        } else {
          last_error = "Error: " + arg +
                       "\nInvalid register details\nThe program will quit\n";
          return;
          /*Error:Address out of bounds*/
        }
      }
    } else {
      last_error = "Error: " + arg +
                   "\nInvalid register details\nThe program will quit\n";
      return;
      /*Error:Invalid Register*/
    }
  } else {
    last_error =
        "Error: " + arg + "\nInvalid argument type\nThe program will quit\n";
    return;
    /*Error: Invalid argument type*/
  }
}

void DCX(string arg, string registers[], bool flag[], string &last_error) {

  int length = arg.length();
  if (length == 1) {

    if (validityRegisters(arg)) {

      int registerID = registerNumber(arg);
      if (registerID == 1 || registerID == 3 || registerID == 5) {

        string data16bit = "";
        string temporary = "";
        string s1 = "";
        string s2 = "";
        if (validityData(registers[registerID]) == true &&
            validityData(registers[registerID + 1]) == true) {

          data16bit =
              data16bit + registers[registerID] + registers[registerID + 1];
          temporary = hexSub16bit(data16bit, "0001", flag, false);
          s1 = s1 + temporary[0] + temporary[1];
          s2 = s2 + temporary[2] + temporary[3];
          registers[registerID] = s1;
          registers[registerID + 1] = s2;
        } else {
          last_error = "Error: " + arg +
                       "\nInvalid data content\nThe program will quit\n";
          return;
          /*Error:Invalid data content in registers*/
        }
      } else {
        last_error = "Error: " + arg +
                     "\nInvalid register pair\nThe program will quit\n";
        return;
        /*Error:Invaid register pair*/
      }
    } else {
      last_error = "Error: " + arg +
                   "\nInvalid register content\nThe program will quit\n";
      return;
      /*Error:Invalid register content*/
    }
  } else {
    last_error =
        "Error: " + arg + "\nInvalid input arguments\nThe program will quit\n";
    return;
    /*Error:Invalid Input Argument*/
  }
}

void CMP(string arg1, string registers[], bool flag[],
         map<string, string> &memory, string &last_error) {
  int l1 = arg1.length();
  if (l1 == 1) {
    if (arg1 == "M") {
      string address = registers[5] + registers[6];
      if (registers[0] < memory[address]) {
        flag[0] = true;
      } else if (registers[0] == memory[address]) {
        flag[6] = true;
        // cout<<"zero set\n";
      } else {
        // cout<<"both reset\n";
        flag[0] = false;
        flag[6] = false;
      }
    } else if (validityRegisters(arg1)) {
      int index = registerNumber(arg1);
      if (registers[0] < registers[index]) {
        // cout<<"carry set\n";
        flag[0] = true;
      } else if (registers[0] == registers[index]) {
        // cout<<"zero set\n";
        flag[6] = true;
      } else {
        // cout<<"both reset\n";
        flag[0] = false;
        flag[6] = false;
      }
    } else {

      last_error =
          "Error: " + arg1 + "\nInvalid registers\nThe program will quit\n";
      return;
    }
  } else {

    last_error =
        "Error: " + arg1 + "\nInvalid argument\nThe program will quit\n";
    return;
  }
}
