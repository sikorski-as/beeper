#include <iostream>
#include <thread>
#include "Server.h"
#include "Server.h"

Server::Server() : listener(), selector(listener) {
    running = false;
}

void Server::start(Address address, int queueLength) {
    if(!running){
        listener.start(address, queueLength);
        selector.setListener(listener);
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
        listener.close();
        selector.clear();
        running = false;
        // todo: let restart server nicely
    }
}

void Server::communicationThreadTask() {
    while(running){
        int activeSockets = selector.wait();

        std::cout << "!\n";

        if(selector.isListenerReady()){
            try{
                TCPSocket newClient = listener.accept();

                // todo: tutaj budujemy stos protokołów
                // todo: tworzymy usera
                // todo: auto newClient = new Client(new CommunicationStack());

                auto address = newClient.getRemoteAddress();
                std::cout << "new client arrived (" << GetAddressAndPortAsString(address) << ")\n";

                selector.add(newClient); // todo: client should register in the selector by itself
                clientMonitor.insertClient(newClient);
            }
            catch (TCPListener::TCPListenerError e){
                // todo: handle event (rebuild listener?)
            }
        }

        for(TCPSocket& socket: selector.getReadReadySockets())
        {
            clientMonitor.notifyRead(socket);
        }

        for(TCPSocket& socket: selector.getWriteReadySockets())
        {
            clientMonitor.notifyWrite(socket);
        }

    }
}
