#ifndef BEEPER_ENCRYPTOR_H
#define BEEPER_ENCRYPTOR_H

#include <string>

class Encryptor
{
public:
  virtual std::string encrypt(std::string data) = 0;
};


#endif //BEEPER_ENCRYPTOR_H
