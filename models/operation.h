#pragma once
#include "./object.h"
#include "./transaction.h"
#include "./schedule.h"
#include <vector>
#include <string>
using namespace std;

class Operation{
  public:
    char type;
    Object object;
    Transaction transaction;

    static vector<Object> resetList(vector<Object> objList);
    static Object readObject(char opType, Object object, Transaction transaction);
    static Object writeObject(char opType, Object object, Transaction transaction);
    static Object validateOperation(string text, Operation operation, Object object, Transaction transaction, Schedule *schedule);
};