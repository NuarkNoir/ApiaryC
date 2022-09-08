#include <assert.h>
#include <string.h>

#include "lib.h"
#include "hive.h"
#include "melipona.h"

int main()
{
  struct Plane* plane = plane_create(1, 2, 3, 4, "Hello, world!", "object1");
  struct Train* train = train_create(5, 6, 7, "Hello, world!", "object2");
  struct Boat* boat = boat_create(133, 222, 3, 4, "Hello, world!", "object3");

  assert(is_plane(plane) && !is_train(plane) && !is_boat(plane));
  assert(is_train(train) && !is_plane(train) && !is_boat(train));
  assert(is_boat(boat) && !is_plane(boat) && !is_train(boat));

  assert(is_plane_attr("len") && is_plane_attr("cap"));
  assert(is_train_attr("cnt") && !is_plane_attr("cnt"));
  assert(is_attr("len") && is_attr("cnt") && is_attr("dest"));

  int* len = (int*)get_attr(plane, "len");
  assert(*len == 1);
  char* dest = *(char**)get_attr(train, "dest");
  assert(strcmp(dest, "Hello, world!") == 0);

  assert(attr_eq_int(plane, "len", 1));
  assert(attr_eq_int(train, "cnt", 5));
  assert(attr_eq_str(boat, "name", "object3"));

  return 0;
}
