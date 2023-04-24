// Defines the comment class in C++
// Maybe the artwork class too


// Defines functions that interact with the database:

// commentEntryList.addcommentEntry()
// queryAllComments(string sortBy) : commentEntryList
// queryWorkComments(string sortBy) : commentEntryList

// comment.EditRating()

// commentEntryList.jsonify()

#include "commentEntry.h"

commentEntry::commentEntry(){
    id = ""; // Q: what to do here?
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
    x = 0;
    y = 0;
    width = 0;
    rating = rating_input; // potential default to add later: 0
    isPinned = isPinned_input;  // potential default to add later: 0
}

commentEntry::commentEntry(sql::SQLString id_input, sql::SQLString name_input, sql::SQLString text_input, sql::SQLString x_input,sql::SQLString y_input, sql::SQLString width_input, sql::SQLString rating_input,sql::SQLString isPinned_input){
    id = id_input;
    name = name_input;
    text = text_input;
    if (text_input==""){
        cerr << "Warning: no comment text provided" << endl;
    }
    artworkID = artworkID_input;
    x = x_input;
    y = y_input;
    width = width_input;
    if (width=="0"){
        cerr << "Warning: zero-width selection given" << endl;
    }
    rating = rating_input;
    isPinned = isPinned_input;

    // TODO: use this template to type-check inputs before/while converting them to the right type.
    // Alternatively (and better), do not have the inputs be SQLStrings
    // We don't want this to actually fail tho. Or do we?
    // try {
    //     userParamType = stoi(userParamTypeString); // this will throw an invalid_argument if userParamTypeString is not easy to convert to an int
    //     if ((userParamType > 3) || (userParamType < 1)){
    //       throw invalid_argument("Input too large.");
    //     } else {
    //       keepgoing  = 1;
    //     }
    //   }
    //   catch (invalid_argument) {
    //     cout << "Please type 1, 2, or 3.\n";
    //     cin >> userParamTypeString;
    //   }
}

bool commentEntry::containsSelection(int commentID){
    if (width == "0") {
        return false;
    } else {
        return true;
    }
}

string userEntry::asText() {
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

string userEntry::asJson() {
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
