#include <stdlib.h>
#include <string>

#include "tokensDB.h"

using namespace std;

tokenDB::tokenDB() {
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

void tokenDB::addToken(string token){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
  	stmt->executeQuery("INSERT INTO Tokens (ID, Token) VALUES (NULL, '" + token + "')");
  	
}

bool tokenDB::checkForToken(string token){
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

    sql::ResultSet *queryResults = stmt->executeQuery("SELECT * FROM Tokens WHERE Token = '" + token + "'");

  	// Get first entry (technically, if there are multiple matches this will return the last one)
    if (queryResults->next()) {
    	return true;
    } else {
        return false;
    }
  	
}