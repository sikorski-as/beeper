#include <iostream>
#include <string>
#include <exception>
#include "../src/Address.h"
#include "../src/TCPClientSocket.h"
#include "../src/Buffer.h"

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

        bool echoMode = false;

        while(true){
            std::string message;

            std::cout << "message to send: ";
            std::getline(std::cin, message);

            try{
                if(message.length() == 0){
                    std::cout << "message cannot be empty!" << std::endl;
                    continue;
                }
                socket.send(message.c_str(), message.length());

                char buffer[256];
                int received = socket.receive(buffer, 256);
                if(received > 0){
                    std::cout << "got response: " << std::string(buffer, received) << std::endl;
                }
            }
            catch (TCPSocket::ConnectionClosed & e){
                std::cout << std::endl << e.what() << std::endl;
                std::cout << "closing app...\n";
                return 0;
            }
        }

    }
    catch(std::exception e){
        std::cout << std::string(e.what()) << std::endl;
    }
    catch(char const* e){
        std::cout << std::string(e) << std::endl;
    }

}