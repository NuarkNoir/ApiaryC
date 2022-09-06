#include "lib.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#ifdef _MSC_VER
#include "microsoft.mixin.c"
#endif

#include "melipona.h"

bool _is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

char* trim_start(char* str) 
{
  while (_is_whitespace(*str)) str++;

  return str;
}

char* trim(char* str)
{
  if (str == NULL)
    return NULL;

  str = trim_start(str);

  char* end;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && _is_whitespace(*end)) end--;

  // Write new null terminator
  *(end + 1) = 0;

  return str;
}

char** read_file(const char* filename)
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

  lines[size] = NULL;

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
  tokens[i] = NULL;

  return tokens;
}

bool seq(char* l, char* r) 
{
  return strcmp(l, r) == 0;
}

bool expect(char* token, char* expected)
{
  return token != NULL && seq(token, expected);
}

size_t count_tokens(char** tokens)
{
  if (tokens == NULL) return 0;
  size_t count = 0;
  while (tokens[count] != NULL) count++;
  return count;
}

bool _is_number(char* str)
{
  if (str == NULL || strlen(str) == 0) return false;
  if (str[0] == '-') str++;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] < '0' || str[i] > '9') return false;
  }

  return true;
}

char** destination_prefixes = NULL;

void _parse_meta_append_to_var_destination_prefixes(char** tokens)
{
  size_t count = count_tokens(tokens);
  destination_prefixes = realloc(destination_prefixes, sizeof(char*) * (count + 1));
  for (int i = 0; i < count; i++)
  {
    destination_prefixes[i] = tokens[i];
  }
  destination_prefixes[count] = NULL;
}

void _parse_meta_append_to_var(char** tokens) 
{
  if (seq(tokens[0], "destination_prefixes")) _parse_meta_append_to_var_destination_prefixes(tokens + 1);
  else printf("Unknown or not appendable variable: %s\n", tokens[0]);
}

void _parse_meta(char** tokens) 
{
  if (seq(tokens[0], "append-to-var")) _parse_meta_append_to_var(tokens+1);
  else printf("Unknown meta command: %s\n", tokens[0]);
}

bool _valid_dest_prefix(char* token)
{
  if (destination_prefixes == NULL) {
    printf("No destination prefixes defined. Please define them in the meta section, e.g.:\n"
      "    @meta append-to-var destination_prefixes <prefix> [<prefix> ...]\n");
    return false;
  }
  for (int i = 0; destination_prefixes[i] != NULL; i++)
  {
    if (seq(token, destination_prefixes[i])) return true;
  }

  return false;
}

char* _parse_desination(char** tokens)
{
  char* destination = (char*)malloc(sizeof(char) * strlen(tokens[0]) + strlen(tokens[1]) + 2);
  sprintf(destination, "%s %s", tokens[0], tokens[1]);
  return destination;
}

void _parse_ADD_plane(char** params, struct Hive* hive) {
  if (count_tokens(params) != 6 || !_is_number(params[0]) || !_is_number(params[1]) || !_is_number(params[2]) || !_is_number(params[3]) || !_valid_dest_prefix(params[4])) 
  {
    printf("Invalid ADD plane comand\n");
    return;
  }
  struct Plane* plane = plane_create(
    atoi(params[0]), atoi(params[1]), atoi(params[2]), atoi(params[3]), _parse_desination(params + 4)
  );
  hive_push(hive, plane);
}

void _parse_ADD_train(char** params, struct Hive* hive) {
  if (count_tokens(params) != 5 || !_is_number(params[0]) || !_is_number(params[1]) || !_is_number(params[2]) || !_valid_dest_prefix(params[3])) 
  {
    printf("Invalid ADD train command\n");
    return;
  }
  struct Train* train = train_create(
    atoi(params[0]), atoi(params[1]), atoi(params[2]), _parse_desination(params + 3)
  );
  hive_push(hive, train);
}

void _parse_ADD(char** params, struct Hive* hive) 
{
  if (params[0] == NULL) printf("Invalid ADD command\n");
  else if (seq(params[0], "plane")) _parse_ADD_plane(params + 1, hive);
  else if (seq(params[0], "train")) _parse_ADD_train(params + 1, hive);
  else printf("Unknown entity type: %s\n", params[0]);
}

