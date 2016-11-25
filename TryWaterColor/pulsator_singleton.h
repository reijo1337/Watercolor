#ifndef PULSATOR_SINGLETON_H
#define PULSATOR_SINGLETON_H

#include <stdlib.h>

template<typename T>
class PulsatorSingleton
{
public:
    static T& instance()
    {
        if(!myInstance)
            myInstance = new T;
        return *myInstance;
    }
private:
    static T* myInstance;
    PulsatorSingleton (const PulsatorSingleton&){}
};

//template<typename T>
//T* PulsatorSingleton::myInstance = NULL;

#endif // PULSATOR_SINGLETON_H
