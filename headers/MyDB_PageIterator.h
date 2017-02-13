//
//  MyDB_PageIterator.h
//  MyDB
//
//  Created by Zhijian Chen on 2/12/17.
//  Copyright © 2017 Zhijian Chen. All rights reserved.
//

#ifndef PAGE_ITERATER_H
#define PAGE_ITERATER_H

#include "MyDB_RecordIterator.h"
#include "MyDB_PageHandle.h"
#include "MyDB_Record.h"
#include "MyDB_PageReaderWriter.h"




class MyDB_PageIterator : public MyDB_RecordIterator {
public:
    // put the contents of the next record in the file/page into the iterator record
    // this should be called BEFORE the iterator record is first examined
    void getNext () = 0;

    // return true iff there is another record in the file/page
    bool hasNext () = 0;

    MyDB_PageIterator(MyDB_PageHandle pageHandle, MyDB_RecordPtr record);

    ~MyDB_PageIterator();

private:

    size_t _current_offset;

    MyDB_PageHandle _pageHandle;

    MyDB_RecordPtr _record;

};


#endif /* MyDB_PageIterator_h */
