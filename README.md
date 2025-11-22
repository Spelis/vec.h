# Vec.h | A single header-only dynamic vector C library.
`Vec.h` is a small, header-only C library for creating dynamic arrays (vectors) with minimal boilerplate. 

It allows you to create vectors for any type, including signed or unsigned integers, floating point numbers, strings or even complete structs!

### Maps/Dictionaries
`Vec.h` also provides a simple map implementation built on top of vectors. It keeps keys and values in sync.

Map value deletion is O(1) but does **not preserve insertion order**.

---

## Features

* Type-safe vectors for any C type
* Dynamic growing and manual shrinking
* Append, insert, delete, and access elements safely
* Lightweight and header only

---

## Installation

Just download `vec.h` into your project and include it:

```c
#include "vec.h"
```

---

## Vector Usage

1. Define a vector type
```c
NEW_VEC_TYPE(int, IntVec, 16); // Defines a vector of ints named IntVec
NEW_VEC_TYPE(float, FloatVec, 16); // Defines a vector of floats
NEW_VEC_TYPE(char*, StringVec, 8); // Defines a vector of strings (char*) (needs to individually free each element before freeing the entire vector)
NEW_VEC_TYPE(TYPE, NAME, MIN_CAP); // Defines a vector of TYPE named NAME with minimum capacity MIN_CAP
```
The first parameter is the element type, the second is the vector name.

---
2. Initialize a vector
```c
IntVec ivec;
vec_init_IntVec(&ivec); // Initializes the vector
```
---
3. Push elements
```c
vec_append_IntVec(&ivec, 42);
vec_append_IntVec(&ivec, 100);
```
---
4. Insert elements
```c
vec_insert_IntVec(&ivec, 1, 55); // Inserts 55 at index 1
```
---
5. Access elements
```c
int value = vec_at_IntVec(&ivec, 0);    // Returns the element at index 0
int first = vec_front_IntVec(&ivec);    // Returns the first element
int last = vec_back_IntVec(&ivec);      // Returns the last element
```
---
6. Delete elements
```c
vec_delete_IntVec(&ivec, 0); // Deletes the element at index 0 (preserves order)
vec_udelete_IntVec(&ivec, 1); // Deletes the element at index 1 (O(1), unordered)
```
> Note: `vec_udelete` swaps the last element into the deleted element's position (unordered). 
---
7. Search elements
```c
ssize_t index = vec_find_IntVec(&ivec, 100);   // Returns index of first occurrence or -1 if not found
unsigned int exists = vec_contains_IntVec(&ivec, 42); // Returns 1 if element exists, 0 otherwise
```
---
8. Query size and capacity
```c
size_t sz = vec_size_IntVec(&ivec);       // Number of elements
size_t cap = vec_capacity_IntVec(&ivec);  // Current allocated capacity
size_t min_cap = vec_minimum_capacity_IntVec(&ivec);  // Minimum allowed allocated capacity
```
> Note: these just return `&ivec->size`, `&ivec->capacity` and `&ivec->min_cap` respectively.
---
9. Shrink the vector
```c
vec_shrink_IntVec(&ivec); // Shrinks capacity if much larger than count
```
---
10. Free the vector
```c
vec_free_IntVec(&ivec);
```
> Note: For pointer types (like `char*`), free individual elements first before freeing the vector.

---
## Map Usage
1. Define a map type
```c
NEW_MAP_TYPE(int, int, IntIntMap, 16); // Defines a map of int:int named IntIntMap (example map)
NEW_MAP_TYPE(KTYPE, VTYPE, NAME, MIN_CAP); // Defines a map of KTYPE:VTYPE named NAME
```
---
2. Initialize a map
```c
IntIntMap iimap;
map_init_IntIntMap(&iimap);
```
---
3. Set a key to a value
```c
map_set_IntIntMap(&iimap, 1, 100);
map_set_IntIntMap(&iimap, 2, 200);
```
---
4. Get a value from a key
```c
map_get_IntIntMap(&iimap, 1); // 100
```
---
5. Delete an entry with a key
```c
map_del_IntIntMap(&iimap, 2); // Removes key 2, and value 200
```
---
6. Free the map
```c
map_free_IntIntMap(&iimap);
```
> Note: if either the key or/and the value is a pointer type (like `char*`), you'll need to free those elements individually first.

---
## License

MIT License, free to use, modify, and re-distribute with or without modification.
