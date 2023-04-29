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

    cout << "Select an option (1-search by id): "; // , 2-search last, 3-search type, 4-add, 5-edit, 6-delete, 7-end): ";
    cin >> o;

    while (o!="7") {

        if (o=="1") {
            // cout << "Enter ID of the comment to find:";
            // string commentid;
            // getline(cin,commentid);

            // result = commentdb.fetchByCommentID(commentid);

            // cout << result.textify() << endl;

            string artworkid = "1";

            artresult = commentdb.findArtworkByID(artworkid);
            commentdb.addArtwork("title", "artist", "00", "path");
            commentdb.editArtwork("1","newtitle", "newartist", "2005", "path");

            cout << artresult.textify() << endl;






	        // results = commentdb.fetchByCommentID(commentid);

            // for (int i = 0; i<results.size(); i++) {
            //     cout << results[i].text() << endl;
            //     cout << typeid(results[i].text()).name() << endl;

            //     vector<string> listOfResults;

            //     listOfResults = split (results[i].text(), " | ");

            //     for (int j = 0; j < listOfResults.size(); j++) {
            //         cout << listOfResults[j] << endl;
            //     }
            // }
      } 
    //   else if (o=="2") {

    //     cout << "Enter last name to find:";
    //     string lastMatch;
    //     getline(cin,lastMatch);

    //     results = commentdb.findByLast(lastMatch);

    //     for (int i = 0; i<results.size(); i++) {
	// 		cout << results[i].text() << endl;
    //     }
    //   } else if (o=="3") {
    //     cout << "Enter type to find:";
    //     string typeMatch;
    //     getline(cin,typeMatch);
    //     results = commentdb.findByType(typeMatch);

    //     for (int i = 0; i<results.size(); i++) {
	// 		cout << results[i].text() << endl;
    //     }
    //   } else if (o=="4") {

    //     cout <<"Enter a first name to add: ";
    //     string first,last,phone,type,email,linkedin;
    //     getline(cin,first);
    //     cout << "Enter a last name to add: ";
    //     getline(cin,last);
    //     cout << "Enter a phone number: ";
    //     getline(cin,phone);
    //     cout << "lastly, enter a type: ";
    //     getline(cin,type);
    //     cout << "Enter an email address: ";
    //     getline(cin,email);
    //     cout << "Enter a linkedin url: ";
    //     getline(cin,linkedin);

    //     commentdb.addEntry(first,last,phone,type,email,linkedin);
    //     cout << "Entry added" << endl;

    //   } else if (o=="5") {
    //     string first,last,phone,type,email,linkedin, IDnum;
    //     cout << "Leave blank to keep same."  << endl;
    //     cout << "Enter an ID number to edit: ";
    //     getline(cin,IDnum);
    //     contactEntry entry=commentdb.fetchEntry(IDnum);
    //     cout  << IDnum << endl;
    //     if (entry.ID.empty()) {
    //     	cout << "Entry with ID = " << IDnum << " not found!" << endl;
    //     } else {
    //     	cout << "Editing: " << entry.text() << endl;
    //     	cin.ignore();
    //     	cout << "Enter a new first name("+entry.first+"): ";
    //     	getline(cin,first);
    //     	if (first.size()>0) entry.first = first;

    //     	cout << "Enter a new last name("+entry.last+"): ";
    //     	getline(cin,last);
    //     	if (last.size()>0) entry.last = last;
        	
    //     	cout << "Enter a new phone number("+entry.phone+"): ";
    //     	getline(cin,phone);
    //     	if (phone.size()>0) entry.phone = phone;

    //     	cout << "Enter a new type("+entry.type+"): ";
    //     	getline(cin,type);
    //     	if (type.size()>0) entry.type = type;

    //       cout << "Enter an email address("+entry.email+"): ";
    //     	getline(cin,email);
    //     	if (email.size()>0) entry.email = email;

    //       cout << "Enter a LinkedIn url("+entry.linkedin+"): ";
    //     	getline(cin,linkedin);
    //     	if (linkedin.size()>0) entry.linkedin = linkedin;
        	
    //     	commentdb.editEntry(entry.ID,entry.first,entry.last,entry.phone,entry.type,entry.email,entry.linkedin);
    //     	cout << "Done!" << endl;
    //     }
    //   } else if (o=="6") {

    //     string IDnum;
    //     cout << "Enter an ID number to delete: ";
    //     getline(cin,IDnum);
    //     commentdb.deleteEntry(IDnum);
    //     cout << "Deleted!" << endl;
    //   }
      cout << "Select an option (1-search first, 2-search last, 3-search type, 4-add, 5-edit, 6-delete, 7-end): ";
      getline(cin,o);

    }
return 0;
}