//
// Created by Михаил Булгаков on 10/09/2018.
//
#pragma once
#ifndef MAI_WEATERSERVER_H
#define MAI_WEATERSERVER_H

//#include <cpprest/http_client_c.h>
#include <cpprest/filestream.h>
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace http::client;



class WeaterServer {

public:
    WeaterServer() {}

    WeaterServer(utility::string_t url);

    pplx::task<void> open() { return w_listener.open(); }

    pplx::task<void> close() { return w_listener.close(); }

private:
    http_listener w_listener;

    void handle_get(http_request msg);

    void handle_put(http_request msg);

    void handle_post(http_request msg);

    void handle_delete(http_request msg);

    json::value answer_c;
    std::unique_ptr<http::client::http_client> client_c;
    string_t api_key;
    string_t api_addr;

};


#endif //MAI_WEATERSERVER_H
