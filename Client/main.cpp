#include <iostream>
#include <string>
#include <exception>
#include <thread>
#include <mutex>
#include "../src/Address.h"
#include "../src/TCPClientSocket.h"
#include "../src/Buffer.h"
#include "../src/TCPCommunicationStack.h"
#include <arpa/inet.h>

TCPCommunicationStack* communicationStack = nullptr;

void readTask(){
    while(true){
        communicationStack->notifyRead();
    }
}

void writeTask(){
    while(true){
        communicationStack->notifyWrite();
    }
}

int main()
{
    TCPClientSocket socket;

    std::cout << "Starting client..." << std::endl;
    sleep(1);

    try{
        socket.connect(CreateAddress("127.0.0.1", 62137));

        std::cout << "Connected!" << std::endl;
        Address local = socket.getLocalAddress();
        std::cout << "Local address: " << GetAddressAndPortAsString(local) << std::endl;
        Address remote = socket.getRemoteAddress();
        std::cout << "Server address: " << GetAddressAndPortAsString(remote) << std::endl;
    }
    catch(TCPSocket::TCPSocketError& e){
        std::cout << e.what() << std::endl;
        return 1;
    }

    sleep(1);

    try{
        communicationStack = new TCPCommunicationStack(socket);
        std::thread notifier1(readTask); notifier1.detach();
        std::thread notifier2(writeTask); notifier2.detach();

        try{
            for(int i = 1; i <= 3; i++){
                std::string username, password;

                std::cout << "Logging in [chance " << i << " out of 3]:" << std::endl;
                std::cout << "Username: "; std::cin >> username;
                std::cout << "Password: "; std::cin >> password;

                std::cout << "Sending login request..." << std::endl;
                sleep(1);

                communicationStack->sendEvent(LoginRequest(username, password));

                auto e = communicationStack->getEvent();
                if(e["type"] == "LOGIN_RESPONSE"){
                    auto response = LoginResponse(e);
                    if(response.status){
                        std::cout << "You just logged in" << std::endl;
                        break;
                    }
                    else{
                        std::cout << "Login failed" << std::endl;
                    }
                }
                else if(e["type"] == "UNKNOWN_REQUEST"){
                    auto response = UnknownRequest();
                    std::cout << "You sent request of unknown type" << std::endl;
                }
                else if(e["type"] == "MALFORMED_REQUEST"){
                    auto response = MalformedRequest();
                    std::cout << "You sent malformed request" << std::endl;
                }
                else{
                    std::cout << "Server sent unknown type of response" << std::endl;
                }
            }
        }
        catch(EventNotValid& e){
            std::cout << "Server sent invalid response" << std::endl;
        }

        std::cout << "Closing client..." << std::endl;
        sleep(2);

        notifier1.~thread(); notifier2.~thread();
        delete communicationStack;
        exit(0);
    }
    catch(TCPSocket::ConnectionClosed & e){
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