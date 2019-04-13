#include <iostream>
#include <string>
#include "../src/Address.h"
#include "../src/TCPClientSocket.h"

int main()
{
    try{
        TCPClientSocket socket;

        socket.connect(CreateAddress("127.0.0.1", 62137));
        std::cout << "connected!" << std::endl;

        Address local = socket.getLocalAddress();
        std::cout << "local address: " << GetAddressAndPortAsString(local) << std::endl;

        Address remote = socket.getRemoteAddress();
        std::cout << "server address: " << GetAddressAndPortAsString(remote) << std::endl;

        while(true){
            std::string message;
            std::cout << "Message to send: ";
            std::cin >> message;
            auto x = socket.send(message.size(), message.c_str());
            std::cout << "writen: " << x << std::endl;

            char msg_buffer[256];
            socket.receive(256, msg_buffer);
            std::string msg(msg_buffer);
            std::cout << "server: " << msg << std::endl;
        }

    }
    catch(char const* e){
        std::cout << std::string(e);
    }

}