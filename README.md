# Vec.h | A single header-only dynamic vector C library.
`Vec.h` is a small, header-only C library for creating dynamic arrays (vectors) with minimal boilerplate. 

It allows you to create vectors for any type, including signed or unsigned integers, floating point numbers, strings or even complete structs!

---

## Features

* Type-safe vectors for any C type
* Dynamic growing and manual shrinking
* Append, insert, delete, and access elements safely
* Lightweight and header only

---

## Installation

Just download `vec.h` and put it in your project

```c
#include "vec.h"
```

No compilation or linking needed; it is completely inline.

---

## Usage

1. Define a vector type
```c
NEW_VEC_TYPE(int, IntVec, 16) // Defines a vector of ints named IntVec
NEW_VEC_TYPE(int, IntVec, 16) // Defines a vector of floats
NEW_VEC_TYPE(int, IntVec, 8) // Defines a vector of strings (char*) (needs to individually free each element before freeing the entire vector)
NEW_VEC_TYPE(TYPE, NAME, MIN_CAP) // Defines a vector of TYPE named NAME with minimum capacity MIN_CAP
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
> Note: When deleting the last element will be moved into the position of 
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
> Note: these just return `&ivec->size` and `&ivec->capacity` respectively.
---
9. Shrink the vector
```c
vec_shrink_IntVec(&ivec); // Shrinks capacity if much larger than count
```
---
10. Free the vector
```c
ivec.free(&ivec);
```
> Note: For pointer types (like `char*`), free individual elements first before freeing the vector.

---
## License

MIT License, free to use, modify, and re-distribute with or without modification.
