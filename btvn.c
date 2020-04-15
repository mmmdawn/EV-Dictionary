#include "../cmake-btree/inc/btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VALUELEN 500
#define KEYLEN 12
#define BUFSIZE 1000

typedef struct {
  char *name;
  int total;
} Order;

char buffer[BUFSIZE];
void convert(Order *);
void print_error(void);
void show_value(const char *value);
void get_value(char *value, Order *tempOrder);

int main() {
  srand((unsigned)time(NULL));
  btinit();
  BTA *order;
  char value[VALUELEN], string_key[KEYLEN];
  int key = 0;
  char filename[] = "/home/dawn/penguin.fa";
  Order *tempOrder = (Order *)malloc(sizeof(Order));

  if ((order = btcrt(filename, 0, FALSE)) == NULL) {
    print_error();
    return EXIT_FAILURE;
  }

  // Nhap vao
  while (fgets(value, VALUELEN, stdin) != NULL) {
    if (strcmp(value, "\n") == 0)
      continue;
    get_value(value, tempOrder);
    convert(tempOrder);
    // co buffer
    key = 0 + rand() % 10000;
    sprintf(string_key, "%.12d", key);
    btins(order, string_key, buffer, BUFSIZE);
  }

  // Doc du lieu
  btpos(order, ZSTART);
  int temp = 0;
  while (btseln(order, string_key, buffer, BUFSIZE, &temp) == 0) {
    show_value(buffer);
    printf("%s\n\n", string_key);
  }

  free(tempOrder);
  btcls(order);
  return EXIT_SUCCESS;
}

void convert(Order *o) {
  char s_total[30];
  sprintf(s_total, "%d", o->total);
  int lenName = strlen(o->name);
  int lenTotal = strlen(s_total);
  buffer[0] = lenName;
  sprintf(buffer + 1, "%s", o->name);
  buffer[lenName + 1] = lenTotal;
  sprintf(buffer + 1 + lenName + 1, "%s", s_total);
}

void show_value(const char *value) {
  int lenName = value[0];
  int lenTotal = value[lenName + 1];
  char tempName[VALUELEN];
  char tempTotal[KEYLEN];
  memcpy(tempName, value + 1, lenName);
  tempName[lenName] = '\0';
  memcpy(tempTotal, value + lenName + 1 + 1, lenTotal);
  tempTotal[lenTotal] = '\0';
  printf("%s\n%s\n", tempName, tempTotal);
}

void get_value(char *value, Order *tempOrder) {
  if (strrchr(value, '\n') != NULL)
    value[strlen(value) - 1] = '\0';
  char *s = strrchr(value, ' ');
  *s = '\0';
  tempOrder->name = value;
  tempOrder->total = atoi(s + 1);
}

void print_error(void) {
  int errorcode, ioerr;
  char fname[ZRNAMESZ], msg[ZMSGSZ];
  btcerr(&errorcode, &ioerr, fname, msg);
  fprintf(stderr, "btsort: btree error (%d) [%s] - %s\n", errorcode, fname,
          msg);
}
