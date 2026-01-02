#include <iostream>
#include <string>
#include <leveldb/db.h>
#include <memory>

//g++ -o test02 test02.cc ../build/libleveldb.a -I../include -pthread
int main(){

    leveldb::Options opts;
    opts.create_if_missing = true;

    leveldb::DB *dbptr = nullptr;
    std::string name = "testdb2";
    leveldb::Status sta = leveldb::DB::Open(opts, name, &dbptr);
    if(sta.ok()){
        std::cout << "query success " << std::endl;
    }else{
        std::cout << sta.ToString() << std::endl;
    }

    std::unique_ptr<leveldb::DB> db(dbptr);

    leveldb::WriteOptions write_opts;
    write_opts.sync = false;

    //数据写入
    sta = db->Put(write_opts, "name", "leveldb2");
    sta = db->Put(write_opts, "time", "20260102");

    //数据删除
    db->Delete(write_opts, "name1");

    //数据查询PointGet
    std::string value;
    leveldb::ReadOptions read_opts;
    sta = db->Get(read_opts, "name2", &value);
    if(sta.ok()){
        std::cout << "query success, value = " << value << std::endl;
    }else if(sta.IsNotFound()){
        std::cout << "query success, value not found " << std::endl;
    }else{
        std::cout << "query falied, readson " <<sta.ToString() << std::endl;
    }

    

    return 0;
}