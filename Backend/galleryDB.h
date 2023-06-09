#include <mariadb/conncpp.hpp>

#include "commentEntry.h"
#include "artworkEntry.h"

// This is what would normally go in a galleryDB.h file
#ifndef COMMENTDB_H // if not defined, define
#define COMMENTDB_H

// global variables
#define DB_URL "jdbc:mariadb://localhost:3306/ArtGalleryProject"
#define USER "root"
#define PASS "AKFMariaDB"

using namespace std;


class galleryDB {
public:
    galleryDB();

    vector<artworkEntry> getAllArtworks();
    artworkEntry findArtworkByID(string artworkID);
    void addArtwork(string title_input, string artist_input, string year_input, string path_input);
    void editArtwork(string artworkID, string title_input, string artist_input, string year_input, string path_input);
    void deleteArtwork(string artworkID);
    // void deactivateArtwork(string artworkID); // would be nice, but we won't have time to build a nice interface for this (a list of all the info from all the artworks in the database and checkboxes)
    // void activateArtwork(string artworkID);
    
    vector<commentEntry> findByArtworkAndSort(string artworkID, string sortParam); // sortParam can be "Rating" or "ID" (TODO: add random option https://vladmihalcea.com/sql-order-by-random/)
    commentEntry fetchByCommentID(string commentID);
    void addComment(string name_input, string text_input, string artworkID, string x_input,string y_input, string width_input, string rating_input,string isPinned_input);
    void changeRating(string commentID, string vote); // vote must be an integer
    void deleteComment(string commentID);
    void togglePinStatus(string commentID);  

    void addToken(string token);
    bool checkForToken(string token);
    void removeToken(string token);

private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* galleryDB_H */
