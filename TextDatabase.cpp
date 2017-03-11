//
//  TextDatabase.cpp
//  Projec1
//
//  Created by Scott English on 3/10/17.
//  Copyright © 2017 Scott English. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "sqlite3.h"
#include "TextDatabase.h"


textdatabase::textdatabase(const char *database){
    if (!(sqlite3_open(database, &db))) {
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

int textdatabase::callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for (i = 0; i<argc; i++) {
        printf("%s = %s\n",azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
void textdatabase::getstatement(char *statement){
    sql=statement;
    ErrMsg=0;
    int rc;
    rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
    if (rc != SQLITE_OK) {
        /*Print Statement for Console Debugging*/
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
    }
    else {
        /*Print Statement for Console Debugging*/
        fprintf(stdout, "Records created successfully\n");
    }
}
void textdatabase::getQuote(){
    sql= "SELECT * from COMPANY";
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
}
