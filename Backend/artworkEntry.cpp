// Defines the artwork class in C++
// Maybe the artwork class too


// Defines functions that interact with the database:

#include <iostream>
#include "artworkEntry.h"

artworkEntry::artworkEntry(){
    id = ""; // Q: what to do here?
    title = "";
    artist = "";
    year = "";
    path = "";
};

artworkEntry::artworkEntry(sql::SQLString id_input, sql::SQLString title_input, sql::SQLString artist_input, sql::SQLString year_input, sql::SQLString path_input){
    id = id_input;
    title = title_input;
    artist = artist_input;
    year = year_input;
    path = path_input;
}

string artworkEntry::textify() {
	string result = id;
	result += " | ";
	result += title;
	result += " | ";
	result += artist;
	result += " | ";
	result += year;
	result += " | ";
	result += path;
	return result;
}

string artworkEntry::jsonify() {
	string result = "{\"ID\":\"" + id + "\",";
	result += "\"title\":\"" + title + "\",";
	result += "\"artist\":\"" + artist + "\",";
	result += "\"year\":\"" + year + "\",";
    result += "\"path\":\"" + path + "\"}";
	return result;

}
