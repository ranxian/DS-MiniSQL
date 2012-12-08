# include <string>

/*----------constant variables for operation type------------------*/
extern const int COMPARISON = 0;
extern const int LOGIC = 1;

/*----------constant variables for indentifying comparisions------------------*/
extern const string E = 0;     // EQUAL  ==  
extern const string NE = 1; // NOT EQUAL <>
extern const string G = 2;    // GREATER THAN  >
extern const string GE = 3; // GREATER or Equal >=
extern const string L = 4;      // LESS THAN <
extern const string LE = 5;     // LESS OR EQUAL <=

struct ConditionTree
{
    ConditionTree * left;
    ConditionTree * right;
    int opType;                         // AND/OR  -- LOGIC 
                                                    // >= /> /== / <= / < / <>  -- COMPARISON
    string opName;
    string leftOperand;
    string rightOperand;
    bool end;
}