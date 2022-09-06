#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  char* str = "  Hello, world!  ";
  char* expected = "Hello, world!";
  char* actual = trim(str);

  assert(strcmp(expected, actual) == 0);

  return 0;
}
