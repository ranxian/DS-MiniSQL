// 存放 表的信息 的结构
typedef struct
{
    char tableName[32];             // 表名，最长 32 位
    int totalColumn;                // 字段数
    int totalLenght;                // 一个记录占的字节数
    int keyAttrNum;                 // 多字段主键中字段数
    union
    {
        pColumnInfo primaryKey;     // 指向主键的指针
        filePtr filePrimaryKey;     // 先不管这个吧，貌似和文件操作有关
    };
} tableInfo;

// 存放 字段的信息 的结构
typedef struct 
{
    char columnName[32];            // 字段名，最长 32 位
    int isPrimary;                  // 是否主键
    columnType colType;             // 字段类型，int/char
    int colLength;                  // 字段占的字节数
    union
    {
        pColumnInfo next;           // 指向下一个字段的指针
        filePtr fileNext;
    }
    union
    {
        pconstraintInfo constraint; // 指向此字段的约束条件的指针
        filePtr fileConstraint;     // 先不管这个吧，貌似和文件操作有关
    };
} columnInfo;