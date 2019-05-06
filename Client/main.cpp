#include <iostream>
#include <string>
#include <exception>
#include "../src/Address.h"
#include "../src/TCPClientSocket.h"
#include "../src/Buffer.h"
#include "../src/TCPCommunicationStack.h"
#include <arpa/inet.h>

int main()
{
    std::string mode = "write";

    TCPClientSocket socket;
    try{
        socket.connect(CreateAddress("127.0.0.1", 62137));
    }
    catch(TCPSocket::TCPSocketError& e){
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "connected!" << std::endl;
    Address local = socket.getLocalAddress();
    std::cout << "local address: " << GetAddressAndPortAsString(local) << std::endl;
    Address remote = socket.getRemoteAddress();
    std::cout << "server address: " << GetAddressAndPortAsString(remote) << std::endl;

    try{
        if(mode == "read"){
            TCPCommunicationStack communicationStack(socket);
            while(true){
                try{
                    sleep(2);
                    communicationStack.notifyRead();
                    communicationStack.notifyRead();

                    Event e = communicationStack.getEvent();
                    std::cout << "got:" << e.dump() << std::endl;
                }
                catch (TCPSocket::ConnectionClosed & e){
                    std::cout << std::endl << e.what() << std::endl;
                    std::cout << "closing app...\n";
                    return 0;
                }
            }
        }
        else if (mode == "write"){
            TCPCommunicationStack communicationStack(socket);
            while(true){
                std::string message;
                std::cout << "message to send: ";
                std::getline(std::cin, message);
                if(message.length() == 0){
                    std::cout << "message cannot be empty!" << std::endl;
                    continue;
                }
                Buffer b;
                b.append(htonl(message.size() + 1));
                b.append(message);
                while(b.getSize() > 0){
                    int sentBytes = socket.send(b.getData(), b.getSize());
                    b.consume(sentBytes);
                }
            }
        }
        else{
            return 1;
        }
    }
    catch (TCPSocket::ConnectionClosed & e){
        std::cout << std::endl << e.what() << std::endl;
        std::cout << "closing app...\n";
        return 0;
    }
    catch(std::exception e){
        std::cout << std::string(e.what()) << std::endl;
    }
    catch(char const* e){
        std::cout << std::string(e) << std::endl;
    }

}