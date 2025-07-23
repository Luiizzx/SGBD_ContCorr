#include "./../models/operation.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Object getObject(char name, vector<Object> objectList){
  int i;
  for(i = 0; i < objectList.size(); i++){

    if(objectList[i].name == name){
      break;
    }
  }

  return objectList[i];
}

Transaction getTransaction(char name, vector<Transaction> transactionList){
  int i;
  for(i = 0; i < transactionList.size(); i++){

    if(transactionList[i].name == name){
      break;
    }
  }
  
  return transactionList[i];
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