#include "Buffer.h"

std::size_t Buffer::getSize() {
    return data.size();
}

const char * Buffer::getData() {
    return data.data();
}

void Buffer::append(const char * buffer, std::size_t size) {
    for(std::size_t i = 0; i < size; i ++){
        data.push_back(buffer[i]);
    }
}

void Buffer::append(char byte) {
    data.push_back(byte);
}

void Buffer::append(bool boolean) {
    append(reinterpret_cast<char*>(&boolean), sizeof(bool));
}

void Buffer::append(int number) {
    append(reinterpret_cast<char*>(&number), sizeof(int));
}

void Buffer::append(std::size_t number) {
    append(reinterpret_cast<char*>(&number), sizeof(std::size_t));
}


void Buffer::append(std::string text) {
    append(text.c_str(), text.size() + 1);
}

void Buffer::consume(std::size_t consumedBytes) {
    if(consumedBytes > data.size()){
        data.clear();
    }
    else{
        data = std::vector<char>(data.begin() + consumedBytes, data.end());
    }
}
