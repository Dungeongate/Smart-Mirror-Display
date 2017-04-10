//
//  TextDatabase.cpp
//  Projec1
//
//  Created by Scott English on 3/10/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <iostream>
#include <string>
#include "sqlite3.h"
#include "TextDatabase.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "Widget.h"
#include "Basic_Image.h"

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
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i<argc; i++) {
        answer=argv[i];
    }
    printf("\n");
    return 0;
}
//Executest the SQL statement within the built in function of sqlite3.c and calls callback to receive the database information
std::string textdatabase::Query(){
    sql= "SELECT * from tbl2";
    ErrMsg=0;
    int rc;
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
