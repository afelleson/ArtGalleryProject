// This program defines the artworkEntry class, which stores all the information about an artwork pulled from the database

#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef artworkEntry_H // If artworkEntry class not already defined...
#define artworkEntry_H // define it

class artworkEntry {
public:
    // Default constructor
    artworkEntry();
    artworkEntry(sql::SQLString id_input, sql::SQLString title_input, sql::SQLString artist_input, sql::SQLString year_input, sql::SQLString path_input);
    string textify();
    string jsonify();
    
private:
    string id;
    string title;
    string artist;
    string year;
    string path;
};

#endif /* End artworkEntry_H define-if block */

