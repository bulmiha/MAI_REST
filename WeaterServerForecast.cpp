//
// Created by Михаил Булгаков on 10/09/2018.
//

#include "WeaterServerForecast.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;



WeaterServerForecast::WeaterServerForecast(utility::string_t url) : w_listener(url) {
    w_listener.support(methods::GET, std::bind(&WeaterServerForecast::handle_get,this,std::placeholders::_1));
    answer_f["unit"]=json::value::string(U("celsius"));

    string_t api_addr;

    if(const char* env_p = std::getenv("API_ADDR")){
        api_addr=U(env_p);
    }
    else{
        api_addr=U("http://api.weatherbit.io/");
    }
}

void WeaterServerForecast::handle_get(http_request msg) {
    string_t key=U("city");
    auto http_get_vars = uri::split_query(msg.request_uri().query());
    if(http_get_vars[key].empty()){
        msg.reply(status_codes::BadRequest);
        return;
    }

    answer_f[key]=json::value::string(http_get_vars[key]);
    answer_f["temperature"]=json::value::number(25);

    msg.reply(status_codes::OK,answer_f);
}