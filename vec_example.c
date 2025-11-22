#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

NEW_VEC_TYPE(int, int_vec, 4);	// NEW_VEC_TYPE(TYPE, NAME, MIN_CAP);

static void print_vec(const int_vec* v) {
	printf("[ ");
	for (size_t i = 0; i < v->count; i++) {
		printf("%d ", v->data[i]);
	}
	printf("] (size=%zu, cap=%zu)\n", v->count, v->capacity);
}

int main(void) {
	int_vec v;
	vec_init_int_vec(&v);

	printf("Starting with an empty vector:\n");
	print_vec(&v);

	// Append a few elements
	printf("\nAppending 1..9:\n");
	for (int i = 1; i <= 9; i++) {
		vec_append_int_vec(&v, i);
		print_vec(&v);
	}

	// Access tests
	printf("\nFront: %d\n", vec_front_int_vec(&v));
	printf("Back : %d\n", vec_back_int_vec(&v));
	printf("At[2]: %d\n", vec_at_int_vec(&v, 2));

	// Insert at index 1
	printf("\nInsert 99 at index 1:\n");
	vec_insert_int_vec(&v, 1, 99);
	print_vec(&v);

	// Unordered delete
	printf("\nUnordered delete at index 2 (swap-with-last):\n");
	vec_udelete_int_vec(&v, 2);
	print_vec(&v);

	// Ordered delete
	printf("\nOrdered delete at first 5 elements (preserve order):\n");
	for (int i = 0; i < 5; i++) {
		vec_delete_int_vec(&v, 0);
	}
	print_vec(&v);

	// Find / contains
	printf("\nFind value 5: index = %zd\n", vec_find_int_vec(&v, 5));
	printf("Contains 7? %s\n", vec_contains_int_vec(&v, 7) ? "yes" : "no");

	// Shrink check
	printf("\nCalling shrink:\n");
	vec_shrink_int_vec(&v);
	print_vec(&v);

	// Metadata
	printf("\nMetadata:\n");
	printf("size     = %zu\n", vec_size_int_vec(&v));
	printf("capacity = %zu\n", vec_capacity_int_vec(&v));
	printf("min cap  = %zu\n", vec_minimum_capacity_int_vec(&v));

	// Clear
	printf("\nClearing vector:\n");
	vec_clear_int_vec(&v);
	print_vec(&v);

	// Append a couple more
	printf("\nAppending 42 and 77 after clear:\n");
	vec_append_int_vec(&v, 42);
	vec_append_int_vec(&v, 77);
	print_vec(&v);

	// Free the vector.
	printf("\nFreeing vector\n");
	vec_free_int_vec(&v);

	return 0;
}
