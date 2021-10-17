/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    main.cc
 * @brief   Driver Code
 */

#include <memory>

#include "xasm/xasm_interpreter.hpp"
#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"
#include "xeus/xserver_zmq.hpp"

int main(int argc, char *argv[]) {
  // Load configuration file
  std::string file_name = (argc == 1) ? "connection.json" : argv[2];
  xeus::xconfiguration config = xeus::load_configuration(file_name);

  auto context = xeus::make_context<zmq::context_t>();
  // Create interpreter instance
  using interpreter_ptr = std::unique_ptr<xasm::xasm_interpreter>;
  interpreter_ptr interpreter = std::make_unique<xasm::xasm_interpreter>();

  // Create kernel instance and start it
  xeus::xkernel kernel(config, xeus::get_user_name(), std::move(context), std::move(interpreter), xeus::make_xserver_zmq);
  kernel.start();

  return 0;
}