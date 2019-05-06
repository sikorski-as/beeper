#include <iostream>
#include "../src/Address.h"
#include "Server.h"

Server server;

int main() {
    std::cout << "server started" << std::endl;

    server.start(CreateAddress("127.0.0.1", 62137), 8);

    std::cout << "server closed" << std::endl;

    return 0;
}
