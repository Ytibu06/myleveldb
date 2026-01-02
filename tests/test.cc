#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/comparator.h"
#include <string>
#include <iostream>
using namespace std;
using namespace leveldb;
//g++ -o test test.cc ../build/libleveldb.a -I../include -pthread
int main(){
    DB* db;
    // Open
    Options options;
    options.create_if_missing=true;
    string name="testdb";
    Status status=DB::Open(options,name,&db);
    cout<<status.ToString()<<endl;

    // Put
    WriteOptions woptions;
    status=db->Put(woptions,"name","owenliang");

    // SST合并
    //db->CompactRange(nullptr, nullptr); 

    // if(options.comparator==BytewiseComparator()){
    //     cout<<"BytewiseComparator"<<endl;
    // }

    // Get
    ReadOptions roptions;
    string value;
    status=db->Get(roptions,"name",&value);
    cout<<status.ToString()<<","<<value<<endl;
    // WriteBatch
    WriteBatch batch;
    batch.Put("a","1");
    batch.Put("b","2");
    status=db->Write(woptions,&batch);
    // Delete
    db->Delete(woptions,"name");
    // Iterator
    Iterator *iter=db->NewIterator(roptions);
    iter->SeekToFirst();
    while(iter->Valid()){
        Slice key=iter->key();
        Slice value=iter->value();
        cout<<key.ToString()<<"="<<value.ToString()<<endl;
        iter->Next();
    }
    delete iter;
    delete db;
    return 0;
}