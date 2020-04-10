#pragma once

#include <assert.h>
#include <pthread.h>
#include <stdlib.h> 

template<typename T>
struct has_no_destroy
{
  template <typename C> static char test(decltype(&C::no_destroy));
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(nullptr)) == 1;  // 0 or nullptr
};

template<typename T>
class CSingleton : noncopyable
{
public:
    CSingleton() = delete;
    ~CSingleton() = delete;

    static T& instance()
    {
        pthread_once(&ponce_, &CSingleton::init);
        assert(value_ != NULL);
        return *value_;
    }

private:
    static void init()
    {
        value_ = new T();
        if (!has_no_destroy<T>::value)  //use function 'no_destroy' decide pointer need destory.
        {
            atexit(destroy);
        }
    }

    static void destroy()
    {
        delete value_;
        value_ = NULL;
    }

private:
    static pthread_once_t ponce_;
    static T*             value_;
};

template<typename T>
pthread_once_t CSingleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* CSingleton<T>::value_ = NULL;