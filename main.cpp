// to compile and run the program, copy and paste the following commands in the terminal:
// g++ main.cpp -o main; ./main
// this program will use wait-die logic for timestamp based concurrency-control
#include "./models/transaction.h"
#include "./models/object.h"
#include "./models/operation.h"
#include "./models/schedule.h"
#include "./utils/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(void){
  int i = 0, j = 0, count = 0;
  char auxChar;
  string auxString;

	stringstream inputfileContent;

  ifstream inputFile("./in.txt");
  ofstream outputFile("./out.txt");

  //reads from file into string
  inputfileContent << inputFile.rdbuf();
	string text = inputfileContent.str();

  //writes into file
  outputFile << text;

  Object newObject;
  Transaction newTransaction;

  vector<Object> objectList;
  vector<Transaction> transactionList;

  //initializes all objects
  while(text[i] != '\n'){
    
    if(text[i] != ',' && text[i] != ' '){
      auxChar += text[i];
    }

    if(text[i] == ','){
      newObject.name = auxChar;
      newObject.readTime = 0;
      newObject.writeTime = 0;
      objectList.push_back(newObject);
    }
    i++;
  }

  i = i + 1;

  while(count < 2){

    if(text[i] != ' ' && text[i] != ','){
      auxString += text[i];
    }

    if(text[i] == ';'){
      count++;
    }

    if(count == 1 && text[i] == ','){
      newTransaction.name = auxString;
      transactionList.push_back(newTransaction);
      auxString = "";
    }

    if(count == 2 && text[i] == ','){
      transactionList[j].timestamp = stoi(auxString);
      auxString = "";
    }

    i++; 
  }

  i = i + 5;
  Schedule newSchedule;
  vector<Schedule> scheduleList;

  string operationText;
  Operation newOperation;

  //runs starting from first operationText to end of each schedule, until EOF
  while(true){

    if(text[i] != ' '){
      operationText += text[i];
    }

    if(text[i] == ' ' || text[i+1] == '\n' || text[i+1] == '\0'){
      newOperation.type = operationText[0];

      newObject = getObject(operationText[3], objectList);
      newTransaction = getTransaction(operationText[2], transactionList);

       //object has never been read or timestamp wins
      if(newOperation.type == 'r' && (newObject.readTime == 0 || newObject.writeTime < newTransaction.timestamp)){
        newObject.readTime = newTransaction.timestamp;
      }

      //object has never been written or timestamp wins
      if(newOperation.type == 'w' && (newObject.writeTime == 0 || newObject.readTime < newTransaction.timestamp)){
        newObject.writeTime = newTransaction.timestamp;
      }
      else{
        //Rollback, since transaction has no priority
      }

      objectList = setObject(newObject, objectList);
      operationText = "";
    }

    //clears the schedule to make a new one
    if(text[i] == '\n'){
      scheduleList.push_back(newSchedule);
      
      //resets the schedule and the operationText, as we ended one schedule
      newSchedule.flush(newSchedule.operations);
      operationText = "";
      i = i + 4; 
    }

    //adds the last schedule
    if(text[i+1] == '\0'){
      scheduleList.push_back(newSchedule);
      break;
    }

    operationText += text[i];
    i++;
  }
}