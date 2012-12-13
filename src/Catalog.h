// 存放 表的信息 的结构
typedef struct *tableInfo pTableInfo;
typedef struct
{
    char tableName[32];             // 表名，最长 32 位
    int totalAttr;                  // 字段数
    int totalLenght;                // 一个记录占的字节数
    pAttrInfo primaryKey;           // 指向主键的指针
} tableInfo;

// 字段的类型
typedef enum {
    INT,
    CHAR
} attrType;

// 存放 字段的信息 的结构
typedef struct *AttrInfo pAttrInfo;
typedef struct 
{
    char attrName[32];              // 字段名，最长 32 位
    int isPrimary;                  // 是否主键
    int colLength;                  // 字段占的字节数
    int isUnique;                   // 是否应该具有唯一值
    attrType colType;               // 字段类型，int/char
    pAttrInfo next;                 // 指向下一个字段的指针
} attrInfo;

/***********************************************************/

class Catalog
{
public:
    bool tableExist(token);             // 返回表是否存在
    bool attrExist(token);              // 返回字段是否存在
    bool attrTypeCheck(token);          // 返回字段信息是否满足类型条件
    bool attrConstraintCheck(token);    // 返回字段信息是否满足约束条件

    pAttrInfo findAttr(token);          // 返回要求的字段的结构（指针）

    void create(token);                 // 建表
    void select(token);                 // 查表
    void insert(token);                 // 插入字段
    void delete(token);                 // 删除

    Catalog();
    ~Catalog();
private:
};