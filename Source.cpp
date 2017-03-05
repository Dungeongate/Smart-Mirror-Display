#include <iostream>
#include <string>
#include <SDL.h>
#include "sqlite3.h"

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(int, char**) {
	
	
	/*SQLITE3 Database Code*/
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		/*Print Statement for Console Debugging*/
		//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		/*Print Statement for Console Debugging*/
		//fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement; Loading Test Data into Test.db File*/
	sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		/*Print Statement for Console Debugging*/
		//fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		/*Print Statement for Console Debugging*/
		//fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);

	// Initialize video only for now
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	/*SDL CODE*/
	// Create main window
	SDL_Window *main_window = SDL_CreateWindow("GUI window test text", 100, 100, 1600, 900, SDL_WINDOW_SHOWN);
	if (main_window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create renderer to draw to main window
	// Second parameter indicates index of redering driver to be used, -1 selects the first usable driver
	SDL_Renderer *main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (main_renderer == nullptr) {
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Load the bmp
	std::string imagePath = "test_img.bmp";
	SDL_Surface *test_image = SDL_LoadBMP(imagePath.c_str());
	if (test_image == nullptr) {
		SDL_DestroyRenderer(main_renderer);
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create texture from test image bmp
	SDL_Texture *test_texture = SDL_CreateTextureFromSurface(main_renderer, test_image);
	SDL_FreeSurface(test_image);
	if (test_texture == nullptr) {
		SDL_DestroyRenderer(main_renderer);
		SDL_DestroyWindow(main_window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Draw test bmp texture
	for (int i = 0; i < 3; ++i) {
		SDL_RenderClear(main_renderer);
		SDL_RenderCopy(main_renderer, test_texture, NULL, NULL);
		SDL_RenderPresent(main_renderer);
		// Wait 6 seconds
		SDL_Delay(2000);
	}

	SDL_DestroyTexture(test_texture);
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;


	
}