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
#include <sstream>

#include "utils.hpp"

using namespace std;

struct Register {
  string A, B, C, D, E, H, L, PC;
  bool S, Z, AC, P, CY;
  string toString() const;
};
class Interpreter {
private:
  map<string, string> Memory; //stores instruction
  string start;
  string pc;
  bool flag[8];
  string registers[7];
  string last_error = "";
public:
  Interpreter();
  Register getRegister();
  void set_address(string start );
  bool execute(const std::string &line);
  std::string get_error();
};

#endif // INTERPRETER_HPP_