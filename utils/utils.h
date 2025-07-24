#pragma once
#include "../models/operation.h"
#include <vector>
#include <string>

class Utils {
  public:
    static Object getObject(char name, vector<Object> objectList);
    static vector<Object> setObject(Object object, vector<Object> objectList);
    static Transaction getTransaction(char name, vector<Transaction> transactionList);
    static string buildScheduleText(Schedule *schedule, char current, int operationCount);
};