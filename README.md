# Vec.h | A single header-only dynamic vector C library.
`Vec.h` is a small, header-only C library for creating dynamic arrays (vectors) with minimal boilerplate. 

It allows you to create vectors for any type, including signed or unsigned integers, floating point numbers, strings or even complete structs!

---

## Features

* Type-safe vectors for any C type
* Dynamic growing and shrinking
* Push, delete, and access elements safely
* Lightweight and header only

---

## Installation

Just download `vec.h` and put it in your project

```
#include "vec.h"
```

No compilation or linking needed; it is completely inline.

---

## Usage

1. Define a vector type
```
NEW_VEC_TYPE(int, IntVec) // Defines a vector of ints named IntVec
NEW_VEC_TYPE(int, IntVec) // Defines a vector of floats
NEW_VEC_TYPE(int, IntVec) // Defines a vector of strings (char*)
NEW_VEC_TYPE(TYPE, NAME) // Defines a vector of TYPE named NAME
```
The first parameter is the element type, the second is the vector name.

---
2. Initialize a vector
```
IntVec ivec;
vec_init_IntVec(&ivec); // Initializes the vector
```
---
3. Push elements
```
ivec.push(&ivec, 42);
ivec.push(&ivec, 100);
```
---
4. Access elements
```
int value = ivec.at(&ivec, 0); // Returns the element at index 0
```
---
5. Delete elements
```
ivec.del(&ivec, 0); // Deletes the element at index 0 and pushes other elements to the left
```
---
6. Free the vector
```
ivec.free(&ivec);
```
> Note: For pointer types (like `char*`), free individual elements first before freeing the vector.

---
## License

MIT License, free to use, modify, and re-distribute with or without modification.
