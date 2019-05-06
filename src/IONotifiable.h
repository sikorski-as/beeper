#ifndef BEEPER_IONOTIFIABLE_H
#define BEEPER_IONOTIFIABLE_H

class IONotifiable {
public:
    virtual void notifyRead() = 0;
    virtual void notifyWrite() = 0;
};

#endif //BEEPER_IONOTIFIABLE_H
