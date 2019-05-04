#include <iostream>
#include "../src/Address.h"
#include "Server.h"

int main() {
    std::cout << "server started" << std::endl;

    Server server;
    server.start(CreateAddress("127.0.0.1", 62137), 8);

    std::cout << "server closed" << std::endl;

    return 0;
}
