#include <string.h>

#include "lib.h"

int main(int argc, const char* argv[])
{
  struct library lib = create_library();

  (void)argc;
  (void)argv;

  return strcmp(lib.name, "ApiaryC") == 0 ? 0 : 1;
}
