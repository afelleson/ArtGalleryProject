
// #include <map>
// #include <algorithm>
// #include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>


#include "../httplib.h"
#include "galleryDB.h"
#include "commentEntry.h"
#include "artworkEntry.h"
#include "CTokenGenerator.h"


using namespace std;

const int port = 5001;
const string staffPassword = "GGstaff000K";


ofstream logfile; 

template <class anEntry>
string jsonResults(vector<anEntry> list) {
	// Given a list of artworkEntries or commentEntries, convert to a list of json results.

	string res = "{\"results\":[";
	for (int i = 0; i<list.size(); i++) {
		res += list[i].jsonify();
		if (i < list.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}

string jsonResult(artworkEntry work) {
	// Return info for a single artwork

	string res = "{\"result\":" + work.jsonify() + "}";
	return res;
}

string generateToken(CTokenGenerator* tokenGenerator){
	// Generate next token from the established token generator. On failure, retry a limited number of times. Return the token as a string.
	// (Should ideally be added to CTokenGenerator.cpp, but we'd have to mess with the header to get the right stuff included, so this is easier rn)
	
	int tokenLength = tokenGenerator->GetTokenLength();
	cout << "Token length: " << tokenLength << "\n";
	char* pToken = new char[tokenLength+1];
	pToken[tokenLength] = 0; // add null terminator
	bool goOn = false;
	int safetyCounter = 0;
	string token;
	while (goOn==false && safetyCounter < 20){
	if (tokenGenerator->GetNextToken(pToken)) { // attempt to generate new token
		string tokenTemp = pToken; // on success, convert char array to string (via string constructor)
		token = tokenTemp; // store token in string variable declared outside the if loop
		goOn = true;
	} else {
		cout << "Error in token generation. Trying again.\n";
		token = "***";
	}
	safetyCounter++;
	}
	return token;
}

void makeReplacements(string& text){
	// Escape single and double quotation marks so they store in the database with the escape chars
	// (necessary to avoid json parse errors).
	
	std::string toRemove = "\"";
	std::string toReplaceWith = "\\\\\\\"";
	boost::replace_all(text , toRemove , toReplaceWith);

	std::string toRemove2 = "\'";
	std::string toReplaceWith2 = "\\\'";
	boost::replace_all(text , toRemove3 , toReplaceWith3);
}

int main() {
	httplib::Server svr;

  	galleryDB database; // Comment List SQL Interface Object
	srand((unsigned int)time(NULL));
	CTokenGenerator *tokenGenerator = new CTokenGenerator(rand());
  
  	vector<commentEntry> results;

  	svr.Get("/", [](const httplib::Request & /*req*/, httplib::Response &res) {
    	res.set_header("Access-Control-Allow-Origin","*");
    	res.set_content("Comment API", "text/plain");
  	});


	// Artwork API calls

	svr.Get(R"(/artwork/getall)", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

		vector<artworkEntry> allArtworks;

		allArtworks = database.getAllArtworks();
		string json = jsonResults(allArtworks);
		res.set_content(json, "text/json");
    	res.status = 200;
  	});

	svr.Get(R"(/artwork/getbyid/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string artworkID = req.matches[1];
    
    	artworkEntry result = database.findArtworkByID(artworkID);
    	string json = jsonResult(result);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});

	// Staff abilities:
	svr.Get(R"(/artwork/add/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string title = req.matches[1];
		makeReplacements(title);
		string artist = req.matches[2];
		makeReplacements(artist);
		string year = req.matches[3];
		string path = req.matches[4];
		cout << path << endl;
		makeReplacements(path);
		cout << path << endl;
		string token = req.matches[5];

		bool tokenExists = database.checkForToken(token);
		if (tokenExists) {
			database.addArtwork(title, artist, year, path);
			res.set_content("{\"status\":\"success\"}", "text/json");
		} else {
			res.set_content("{\"status\":\"Invalid token. Try logging in again.\"}", "text/json");
		}
    
    	res.status = 200;
  	});

	svr.Get(R"(/artwork/delete/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string artworkID = req.matches[1];
		string token = req.matches[2];

		bool tokenExists = database.checkForToken(token);
		if (tokenExists) {
			database.deleteArtwork(artworkID);
			res.set_content("{\"status\":\"success\"}", "text/json");
		} else {
			res.set_content("{\"status\":\"Invalid token. Try logging in again.\"}", "text/json");
		}
    
    	res.status = 200;
  	});


	// Comment API calls

  	svr.Get(R"(/comment/fetchforwork/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");
		string work = req.matches[1];
		string sortMethod = req.matches[2];
    	results = database.findByArtworkAndSort(work, sortMethod);
    	string json = jsonResults(results);
    	res.set_content(json, "text/json");
    	res.status = 200;
  	});
  	  	
  	svr.Get(R"(/comment/add/(.*)/(.*)/(.*)/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");
		
    	string name = req.matches[1];
		makeReplacements(name);
    	string body = req.matches[2];
		makeReplacements(body);
		string artworkID = req.matches[3];
    	string x = req.matches[4];
    	string y = req.matches[5];
		string width = req.matches[6];
		cout << "here2\n"; 
		// string rating = req.matches[7];
		// string isPinned = req.matches[8];
    	database.addComment(name,body,artworkID,x,y,width,"0","0"); // 0 for initial rating and isPinned status
		cout << "here3\n"; 
    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});
 
   	svr.Get(R"(/comment/changerating/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string commentID = req.matches[1];
    	string vote = req.matches[2];
    
    	database.changeRating(commentID, vote);

    	res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	}); 

	// Staff abilities
	svr.Get(R"(/comment/delete/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string commentID = req.matches[1];
		string token = req.matches[2];
    
		bool tokenExists = database.checkForToken(token);
		if (tokenExists) {
			database.deleteComment(commentID);
			res.set_content("{\"status\":\"success\"}", "text/json");
		} else {
			res.set_content("{\"status\":\"Invalid token. Try logging in again.\"}", "text/json");
		}
    	
    	res.status = 200;
  	}); 

	svr.Get(R"(/comment/togglepin/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string commentID = req.matches[1];
		string token = req.matches[2];

		bool tokenExists = database.checkForToken(token);
		if (tokenExists) {
			database.togglePinStatus(commentID);
			res.set_content("{\"status\":\"success\"}", "text/json");
		} else {
			res.set_content("{\"status\":\"Invalid token. Try logging in again.\"}", "text/json");
		}
    
    	res.status = 200;
  	});



	// Staff login/logout API calls

	svr.Get(R"(/stafflogin/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");

    	string inputPassword = req.matches[1];
		string jsonToReturn = "";
    
		if (inputPassword==staffPassword){
			jsonToReturn = "{\"status\":\"success\",";

			string token = generateToken(tokenGenerator);  // Generate new token for this user's current session
			database.addToken(token); // Add it to the DB
			jsonToReturn += "\"token\":\"" + token + "\"}"; // append token to json response
		} else {
			jsonToReturn = "{\"status\":\"Incorrect password\"}";
		}
    	
		res.set_content(jsonToReturn, "text/json");
    	res.status = 200;
  	});

	svr.Get(R"(/stafflogout/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
    	res.set_header("Access-Control-Allow-Origin","*");
		cout << "logout API called" << endl;
    	string token = req.matches[1];
    
		database.removeToken(token);

		res.set_content("{\"status\":\"success\"}", "text/json");
    	res.status = 200;
  	});
  	 

  	cout << "Server listening on port " << port << endl;
  	svr.listen("0.0.0.0", port);

}


