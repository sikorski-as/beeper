#include <string>
#include <netinet/in.h>

#ifndef BEEPER_ADDRESS_H
#define BEEPER_ADDRESS_H

//using Address = sockaddr_in;
typedef sockaddr_in Address;

Address CreateAddress(std::string ip, int port);
Address CreateAddress(int port);
Address CreateAddress();

std::string GetAddressAsString(Address);
int GetPort(Address);
std::string GetAddressAndPortAsString(Address);

#endif //BEEPER_ADDRESS_H
