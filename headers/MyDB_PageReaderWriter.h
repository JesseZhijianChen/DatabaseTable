
#ifndef PAGE_RW_H
#define PAGE_RW_H

#include "MyDB_PageType.h"
#include "MyDB_TableReaderWriter.h"

#define HEADER_SIZE (sizeof (MyDB_PageType) + sizeof (size_t))
#define GET_TYPE(ptr) (*((MyDB_PageType *) ptr))
#define GET_OFFSET_UNTIL_END(ptr)  (*((size_t *) (((char *) ptr) + sizeof (MyDB_PageType))))

typedef shared_ptr<MyDB_PageReaderWriter> MyDB_PageReaderWriterPtr;

class MyDB_PageReaderWriter {

public:

	// ANY OTHER METHODS YOU WANT HERE

	// empties out the contents of this page, so that it has no records in it
	// the type of the page is set to MyDB_PageType :: RegularPage
	void clear ();

	// return an itrator over this page... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// appends a record to this page... return false is the append fails because
	// there is not enough space on the page; otherwise, return true
	bool append (MyDB_RecordPtr appendMe);

	// gets the type of this page... this is just a value from an ennumeration
	// that is stored within the page
	MyDB_PageType getType ();

	// sets the type of the page
	void setType (MyDB_PageType toMe);


  MyDB_PageReaderWriter(MyDB_PageHandle, size_t);

  ~MyDB_PageReaderWriter();



private:

    //MyDB_PageType _pageType;
    //MyDB_BufferManagerPtr bufferMgr;

    MyDB_PageHandle _pageHandle;
    size_t _pageSize;

};

#endif
