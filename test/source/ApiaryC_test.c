#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"

void check_trim();
void check_tokenizer();
void check_hive();
void check_hive_long();

int main()
{
  check_trim();
  check_tokenizer();
  check_hive();
  check_hive_long();

  return 0;
}

void check_trim() {
  char* str = "  Hello, world!  ";
  char* expected = "Hello, world!";
  char* actual = trim(str);

  assert(strcmp(expected, actual) == 0);
}

void check_tokenizer() {
  char* str = "ab bc cd 0.0 2 -1";
  char** expected = (char*[]){"ab", "bc", "cd", "0.0", "2", "-1", NULL};
  char** actual = tokenize(str);

  for (int i = 0; expected[i] != NULL; i++) {
    assert(strcmp(expected[i], actual[i]) == 0);
  }
}

void check_hive() {
  struct Hive* hive = hive_create();
  assert(hive_is_empty(hive));

  hive_push(hive, "Hello");
  assert(!hive_is_empty(hive));

  hive_push(hive, "world");
  hive_push(hive, "!");
  hive_pop_start(hive);
  hive_pop_end(hive);
  assert(strcmp((char*)hive->head->data, "world") == 0);

  hive_destroy(hive);
}

void check_hive_long() {
  // struct Hive* hive = hive_create();
  // assert(hive_is_empty(hive));
  // 
  // char** combs = (char*[]){"ab", "bc", "cd", "0.0", "2", "-1", NULL};
  // struct Honeycomb* nodes[6];
  // for (int i = 0; combs[i] != NULL; i++) {
  //   hive_push(hive, combs[i]);
  //   nodes[i] = hive->head;
  // }

  // hive_remove(hive, nodes[2]); // cd
  // assert(strcmp((char*)hive->head->data, "ab") == 0);
  // assert(strcmp((char*)hive->head->next->data, "bc") == 0);
  // assert(strcmp((char*)hive->head->next->next->data, "0.0") == 0);
}
