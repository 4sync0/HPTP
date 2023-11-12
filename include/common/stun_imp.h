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



    
    void handler_t(const system::error_code& ec, std::size_t bytes_transferred) {
        if (ec)
            std::cerr << "unsuccessful operation    " << ec.message() << "\n";
        else
            std::cout << "successful operation\n";
    }

    void handler_r(const system::error_code& ec, std::size_t bytes_transferred) {
        if (ec)
            std::cerr << "unsuccessful operation    " << ec.message() << "\n";
        else
            std::cout << "successful operation\n";
    }

    void send(std::array<uint8_t, 256> message, int size) {
        asio::ip::udp::socket socket_t(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));

        asio::ip::udp::resolver resolver(io_context);
        asio::ip::udp::resolver::results_type endpoint = resolver.resolve(asio::ip::udp::v4(), server, std::to_string(port));
        asio::ip::udp::endpoint target_endpoint = *endpoint.begin();

        socket_t.async_send_to(asio::buffer(message, size), target_endpoint, handler_t);
        io_context.run();

    }

    void receive() {
        asio::ip::udp::socket socket_r(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port_def));
        std::vector<uint8_t> data;
        
        asio::ip::udp::endpoint sender_endpoint;

        socket_r.async_receive_from(asio::buffer(data, 50), sender_endpoint, handler_r);
        io_context.run();
    }
}