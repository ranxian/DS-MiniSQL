# include <string>

/*----------constant variables for indentifying  attribute type------------------*/
extern const int VARCHAR = 0;
extern const int VARINT = 1;

struct Table
{
   string name;
   struct attribute
   {
    string name;                        // name of attribute
    int attributeType;              // VARCHAR  or VARINT
    bool unique;                        
    int charNum;                        // the maximum number of char that can be stored
    bool isIndex;
    string indexName;               
   } attributes[32];
   int primaryKey;
   string value[32];                    // UNKNOWN 
};