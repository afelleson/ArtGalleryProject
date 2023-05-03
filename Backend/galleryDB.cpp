#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "commentEntry.h"
#include "artworkEntry.h"
#include "galleryDB.h"


galleryDB::galleryDB() {
  	// Instantiate Driver
  	driver = sql::mariadb::get_driver_instance();
  	
 	// Configure Connection
  	// The URL or TCP connection string format is
  	// ``jdbc:mariadb://host:port/database``.
  	sql::SQLString url(db_url);

    // Use a properties map for the other connection options
  	sql::Properties my_properties({{"user", user}, {"password",pass}});
  	// Save properties in object
  	properties = my_properties;

    // Establish Connection
  	std::unique_ptr<sql::Connection> my_conn(driver->connect(db_url, properties));
    
    // Check success
    if (!my_conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}	
   	
   	// Save connection in object
   	conn = std::move(my_conn);
   	
}


vector<commentEntry> galleryDB::findByArtworkAndSort(string artworkID, string sortParam){

    // Make sure the connection is still valid
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    vector<commentEntry> resultsVec;
    // Execute query
    sql::ResultSet *queryResults = stmt->executeQuery(
			"SELECT * FROM Comments WHERE ArtworkID = '" + artworkID + "' " +
            "ORDER BY " + sortParam + " DESC, isPinned DESC");
    
    // Loop through results and push commentEntry object to a vector
    while (queryResults->next()) {
    	commentEntry entry(queryResults->getString("ID"),queryResults->getString("Name"),queryResults->getString("CommentText"),
			queryResults->getString("ArtworkID"), queryResults->getString("SelectionXCoord"), queryResults->getString("SelectionYCoord"), queryResults->getString("SelectionWidth"), queryResults->getString("Rating"), queryResults->getString("isPinned"));
	    	
	    resultsVec.push_back(entry);

    }
    return resultsVec;

}


commentEntry galleryDB::fetchByCommentID(string commentID){

	commentEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmt(conn->createStatement());
  	
    sql::ResultSet *queryResults = stmt->executeQuery("SELECT * FROM Comments WHERE ID = '" + commentID + "'");
    
    // Get first entry
    if (queryResults->next()) {
    	entry = commentEntry(queryResults->getString("ID"),queryResults->getString("Name"),queryResults->getString("CommentText"),
			queryResults->getString("ArtworkID"), queryResults->getString("SelectionXCoord"), queryResults->getString("SelectionYCoord"), queryResults->getString("SelectionWidth"), queryResults->getString("Rating"), queryResults->getString("isPinned"));
    }
    return entry;
}

void galleryDB::addComment(string name_input, string text_input, string artworkID, string x_input,string y_input, string width_input, string rating_input,string isPinned_input){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

  	cout << typeid(stmt).name() << endl;
  	stmt->executeQuery("INSERT INTO Comments (ID, Name, CommentText, ArtworkID, SelectionXCoord, SelectionYCoord, SelectionWidth, Rating, isPinned) VALUES (NUll,'"+name_input+"','"+text_input+"','"+artworkID+"','"+x_input+"','"+y_input+"','"+width_input+"','"+rating_input+"','"+isPinned_input+"')");
}


void galleryDB::changeRating(string commentID, string vote){

    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("UPDATE Comments SET Rating = Rating + " + vote + " WHERE ID='" + commentID + "'");
}


void galleryDB::changePinStatus(string commentID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("UPDATE Comments SET Rating = !Rating WHERE ID='" + commentID + "'");
}   

void galleryDB::deleteComment(string commentID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("DELETE FROM Comments WHERE ID='"+commentID+"'");    
}




artworkEntry galleryDB::findArtworkByID(string artworkID){
    artworkEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmt(conn->createStatement());
  	
    sql::ResultSet *queryResults = stmt->executeQuery("SELECT * FROM Artworks WHERE ArtworkID = '" + artworkID + "'");
    
    // Get first entry (technically, if there are multiple matches this will return the last one)
    if (queryResults->next()) {
    	entry = artworkEntry(queryResults->getString("ArtworkID"), queryResults->getString("Title"),queryResults->getString("Artist"),
        queryResults->getString("Year"), queryResults->getString("Path"));
    }
    return entry;
}

void galleryDB::addArtwork(string title_input, string artist_input, string year_input, string path_input){
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

  	cout << typeid(stmt).name() << endl;
  	stmt->executeQuery("INSERT INTO Artworks (ArtworkID, Title, Artist, Year, Path) VALUES (NULL,'"+title_input+"','"+artist_input+"','"+year_input+"','"+path_input+"')");
}

void galleryDB::editArtwork(string artworkID, string title_input, string artist_input, string year_input, string path_input){
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmt(conn->createStatement());
	
    stmt->execute("UPDATE Artworks SET Title = '" + title_input + "', Artist = '" +  artist_input + "', Year = '" +  year_input + "', Path = '" +  path_input  + "' WHERE ArtworkID='" + artworkID + "'");
}

void galleryDB::deleteArtwork(string artworkID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("DELETE FROM Artworks WHERE ArtworkID='"+artworkID+"'"); 
}

vector<artworkEntry> galleryDB::getAllArtworks(){
    // Make sure the connection is still valid
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    vector<artworkEntry> resultsVec;
    // Execute query
    sql::ResultSet *queryResults = stmt->executeQuery("SELECT * FROM Artworks");
    
    // Loop through results and push artworkEntry object to a vector
    while (queryResults->next()) {
    	artworkEntry entry(queryResults->getString("ArtworkID"),queryResults->getString("Title"),queryResults->getString("Artist"),
			queryResults->getString("Year"), queryResults->getString("Path"));
	    	
	    resultsVec.push_back(entry);

    }
    return resultsVec;

}



void galleryDB::addToken(string token){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmt(conn->createStatement());
  	stmt->executeQuery("INSERT INTO Tokens (ID, Token) VALUES (NULL, '" + token + "')");
}

bool galleryDB::checkForToken(string token){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    sql::ResultSet *queryResults = stmt->executeQuery("SELECT * FROM Tokens WHERE Token = '" + token + "'");

  	// Get first entry (technically, if there are multiple matches this will return the last one)
    if (queryResults->next()) {
    	return true;
    } else {
        return false;
    }
}

void galleryDB::removeToken(string token){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    stmt->execute("DELETE FROM Tokens WHERE Token='"+token+"'");  
}