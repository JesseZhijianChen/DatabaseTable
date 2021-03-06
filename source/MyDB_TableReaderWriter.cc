
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_TableIterator.h"


using namespace std;


MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr table, MyDB_BufferManagerPtr bufferMgr) {
    //cout<< "[MyDB_TableReaderWriter :: MyDB_TableReaderWriter] "<< "Constructor." << endl;
	_table = table;
	_bufferMgr = bufferMgr;
    _emptyRecord = make_shared <MyDB_Record> (table->getSchema());
    if (_table -> lastPage() == -1) {
        _table -> setLastPage(0);
        (*this)[0].clear();
    }
}

MyDB_TableReaderWriter :: ~MyDB_TableReaderWriter() {

}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: operator [] (size_t id) {

	PageMap :: iterator it = _pageMap.find(id);

	//pagePtr exist
	if (it != _pageMap.end()) {
		MyDB_PageReaderWriterPtr ptr = it->second;
		return *ptr;
	}
	//pagePtr doesn't exist
	else {
    MyDB_PageHandle pageHandle = _bufferMgr->getPage(_table, (long) id);
    size_t pageSize = _bufferMgr->getPageSize();
		MyDB_PageReaderWriterPtr ptr = make_shared<MyDB_PageReaderWriter>(pageHandle, pageSize);
		_pageMap[id] = ptr;
		return *ptr;
	}

}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
	return _emptyRecord;
}

MyDB_PageReaderWriter &MyDB_TableReaderWriter :: last () {
    int lastPage = _table->lastPage();
    return (*this)[lastPage];
}

void MyDB_TableReaderWriter :: append (MyDB_RecordPtr record) {
    while (!last().append(record)) {
        int last = _table -> lastPage() + 1;
        _table->setLastPage(last);
        (*this)[last].clear();
    }
}

void MyDB_TableReaderWriter :: loadFromTextFile (string fNameIn) {
    int last = getLastPage();
    for (int i = 0; i <= last; i++) {
        (*this)[i].clear();
    }
    _table -> setLastPage(0);
    string line;
    ifstream myFile;
    myFile.open(fNameIn);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            _emptyRecord -> fromString(line);
            append(_emptyRecord);
        }
    }
    myFile.close();
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr record) {
  shared_ptr<MyDB_RecordIterator> ret = make_shared<MyDB_TableIterator>(this, record);
  return ret;
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string fNameOut) {
    MyDB_RecordIteratorPtr iterator = getIterator(_emptyRecord);
    ofstream myFile (fNameOut, ofstream::out | ofstream::trunc);
    if (myFile.is_open()) {
        while (iterator->hasNext()) {
            iterator->getNext();
            myFile << _emptyRecord << endl;
        }
    }
    myFile.close();
}

int MyDB_TableReaderWriter :: getLastPage(){
    return _table -> lastPage();
}

#endif
