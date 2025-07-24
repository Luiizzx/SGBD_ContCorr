// to compile and run the program, copy and paste the following commands in the terminal:
// g++ main.cpp -o main; ./main
// this program will use wait-die logic for timestamp based concurrency-control
#include "./utils/utils.h"
#include "./models/schedule.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(void){
  int i = 0, j = 0, scheduleIndex = 0;
  int operationCounter = 0, lineCounter = 0;

  char auxChar;
  string auxString;
	stringstream inputfileContent;

  ifstream inputFile("./in.txt");
  ofstream outputFile("./out.txt");

  //reads from file into string
  inputfileContent << inputFile.rdbuf();
	string text = inputfileContent.str();

  Object newObject;
  vector<Object> objectList;
  
  Transaction newTransaction;
  vector<Transaction> transactionList;

  //initializes all objects
  while(text[i] != '\n'){

    if(text[i] == ',' || text[i] == ';'){
      newObject.name = auxChar;
      newObject.readTime = 0;
      newObject.writeTime = 0;

      objectList.push_back(newObject);
      auxChar = ' ';
    }
    else if(text[i] != ' '){
      auxChar = text[i];
    }

    i++;
  }

  i = i + 1;

  //initializes all transactions with their timestamps
  while(lineCounter < 2){

    if(text[i] != ' ' && text[i] != ',' && text[i] != ';'){
      auxString += text[i];
    }

    if(text[i] == ',' || text[i] == ';'){

      if(lineCounter == 0){ //transactions line actions
        newTransaction.name = auxString[1];
        transactionList.push_back(newTransaction);
        auxString = "";
      }
      else{ //timestamps line actions
        transactionList[j].timestamp = stoi(auxString);
        auxString = "";
        j++;
      }
    }

    if(text[i] == ';'){
      lineCounter++;
    }
    i++; 
  }

  i = i + 1;
  j = 0;

  string schedule;
  vector<string> scheduleList;

  while(text[i] != '\0'){
    schedule += text[i];

    if(text[i+1] == '\n'){
      scheduleList.push_back(schedule);
      schedule = "";

      j++;
      i++;
    }
    i++;
  }

  string operationText;
  Operation newOperation;

  Schedule scheduleItem; 

  scheduleItem.status = "Ok";
  scheduleItem.operations = scheduleList[0];

  char currentSchedule = scheduleList[0][2];

  i = 4;

  while(scheduleIndex < scheduleList.size()){

    if(scheduleItem.operations[i] != ' '){
      operationText += scheduleItem.operations[i];
    }
    
    if(scheduleItem.operations[i] == ' ' || scheduleItem.operations[i+1] == '\n' || scheduleItem.operations[i+1] == '\0'){
      newOperation.type = operationText[0];

      newObject = getObject(operationText[3], objectList);
      
      newTransaction = getTransaction(operationText[1], transactionList);

      //a transaction has been commited, so its important to check if any objects hold a related timestamp
      if(newOperation.type == 'c'){
        objectList = newOperation.resetList(objectList);
      }
      else if(newObject.readTimeTransactName == newTransaction.name || newObject.writeTimeTransactName == newTransaction.name){ 
        operationCounter++;

        if(newOperation.type == 'r'){
          newObject = newOperation.readObject(operationText[1], newObject, newTransaction);
        }
        else{
          newObject = newOperation.writeObject(operationText[1], newObject, newTransaction);
        }

        objectList = setObject(newObject, objectList);
      }
      else if(newObject.writeTime < newTransaction.timestamp){
        operationCounter++;

        if(newOperation.type == 'r'){
          newObject = newOperation.readObject(operationText[1], newObject, newTransaction);
        }
        else if(newObject.readTime < newTransaction.timestamp){
          newObject = newOperation.writeObject(operationText[1], newObject, newTransaction);
        }

        objectList = setObject(newObject, objectList);
      }
      else{
        //Rollback
        scheduleItem.status = "Rollback";
      }
      cout << "ID-Objeto: " << newObject.name << ", TS-Read: " << newObject.readTime << ", TS-Write: " << newObject.writeTime << "\n";
      operationText = "";
    }

    if(i == scheduleItem.operations.length() || scheduleItem.status == "Rollback"){
      string scheduleResult = scheduleItem.buildScheduleText(currentSchedule, operationCounter);

      scheduleResult += "\n";
      outputFile << scheduleResult;

      scheduleIndex++;

      if(scheduleIndex == scheduleList.size()){
        break;
      }

      operationCounter = 0;
      operationText = "";

      currentSchedule = scheduleList[scheduleIndex][2];
      scheduleItem.operations = scheduleList[scheduleIndex];
      scheduleItem.status = "Ok";
      objectList = newOperation.resetList(objectList);
      i = 3; 
    }

    i++;
  }

  cout << "Saiu do loop";
}