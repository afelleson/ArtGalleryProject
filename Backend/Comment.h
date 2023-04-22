#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef COMMENT_H // if Comment class not already defined...
#define COMMENT_H // define it

class Comment {
public:
    Comment();
    Comment(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString rating_input,sql::SQLString isPinned_input); // for comments without a partial-image selection
    Comment(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input); // for comments with a partial-image selection
    string changeRating(int vote);
    string deleteComment(int commentID);
    string changePinStatus(int commentID);      
     

private:
    int id;
    string name;
    string text;
    double x;
    double y;
    double width;
    int rating;
    bool isPinned;

};

#endif /* End COMMENT_H define-if block */

