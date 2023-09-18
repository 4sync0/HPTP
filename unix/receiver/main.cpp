#include <Poco/URI.h>
#include <Poco/Net/IPAddress.h>
#include <string>

#include "../include/common/http_imp.h"
#include "../include/common/stun_imp.h"

using std::string;

Poco::URI uri("http://localhost:631");

int main() {
    udp::receive();

    return 0;
}