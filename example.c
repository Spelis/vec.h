#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

NEW_VEC_TYPE(int, IntVec, 16)
NEW_VEC_TYPE(float, FloatVec, 16)
NEW_VEC_TYPE(char*, StringVec,
			 0)	 // works even with a zero value. gets set to 1 internally.

int main(void) {
	// --- Integers ---
	IntVec ivec;
	vec_init_IntVec(&ivec);

	vec_append_IntVec(&ivec, 10);
	vec_append_IntVec(&ivec, 20);
	vec_append_IntVec(&ivec, 30);

	printf("Integer vector:\n");
	for (size_t i = 0; i < vec_size_IntVec(&ivec); i++) {
		printf("ivec[%zu] = %d\n", i, vec_at_IntVec(&ivec, i));
	}

	vec_delete_IntVec(&ivec, 1);  // unordered delete: removes 20
	printf("After deleting index 1:\n");
	for (size_t i = 0; i < vec_size_IntVec(&ivec); i++) {
		printf("ivec[%zu] = %d\n", i, vec_at_IntVec(&ivec, i));
	}

	vec_free_IntVec(&ivec);

	printf("\n");

	// --- Floats ---
	FloatVec fvec;
	vec_init_FloatVec(&fvec);

	vec_append_FloatVec(&fvec, 1.23f);
	vec_append_FloatVec(&fvec, 4.56f);
	vec_append_FloatVec(&fvec, 7.89f);

	printf("Float vector:\n");
	for (size_t i = 0; i < vec_size_FloatVec(&fvec); i++) {
		printf("fvec[%zu] = %.2f\n", i, vec_at_FloatVec(&fvec, i));
	}

	vec_delete_FloatVec(&fvec, 0);	// unordered delete: removes 1.23
	printf("After deleting index 0:\n");
	for (size_t i = 0; i < vec_size_FloatVec(&fvec); i++) {
		printf("fvec[%zu] = %.2f\n", i, vec_at_FloatVec(&fvec, i));
	}

	vec_free_FloatVec(&fvec);

	printf("\n");

	// --- Strings (char*) ---
	StringVec svec;
	vec_init_StringVec(&svec);

	vec_append_StringVec(&svec, strdup("apple"));
	vec_append_StringVec(&svec, strdup("banana"));
	vec_append_StringVec(&svec, strdup("cherry"));

	printf("String vector:\n");
	for (size_t i = 0; i < vec_size_StringVec(&svec); i++) {
		printf("svec[%zu] = %s\n", i, vec_at_StringVec(&svec, i));
	}

	// Remove "banana"
	free(vec_at_StringVec(&svec, 1));  // free string first
	vec_delete_StringVec(&svec, 1);

	printf("After deleting index 1:\n");
	for (size_t i = 0; i < vec_size_StringVec(&svec); i++) {
		printf("svec[%zu] = %s\n", i, vec_at_StringVec(&svec, i));
	}

	// Free all remaining strings
	for (size_t i = 0; i < vec_size_StringVec(&svec); i++) {
		free(vec_at_StringVec(&svec, i));
	}
	vec_free_StringVec(&svec);

	return 0;
}
