//
// Created by David on 17/9/2017.
//

#include "HashTableEntry.h"
#include "string.h"

HashTableEntry::HashTableEntry()
{
    primerIdxEntry=-1;
    actualIdxEntry=-1;
}

char * HashTableEntry::toChar()
{
    int pos=0;
    char * data = new char[8];
    memcpy(&data[pos],&primerIdxEntry,4);
    pos+=4;
    memcpy(&data[pos],&actualIdxEntry,4);
    pos+=4;
}
void HashTableEntry::initFromChar(char * data)
{
    int pos=0;
    memcpy(&primerIdxEntry,&data[pos],4);
    pos+=4;
    memcpy(&actualIdxEntry,&data[pos],4);
    pos+=4;
}