
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

using namespace std;
class MyDB_RecordIterator;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr table, MyDB_BufferManager bufferMgr) {
	_table = table;
	_bufferManager = bufferMgr;
  _emptyRecord = make_shared <MyDB_Record> (myTable->getSchema());
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t id) {
	PageMap :: iterator it = _pageMap.find(id);
	//pagePtr exist
	if (it != pageMap.end()) {
		MyDB_PageReaderWriterPtr ptr = it->second;
		return *(ptr);
	}
	//pagePtr doesn't exist
	else {
    MyDB_PageHandle pageHandle = _bufferManager->get(_table, (long) id);
    size_t pageSize = _bufferManager->getPageSize();
		MyDB_PageReaderWriterPtr ptr = make_shared<MyDB_PageReaderWriter>(pageHandle, pageSize);
		pageMap[id] = ptr;
		return *(ptr);
	}
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	return _emptyRecord;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
  int lastPage = _table->lastPage();
  return _pageMap[lastPage];
}


void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {
  last()->append(record);
}

void MyDB_TableReaderWriter :: loadFromTextFile (string) {
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr record) {
  shared_ptr<MyDB_RecordIterator> ret = make_shared<MyDB_TableIterator>(_table, record);
  return ret;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string) {
}

#endif
