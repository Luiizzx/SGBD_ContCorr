#include "./operation.h"
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

Object Operation::validateOperation(string text, Operation operation, Object object, Transaction transaction, Schedule *schedule, int *counter){
  if(object.readTimeTransactName == transaction.name || object.writeTimeTransactName == transaction.name){ //same transaction
    if(operation.type == 'r'){
      object = operation.readObject(text[1], object, transaction);
    }
    else{
      object = operation.writeObject(text[1], object, transaction);
    }
    *counter = *counter + 1;
    return object;
  }
  else if(object.writeTime < transaction.timestamp){
    if(operation.type == 'r'){
      object = operation.readObject(text[1], object, transaction);
      *counter = *counter + 1;

      return object;
    }
    else if(object.readTime < transaction.timestamp){
      object = operation.writeObject(text[1], object, transaction);
      *counter = *counter + 1;
      
      return object;
    }
  }
  *counter = *counter + 1;
  schedule->status = "Rollback";
  return object;
}