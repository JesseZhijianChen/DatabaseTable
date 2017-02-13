//
//  MyDB_TableIterator.h
//  MyDB
//
//  Created by Zhijian Chen on 2/12/17.
//  Copyright © 2017 Zhijian Chen. All rights reserved.
//

#ifndef MyDB_TableIterator_h
#define MyDB_TableIterator_h

#include "MyDB_RecordIterator.h"

class MyDB_TableIterator : public MyDB_RecordIterator {
public:
    // put the contents of the next record in the file/page into the iterator record
    // this should be called BEFORE the iterator record is first examined
    void getNext () = 0;
    
    // return true iff there is another record in the file/page
    bool hasNext () = 0;
    
    MyDB_TableIterator();
    
    ~MyDB_TableIterator();
    
private:
    
};


#endif /* MyDB_TableIterator_h */
