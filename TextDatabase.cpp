//
//  TextDatabase.cpp
//  Projec1
//
//  Created by Scott English on 3/10/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "sqlite3.h"
#include "TextDatabase.h"
#include <stdlib.h>
#include <time.h>
#include <cstring>

std::string answer;
//Constructor initiates the connection to the database and assigns a pointer to the database file location
textdatabase::textdatabase(const char *database){
    if ((sqlite3_open(database, &db))) {
        /*Print Statement for Console Debugging*/
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
}
//Text database destructor
textdatabase::~textdatabase(){
}
//Recieves the database after the SQL Statement and executes a query returning the information from the database from the second table within the database
int textdatabase::callback(void *data, int argc, char **argv, char **azColName){
    if(argc==1){ //Conditional for whether the row actually has information in it or not. 1 represents information present, 0 represents no information present within the row.
        answer=argv[0];
    }
    //If the row didn't have any information, we skip it.
    return 0;
}
//Executest the SQL statement within the built in function of sqlite3.c and calls callback to receive the database information in the designated row.
std::string textdatabase::Query(){
    int randomnumber,rc;
    char *sqlstatement;
    std::string name,statement="select * from tbl2 LIMIT 1 OFFSET ";
    
    /* initialize random seed: */
    srand (time(NULL));
    /* generate random number between 1 and number of rows in our database currently: */
    randomnumber = rand() % (count+1);
    if(randomnumber==count){ //Conditional that detects if were trying to ascess content outside of the rows that do contain content. If we have, then we pull the data from the last row.
        randomnumber -= 1;
    }
    
    //Append our random number to the SQL statement to access our data on the row specified by the random number.
    name = statement + std::to_string(randomnumber);
    sqlstatement=new char[name.length() + 1];
    std::strcpy(sqlstatement, name.c_str());
    sql= sqlstatement;
    ErrMsg=0;
    
    //Execute the SQL statement and dump info to callback function to be printed to the screen.
    rc = sqlite3_exec(db, sql, callback, (void*)data, &ErrMsg);
    quote=answer;
    return quote;
}
//CountRows counts how many rows present in our table that have actualy data in them.
void textdatabase::CountRows(){
    int rc,n;
    sql= "SELECT COUNT(*) FROM tbl2";
    ErrMsg=0;
    rc = sqlite3_exec(db, sql, callback, (void*)data, &ErrMsg);
    std::stringstream stream(answer);
    while(1) {
        stream >> n;
        if(!stream)
            break;
        count=n;
    }
}
