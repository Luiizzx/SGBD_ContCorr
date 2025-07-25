// to compile and run the program, copy and paste the following commands in the terminal:
// g++ main.cpp -o main; ./main
#include "./utils/utils.cpp"
#include "./operation/operations.cpp"
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

  string schedule;
  vector<string> scheduleList;

  //initializes schedules list
  while(true){
    schedule += text[i];

    if(text[i+1] == '\0'){
      scheduleList.push_back(schedule);
      break;
    }
    else if(text[i+1] == '\n'){
      scheduleList.push_back(schedule);
      schedule = "";

      i++; //ATTENTION HERE
    }

    i++;
  }

  string operationText;
  Operation newOperation;

  Schedule scheduleItem;

  scheduleItem.status = "Ok";
  scheduleItem.operations = scheduleList[0];

  char currentSchedule = scheduleList[0][2];

  scheduleItem.name = "E_" + string(1, currentSchedule);
  i = 4;

  while(true){

    if(scheduleItem.operations[i] != ' '){
      operationText += scheduleItem.operations[i];
    }

    if(scheduleItem.operations[i] == ' ' || scheduleItem.operations[i+1] == '\n' || scheduleItem.operations[i+1] == '\0'){
      newOperation.type = operationText[0];

      if(newOperation.type == 'c'){ //commit operation
        operationCounter++;
        objectList = Operation::resetList(objectList);
      }
      else{

        newObject = Utils::getObject(operationText[3], objectList);
        newTransaction = Utils::getTransaction(operationText[1], transactionList);

        newObject = Operation::validateOperation(operationText, newOperation, newObject, newTransaction, &scheduleItem, &operationCounter);
        objectList = Utils::setObject(newObject, objectList);

        cout << "ID-O: " << newObject.name << ", TS-R: " << newObject.readTime << ", TS-W: " << newObject.writeTime << ", TS-T: " << newTransaction.name << "\n";

        Utils::writeIntoFile(scheduleItem.name, operationText, operationCounter);
      }

      operationText = "";
    }

    if(i == (scheduleItem.operations.length() - 1) || scheduleItem.status == "Rollback"){
      string scheduleResult = Utils::buildScheduleText(&scheduleItem, currentSchedule, operationCounter);

      scheduleResult += "\n";
      outputFile << scheduleResult;

      scheduleIndex++;

      if(scheduleIndex == scheduleList.size()){
        break;
      }

      currentSchedule = scheduleList[scheduleIndex][2];
      scheduleItem.operations = scheduleList[scheduleIndex];
      
      scheduleItem.status = "Ok";
      scheduleItem.name = "E_" + string(1, currentSchedule);
      
      objectList = Operation::resetList(objectList);

      i = 3;
      operationCounter = 0;
      operationText = "";
    }

    i++;
  }

  cout << "Saiu do loop";
}