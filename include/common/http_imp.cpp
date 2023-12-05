// SPDX-License-Identifier: BSL-1.0

#include "include/common/http_imp.h"

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/NetException.h>

#include <iostream>
#include <string>

using namespace httpPing;
using std::string;


class preNpost {
    public:
        preNpost(const Poco::URI& uri) : uri_(uri), session_(uri.getHost(), uri.getPort()) {
            session_.setKeepAlive(true);
        }
        void transmit(bool pre) {
            using namespace Poco::Net;
            HTTPRequest request(HTTPRequest::HTTP_HEAD, "/", HTTPRequest::HTTP_1_1);
            if (pre) { request.add("User-Agent", "HPCpre");  }
            else if (!pre) { request.add("User-Agent", "HPCpost"); }
            session_.sendRequest(request);
            session_.reset();
        }
        void receive() {
            Poco::Net::HTTPResponse response;
            try { std::istream& responseObtained = session_.receiveResponse(response); }
            catch (Poco::Net::InvalidSocketException& e) {}
            std::cout << response.getStatus() <<"\n";
        }
    
    private:
        Poco::URI uri_;
        Poco::Net::HTTPClientSession session_;
            
};