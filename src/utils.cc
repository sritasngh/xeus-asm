/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    utils.cc
 * @brief   contains implementation for all the helper funtions
 */

#include "xasm/utils.hpp"

string nextAddress(string str, int n) {

  int array[4];
  string result = "";
  hexToDecimal(str, array);
  int i = 3;
  array[i] += n;
  while (array[i] >= 16) {
    array[i] = array[i] % 16;
    array[i - 1]++;
    i--;
  }
  for (int i = 0; i < 4; i++) {

    if (array[i] >= 0 && array[i] <= 9)
      result = result + char('0' + array[i]);
    else
      result = result + char('A' + (array[i] - 10));
  }
  return result;
}

string executionCode(string command, string Registers[], bool flag[],
                     map<string, string> &memory, string programCounter, string &last_error) {
  vector<string> commandPart;
  // string command = memory[programCounter];
  string inst;
  int commandSize;
  const char *partition = command.c_str();
  char *temporary = (char *)partition;
  const char *delimiter = " ,";
  char *part = strtok(temporary, delimiter);

  while (part != NULL) {
    inst = part;
    commandPart.push_back(inst);
    part = strtok(NULL, delimiter);
  }
  // instruction1[commandPart[0]](commandPart[1], Registers, flag, memory);
  // instruction2[commandPart[0]](commandPart[1], commandPart[2], Registers,
  // flag,
  //                              memory);
  if (commandPart[0] == "MOV") {
    MOV(commandPart[1], commandPart[2], Registers, flag, memory, last_error);
    commandSize = operationSize(commandPart[0]);
    return nextAddress(programCounter, commandSize);
  } else if (commandPart[0] == "ADD") {
    ADD(commandPart[1], Registers, flag, memory, last_error);
    commandSize = operationSize(commandPart[0]);
    return nextAddress(programCounter, commandSize);
  } else if (commandPart[0] == "MVI") {
    MVI(commandPart[1], commandPart[2], Registers, flag, memory, last_error);
    commandSize = operationSize(commandPart[0]);
    return nextAddress(programCounter, commandSize);
  }
  return "";
}

bool validityAddress(string data) {
  bool flag;
  int l = data.length();
  for (int i = 0; i < l; i++) {
    if ((data[i] >= '0' && data[i] <= '9') ||
        (data[i] >= 'A' && data[i] <= 'F'))
      flag = true;
    else {
      flag = false;
      break;
    }
  }
  return flag;
}

int operationSize(string str) {
  string one[] = {"HLT", "MOV", "ADD"};
  string two[] = {"MVI"};
  string three[] = {"SET"};
  const char *ch = str.c_str();
  char *var = (char *)ch;
  const char *delimiter = " ,";
  char *pch = strtok(var, delimiter);
  string query = pch;

  int length = sizeof(one) / sizeof(one[0]);
  for (int i = 0; i < length; i++) {

    if (one[i] == query)
      return 1;
  }
  length = sizeof(two) / sizeof(two[0]);
  for (int i = 0; i < length; i++) {

    if (two[i] == query)
      return 2;
  }
  length = sizeof(three) / sizeof(three[0]);
  for (int i = 0; i < length; i++) {

    if (three[i] == query)
      return 3;
  }
  return 0;
}

void hexToDecimal(string pc, int arr[]) {
  int l = pc.length();
  int p = 0;
  for (int i = 0; i < l; i++) {
    if (pc[i] >= '0' && pc[i] <= '9')
      arr[i] = pc[i] - '0';
    else
      arr[i] = 10 + (pc[i] - 'A');
  }
}

string updatedAddress(string PC, map<string, string> &Memory) {

  string command = Memory[PC];
  string opcode;
  if (command == "HLT" || command == "XCHG" || command == "CMA") {
    opcode = command;
  } else {
    const char *partition = command.c_str();
    char *temporary = (char *)partition;
    const char *delimiter = " ,";
    char *part = strtok(temporary, delimiter);
    opcode = part;
  }
  int n = operationSize(opcode);
  string result;
  for (int j = 1; j <= n; j++) {
    int array[4] = {-1, -1, -1, -1};
    result = "";
    hexToDecimal(PC, array);
    int i = 3;
    array[i] += 1;
    while (array[i] >= 16) {
      array[i] = array[i] % 16;
      array[i - 1]++;
      i--;
    }
    for (int i = 0; i < 4; i++) {
      if (array[i] >= 0 && array[i] <= 9)
        result = result + char('0' + array[i]);
      else
        result = result + char('A' + (array[i] - 10));
    }
    Memory[result] = Memory[PC];
    PC = result;
  }
  return PC;
}

bool validityRegisters(string reg) {
  return string("ABCDEHL").find(reg) != string::npos;
}

bool validityRegisterPair(string reg) {
  return string("BDHM").find(reg) != string::npos;
}

int registerNumber(string str) {
  auto index = string("ABCDEHL").find(str);
  return index != string::npos ? index : 0;
}

string hexAdd(string arg1, string arg2, bool flag[], bool carry) {

  string resultant = "";
  int variable;
  int value1[5] = {0, 0};
  int value2[5] = {0, 0};
  int tempAnswer[2];
  hexToDecimal(arg1, value1);
  hexToDecimal(arg2, value2);
  tempAnswer[1] = value1[1] + value2[1];
  if (tempAnswer[1] >= 16) {
    tempAnswer[1] = tempAnswer[1] % 16;
    value1[0]++;
    flag[4] = true;
  }
  tempAnswer[0] = value1[0] + value2[0];
  if (tempAnswer[0] >= 16) {
    tempAnswer[0] = tempAnswer[0] % 16;
    if (carry == true)
      flag[0] = true;
  }

  variable = tempAnswer[0] * 16 + tempAnswer[1];
  bitset<8> dataInBinary(variable);
  /*Setting parity flag*/
  int parity = dataInBinary.count();
  if (parity % 2 == 0 && parity != 0)
    flag[2] = true;
  else
    flag[2] = false;
  /*Setting sign flag*/
  flag[7] = dataInBinary[7];
  /*Setting zero flag*/
  if (parity == 0)
    flag[6] = true;

  /*Convert decimal data to hexadecimal and store in accumulator*/
  for (int i = 1; i >= 0; --i) {

    if (tempAnswer[i] >= 0 && tempAnswer[i] <= 9)
      resultant = char('0' + tempAnswer[i]) + resultant;
    else if (tempAnswer[i] >= 10 && tempAnswer[i] <= 15)
      resultant = (char)('A' + (tempAnswer[i] - 10)) + resultant;
  }

  return resultant;
}

bool isHexadecimal(char a){

	if((a>='0' && a<='9') || (a>='A' && a<='F'))
		return true;
	else
		return false;
}

bool validityData(string a){

	int l=a.length();
	if(l==2 && isHexadecimal(a[0]) && isHexadecimal(a[1]))
		return true;
	else 
		return false;
}
