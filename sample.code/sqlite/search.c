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
  
  char find[50];
  
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("../..//SQLite_database/dictionary.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n",
        sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  printf("Bây giờ mày thích gì ? Nói nhanh không thì lượn.\nDạ dạ anh tìm giúp em cái từ gì ấy mà bắt đầu bằng : ");
  scanf("%s",find);

  char sql[200];
  sprintf(sql,"SELECT * FROM Dictionary WHERE INSTR(key_word,\"%s\") = 1 ;" ,find);
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

