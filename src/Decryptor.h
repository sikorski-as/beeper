#ifndef BEEPER_DECRYPTOR_H
#define BEEPER_DECRYPTOR_H

#include <string>

class Decryptor
{
public:
  virtual std::string decrypt(std::string data) = 0;
};


#endif //BEEPER_DECRYPTOR_H
