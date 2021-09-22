/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    interpreter.hpp
 * @brief   header file interperter class of 8085 microprocessor
 */

#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.hpp"

using namespace std;

struct Register {
  string A, B, C, D, E, H, L, PC;
  bool S, Z, AC, P, CA;
  friend ostream &operator<<(ostream &out, const Register &r);
};
class Interpreter {
private:
  map<string, string> Memory; //stores instruction
  vector<string> sequence; //stores pc pointing to an instruction
  string start;
  string pc;
  bool flag[8];
  string registers[7];

public:
  Interpreter();
  Register getRegister();
  void input();
  void multiLine();
  void execution(string pc, map<string, string> &Memory,
                 vector<string> &sequence, bool flag[], string registers[]);
};

#endif // INTERPRETER_HPP_