#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    public:
    T back(){
        if (is_empty())throw("it's empty");
        else return array[back];
    }
};
