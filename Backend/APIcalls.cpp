
// #include <map>
// #include <algorithm>
// #include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "../httplib.h"
#include "galleryDB.h"
#include "commentEntry.h"
#include "artworkEntry.h"

// Call functions from the other C++ files to carry out
// GET requests and return results in JSON format

// (the javascript files will receive the JSON and create
// basically identitical comment objects to the
// ones defined in CommentClasses.cpp)


// /fetchForArtwork/$artworkID$/sortby/$something$
// Filter by artwork, sort by parameter


// /fetchallworks/sortby/$something$
// Get all comments, sort by parameter


// /addcomment/


// /removecomment/$commentID$


// /pincomment/$commentID$


// /unpincomment/$commentID$


// /changerating/$commentID$/$vote$


using namespace std;

const int port = 5001;

ofstream logfile; 

string jsonResults(vector<commentEntry> pbList) {
	string res = "{\"results\":[";
	for (int i = 0; i<pbList.size(); i++) {
		res += pbList[i].jsonify();
		if (i < pbList.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}

string jsonResult(artworkEntry work) {
	string res = "{\"result\":";
	res += work.jsonify();
	
	res += "}";
	return res;
}

int main() {
	httplib::Server svr;

  	galleryDB cdb; // Comment List SQL Interface Object
  
  	vector<commentEntry> results;

  	svr.Get("/", [](const httplib::Request & /*req*/, httplib::Response &res) {
    	res.set_header("Access-Control-Allow-Origin","*");
    	res.set_content("Comment API", "text/plain");
  	});

  	svr.Get(R"(/comment/fetchforwork/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");
		string work = req.matches[1];
		string sortMethod = req.matches[2];
    	results = cdb.findByArtworkAndSort(work, sortMethod);
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});
  	  	
  	
  	svr.Get(R"(/comment/add/(.*)/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");
		cout << "here1\n"; 

    	string name = req.matches[1];
    	string body = req.matches[2];
		string artworkID = req.matches[3];
    	string x = req.matches[4];
    	string y = req.matches[5];
		string width = req.matches[6];
		cout << "here2\n"; 
		// string rating = req.matches[7];
		// string isPinned = req.matches[8];
    	cdb.addComment(name,body,artworkID,x,y,width,"0","0"); // 0 for initial rating and isPinned status
		cout << "here3\n"; 
    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});
 
   	svr.Get(R"(/comment/changerating/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string commentID = req.matches[1];
    	string vote = req.matches[2];
    
    	cdb.changeRating(commentID, vote);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 



	svr.Get(R"(/artwork/getbyid/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string artworkID = req.matches[1];
    
    	artworkEntry result = cdb.findArtworkByID(artworkID);
    	string json = jsonResult(result);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});



    // void addArtwork(string title_input, string artist_input, string year_input, string path_input);
    // void editArtwork(string artworkID, string title_input, string artist_input, string year_input, string path_input);
    // void deleteArtwork(string artworkID);
    // vector<artworkEntry> getAllArtworks();



  	// svr.Get(R"(/comment/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string ID = req.matches[1];
	// 	cdb.deleteEntry(ID);
    // 	res.set_content("{\"status\":\"success\"}", "text/json");
    // 	res.status = 200;
  	// });  
  	 
  	cout << "Server listening on port " << port << endl;
  	svr.listen("0.0.0.0", port);

}