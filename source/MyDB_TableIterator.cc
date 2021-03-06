#ifndef TABLE_ITERATER_CC
#define TABLE_ITERATER_CC

#include "MyDB_TableIterator.h"
#include "MyDB_PageReaderWriter.h"

void MyDB_TableIterator :: getNext() {
    if (_currentPageIterator->hasNext()) {
        _currentPageIterator->getNext();
        return;
    } else {
        while (_current_page < _tableReaderWriter -> getLastPage()) {
            _currentPageIterator = (*_tableReaderWriter)[++_current_page].getIterator(_record);
            if (_currentPageIterator -> hasNext()) {
                _currentPageIterator -> getNext();
                return;
            } else {
                continue;
            }
        }
    cout << "Error: reach the end of the table." << endl;
    }
}

bool MyDB_TableIterator :: hasNext() {

    if (_currentPageIterator -> hasNext()) {
        return true;
    }
    while (_current_page < _tableReaderWriter -> getLastPage()) {
        _currentPageIterator = (*_tableReaderWriter)[++_current_page].getIterator(_record);
        if (_currentPageIterator -> hasNext()) {
            return true;
        }
    }
    return false;
}

MyDB_TableIterator :: MyDB_TableIterator(MyDB_TableReaderWriter* tableReaderWriter, MyDB_RecordPtr record) {
    _tableReaderWriter = tableReaderWriter;
    _record = record;
    _current_page = 0;
    _currentPageIterator = ((*tableReaderWriter)[0]).getIterator(record);
}

MyDB_TableIterator :: ~MyDB_TableIterator() {

}



#endif
