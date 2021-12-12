/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    utils.hpp
 * @brief   header file to contain signature of all the helper functions
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <bitset>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "instruction.hpp"

using namespace std;

bool validityAddress(string data);
int operationSize(string str);
void hexToDecimal(string pc, int arr[]);
string updatedAddress(string PC, map<string, string> &Memory);
string nextAddress(string str, int n);
string executionCode(string command, string Registers[], bool flag[],
                     map<string, string> &memory, string programCounter, string &);
bool validityRegisters(string reg);
bool validityRegisterPair(string reg);
int registerNumber(string str);
string hexAdd(string arg1, string arg2, bool flag[], bool carry);
string hexSub(string arg1, string arg2, bool flag[], bool carry);

// map<string, function<void(string, string[], bool[], map<string, string> &)>>
// instruction1{{"add", ADD}};

// map<string, function<void(string, string, string[], bool[], map<string, string> &)>>
// instruction2{{"mov", MOV}};

bool isHexadecimal(char a);
bool validityData(string a);
string increaseAddress(string a);
string hexSub16bit(string arg1,string arg2,bool flag[],bool carry);
string complement(string a);
#endif // UTILS_HPP_