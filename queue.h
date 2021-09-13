#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
    public:
        void enqueue(T data);
        int dequeue();
        void display(); 
};

template <typename T>
void QueueArray<T>::enqueue(T data){
    if(is_empty()) {
        front=0;
        back=0;
        array[front]=data;
    };
    else if(is_full()) throw("it's full");
    else {
        back=next(back);
        array[back]=data;
    }
}

template <typename T>
int QueueArray<T>::dequeue(){
    if(is_empty())throw("it's empty");
    else if(size()==1){
        int t=front;
        front=-1;
        back=-1;
        return array[t];
    }
    else{
        front=next[front];
        return array[back(front)];
    }
}

template <typename T>
void QueueArray<T>::display(){
    int t_front=front;
    do{
        cout<<array[t_front]<<" ";
        t_front=next(t_front);
    }while(t_front!=next(back));
}
