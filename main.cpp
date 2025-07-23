// to compile and run the program, copy and paste the following commands in the terminal:
// g++ main.cpp -o main; ./main
// this program will use wait-die logic for timestamp based concurrency-control
#include "./utils/utils.h"
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(void){
  int i = 0, j = 0, auxCount = 0;
  int operationCount = 0;
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
    
    if(text[i] != ',' && text[i] != ' ' && text[i] != ';'){
      auxChar = text[i];
    }

    if(text[i] == ',' || text[i] == ';'){
      newObject.name = auxChar;
      newObject.readTime = 0;
      newObject.writeTime = 0;

      objectList.push_back(newObject);
      auxChar = ' ';
    }
    i++;
  }

  i = i + 1;

  //initializes all transactions with their timestamps
  while(auxCount < 2){

    if(text[i] != ' ' && text[i] != ',' && text[i] != ';'){
      auxString += text[i];
    }

    if(text[i] == ',' || text[i] == ';'){

      if(auxCount == 0){ //transactions line actions
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
      auxCount++;
    }
    i++; 
  }

  string operationText;
  Operation newOperation;

  // allows skipping right to the operations start
  // i = i + 5;

  //this is just for test of schedules. Must read them properly from .txt file
  string scheduleText = "r3(X) w3(Y) c1 r1(X) w1(Y) c2 r2(Y) w2(Z) c3";
  i = 0;

  //runs from first operation of the first schedule until EOF
  //while(text[i] != '\0){}
  while(scheduleText[i] != ';'){

    if(scheduleText[i] != ' '){
      operationText += scheduleText[i];
    }
    
    if(scheduleText[i] == ' ' || scheduleText[i+1] == '\n' || scheduleText[i+1] == '\0'){
      newOperation.type = operationText[0];

      newObject = getObject(operationText[3], objectList);
   
      newTransaction = getTransaction(operationText[1], transactionList);

      //TODO: if the current operation is being done by the same transaction as previous, can just store the timestamp
      //and add timestamp reset in case of commits by a transaction whose timestamp is set to an object

      //a transaction has been commited, so its important to check if any objects hold a related timestamp
      if(newOperation.type == 'c'){
        cout << newObject.readTimeTransactName;
        if(operationText[1] == newObject.readTimeTransactName){
          newObject.readTime = 0;
        }
        if(operationText[1] == newObject.writeTimeTransactName){
          newObject.writeTime = 0;
        }
      }
      //object has never been read or timestamp wins
      else if(newOperation.type == 'r' && newObject.writeTime < newTransaction.timestamp){
        newObject.readTime = newTransaction.timestamp;
        newObject.readTimeTransactName = newTransaction.name;
      }
      //object has never been written or timestamp wins
      else if(newOperation.type == 'w' && (newObject.writeTime < newTransaction.timestamp && newObject.readTime < newTransaction.timestamp)){
        newObject.writeTime = newTransaction.timestamp;
        newObject.writeTimeTransactName = newTransaction.name;
      }
      else{
        cout << operationText;
        cout << "Rollback-" << operationCount;
        break;
        //Rollback, since transaction has no priority
      }

      operationCount++;
      objectList = setObject(newObject, objectList);
      operationText = "";
    }

    if(scheduleText[i] == '\n'){
      operationText = "";
      i = i + 4; 
    }

    i++;
  }
}