#include "./object.h"
#include "./transaction.h"
#include <string>
using namespace std;

class Operation{
  public:
    char type;
    Object object;
    Transaction transaction;
};