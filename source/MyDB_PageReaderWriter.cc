
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

class MyDB_RecordIterator;

void MyDB_PageReaderWriter :: clear () {
    GET_OFFSET_UNTIL_END(_pageHandle -> getBytes()) = HEADER_SIZE;
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
	return GET_TYPE(_pageHandle -> getBytes());
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr record) {
    shared_ptr<MyDB_RecordIterator> ret = make_shared<MyDB_RecordIterator>(_pageHandle, record);
    return ret;
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType pageType) {
    GET_TYPE(_pageHandle -> getBytes()) = pageType;
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr record) {
    char *head = (char*)_pageHandle -> getBytes();
    size_t recordSize = record -> getBinarySize();
    size_t offset = GET_OFFSET_UNTIL_END(head);
    if (recordSize + offset <= _pageSize) {
        char *writeTo = offset + head;
        char *end = (char*)record -> toBinary(writeTo);
        GET_OFFSET_UNTIL_END(head) = end - head;
        return true;
    } else {
        cout << "Fail to append record: pageSize exceeds." << endl;
        return false;
    }
}

MyDB_PageReaderWriter :: MyDB_PageReaderWriter (MyDB_PageHandle pageHandle, size_t pageSize) {
    _pageHandle = pageHandle;
    _pageSize = pageSize;
}

MyDB_PageReaderWriter :: ~MyDB_PageReaderWriter() {
    
}

#endif
