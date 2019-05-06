#include "ClientHandler.h"

ClientHandler::ClientHandler(TCPSocket s)
: socket(s), incomingBufferAccess(new std::mutex()), outgoingBufferAccess(new std::mutex())
{

}

ClientHandler::~ClientHandler(){

}
