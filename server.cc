#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "json.hpp"
using nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server& s, websocketpp::connection_hdl handle, server::message_ptr msg) {
  auto j = json::parse(msg->get_payload());

  std::cout << j.dump(4) << std::endl;

  j["ack"] = true;

  std::string response = j.dump();

  s.send(handle, response, msg->get_opcode());
}

int main() {
  server print_server;

  print_server.set_message_handler(
    [&](websocketpp::connection_hdl handle, server::message_ptr msg) {
      on_message(print_server, handle, msg);
    });
  print_server.set_access_channels(websocketpp::log::alevel::all);
  print_server.set_error_channels(websocketpp::log::elevel::all);

  print_server.init_asio();
  print_server.listen(9002);
  print_server.start_accept();

  print_server.run();
}
