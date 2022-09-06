#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

void check_trim();
void check_tokenizer();
void check_hive();
void check_hive_long();
void check_melipona();
void check_hive_attributic();

int main()
{
  check_trim();
  check_tokenizer();
  check_hive();
  check_hive_long();
  check_melipona();
  check_hive_attributic();

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
  struct Hive* hive = hive_create();
  assert(hive_is_empty(hive));
  
  char** combs = (char*[]){"ab", "bc", "cd", "0.0", "2", "-1", NULL};
  struct Honeycomb* nodes[6];
  for (int i = 0; combs[i] != NULL; i++) {
    hive_push(hive, combs[i]);
    nodes[i] = hive->head;
  }
  hive_reverse(hive);

  hive_remove(hive, nodes[2]); // cd
  assert(strcmp((char*)hive->head->data, "ab") == 0);
  assert(strcmp((char*)hive->head->next->data, "bc") == 0);
  assert(strcmp((char*)hive->head->next->next->data, "0.0") == 0);
}

void check_melipona() {
  struct Plane* plane = plane_create(1, 2, 3, 4, "Hello, world!");
  struct Train* train = train_create(5, 6, 7, "Hello, world!");

  assert(is_plane(plane) && !is_train(plane));
  assert(is_train(train) && !is_plane(train));

  assert(is_plane_attr("len") && is_plane_attr("cap"));
  assert(is_train_attr("cnt") && !is_plane_attr("cnt"));
  assert(is_attr("len") && is_attr("cnt") && is_attr("dest"));

  int* len = (int*)get_attr(plane, "len");
  assert(*len == 1);
  char* dest = *(char**)get_attr(train, "dest");
  assert(strcmp(dest, "Hello, world!") == 0);

  assert(attr_eq_int(plane, "len", 1));
  assert(attr_eq_int(train, "cnt", 5));
  assert(attr_eq_str(plane, "dest", "Hello, world!"));
}

void check_hive_attributic() {
  struct Hive* hive = hive_create();

  hive_push(hive, plane_create(1, 2, 3, 4, "Hello, world!"));
  hive_push(hive, train_create(5, 6, 7, "Hello, world!"));
  hive_push(hive, plane_create(1, 3, 5, 4, "Hello, world!"));
  hive_push(hive, train_create(5, 6, 7, "Hello, world!"));
  char* v = "2";
  hive_remove_if_attr(hive, "cap", "<", v);
}
