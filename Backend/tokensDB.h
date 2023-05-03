#include <mariadb/conncpp.hpp>

using namespace std;

#ifndef TOKENDB_H // if not defined, define
#define TOKENDB_H

// global variables
#define DB_URL "jdbc:mariadb://localhost:3306/ArtGalleryProject"
#define USER "root"
#define PASS "AKFMariaDB"


class tokenDB {

public:
    tokenDB();
    void addToken(string token)
    bool checkForToken(string token)
}
#endif /* tokenDB_H */