#pragma once

template <class T>
class pqentry{
    private:
        T value;
        float priority;
    public:
        pqentry(T value, float priority);
        pqentry();
        float getPriority();
        T getValue();
        void set(T value, float priority);
};



//////////////////////////
template <class T>
pqentry<T>::pqentry(T value, float priority){
    this->value=value;
    this->priority=priority;
}
template <class T>
pqentry<T>::pqentry(){
    //NOP
}

template <class T>
float pqentry<T>::getPriority(){
    return this->priority;
}

template <class T>
T pqentry<T>::getValue(){
    return this->value;
}

template <class T>
void pqentry<T>::set(T value, float priority){
    this->value=value;
    this->priority=priority;
}