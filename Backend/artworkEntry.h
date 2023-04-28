// #include <mariadb/conncpp.hpp>
// #include <string>
// using namespace std;

// #ifndef artworkEntry_H // If artworkEntry class not already defined...
// #define artworkEntry_H // define it

// class artworkEntry {
// public:
//     // Default constructor
//     artworkEntry();
//     // Constructor for artworks without a partial-image selection
//     // zeroSQLString = "0" // ???? (to set as the default for )
//     artworkEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString rating_input,sql::SQLString isPinned_input);
//     // Constructor for artworks with a partial-image selection
//     artworkEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input);
//     bool containsSelection(string artworkID);
//     string textify();
//     string jsonify();
    
// private:
//     string id;
//     string name;
//     string text;
//     string artworkID;
//     string x;
//     string y;
//     string width;
//     string rating;
//     string isPinned;
// };

// #endif /* End artworkEntry_H define-if block */

