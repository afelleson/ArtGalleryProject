#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "commentEntry.h"
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
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

    vector<commentEntry> resultsVec;
    // Execute query
    sql::ResultSet *queryResults = stmnt->executeQuery(
			"SELECT * FROM Comments WHERE ArtworkID = '" + artworkID + "' " +
            "ORDER BY " + sortParam + " DESC");
    
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

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
  	
    sql::ResultSet *queryResults = stmnt->executeQuery("SELECT * FROM Comments WHERE ID = '" + commentID + "'");
    
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

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

  	cout << typeid(stmnt).name() << endl;
  	stmnt->executeQuery("INSERT INTO Comments (ID, Name, CommentText, ArtworkID, SelectionXCoord, SelectionYCoord, SelectionWidth, Rating, isPinned) VALUES (NUll,'"+name_input+"','"+text_input+"','"+artworkID+"','"+x_input+"','"+y_input+"','"+width_input+"','"+rating_input+"','"+isPinned_input+"')");
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

    stmt->execute("DELETE FROM ChatAppUsers WHERE ID='"+commentID+"'");    
}




vector<artworkEntry> galleryDB::findArtworkByID(string artworkID){
    artworkEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
  	
    sql::ResultSet *queryResults = stmnt->executeQuery("SELECT * FROM Artworks WHERE ID = '" + artworkID + "'");
    
    // Get first entry
    if (queryResults->next()) {
    	entry = artworkEntry(queryResults->getString("Title"),queryResults->getString("Artist"),queryResults->getString("Year"),
			queryResults->getString("ArtworkID"));
    }
    return entry;
}

void galleryDB::addArtwork(string title_input, string artist_input, string year_input){
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

  	cout << typeid(stmnt).name() << endl;
  	stmnt->executeQuery("INSERT INTO Artworks (ArtworkID, Title, Artist, Year) VALUES (NULL,'"+title_input+"','"+artist_input+"','"+year_input+"')");
}

void galleryDB::editArtwork(string artworkID, string title_input, string artist_input, string year_input){
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
	
    stmt->execute("UPDATE Artworks SET Title = " + title_input + ", Artist = " +  artist_input + ", Year = " +  year_input + " WHERE ID='" + artworkID + "'");
}

void galleryDB::deleteArtwork(string artworkID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("DELETE FROM Artworks WHERE ID='"+artworkID+"'"); 
}

vector<artworkEntry> galleryDB::getAllArtworks(){
    // Make sure the connection is still valid
    if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

    vector<artworkEntry> resultsVec;
    // Execute query
    sql::ResultSet *queryResults = stmnt->executeQuery("SELECT * FROM Artworks");
    
    // Loop through results and push artworkEntry object to a vector
    while (queryResults->next()) {
    	artworkEntry entry(queryResults->getString("ArtworkID"),queryResults->getString("Title"),queryResults->getString("Artist"),
			queryResults->getString("Year"));
	    	
	    resultsVec.push_back(entry);

    }
    return resultsVec;

}