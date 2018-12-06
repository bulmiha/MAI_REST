#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "WeaterServer.h"
#include "WeaterServerForecast.h"


using namespace web;
using namespace http;
using namespace utility;

std::unique_ptr<WeaterServer> g_http_cur;
std::unique_ptr<WeaterServerForecast> g_http_forecast;

void on_start(const string_t &address) {
    uri_builder uri_c(address);
    uri_c.append_path(U("/v1/current/"));

    auto addr = uri_c.to_uri().to_string();
    g_http_cur = std::unique_ptr<WeaterServer>(new WeaterServer(addr));

    ucout << string_t(U("Listening on: ")) << addr << std::endl;

    uri_builder uri_f(address);
    uri_f.append_path(U("/v1/forecast/"));

    addr = uri_f.to_uri().to_string();
    g_http_forecast = std::unique_ptr<WeaterServerForecast>(new WeaterServerForecast(addr));

    g_http_cur->open().wait();
    g_http_forecast->open().wait();

    ucout << string_t(U("Listening on: ")) << addr << std::endl;

    return;
}

void on_end() {
    g_http_cur->close().wait();

    g_http_forecast->close().wait();
    return;
}

int main(int argc, char *args[]) {
    string_t port = U("8080");

    if (const char *env_p = std::getenv("LISTEN_PORT")) {
        port = env_p;
    }

    if (argc >= 2) {
        port = args[1];
    }

    string_t address = U("http://0.0.0.0:");

    address.append(port);

    on_start(address);

    std::cout << "Write exit and press Enter to exit" << std::endl;

    std::string line;
    do {
        std::getline(std::cin, line);
    }
    while (line!="exit");

    on_end();

    return 0;
}
