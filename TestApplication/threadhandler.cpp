#include "threadhandler.h"

ThreadHandler::ThreadHandler(){
}

ThreadHandler::~ThreadHandler(){
    emit finished();
}

long long ThreadHandler::m_value = 0;
int ThreadHandler::m_counter = 0;

void ThreadHandler::process(){
    long long i = 10000000000;
    while (true) {
        m_value ++;
        if(m_value == i){
            m_counter ++;
            m_value = 0;
            emit rounding();
        }
    }
}

long long ThreadHandler::getValue(){
    return m_value;
}

int ThreadHandler::getCounter(){
    return m_counter;
}

void ThreadHandler::stopThread(){
    emit finished();
}