void _hive_PRINT_plane(struct Plane* plane)
{
  printf("Plane {len: %d; cap: %d; spd: %d; dist: %d; dest: '%s'}\n", plane->len, plane->cap, plane->spd, plane->dist, plane->dest);
}

void _hive_PRINT_train(struct Train* train)
{
  printf("Train {cnt: %d; spd: %d; dest: '%s'}\n", train->cnt, train->spd, train->dest);
}

void _parse_PRINT_internals(void* data) 
{
  if (is_plane(data)) _hive_PRINT_plane((struct Plane*)data);
  else if (is_train(data)) _hive_PRINT_train((struct Train*)data);
  else printf("%p\n", data);
}

void _parse_PRINT(struct Hive* hive) 
{
  if (hive_is_empty(hive)) printf("Empty\n");
  else hive_print(hive, &_parse_PRINT_internals);
}

void _parse_CLEAR(struct Hive* hive) 
{
  hive_clear(hive);
}

bool _parse_SORT_comparator(char* attr, void* a, void* b) 
{
  void* attrA = get_attr(a, attr);
  void* attrB = get_attr(b, attr);
  if (attrA == NULL) return true;
  if (attrB == NULL) return false;
  if (seq(attr, "dest")) return strcmp(*(char**)attrA, *(char**)attrB) < 0;
  return *(int*)attrA < *(int*)attrB;
}

void _parse_SORT(char** params, struct Hive* hive) 
{
  if (params[0] == NULL || count_tokens(params) > 1) printf("Invalid SORT command\n");
  else if (!is_attr(params[0])) printf("Invalid SORT attribute: %s\n", params[0]);
  else hive_sort(hive, params[0], &_parse_SORT_comparator);
}

bool _is_predicate(char* predicate) 
{
  return seq(predicate, "=") || seq(predicate, "<") || seq(predicate, ">") || seq(predicate, "!=");
}

bool _is_string_predicate(char* predicate) 
{
  return seq(predicate, "=") || seq(predicate, "!=");
}

void _parse_REM(char** params, struct Hive* hive) 
{
  // if <attr> <predicate> <value>
  if (params[0] == NULL || !seq(params[0], "if") && (count_tokens(params) != 4 || (count_tokens(params) != 5 && _valid_dest_prefix(params[3])))) printf("Invalid REM command\n");
  else {
    char* attr = params[1];
    char* predicate = params[2];
    char* value = params[3];
    if (!is_attr(attr)) printf("Invalid REM attribute: %s\n", attr);
    else if (!_is_predicate(predicate)) printf("Invalid REM predicate: %s\n", predicate);
    else if (!_is_number(value) && !_is_string_predicate(predicate)) printf("Invalid REM string predicate: %s\n", value);
    else hive_remove_if_attr(hive, attr, predicate, count_tokens(params) == 4 ? value : _parse_desination(params + 3));
  }
}

void _parse_ECHO(char** tokens) 
{
  if (tokens != NULL) {
    for (int i = 0; tokens[i] != NULL; i++) printf("%s ", tokens[i]);
  }
  printf("\n");
}

void _parse_EXIT(char** tokens) 
{
  int exitCode = 0;
  if (tokens != NULL && tokens[0] != NULL && _is_number(tokens[0])) {
    exitCode = atoi(tokens[0]);
  }
  printf("Exiting with code %d\n", exitCode);
  exit(exitCode);
}

void parse_line(char** tokens, struct Hive* hive) {
  if (seq(tokens[0], "@meta")) _parse_meta(tokens + 1);
  else if (seq(tokens[0], "ADD")) _parse_ADD(tokens + 1, hive);
  else if (seq(tokens[0], "PRINT")) _parse_PRINT(hive);
  else if (seq(tokens[0], "CLEAR")) _parse_CLEAR(hive);
  else if (seq(tokens[0], "SORT")) _parse_SORT(tokens + 1, hive);
  else if (seq(tokens[0], "REM")) _parse_REM(tokens + 1, hive);
  else if (seq(tokens[0], "ECHO")) _parse_ECHO(tokens + 1);
  else if (seq(tokens[0], "EXIT")) _parse_EXIT(tokens + 1);
  else printf("Unknown command: %s\n", tokens[0]);
}
