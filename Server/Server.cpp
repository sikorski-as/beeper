#include <iostream>
#include <thread>
#include "Server.h"
#include "Server.h"
#include "../src/TCPCommunicationStack.h"

Server::Server() : listener(), selector(listener), clientMonitor(selector), database() {
    running = false;
}

void Server::start(Address address, int queueLength) {
    if(!running){
        listener.start(address, queueLength);
        selector.setListener(listener);

        database.openDB("beeper.db");

        running = true;
        std::thread communicationThread(&Server::communicationThreadTask, this);
        communicationThread.join();
    }
}

bool Server::isRunning() {
    return running;
}

void Server::stop() {
    if(running){
        clientMonitor.removeAllClients(); // todo: nice way to inform clients about stopping server
        listener.close();
        selector.clear();
        database.closeDB();

        running = false;
        // todo: let restart server nicely
    }
}

void Server::communicationThreadTask() {
    while(running){
        int activeSockets = selector.wait();

        if(selector.isListenerReady()){
            try{
                TCPSocket newClientSocket = listener.accept();

                CommunicationStack* commStack = new TCPCommunicationStack(newClientSocket);
                auto newClient = new Client(commStack);

                auto address = newClientSocket.getRemoteAddress();
                std::cout << "new client arrived from " << GetAddressAndPortAsString(address) << "\n";

                clientMonitor.insertClient(newClientSocket, newClient);

                clientMonitor.status();
            }
            catch (TCPListener::TCPListenerError e){
                std::cout << e.what() << std::endl;
            }
        }

        for(TCPSocket& socket: selector.getReadReadySockets())
        {
            try{
                clientMonitor.notifyRead(socket);
            }
            catch(TCPSocket::IOError& e){
                clientMonitor.removeClient(socket);
                clientMonitor.status();
            }
            catch(TCPSocket::ConnectionClosed& e){
                clientMonitor.removeClient(socket);
                clientMonitor.status();
            }
        }

        for(TCPSocket& socket: selector.getWriteReadySockets())
        {
            try{
                clientMonitor.notifyWrite(socket);
            }
            catch(TCPSocket::IOError& e){
                clientMonitor.removeClient(socket);
                clientMonitor.status();
            }
            catch(TCPSocket::ConnectionClosed& e){
                clientMonitor.removeClient(socket);
                clientMonitor.status();
            }
        }

    }
}
