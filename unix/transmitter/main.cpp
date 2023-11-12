#include <Poco/URI.h>
#include <Poco/Net/IPAddress.h>
#include <string>

#include "../include/common/http_imp.h"
#include "../include/common/stun_imp.h"

using std::string;

Poco::URI uri("http://localhost:631");

int main() {
    httpPing::preNpost transmitter(uri);
    transmitter.transmit(true);
    std::array<uint8_t, 256> stun_msg;
    stun_msg[0] = 0x00;
    stun_msg[1] = 0x01;
    udp::send(stun_msg, 256);

    udp::receive();
    return 0;
}