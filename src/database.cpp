#include "database.h"


bool Database::execute(const std::string& sql, std::string &output) {
    char* errMsg = nullptr;
    std::ostringstream oss;
    int rc = sqlite3_exec(db, sql.c_str(), callback, &oss, &errMsg);
    output = oss.str();
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int Database::callback(void *data, int argc, char **argv, char **azColName) {
    std::ostringstream &out = *static_cast<std::ostringstream*>(data);
    for (int i = 0; i < argc; i++) {
        out << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    out << "\n";
    return 0;
}
