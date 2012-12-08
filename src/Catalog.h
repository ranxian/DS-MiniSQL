// 存放 表的信息 的结构
typedef struct *tableInfo pTableInfo;
typedef struct
{
    char tableName[32];             // 表名，最长 32 位
    int totalColumn;                // 字段数
    int totalLenght;                // 一个记录占的字节数

    pColumnInfo primaryKey;         // 指向主键的指针
} tableInfo;

// 字段的类型
typedef enum {
    INT,
    CHAR
} columnType;

// 存放 字段的信息 的结构
typedef struct *columnInfo pColumnInfo;
typedef struct 
{
    char columnName[32];            // 字段名，最长 32 位
    int isPrimary;                  // 是否主键
    columnType colType;             // 字段类型，int/char
    int colLength;                  // 字段占的字节数
    pColumnInfo next;               // 指向下一个字段的指针
    pconstraintInfo constraint;     // 指向此字段的约束条件的指针
} columnInfo;