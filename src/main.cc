/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    main.cc
 * @brief   Driver Code
 */

#include "xasm/interpreter.hpp"

int main(int argc, char *argv[]) {
  Interpreter instance;
  instance.input();
  instance.multiLine();
  cout<<instance.getRegister();
}