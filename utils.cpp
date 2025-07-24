#include "./utils/utils.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Object Utils::getObject(char name, vector<Object> objectList){
  int i;
  for(i = 0; i < objectList.size(); i++){

    if(objectList[i].name == name){
      break;
    }
  }

  return objectList[i];
}

vector<Object> Utils::setObject(Object object, vector<Object> objectList){
  for(int i = 0; i < objectList.size(); i++){

    if(object.name == objectList[i].name){
      objectList[i] = object;
      break;
    }
  }

  return objectList;
}

Transaction Utils::getTransaction(char name, vector<Transaction> transactionList){
  int i;
  for(i = 0; i < transactionList.size(); i++){

    if(transactionList[i].name == name){
      break;
    }
  }

  return transactionList[i];
}

string Utils::buildScheduleText(Schedule *schedule, char current, int operationCount){
  schedule->name = "E_" + string(1,current);

  if(schedule->status == "Rollback"){
    cout << schedule->name + "-" + schedule->status + "-" + to_string(operationCount) << "\n";
    return schedule->name + "-" + schedule->status + "-" + to_string(operationCount);
  }

  cout << schedule->name + "-" + schedule->status << "\n";
  return schedule->name + "-" + schedule->status;
}
