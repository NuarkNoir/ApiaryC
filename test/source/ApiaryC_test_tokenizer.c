#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  char* str = "ab bc cd 0.0 2 -1";
  char** expected = (char*[]){"ab", "bc", "cd", "0.0", "2", "-1", NULL};
  char** actual = tokenize(str);

  for (int i = 0; expected[i] != NULL; i++) {
    assert(strcmp(expected[i], actual[i]) == 0);
  }

  return 0;
}
