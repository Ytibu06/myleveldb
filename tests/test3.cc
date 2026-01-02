#include <string>
#include <iostream>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <memory>

int main(int argc, const char argv[]){

    leveldb::Options options;
    options.create_if_missing = false;
    leveldb::DB *dbptr = nullptr;
    std::string dbname = "testdb2";

    leveldb::Status s = leveldb::DB::Open(options, dbname, &dbptr);
    if(s.ok()){
        std::cout << "leveldb open success" << std::endl;
    }else{
        std::cout << "leveldb open failed" << std::endl;
    }

    std::unique_ptr<leveldb::DB> db(dbptr);

    leveldb::WriteOptions write_opts;
    write_opts.sync = true;

    //使用WriteBatch打包多个操作，保证原子写入
    leveldb::WriteBatch batch;

    db->Put(write_opts, "name", "leveldb");
    db->Put(write_opts, "time", "20230102");
    db->Delete(write_opts, "addr");

    leveldb::Status sta = db->Write(write_opts, &batch);

    return 0;
}