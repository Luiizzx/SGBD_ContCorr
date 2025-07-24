#include "./transactOperations.cpp"
#include "./models/schedule.h"
using namespace std;

Object handleOperation(string text, Operation operation, Object object, Transaction transaction, Schedule *schedule){
  if(object.readTimeTransactName == transaction.name || object.writeTimeTransactName == transaction.name){
    if(operation.type == 'r'){
      object = operation.readObject(text[1], object, transaction);
    }
    else{
      object = operation.writeObject(text[1], object, transaction);
    }
    return object;
  }
  else if(object.writeTime < transaction.timestamp){
    if(operation.type == 'r'){
      object = operation.readObject(text[1], object, transaction);
    }
    else if(object.readTime < transaction.timestamp){
      object = operation.writeObject(text[1], object, transaction);
    }
    return object;
  }

  schedule->status = "Rollback";
  return object;
}