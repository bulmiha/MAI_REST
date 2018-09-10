//
// Created by Михаил Булгаков on 10/09/2018.
//
#pragma once

#ifndef MAI_WEATERSERVERFORECAST_H
#define MAI_WEATERSERVERFORECAST_H

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_client.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;



class WeaterServerForecast {
public:
    WeaterServerForecast() {}

    WeaterServerForecast(utility::string_t url);

    pplx::task<void> open() { return w_listener.open(); }

    pplx::task<void> close() { return w_listener.close(); }

private:
    http_listener w_listener;

    void handle_get(http_request msg);

    void handle_put(http_request msg);

    void handle_post(http_request msg);

    void handle_delete(http_request msg);

    json::value answer_f;

};


#endif //MAI_WEATERSERVERFORECAST_H
