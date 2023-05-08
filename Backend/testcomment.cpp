// This program tests a couple key functions for interacting with the database.

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <mariadb/conncpp.hpp>

#include "galleryDB.h"

using namespace std;

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


int main(){
    galleryDB commentdb;
    vector<commentEntry> results;
    commentEntry result;
    artworkEntry artresult;
    string o;

    cout << "Contacts test program" << endl;

    string prompt = "Select an option (1-search for comment by id, 2-run artwork functions, 7-end): ";
    cout << prompt; // , 2-search last, 3-search type, 4-add, 5-edit, 6-delete, 7-end): ";
    cin >> o;

    while (o!="7") {

        if (o=="1") {
            cout << "Enter ID of the comment to find:";
            string commentid;
            getline(cin,commentid);

            result = commentdb.fetchByCommentID(commentid);

            cout << result.textify() << endl;
        } else if (o=="2") {

            string artworkid = "1";

            artresult = commentdb.findArtworkByID(artworkid);
            commentdb.addArtwork("title", "artist", "00", "path");
            commentdb.editArtwork("1","newtitle", "newartist", "2005", "path");

            cout << artresult.textify() << endl;
        }
        cout << prompt;
        getline(cin,o);
    } 
return 0;
}