// This program defines the commentEntry class, which stores all the information about a comment pulled from the database

#include <iostream>
#include "commentEntry.h"

commentEntry::commentEntry(){
    id = ""; //(?)
    name = "";
    text = "";
    artworkID = "";
    x = "";
    y = "";
    width = "";
    rating = "";
    isPinned = "";
};

commentEntry::commentEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString rating_input,sql::SQLString isPinned_input){
    id = id_input;
    name = name_input;
    text = text_input;
    if (text_input==""){
        cerr << "Warning: no comment text provided" << endl;
    }
    artworkID = artworkID_input;
    x = "0";
    y = "0";
    width = "0";
    rating = rating_input; // potential default (currently handled in APIcalls.cpp): 0
    isPinned = isPinned_input;  // potential default (currently handled in APIcalls.cpp): 0
}

commentEntry::commentEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString artworkID_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input){
    id = id_input;
    name = name_input;
    text = text_input;
    // if (text_input==""){
    //     cerr << "Warning: no comment text provided" << endl;
    // }
    artworkID = artworkID_input;
    x = x_input;
    y = y_input;
    width = width_input;
    // if (width=="0"){
        // cerr << "Warning: zero-width selection given" << endl;
    // }
    rating = rating_input;
    isPinned = isPinned_input;
}

bool commentEntry::containsSelection(string commentID){
    if (width == "0") {
        return false;
    } else {
        return true;
    }
}

string commentEntry::textify() {
	string result = id;
	result += " | ";
	result += name;
	result += " | ";
	result += text;
	result += " | ";
	result += artworkID;
	result += " | ";
	result += x;
    result += " | ";
	result += y;
    result += " | ";
	result += width;
    result += " | ";
	result += rating;
    result += " | ";
	result += isPinned;
	return result;

}

string commentEntry::jsonify() {
	string result = "{\"ID\":\"" + id + "\",";
	result += "\"name\":\"" + name + "\",";
	result += "\"commentText\":\"" + text + "\",";
	result += "\"artworkID\":\"" + artworkID + "\",";
    result += "\"x\":\"" + x + "\",";
    result += "\"y\":\"" + y + "\",";
    result += "\"width\":\"" + width + "\",";
    result += "\"rating\":\"" + rating + "\",";
	result += "\"isPinned\":\"" + isPinned + "\"}";
	return result;

}
