#ifndef BEEPER_CLIENTMONITOR_H
#define BEEPER_CLIENTMONITOR_H

#include <string>
#include <exception>
#include <mutex>
#include <vector>
#include <unordered_map>
#include "../src/TCPSocket.h"
#include "../src/Selector.h"
#include "Client.h"
#include "Event.h"


class ClientMonitor {
    std::mutex clientListAccess;
    std::vector<Client*> clients;
    std::unordered_map<TCPSocket, Client*> socketToClientMap;
    Selector& selector;

    // callers of these need to lock clientListAccess first
    int findClientBy(const TCPSocket & socket);
    int findClientBy(const std::string& username);
    int findClientBy(Client*);

    bool clientExists(TCPSocket & socket);
    bool clientExists(const std::string& username);
public:
    void status();
    // new client arrived
    ClientMonitor(Selector&);

    void insertClient(const TCPSocket&, Client*);

    // connection with client is closed / should be closed
    void removeClient(Client*);
    void removeClient(const TCPSocket&);
    void removeAllClients();

    // notify ClientThreadTask (sending possible, receiving possible, new event in queue)
    void notifyRead(TCPSocket&);
    void notifyWrite(TCPSocket&);

    // todo: functions like void sendMessage(username of the recipient, message);

    class ClientNotFound : public std::exception{
    public:
        virtual const char* what(){return "Specified Client not found in ClientMonitor";}
    };
};

#endif //BEEPER_CLIENTMONITOR_H
