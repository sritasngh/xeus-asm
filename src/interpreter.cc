/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    interpreter.cc
 * @brief   contains implementation for interpreter function
 */

#include "xasm/interpreter.hpp"

ostream &operator<<(ostream &out, const Register &r) {
  out << "Registers\nA\t" << r.A << "\nBC\t" << r.B << "\t" << r.C << "\nDE\t"
      << r.D << "\t" << r.E << "\nHL\t" << r.H << "\t" << r.L << "\nPC\t"
      << r.PC << "\n";
  out << "Flags\nS\tZ\tAC\tP\tAC\n"
      << r.S << "\t" << r.Z << "\t" << r.AC << "\t" << r.P << "\t" << r.C
      << "\n";
  return out;
}

Interpreter::Interpreter() {

  for (int i = 0; i < 7; i++)
    registers[i] = "NULL";
  for (int i = 0; i < 8; i++)
    flag[i] = false;

  start = "";
  pc = "";
}

Register Interpreter::getRegister() {
  Register resister = {registers[0], registers[1], registers[2], registers[3],
                       registers[4], registers[5], registers[6], pc,
                       flag[7],      flag[6],      flag[4],      flag[2],
                       flag[0]};
  return resister;
}

void Interpreter::input() {
  cout << "\nEnter the starting address:\n";
  cin >> start;
  pc = start;
  if (!validityAddress(start)) {

    cout << "The memory you entered either does not exist or is reserved by "
            "the system\nPlease re-enter the program from a new memory "
            "location\nThe program will quit\n";
    exit(1);
  }
  sequence.push_back(start);
}

void Interpreter::multiLine() {
  cin.ignore();
  cout << "\nEnter the code:\n";
  while (1) {
    cout << ">> " << pc << " ";
    string line;
    getline(cin, line);
    Memory[pc] = line;
    pc = updatedAddress(pc, Memory);
    if (line == "HLT") {
      break;
      sequence.push_back(pc);
    }
  }
  execution(start, Memory, sequence, flag, registers);
}

void Interpreter::execution(string pc, map<string, string> &Memory,
                            vector<string> &sequence, bool flag[],
                            string registers[]) {
  int size = sequence.size();
  for (int i = 0; i < size; i++) {
    pc = executionCode(Memory[sequence[i]], registers, flag, Memory, pc);
  }
}
