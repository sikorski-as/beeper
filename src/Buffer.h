#ifndef BEEPER_BUFFER_H
#define BEEPER_BUFFER_H

#include <vector>
#include <string>

class Buffer {
    std::vector<char> data;
public:
    std::size_t getSize();
    const char * getData();

    void append(const char * buffer, std::size_t size);
    void append(std::string);
    void append(char);
    void append(bool);
    void append(int);
    void append(std::size_t);

    void consume(std::size_t);
};

#endif //BEEPER_BUFFER_H
