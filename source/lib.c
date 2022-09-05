#include "lib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef _MSC_VER
#include "microsoft.mixin.c"
#endif

char* trim_start(char* str) 
{
  while (isspace((unsigned char)*str)) 
  {
    str++;
  }

  return str;
}

char* trim(char* str)
{
  if (str == NULL)
    return NULL;

  char* end;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  // Write new null terminator
  *(end + 1) = 0;

  return str;
}

char** read_file(char* filename)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) return NULL;

  char** lines = NULL;
  size_t size = 0;

  char* line = NULL;
  size_t len = 0;
  signed long long read;

  while ((read = getline(&line, &len, file)) != -1)
  {
    line = trim_start(line);
    if (line[0] == '#') continue;

    line = trim(line);
    if (strlen(line) == 0) continue;

    lines = realloc(lines, sizeof(char*) * ++size);
    if (lines == NULL) return NULL;

    lines[size - 1] = line;
    line = NULL;
  }

  free(line);
  fclose(file);

  return lines;
}

char** tokenize(char* str)
{
  char** tokens = NULL;
  char* token = strtok(str, " ");

  int i = 0;
  while (token != NULL) 
  {
    tokens = realloc(tokens, sizeof(char*) * ++i);

    if (tokens == NULL) return NULL;

    tokens[i - 1] = token;

    token = strtok(NULL, " ");
  }

  tokens = realloc(tokens, sizeof(char*) * (i + 1));
  tokens[i] = 0;

  return tokens;
}