#include <iostream>
// #include <fstream>
// #include <map>
// #include <algorithm>
// #include <cstring>
#include "httplib.h"
#include "commentDB.cpp"

// Call functions from the other C++ files to carry out
// GET requests and return results in JSON format

// (the javascript files will receive the JSON and create
// basically identitical comment objects to the
// ones defined in CommentClasses.cpp)


string jsonCommentList(vector<commentEntry> pbList) { // produces something that looks like this: {"results":[{"username":"alex","pw":"123"},{"username":"alex2","pw":"1234"}]}
	string res = "{\"comments\":[";
	for (int i = 0; i<pbList.size(); i++) {
		res += pbList[i].json();
		if (i < pbList.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}




// /fetchForArtwork/$artworkID$/sortby/$something$
// Filter by artwork, sort by parameter


// /fetchallworks/sortby/$something$
// Get all comments, sort by parameter


// /addcomment


// /removecomment/$commentID$


// /pincomment/$commentID$


// /unpincomment/$commentID$


// /changerating/$commentID$/$vote$




