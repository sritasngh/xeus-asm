/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    instruction.cc
 * @brief   contains implementation for all the 8085 instructions
 */

#include "xasm/instruction.hpp"

void ADD(string arg1, string registers[], bool flag[],
         map<string, string> &memory) {

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

          cout << "Error: " << arg1 << "\n";
          cout << "Address out of bounds\nThe program will quit\n";
          exit(0);
          /*error message of address out of bounds*/
        }
      }
    } else {

      cout << "Error: " << arg1
           << "\nInvalid register details\nThe program will quit\n";
      exit(0);
      /*error of invalid register details*/
    }
  } else {

    cout << "Error: " << arg1 << "\nInvalid arguments\nThe program will quit\n";
    exit(0);
    /*Error message of invalid arguments*/
  }
}

void MOV(string argument1, string argument2, string registers[], bool flag[],
         map<string, string> &memory) {
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
      cout << "Error: "
           << "Invalid content\nThe program will quit\n";
      exit(0);
    }
  }
}

void MVI (string arg1,string arg2,string registers[],bool flags[],map<string,string> &memory){
	int l1=arg1.length();
	int l2=arg2.length();
	if(l1==1&&l2==2){
        	if(arg1=="M"){
            		string address=registers[5]+registers[6];
            		if(validityData(arg2))
                		memory[address]=arg2;
            		else{
				cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				exit(0);
				}
        	}
		else if(validityRegisters(arg1)&&validityData(arg2)){	
			registers[registerNumber(arg1)] = arg2;
		}
		else{
			cout<<"Error: "<<"Invalid content\nThe program will quit\n";
			exit(0);
		}
	}
	else{
		cout<<"Error: "<<"Invalid content\nThe program will quit\n";
		exit(0);
	}
}