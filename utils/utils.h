#include "./object.h"
#include "./transaction.h"
#include <vector>
#include <string>
using namespace std;

Object getObject(char name, vector<Object> objectList){
  for(int i = 0; i < objectList.size(); i++){

    if(name == objectList[i].name){
      return objectList[i];
    }
  }
}

Transaction getTransaction(char name, vector<Transaction> transactionList){
  for(int i = 0; i < transactionList.size(); i++){

    if(transactionList[i].name[1] == name){
      return transactionList[i];
    }
  }
}

vector<Object> setObject(Object object, vector<Object> objectList){
  for(int i = 0; i < objectList.size(); i++){

    if(object.name == objectList[i].name){
      objectList[i] = object;
      break;
    }
  }

  return objectList;
}