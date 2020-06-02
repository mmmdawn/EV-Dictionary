#include "../../sqlite/sqlite3.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  sqlite3 *db;
  char *err_msg = 0;
  int rc = sqlite3_open("test.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  char sql[21000] = "DROP TABLE IF EXISTS Dict;"
        "CREATE TABLE Dict(key_word TEXT,meaning TEXT);";
  rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

  char temp_kword[30];
  char temp_meaning[20000];

  FILE *fptr = fopen("/home/dawn/test.txt", "r");
  while (!feof(fptr)){
    fscanf(fptr, "%[^@-*]", temp_kword);
    fgets(temp_meaning, 20000, fptr);
    sprintf(sql, "INSERT INTO Dict VALUES(\"%s\", \"%s\");", temp_kword, temp_meaning);
    /* printf("%s\n",sql); */
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  }

  /* sprintf(sql, "INSERT INTO Dict VALUES('about', \"@about /ə'baut/\n*  phó từ\n- xung quanh, quanh quẩn, đây đó, rải rác\n=he is somewhere about+ anh ta ở quanh quẩn đâu đó\n=rumours are about+ đây đó có tiếng đồn (về việc gì)\n- đằng sau\n=about turn!+ đằng sau quay\n- khoảng chừng, gần\n=about forty+ khoảng 40\n=it is about two o'clock+ bây giờ khoảng chừng hai giờ\n- vòng\n=to go a long way about+ đi đường vòng xa\n!about and about\n- (từ Mỹ,nghĩa Mỹ) rất giống nhau\n!to be about\n- bận (làm gì)\n- đã dậy được (sau khi ốm)\n- có mặt\n!about right\n- đúng, đúng đắn\n- tốt, được\n*  giới từ\n- về\n=to know much about Vietnam+ biết nhiều về Việt Nam\n=what shall we write about?+ chúng ta sẽ viết về cái gì bây giờ?\n- quanh quất, quanh quẩn đây đó, rải rác\n=to walk about the garden+ đi quanh quẩn trong vườn\n- xung quanh\n=the trees about the pound+ cây cối xung quanh ao\n- khoảng chừng, vào khoảng\n=about nightfall+ vào khoảng chập tối\n- bận, đang làm (gì...)\n=he is still about it+ hắn hãy còn bận làm việc đó\n=to go about one's work+ đi làm\n- ở (ai); trong người (ai), theo với (ai)\n=I have all the documents about me+ tôi có mang theo đầy đủ tài liệu\n=there's something nice about him+ ở anh ta có một cái gì đó hay hay\n!to be about to\n- sắp, sắp sửa\n=the train is about to start+ xe lửa sắp khởi hành\n=man about town+ tay ăn chơi, tay giao thiệp rộng\n=what are you about?+ anh muốn gì?, anh cần gì?\n- (từ hiếm,nghĩa hiếm) anh đang làm gì đấy?\n!what about?\n- (xem) what\n*  ngoại động từ\n- lái (thuyền...) theo hướng khác\n@Chuyên ngành kinh tế\n-chừng\n-độ chừng\n-khoảng\n-vào khoảng\n@Chuyên ngành kỹ thuật\n-khoảng\n-xung quanh\n@Lĩnh vực: toán & tin\n-đối với\n-khoảng chừng\n-nói về\n@Lĩnh vực: xây dựng\n-về\")"); */
  /* rc = sqlite3_exec(db, sql, 0, 0, &err_msg); */

  if (rc != SQLITE_OK ) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}
