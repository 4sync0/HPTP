// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <boost/asio.hpp>
#include <vector>


using std::vector;
using namespace boost;

namespace udp {

    void handler(const system::error_code& ec, std::size_t bytes_transferred) {}

    void send(std::array<uint8_t, 256> message, int size) {}

}