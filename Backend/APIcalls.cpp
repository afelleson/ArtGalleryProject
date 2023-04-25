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
		res += pbList[i].jsonify();
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


// /addcomment/


// /removecomment/$commentID$


// /pincomment/$commentID$


// /unpincomment/$commentID$


// /changerating/$commentID$/$vote$




#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "httplib.h"
#include "commentDB.h"
#include "commentEntry.h"
const int port = 5001;

using namespace std;

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

int main() {
	httplib::Server svr;

  	commentDB cdb; // Comment List SQL Interface Object
  
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
  	  	
  	// svr.Get(R"(/comment/find/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string last = req.matches[1];
    // 	results = ctdb.find(last);
    // 	string json = jsonResults(results);
    // 	res.set_content(json, "text/json");
    // 	res.status = 200;
  	// });
  	
  	// svr.Get(R"(/comment/last/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string last = req.matches[1];
    // 	results = ctdb.findByLast(last);
    // 	string json = jsonResults(results);
    // 	cout << "Last: " << json << endl;
    // 	res.set_content(json, "text/json");
    // 	res.status = 200;
  	// });
  	
  	// svr.Get(R"(/comment/first/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string first = req.matches[1];
    // 	results = ctdb.findByFirst(first);
    // 	string json = jsonResults(results);
    // 	cout << "first: " << json << endl;
    // 	res.set_content(json, "text/json");
    // 	res.status = 200;
  	// });  	

  	// svr.Get(R"(/comment/type/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string type = req.matches[1];
    // 	results = ctdb.findByType(type);
    // 	string json = jsonResults(results);
    // 	cout << "type: " << json << endl;
    // 	res.set_content(json, "text/json");
    // 	res.status = 200;
  	// });  
  	
  	svr.Get(R"(/comment/add/(.*)/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string name = req.matches[1];
    	string body = req.matches[2];
		string artworkID = req.matches[3];
    	string x = req.matches[4];
    	string y = req.matches[5];
		string width = req.matches[6];
		// string rating = req.matches[7];
		// string isPinned = req.matches[8];
    	cdb.addEntry(name,body,artworkID,x,y,width,0,0); // 0 for initial rating and isPinned status

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});
 
   	// svr.Get(R"(/comment/update/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string ID = req.matches[1];
    // 	string first = req.matches[2];
    // 	string last = req.matches[3];
    // 	string phone = req.matches[4];
    // 	string type = req.matches[5];
    // 	ctdb.editEntry(ID,first,last,phone,type);

    // 	res.set_content("{\"status\":\"success\"}", "text/json");
    // 	res.status = 200;
  	// }); 

  	// svr.Get(R"(/comment/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    // 	res.set_header("Access-Control-Allow-Origin","*");

    // 	string ID = req.matches[1];
	// 	ctdb.deleteEntry(ID);
    // 	res.set_content("{\"status\":\"success\"}", "text/json");
    // 	res.status = 200;
  	// });  
  	 
  	cout << "Server listening on port " << port << endl;
  	svr.listen("0.0.0.0", port);

}