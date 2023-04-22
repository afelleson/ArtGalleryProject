// Defines the comment class in C++
// Maybe the artwork class too


// Defines functions that interact with the database:

// CommentList.addComment()
// queryAllComments(string sortBy) : CommentList
// queryWorkComments(string sortBy) : CommentList

// comment.EditRating()

// CommentList.jsonify()

#include "Comment.h"

Comment::Comment(){

};

Comment::Comment(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString rating_input,sql::SQLString isPinned_input){
    id = id_input;
    string name;
    string text;
    double x;
    double y;
    double width;
    int rating;
    bool isPinned;
}

Comment::Comment(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input){

}

string Comment::changeRating(int vote){

}

string Comment::deleteComment(int commentID){

}

string Comment::changePinStatus(int commentID){

}   
    



