//
// Created by Михаил Булгаков on 10/09/2018.
//

#include "WeaterServer.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

json::value answer_c;

WeaterServer::WeaterServer(utility::string_t url) : w_listener(url) {
    w_listener.support(methods::GET, std::bind(&WeaterServer::handle_get,this,std::placeholders::_1));
    answer_c["unit"]=json::value::string(U("celsius"));
}

void WeaterServer::handle_get(http_request msg) {
//    ucout<< msg.to_string() << endl;
    string_t key=U("city");
    auto http_get_vars = uri::split_query(msg.request_uri().query());
    ucout << http_get_vars[key] << endl;
    http_response response;
//    json::value v1=json::value::string(U(http_get_vars["city"]));

    answer_c[key]=json::value::string(http_get_vars[key]);
    answer_c["temperature"]=json::value::number(25);

    msg.reply(status_codes::OK,answer_c);
}