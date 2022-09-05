#include <assert.h>
#include <string.h>

#include "lib.h"

void check_trim();
void check_tokenizer();

int main()
{
  check_trim();
  check_tokenizer();

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
