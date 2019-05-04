#ifndef BEEPER_CLIENTMONITOR_H
#define BEEPER_CLIENTMONITOR_H

#include <string>
#include <exception>
#include <mutex>
#include <vector>
#include "../src/TCPSocket.h"
#include "Client.h"
#include "Event.h"


class ClientMonitor {
    std::mutex clientListAccess;
    std::vector<Client*> clients;

    // callers of these need to lock clientListAccess first
    int findClientBy(TCPSocket & socket);
    int findClientBy(const std::string& username);
    bool clientExists(TCPSocket & socket);
    bool clientExists(const std::string& username);
public:
    // new client arrived
    void insertClient(Client*);
    void insertClient(TCPSocket& socket);

    // connection with client is closed / should be closed
    // todo: void removeClient(Client*);
    void removeClient(TCPSocket& socket);
    void removeClient(const std::string& username);
    void removeAllClients();

    // insert event to handle (login, message from another client)
    void insertIntoUsersIncomingQueue(TCPSocket&, Event e);
    void insertIntoUsersIncomingQueue(const std::string& username, Event e);

    // notify ClientThreadTask (sending possible, receiving possible, new event in queue)
    void notifyRead(TCPSocket&);
    void notifyWrite(TCPSocket&);

    // void notify(const std::string& username);

    class ClientNotFound : public std::exception{
    public:
        virtual const char* what(){return "Specified Client not found in ClientMonitor";}
    };
};


#endif //BEEPER_CLIENTMONITOR_H
