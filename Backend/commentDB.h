#include <mariadb/conncpp.hpp>

#include "commentEntry.h"


// This is what would normally go in a commentDB.h file
#ifndef COMMENTDB_H // if not defined, define
#define COMMENTDB_H

// global variables
#define DB_URL "jdbc:mariadb://localhost:3306/ArtGalleryProject"
#define USER "root"
#define PASS "AKFMariaDB"

using namespace std;


class commentDB {
public:
    commentDB();
    
    // sortParam can be "Rating" or "ID" (TODO: add random option https://vladmihalcea.com/sql-order-by-random/)
    vector<commentEntry> findByArtworkAndSort(string artworkID, string sortParam);
    commentEntry fetchByCommentID(string commentID);
    void addComment(string name_input, string text_input, string artworkID, string x_input,string y_input, string width_input, string rating_input,string isPinned_input);
    void changeRating(string commentID, string newRating);
    void deleteComment(string commentID);
    void changePinStatus(string commentID);  

private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* commentDB_H */