#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "../src/Address.h"
#include "../src/Selector.h"
#include "../src/TCPListener.h"
#include "../src/TCPSocket.h"

int main() {
    try{

    std::vector <TCPSocket> clients;
    Selector selector;
    TCPListener listener(CreateAddress("127.0.0.1", 62137));
    listener.start(8);

    Address local = listener.getLocalAddress();
    std::cout << "started listening at: " << GetAddressAndPortAsString(local) << std::endl;

    selector.add(listener);

    while (true) {
        int x = selector.wait();
        //std::cout << "ready: " << x << std::endl;

        for (TCPSocket & clientSocket: clients) {
            if (selector.isReadReady(clientSocket)) {
                Address clientRemote = clientSocket.getRemoteAddress();
                std::cout << "message from " << GetAddressAndPortAsString(clientRemote) << ": ";
                char message[256]; memset(message, 0, 256);
                clientSocket.receive(256, message);
                std::string msg(message);
                std::cout << message << std::endl;
                clientSocket.send(msg.size(), msg.c_str());
            }
        }

        if (selector.isReadReady(listener)) {
            TCPSocket newClient = listener.accept();
            clients.push_back(newClient);
            selector.add(newClient);
            Address clientRemote = newClient.getRemoteAddress();
            std::cout << "new client arrived (" << GetAddressAndPortAsString(clientRemote) << ")" << std::endl;
        }
    }

    }
    catch(const char* e){
        std::cout << std::string(e) << std::endl;
    }
}
