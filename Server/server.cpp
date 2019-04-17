#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <exception>
#include <condition_variable>

#include "../src/Address.h"
#include "../src/Selector.h"
#include "../src/TCPListener.h"
#include "../src/TCPSocket.h"
#include "../src/Buffer.h"

#include "ClientHandler.h"

/*
 *
 * server data
 *
 */

std::atomic<bool> running{true};

//const int INIT_CLIENTS = 1024;
std::mutex clientsListAccess;
std::vector<ClientHandler> clients;

std::mutex serviceNeededMutex;
std::condition_variable serviceNeeded;

void deb(std::string msg){
    std::cout << msg << std::endl;
}

/*
 *
 * tasks
 *
 */

void communicationThreadTask(){
    Selector selector(true, true, false);
    TCPListener listener;
    selector.add(listener);

    try{
        listener.start(CreateAddress("127.0.0.1", 62137), 8);
    }
    catch(TCPListener::TCPListenerError e){
        std::cout << e.what() << std::endl;
        std::cout << "closing..." << std::endl;
        running = false;
        return;
    }

    std::cout << "server started at " << GetAddressAndPortAsString(listener.getLocalAddress()) << std::endl;

    while(running){
        selector.wait();

        if(selector.isReadReady(listener)){
            try{
                TCPSocket newClient = listener.accept();
                selector.add(newClient);
                {
                    std::lock_guard<std::mutex> lock(clientsListAccess);
                    clients.push_back(ClientHandler(newClient));
                }

                Address clientsAddress = newClient.getRemoteAddress();
                std::cout << "new client (" << GetAddressAndPortAsString(clientsAddress) << ")" << std::endl;
                serviceNeeded.notify_one();
            }
            catch(TCPListener::TCPListenerError e){
                std::cout << e.what() << std::endl;
                std::cout << "closing..." << std::endl;
                running = false; // todo: nowy listener
                return;
            }
        }

        for(auto& clientHandler : clients){
            if(selector.isReadReady(clientHandler.socket)){
                char buffer[256];
                try{
                    int received = clientHandler.socket.receive(buffer, 256);
                    std::cout << "got data from client" << std::endl;

                    // critical section
                    {
                        std::lock_guard<std::mutex> lock(*clientHandler.incomingBufferAccess);
                        clientHandler.incomingBuffer.append(buffer, received);
                    }

                    serviceNeeded.notify_one();
                }
                catch(TCPSocket::ConnectionClosed e){
                    // todo: remove client from clients vector
                    selector.remove(clientHandler.socket);
                    std::cout << "client disconnected [1]" << std::endl;
                    continue;
                }
                catch(TCPSocket::IOError){
                    std::cout << "io error, could not receive" << std::endl;
                }
            }

            if(selector.isWriteReady(clientHandler.socket)){
                try{
                    // critical section
                    {
                        std::lock_guard<std::mutex> lock(*clientHandler.outgoingBufferAccess);
                        if(clientHandler.outgoingBuffer.getSize() > 0){
                            int sent = clientHandler.socket.send(
                                    clientHandler.outgoingBuffer.getData(),
                                    clientHandler.outgoingBuffer.getSize()
                            );
                            clientHandler.outgoingBuffer.consume(sent);
                            std::cout << "Sending..." << std::endl;
                        }
                    }
                    // serviceNeeded.notify_one(); -> jeśli chcemy powiadomić wątek obsługi o wysłanych danych
                }
                catch(TCPSocket::ConnectionClosed e){
                    // todo: remove client from clients vector
                    selector.remove(clientHandler.socket);
                    std::cout << "client disconnected [2]" << std::endl;
                    continue;
                }
                catch(TCPSocket::IOError){
                    std::cout << "io error, could not send" << std::endl;
                }
            }
        }
    }
}

void serviceThreadTask(){
    while(running){
        if(running){
            std::unique_lock<std::mutex> lock(serviceNeededMutex);
            serviceNeeded.wait(lock);
        }
        std::cout << "service thread has been notified and it is working!\n"; // this thread has been notified by the communication thread

        clientsListAccess.lock();
        for(auto& clientHandler : clients) {
            {
                std::lock_guard<std::mutex> lock1(*clientHandler.incomingBufferAccess);
                std::lock_guard<std::mutex> lock2(*clientHandler.outgoingBufferAccess);

                auto size = clientHandler.incomingBuffer.getSize();
                std::string msg(clientHandler.incomingBuffer.getData(), size);

                if(size > 0){
                    if(msg == "stop"){
                        running = false;
                        clientHandler.incomingBuffer.consume(4);
                    }
                    else{
                        std::string echo("I, server, got your message: \"");
                        clientHandler.outgoingBuffer.append(echo + msg + "\"");
                        clientHandler.incomingBuffer.consume(size);
                    }
                }
            }
        }
        clientsListAccess.unlock();
    }
}

int main() {
    std::cout << "starting server..." << std::endl;

    std::thread communicationThread(communicationThreadTask);
    std::thread serviceThread(serviceThreadTask);

    communicationThread.join();
    serviceThread.join();

    std::cout << "server closed" << std::endl;
}
