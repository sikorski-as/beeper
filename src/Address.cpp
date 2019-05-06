#include <netinet/in.h>
#include <arpa/inet.h>
#include "Address.h"

Address CreateAddress(std::string ip, int port){
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = inet_addr(ip.c_str());
    inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
    address.sin_port = htons(port);

    return address;
}

Address CreateAddress(int port){
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    return address;
}

Address CreateAddress(){
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(0);

    return address;
}

std::string GetAddressAsString(Address address){
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, str, INET_ADDRSTRLEN);
    return std::string(str);
}

int GetPort(Address address){
    return ntohs(address.sin_port);
}

std::string GetAddressAndPortAsString(Address address){
    std::string s = GetAddressAsString(address) + ":" + std::to_string(GetPort(address));
    return s;
}
