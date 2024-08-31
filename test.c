#include "src/map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void test_int(void);
void test_void(void);
void test_string(void);

int main(int argc, char* argv[])
{
  srand(time(NULL));
  test_int();
  test_string();

  return 0;
}

void test_int(void)
{
  printf("test int: start\n");
  bool success = true;
  const int number = 10;
  int success_val[number];

  map_t(int) map;
  map_init(&map);

  // Fill
  for (int i = 0; i < number; i++) {
    success_val[i] = rand();
    map_set(&map, (char*)&i, success_val[i]);
  }

  // Check success value
  for (int i = 0; i < number; i++) {
    const int* get_value = (int*)map_get(&map, (char*)&i);
    if ((*get_value) != success_val[i]) {
      success = false;
      printf("error: key = %d; value = %d; success_val = %d\n", i, (*get_value), success_val[i]);
    }
  }

  // Check invalid key
  for (int i = number; i < number + 10; i++) {
    const int* get_value = (int*)map_get(&map, (char*)&i);
    if (get_value != NULL) {
      success = false;
      printf("error: test invalid key: %d; ptr = %u\n", i, get_value);
    }
  }

  map_deinit(&map);

  printf("test int: ");
  if (success)
    printf("Success\n\n");
  else
    printf("Error\n\n");
}

void test_void(void)
{
}

// return: string size - '\0'
size_t test_string_fill(char* str, size_t str_size)
{
  const size_t char_number = ('z' - '0') + 1;
  int i = 0;

  str_size--;
  for (; i < str_size; i++)
    str[i] = (rand() % char_number) + '0';
  str[i] = '\0';

  return str_size;
}

void test_string(void)
{
  printf("test string: start\n");
  bool success = true;
  const int number = 10;
  const size_t min_size = 10;
  const size_t max_size = 100;
  char* success_val[number];
  size_t success_val_size[number];

  map_t(int) map;
  map_init(&map);

  // Fill
  for (int i = 0; i < number; i++) {
    success_val_size[i] = (rand() % max_size) + min_size;
    success_val[i] = malloc(success_val_size[i]);
    test_string_fill(success_val[i], success_val_size[i]);
    map_set_(&map.base, (char*)&i, success_val[i], success_val_size[i]);
  }

  for (int i = 0; i < number; i++) {
    const char* get_str = (char*)map_get(&map, (char*)&i);
    if(get_str == success_val[i]){
      /* success = false; */
      printf("warning: pointers are equal\n");
    }
    if (strcmp(success_val[i], get_str)) {
      success = false;
      printf("error: key = %d\n    value[size:%lu] = %s\n    success_val[size:%lu] = %s\n",
          i, strlen(get_str), get_str, strlen(success_val[i]), success_val[i]);
    }
  }

  // Check invalid key
  for (int i = number; i < number + 10; i++) {
    const char* get_str = (char*)map_get(&map, (char*)&i);
    if (get_str != NULL) {
      success = false;
      printf("error: test invalid key: %d; ptr = %u\n", i, get_str);
    }
  }

  // Free string
  for (int i = 0; i < number; i++)
    free(success_val[i]);

  map_deinit(&map);

  printf("test string: ");
  if (success)
    printf("Success\n\n");
  else
    printf("Error\n\n");
}
