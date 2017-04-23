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
    else {
        /*Print Statement for Console Debugging*/
        fprintf(stderr, "Opened database successfully\n");
    }
}
textdatabase::~textdatabase(){
}
//Recieves the database after the SQL Statement and executes a query returning the information from the database from the second table within the database
int textdatabase::callback(void *data, int argc, char **argv, char **azColName){
    fprintf(stderr, "%s: ", (const char*)data);
    if(argc==1){
        answer=argv[0];
    }
    printf("\n");
    return 0;
}
//Executest the SQL statement within the built in function of sqlite3.c and calls callback to receive the database information
std::string textdatabase::Query(){
    int randomnumber,rc;
    char *sqlstatement;
    std::string name,statement="select * from tbl2 LIMIT 1 OFFSET ";
    /* initialize random seed: */
    srand (time(NULL));
    /* generate random number between 1 and number of rows in our database currently: */
    randomnumber = rand() % (count+1);
    if(randomnumber==count){
        randomnumber -= 1;
    }
    name = statement + std::to_string(randomnumber);
    sqlstatement=new char[name.length() + 1];
    std::strcpy(sqlstatement, name.c_str());
    std::cout<<sqlstatement;
    sql= sqlstatement;
    ErrMsg=0;
    rc = sqlite3_exec(db, sql, callback, (void*)data, &ErrMsg);
    if (rc != SQLITE_OK) {
        /*Print Statement for Console Debugging*/
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
    }
    else {
        /*Print Statement for Console Debugging*/
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    quote=answer;
    return quote;
}
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
