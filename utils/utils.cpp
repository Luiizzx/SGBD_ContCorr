#include "./utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
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

  string textBuilder = schedule->name + "-" + schedule->status + (schedule->status == "Rollback" ? to_string(operationCount - 1) : "");
  cout << textBuilder << "\n";
  return textBuilder;
}

void Utils::writeIntoFile(string scheduleName, string operationText, int count){
  string fileDirectory = "./output/" + string(1, operationText[3]) + ".txt";

  //std::ios:app helps writing in the right place, depending if the file is
  //empty (write into first line) or not (write into last line)
  ofstream file(fileDirectory, std::ios::app); 

  string outText = scheduleName + "," + (operationText[0] == 'w' ? "write," : "read,") + to_string(count - 1) + "\n";
  file << outText;
}