#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>

//#include "mysql_connection.h"
//#include "mysql_driver.h"
#include <mariadb/conncpp.hpp>

#include "commentEntry.h"


// This is what would normally go in a commentDB.h file
#ifndef COMMENTDB_H // if not defined, define
#define COMMENTDB_H

// global variables
#define DB_URL "jdbc:mariadb://localhost:3306/ChatApp"
#define USER "root"
#define PASS "AKFMariaDB"

using namespace std;


class commentDB {
public:
    commentDB();
    
    // sortParam can be "Rating" or "ID" (TODO: add random option https://vladmihalcea.com/sql-order-by-random/)
    vector<commentEntry> findByArtworkAndSort(string artworkID, string sortParam);
    commentEntry fetchByCommentID(string commentID);
    void addComment(string id_input, string name_input, string text_input, string artworkID, string x_input,string y_input, string width_input, string rating_input,string isPinned_input);
    void changeRating(string commentID, string newRating);
    void deleteComment(string commentID);
    void changePinStatus(string commentID);  

private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* commentDB_H */



commentDB::commentDB() {
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


vector<commentEntry> findByArtworkAndSort(string artworkID, string sortParam){

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
			queryResults->getString("ArtworkID"), queryResults->getString("SelectionXCoord"), queryResults->getString("SelectionYCoord"), queryResults->getString("SelelectionWidth"), queryResults->getString("Rating"), queryResults->getString("isPinned"));
	    	
	    resultsVec.push_back(entry);

    }
    return resultsVec;

}


commentEntry commentDB::fetchByCommentID(string commentID){

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
			queryResults->getString("ArtworkID"), queryResults->getString("SelectionXCoord"), queryResults->getString("SelectionYCoord"), queryResults->getString("SelelectionWidth"), queryResults->getString("Rating"), queryResults->getString("isPinned"));
    }
    return entry;
}


void commentDB::addComment(string id_input, string name_input, string text_input, string artworkID, string x_input,string y_input, string width_input, string rating_input,string isPinned_input){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());

  	
  	stmnt->executeQuery("INSERT INTO Comments(ID, Name, CommentText, ArtworkID, SelectionXCoord, SelectionYCoor, SelectionWidth, Rating, isPinned) VALUES ('"+id_input+"','"+name_input+"','"+artworkID+"','"+x_input+"','"+y_input+"','"+width_input+"','"+rating_input+"','"+isPinned_input+"')");
}


void commentDB::changeRating(string commentID, string newRating){

    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("UPDATE Comments SET Rating = '" + newRating + "' WHERE ID='" + commentID + "'");
}


void commentDB::changePinStatus(string commentID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("UPDATE Comments SET Rating = !Rating WHERE ID='" + commentID + "'");
}   

void commentDB::deleteComment(string commentID){
    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(db_url, properties));
    if (!conn) {
        cerr << "Invalid database connection" << endl;
        exit (EXIT_FAILURE);
    }

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());

    stmt->execute("DELETE FROM ChatAppUsers WHERE ID='"+commentID+"'");    
}