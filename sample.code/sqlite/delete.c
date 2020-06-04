

#include "../../mylib/sqlite3.h"

#include <stdio.h>

int callback(void *NotUsed, int argc, char **argv,
          char **azColName) {
  NotUsed = 0;
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(void) {
  
  char delete[50];
  
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("../..//SQLite_database/dictionary.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n",
        sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  printf("What do you want ?\nI want to delete : ");
  scanf("%s",delete);

  char sql[200];
  sprintf(sql,"DELETE FROM Dictionary WHERE key_word = \"%s\" ;", delete);
  rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }
  sqlite3_close(db);
  return 0;
}

