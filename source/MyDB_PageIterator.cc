//
//  MyDB_PageIterator.cpp
//  MyDB
//
//  Created by Zhijian Chen on 2/12/17.
//  Copyright © 2017 Zhijian Chen. All rights reserved.
//

#ifndef PAGE_ITERATER_CC
#define PAGE_ITERATER_CC

#include "MyDB_PageIterator.h"


void MyDB_PageIterator :: getNext (){
    //cout <<" [MyDB_PageIterator :: getNext ()] " << endl;
    if (hasNext()) {
        char *head = (char*)_pageHandle -> getBytes();
        char *readFrom = head + _current_offset;
        char *next = (char*)_record -> fromBinary(readFrom);
        _current_offset = next - head;
        //cout << " [MyDB_PageIterator :: getNext ()] " << endl;
    } else {
        cout<< "Reach the end of the page." << endl;
    }
}

bool MyDB_PageIterator :: hasNext (){
    
    //cout <<" [MyDB_PageIterator :: hasNext ()] "<< endl;
    //current offset is" << _current_offset << endl;
    //cout <<" [MyDB_PageIterator :: hasNext ()] the end of offset is" << GET_OFFSET_UNTIL_END(_pageHandle -> getBytes()) << endl;
    return _current_offset < GET_OFFSET_UNTIL_END(_pageHandle -> getBytes());
}

MyDB_PageIterator :: MyDB_PageIterator(MyDB_PageHandle pageHandle, MyDB_RecordPtr record) {

    _current_offset = HEADER_SIZE;
    _pageHandle = pageHandle;
    _record = record;
}

MyDB_PageIterator :: ~MyDB_PageIterator() {

}









#endif
