#include <iostream>
#include<queue>
#include<cmath>
using namespace std;

template <class T>
class CircularArray
{
protected:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray(); 
    CircularArray(int _capacity); 
    virtual ~CircularArray();  
        void push_front(T data);
        void push_back(T data);
        void insert(T data, int pos);
        T pop_front();
        T pop_back();
        bool is_full();
        bool is_empty();
        int size();
        void clear();
        T &operator[](int);
        void sort();
        bool is_sorted();
        void reverse();
    string to_string(string sep=" "); 
    int get_cmax(); //obtener cifras del numero mayor para usar Radix Sort
    void imp();

protected:
    int next(int); 
    int prev(int); 
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}

//-------------------------IMPLEMENTACION--------------------------------

template <class T>
void CircularArray<T>::push_front(T data){
    if(is_full())throw("it's full");
    else if(is_empty()){
        front=0; back=0;
        array[front]=data;
    }
    else{
        front=prev(front);
        array[front]=data;
    }
}

template <class T>
void CircularArray<T>::push_back(T data){
    if(is_full())throw("it's full");
    else if(is_empty()){
        front=0; back=0;
        array[back]=data;
    }
    else{
        back=next(back);
        array[back]=data;
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos){
    if(is_full())throw("it's full");
    else{
        back=next(back);
        int t_back=back;
        do{
            array[t_back]=array[prev(t_back)];
            t_back=prev(t_back);
        }while(t_back!=(pos-1));
        array[pos-1]=data;
    }
}

template <class T>
T CircularArray<T>::pop_front(){
    if(is_empty())throw("it's empty");
    else{
        if(size()==1){
            int t_front=front;
            front=-1;back=-1;
            return array[t_front];
        }
        front=next(front);
        return array[prev(front)];
    }
}

template <class T>
T CircularArray<T>::pop_back(){
    if(is_empty())throw("it's empty");
    else{
        if(size()==1){
            int t_back=back;
            front=-1;back=-1;
            return array[t_back];
        }
        back=prev(back);
        return array[next(back)];
    }
}

template <class T>
bool CircularArray<T>::is_full(){
    return next(back)==front;
}

template <class T>
bool CircularArray<T>::is_empty(){
    return(front==-1);
}

template <class T>
int CircularArray<T>::size(){
    if(is_empty())return 0;
    else{
        if(front==back && back!=-1)return 1;

        int s=1, temp=front;
        do{
            temp=next(temp);
            ++s;
        }while(temp!=back);
        return s;
    }
}

template <class T>
void CircularArray<T>::clear(){
    delete[]array;
    array=new T[capacity];
    front=back=-1;
}

// TA: Para el operador corchetes, podrías usar fórmulas como if (front < back) -> return array[(front + (back-front))%capacity] y así para los otros casos, reduciría el costo de la función.
template <class T>
T &CircularArray<T>::operator[](int n){
    if(!is_empty()){
        int temp=front,cont=0;
        if (n==0) return array[front];
        else {
            int temp=front;
            do{
                temp=next(temp);
                ++cont;
            }while(cont!=n);
            return array[temp];
        }
    }
}

template<typename T>
int CircularArray<T>::get_cmax(){ //obtener mayor cantidad de cifras del array
    int num=0;
    int t_front=front, cifras=1;
    if (is_empty())throw("it's empty");
    else{
        if (size()>1){
            do{
                if (array[t_front]>num) num=array[t_front];
                t_front=next(t_front);
            }while(t_front!=next(back));
        }   
        while (num>=10){
        num/=10;
        ++cifras;
        }
    return cifras;
    }
}

template <class T>
void CircularArray<T>::imp(){
    cout<<get_cmax();
}

template <class T>
void CircularArray<T>::sort(){  
    //radixsort
    
    int a, b, index, temp, count, i, j,t_front;
    int cif=get_cmax();
    queue<int> queueArray[10];
    for(i = 0; i< cif; i++) {
        a = pow(10, i+1);
        b = pow(10, i);
        t_front=front;
        do{
            temp = array[t_front]%a;
            index = temp/b;
            queueArray[index].push(array[t_front]);
            t_front=next(t_front);
        }while(t_front!=next(back));
        t_front=front;
        for(j = 0; j<10; j++) {
            while(!queueArray[j].empty()) {
                array[t_front] = queueArray[j].front();
                queueArray[j].pop();
                t_front=next(t_front);
            }
        }
    }
}
    
template <class T>
bool CircularArray<T>::is_sorted(){ //de forma ascendente
    int temp=front;
    do{
        if ( array[temp]>array[next(temp)]){
            return false;
        }
        temp=next(temp);
    }while(temp!=back);
    return true;
}
    
template <class T>
void CircularArray<T>::reverse(){
    if(is_empty()) throw("it's empty");
    else{
        int t_back=back;
        int t_front=front;
        T temp;
        do{
            temp=array[t_front];
            array[t_front]=array[t_back];
            array[t_back]=temp;
            t_back=prev(t_back);
            t_front=next(t_front);
            if(prev(t_front)==t_back) break;
            if(t_back==t_front) break;
        }while(true);
    }
}

//----------------------------------------------------------------------
