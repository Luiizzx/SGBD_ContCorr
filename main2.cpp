#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "./transaction.h"
#include "./object.h"
#include "./operation.h"
#include "./schedule.h"
#include "./utils.h"
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

  while(count < 3){
    if(text[i] == ';'){
      count++;
    }

    i++;
  }

  i = i + 5;
  
  while(text[i] != '\0'){

  }
}