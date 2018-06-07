#pragma once
#include "PQ_entry.hpp"

template<class T>
class PriorityQueue{
    private:
        pqentry<T> *arr;
        int size;
        int count;
        void resize();
    public:
        PriorityQueue();
        void insert(T value, float priority);
        T extractMin();
        float getMinPrio();
        T getMinValue();
        void decreaseKey(T value, float priority);
        void remove(T value);
        bool hasValue();
        ~PriorityQueue();
};


template <class T>
void PriorityQueue<T>::resize(){
    if(this->size==this->count){
        this->size*=2;
        pqentry<T> *narr = new pqentry<T>[this->size];
        for(int i=0;i<this->count;i++)narr[i]=this->arr[i];
        delete[] this->arr;
        this->arr = narr;
    }
    else{
        if(this->count < this->size/2 && this->size>8){
            this->size/=2;
            pqentry<T> *narr = new pqentry<T>[this->size];
            for(int i=0;i<this->count;i++)narr[i]=this->arr[i];
            delete[] this->arr;
            this->arr = narr;
        }
    }
};

template <class T>
PriorityQueue<T>::PriorityQueue(){
    this->arr = new pqentry<T>[8];
    this->size=8;
    this->count=0;
};

template <class T>
void PriorityQueue<T>::insert(T value, float priority){
    pqentry<T> ne(value,priority);
    int i=0;int j=0;char f=0;

    if(this->count==0){
        this->arr[0]=ne;
    }
    else{
        for(i=0;i<this->count;i++){
            if(priority>=this->arr[i].getPriority()){
                for(j=this->count;j>i;j--){
                this->arr[j]=this->arr[j-1];
                }
                this->arr[i]=ne;
                f=1;
                break;
            }
            if(!f){
                this->arr[this->count]=ne;
            }
        }
    }
    this->count++;
    resize(); 
};

template <class T>
T PriorityQueue<T>::extractMin(){
    if(this->count>0){
        this->count--;
        return this->arr[this->count].getValue();
    }
    else{
        return 0;
    }
};
template <class T>
float PriorityQueue<T>::getMinPrio(){
    if(this->count>0){
        return this->arr[this->count-1].getPriority();
    }
    else{
        throw 777;
    }
};

template <class T>
T PriorityQueue<T>::getMinValue(){
    if(this->count>0){
        return this->arr[this->count-1].getValue();
    }
    else{
        throw 777;
    }
};

template <class T>
bool PriorityQueue<T>::hasValue(){
    return this->count>0;
};

template <class T>
void PriorityQueue<T>::decreaseKey(T value, float priority){
    try{
        remove(value);
        insert(value,priority);
    }
    catch(int ex){
        throw ex;
    }
};

template <class T>
void PriorityQueue<T>::remove(T value){
    int i,j=0;bool f = false;
    if(this->count>0){
        for(i=0;i<this->count;i++){
            if(value==this->arr[i].getValue()){
                for(j=i;j<this->count-1;j++){
                    this->arr[j] = this->arr[j+1];
                }
                f=true;
                break;
            }
        }
        if(f)
            this->count--;
        else throw 404;
    }
    else{
        throw 404;
    }
};

template <class T>
PriorityQueue<T>::~PriorityQueue(){
    delete[] this->arr;
};