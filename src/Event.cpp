#include "Event.h"

bool checkEventKeys(Event object, std::initializer_list<std::string> keysToBeInEvent){
    try{
        std::set<std::string> setOfObjectKeys;
        std::set<std::string> setOfRequiredKeys(keysToBeInEvent);

        for (json::iterator it = object.begin(); it != object.end(); ++it) {
            setOfObjectKeys.insert(it.key());
        }

        return setOfObjectKeys == setOfRequiredKeys;
    }
    catch(EventNotValid e)
    {
        return false;
    }
}