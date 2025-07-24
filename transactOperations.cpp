#include "./models/operation.h"
#include <vector>
#include <iostream>
using namespace std;

vector<Object> Operation::resetList(vector<Object> objList){
    for(int i = 0; i < objList.size(); i++){
      objList[i].readTime = 0;
      objList[i].writeTime = 0;
    }

    return objList;
}

Object Operation::readObject(char opType, Object object, Transaction transaction){
  object.readTime = transaction.timestamp;
  object.readTimeTransactName = transaction.name;
  
  return object;
}

Object Operation::writeObject(char opType, Object object, Transaction transaction){
  object.writeTime = transaction.timestamp;
  object.writeTimeTransactName = transaction.name;

  return object;
}