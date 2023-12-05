// SPDX-License-Identifier: BSL-1.0

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <iostream>

#pragma once

using  std::string;
using std::vector;
using namespace boost;

namespace udp {
    const string server = "stun.l.google.com";
    const int port = 19302;
    const int port_def = 3478;

    asio::io_context io_context;

    asio::ip::udp::socket socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));

    void handler(const system::error_code& ec, std::size_t bytes_transferred) {
        if (ec)
            std::cerr << "unsuccessful operation    " << ec.message() << "\n";
        else
            std::cout << "successful operation\n";
    }

    void send(std::array<uint8_t, 256> message, int size) {

        asio::ip::udp::resolver resolver(io_context);
        asio::ip::udp::resolver::results_type unrslv_endpoint = resolver.resolve(asio::ip::udp::v4(), server, std::to_string(port));
        asio::ip::udp::endpoint endpoint = *unrslv_endpoint.begin();

        socket.async_send_to(asio::buffer(message, size), endpoint, handler);
        
        socket.async_receive_from(asio::buffer(message, 256), endpoint, handler);
        io_context.run();

    }

}