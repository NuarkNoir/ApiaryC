#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

void start_repl(struct Hive* hive);

int main(int argc, const char* argv[])
{
  if (argc > 2)
  {
    printf("Usage: %s [filename]\n", argv[0]);
  }
  
  struct Hive* hive = hive_create();
  if (argc == 2) {
    char** lines = read_file(argv[1]);
    for (int i = 0; lines[i] != NULL; i++) {
      char** tokens = tokenize(lines[i]);
      parse_line(tokens, hive);
    }
  } else {
    start_repl(hive);
  }

  return 0;
}

void start_repl(struct Hive* hive) {
  char line[1024];
  while (1) {
    printf(">>> ");
    fgets(line, 1024, stdin);
    char* trimmed = trim(line);
    if (strlen(trimmed) < 2) continue;
    char** tokens = tokenize(trimmed);
    parse_line(tokens, hive);
  }
}
