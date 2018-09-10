//
// Created by Михаил Булгаков on 10/09/2018.
//

#include "WeaterServerForecast.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;
using namespace client;


WeaterServerForecast::WeaterServerForecast(utility::string_t url) : w_listener(url) {
    w_listener.support(methods::GET, std::bind(&WeaterServerForecast::handle_get, this, std::placeholders::_1));
    answer_f["unit"] = json::value::string(U("celsius"));

    if (const char *env_p = std::getenv("API_ADDR")) {
        api_addr = U(env_p);
    } else {
        api_addr = U("http://api.weatherbit.io/");
    }
    if (const char *env_p = std::getenv("API_KEY")) {
        api_key = U(env_p);
    } else {
        ucout << "Please provide api key through env" << endl;
        api_key = U("0");
    }
    client = std::unique_ptr<http::client::http_client>(new http_client(api_addr));
}

void WeaterServerForecast::handle_get(http_request msg) {
    string_t key = U("city");
    auto http_get_vars = uri::split_query(msg.request_uri().query());
    if (http_get_vars[key].empty()) {
        msg.reply(status_codes::BadRequest);
        return;
    }

    uri_builder builder(U("/v2.0/forecast/daily"));
    builder.append_query(U("key"), api_key);
    builder.append_query(U("city"), U(http_get_vars[key]));

    http_response response = client->request(methods::GET, builder.to_string()).get();

    if (response.status_code() != status_codes::OK) {
        msg.reply(status_codes::BadRequest);
        return;
    }

    json::value v1 = response.extract_json().get();

    uint8_t c = 0;

    for (uint8_t i = 0; i < 16; i++) {
        if (v1["data"][i]["datetime"].as_string() == http_get_vars["dt"]) {
            c = i;
            break;
        } else if (i == 15) {
            msg.reply(status_codes::BadRequest);
            return;
        }
    }

    answer_f[key] = json::value::string(http_get_vars[key]);
    answer_f["temperature"] = v1["data"][c]["temp"];

    msg.reply(status_codes::OK, answer_f);
}
