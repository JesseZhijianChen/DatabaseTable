#ifndef TABLE_ITERATER_CC
#define TABLE_ITERATER_CC

#include "MyDB_TableIterator.h"

void MyDB_TableIterator :: getNext() {

}

bool MyDB_TableIterator :: hasNext() {

}

MyDB_TableIterator :: MyDB_TableIterator() {

}

MyDB_TableIterator :: ~MyDB_TableIterator(MyDB_TablePtr table, MyDB_RecordPtr record) {
  _table = table;
  _record = record;
}

#endif
