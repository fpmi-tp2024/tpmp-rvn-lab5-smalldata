#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <sstream>
#include <iostream>


class Database {
private:
    sqlite3* db;
public:
    explicit Database(const std::string& dbPath) { sqlite3_open(dbPath.c_str(), &db); };
    ~Database() { sqlite3_close(db); };
    bool execute(const std::string& sql, std::string &output);
    static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif
