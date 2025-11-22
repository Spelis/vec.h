#include <stdio.h>
#include <stdlib.h>

#define VEC_MAP
#include "vec.h"

// NEW_MAP_TYPE(KEYTYPE, VALTYPE, NAME, MIN_CAP)
NEW_MAP_TYPE(int, int, int_int_map, 1);

static void print_map(const int_int_map* m) {
	printf("{ ");
	for (size_t i = 0; i < m->keys.count; i++) {
		printf("%d:%d ", m->keys.data[i], m->values.data[i]);
	}
	printf("} (size=%zu, capacity=%zu)\n", m->keys.count, m->keys.capacity);
}

int main(void) {
	int_int_map m;
	map_init_int_int_map(&m);

	printf("Starting with empty map:\n");
	print_map(&m);

	// Insert a few pairs
	printf("\nInserting key->value pairs:\n");
	for (int i = 1; i <= 5; i++) {
		map_set_int_int_map(&m, i, i * 10);
		print_map(&m);
	}

	// Test updating an existing key
	printf("\nUpdating key 3 -> 999:\n");
	map_set_int_int_map(&m, 3, 999);
	print_map(&m);

	// Test lookup
	printf("\nLookup key 4: %d\n", map_get_int_int_map(&m, 4));

	// Test deletion
	printf("\nDeleting key 2:\n");
	map_del_int_int_map(&m, 2);
	print_map(&m);

	// Test deletion of last existing pair
	printf("\nDeleting key 5:\n");
	map_del_int_int_map(&m, 5);
	print_map(&m);

	// Insert after deletion
	printf("\nInserting key 42 -> 777:\n");
	map_set_int_int_map(&m, 42, 777);
	print_map(&m);

	// Free the map
	printf("\nFreeing map\n");
	map_free_int_int_map(&m);

	return 0;
}
