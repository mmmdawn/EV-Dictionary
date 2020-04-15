#include "phonebook.h"
#include "../cmake-btree/inc/btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printError(void);
void printMenu(void);
void skipNewLine(void);
void convertToValue(const Node);
void printValue(const char *);

int main() {
  char filename[] = "/home/dawn/phonebook.bt";
  char tempName[NAMELEN], tempEmail[EMAILLEN], tempNumber[NUMBERLEN];
  Node tempNode = (Node)malloc(sizeof(struct phoneBookNode));
  BTA *book;
  int key = 0;
  int status = 0;
  int intTemp = 0;

  // khởi tạo
  btinit();
  if ((book = btopn(filename, 0, FALSE)) == NULL)
    if ((book = btcrt(filename, 0, FALSE)) == NULL)
      goto fin;

  while (key != 5) {
    printMenu();
    scanf("%d", &key);
    switch (key) {
    case 1:
      skipNewLine();
      printf("\n\n-----Thêm/Cập nhật thông tin liên lạc-----\n");
      printf("Tên: ");
      tempNode->name = fgets(tempName, NAMELEN, stdin);
      tempNode->name[strlen(tempNode->name) - 1] = '\0';

      printf("Email: ");
      tempNode->email = fgets(tempEmail, EMAILLEN, stdin);
      tempNode->email[strlen(tempNode->email) - 1] = '\0';

      printf("SDT: ");
      tempNode->number = fgets(tempNumber, NUMBERLEN, stdin);
      tempNode->number[strlen(tempNode->number) - 1] = '\0';

      // key = name ; value = email + number
      convertToValue(tempNode);
      status = btins(book, tempNode->name, buffer, BUFSIZE);
      if (status != 0) {
        printError();
        break;
      }
      break;

    case 2:
      printf("\n\n-----Tìm kiếm theo tên-----\n");
      skipNewLine();
      printf("Tên người muốn tìm: ");
      fgets(tempName, NAMELEN, stdin);
      tempName[strlen(tempName) - 1] = '\0';
      if (btsel(book, tempName, buffer, BUFSIZE, &intTemp) == 0) {
        printf("\nTìm thấy:\n\n");
        printf("Tên: %s\n", tempName);
        printValue(buffer);
      } else {
        printf("\nKhông tìm thấy người này\n");
      }
      break;

    case 3:
      printf("\n\n-----Hiển thị toàn bộ danh bạ-----\n");
      btpos(book, ZSTART);
      while (btseln(book, tempName, buffer, BUFSIZE, &intTemp) == 0) {
        printf("Tên: %s\n", tempName);
        printValue(buffer);
      }

      break;
    case 4:
      printf("\n\n-----Xóa một thông tin liên lạc-----\n");
      skipNewLine();
      printf("Tên người muốn xóa : ");
      fgets(tempName, NAMELEN, stdin);
      tempName[strlen(tempName) - 1] = '\0';
      if (btdel(book, tempName) != 0) {
        printError();
        break;
      }
      printf("Xóa thành công\n");
      break;

    case 5:
      free(tempNode);
      btcls(book);
      break;

    default:
      printf("Không có lựa chọn này, nhập lại !\n");
    }
  }

  return EXIT_SUCCESS;
fin:
  printError();
  return EXIT_FAILURE;
}

void printError(void) {
  int errorcode, ioerr;
  char fname[ZRNAMESZ], msg[ZMSGSZ];
  btcerr(&errorcode, &ioerr, fname, msg);
  fprintf(stderr, "btsort: btree error (%d) [%s] - %s\n", errorcode, fname,
          msg);
}

void printMenu(void) {
  printf("\n------------------\n");
  printf("1. Thêm/Cập nhật thông tin liên lạc\n");
  printf("2. Tìm kiếm theo tên\n");
  printf("3. Hiển thị toàn bộ danh bạ\n");
  printf("4. Xóa một thông tin liên lạc\n");
  printf("5. Thoát\n");
  printf("Lựa chọn: ");
}

void skipNewLine(void) {
  int c;
  while ((c = getchar()) != '\n') {
  }
}

void convertToValue(const Node sample) {
  int lenEmail = strlen(sample->email);
  int lenNumber = strlen(sample->number);
  buffer[0] = lenEmail;
  sprintf(buffer + 1, "%s", sample->email);
  buffer[lenEmail + 1] = lenNumber;
  sprintf(buffer + 1 + lenEmail + 1, "%s", sample->number);
}

void printValue(const char *value) {
  int lenEmail = value[0];
  int lenNumber = value[lenEmail + 1];
  char email[EMAILLEN], number[NUMBERLEN];
  memcpy(email, value + 1, lenEmail);
  email[lenEmail] = '\0';
  memcpy(number, value + 1 + lenEmail + 1, lenNumber);
  number[lenNumber] = '\0';
  printf("Email: %s\nSDT: %s\n\n", email, number);
}
