// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <Poco/Net/HTTPClientSession.h>


namespace httpPing {
    class preNpost {
        public:
            preNpost(const Poco::URI& uri) : uri_(uri), session_(uri.getHost(), uri.getPort()) {}

            void transmit(bool pre) {}

            void receive() {}

        
        private:
            Poco::URI uri_;
            Poco::Net::HTTPClientSession session_;
                
    };

};