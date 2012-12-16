/*
Record.cpp

未知：
lastInsert
totalLenth
*/

#include<iostream>
using namespace std;


filePtr Record::Insert(recInfo &a)
{
    cellInfo *temp = a.head;
    filePtr insertPlace = findPlace();
    void *ptr2write = (void *) insertPlace;
    int *p = &(temp->value);
    memWrite((void *)insertPlace, sizeof(filePtr), ptr2write);
    ptr2write += sizeof(filePtr);
    while (temp)
    {
        memWrite(p, temp->colLength, ptr2write);
        switch (temp->colType)
        {
            case 'i':
                ptr2write += temp->colLength;
                break;
            case 'c':
                ptr2write += temp->colLength + 1;
        }
        temp = temp->next;
    }
    return insertPlace;
}

filePtr Record::findPlace()
{
    if(firstDel == lastDel == 0)
    {
        switch(colType)
        {
            case 'i':
                insertPlace = lastInsert + totalLenth + sizeof(filePtr);
                break;
            case 'c':
                insertPlace = lastInsert + totalLenth + 1 + sizeof(filePtr);
        }
        insertPlace = lastInsert + totalLenth + sizeof(filePtr); 

    }
    else
    {
        insertPlace = firstDel;
        firstDel = firstDel->filePtr;
    }
    return insertPlace;
}

void Record::Delete(fileAddr &delTarget)
{
    filePtr *temp = (filePtr *)delTarget.changeToMem();
    if (firstDel == lastDel == 0)
    {
        firstDel = temp;
        temp->filePageId = 0;
        temp->offset = 0;

    }
    else
    {
        filePtr *p1 = (filePtr *)lastDel.changeToMem();
        filePtr *p1 = (filePtr *)delTarget.changeToMem();
        *p1 = delTarget;
        lastDel = delTarget;
        p2->filePageId = 0;
        p2->offset = 0;
    }


    
}

recInfo *Select(fileAddr &, selectRecInfo &) const
{
    recInfo *RPrecInfo = new recInfo;

}

void Record::Update(fileAddr& UpdateFAddr, recInfo& UpdateInfo)
{
    cellInfo* temp = UpdateInfo.head;
    UpdateFAddr = filePtr->changeToMem();
    int *i = &(temp->value);
    while (temp)
    {
        memWrite(i, temp->colLength, sizeof(filePtr) + priorLength);
        temp = temp->next;
    }

    fileAddr UFATemp = UpdateFAddr;
    
    UFATemp.ShiftOffset(sizeof (fileAddr));

}

void Record::Print(filePtr, recInfo &a)
{
    filePtr *temp = a.head;
    
}




