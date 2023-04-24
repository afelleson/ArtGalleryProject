#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef commentEntry_H // If commentEntry class not already defined...
#define commentEntry_H // define it

class commentEntry {
public:
    // Default constructor
    commentEntry();
    // Constructor for comments without a partial-image selection
    // zeroSQLString = "0" // ???? (to set as the default for )
    commentEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString rating_input,sql::SQLString isPinned_input);
    // Constructor for comments with a partial-image selection
    commentEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input);
    bool containsSelection(string commentID);
    string textify();
    string jsonify();
    
private:
    string id;
    string name;
    string text;
    string artworkID;
    string x;
    string y;
    string width;
    string rating;
    string isPinned;
};

#endif /* End commentEntry_H define-if block */

