#include "../../mylib/sqlite3.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char* trim(char* token);

int main(int argc, char const *argv[])
{
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("dictionary.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  char sql[11000] = "DROP TABLE IF EXISTS Dictionary;"
        "CREATE TABLE Dictionary(key_word TEXT,meaning TEXT);";
  rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

  char temp_kword[100];
  char temp_meaning[10000];

  FILE *fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    printf("Cannot open the text file\n");
    exit(-1);
  }
  while (!feof(fptr)){
    fscanf(fptr, "%[^/\n]", temp_kword);
    fscanf(fptr, "%[^@]", temp_meaning);
    sprintf(sql, "INSERT INTO Dictionary VALUES(\"%s\",\"%s\");", (trim(temp_kword))+1, trim(temp_meaning));
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  }

  if (rc != SQLITE_OK ) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

char* trim(char* token){
  while (isspace((unsigned)token[0])) token++;
  while (isspace((unsigned)token[strlen(token)-1])) token[strlen(token)-1] = '\0';
  return strdup(token);
}