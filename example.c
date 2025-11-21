#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec.h"

NEW_VEC_TYPE(int, IntVec)
NEW_VEC_TYPE(float, FloatVec)
NEW_VEC_TYPE(char*, StringVec)

int main(void) {
	// --- Integers ---
	IntVec ivec;
	vec_init_IntVec(&ivec);

	ivec.push(&ivec, 10);
	ivec.push(&ivec, 20);
	ivec.push(&ivec, 30);

	printf("Integer vector:\n");
	for (size_t i = 0; i < ivec.count; i++) {
		printf("ivec[%zu] = %d\n", i, ivec.at(&ivec, i));
	}
	ivec.del(&ivec, 1);	 // remove 20
	printf("After deleting index 1:\n");
	for (size_t i = 0; i < ivec.count; i++) {
		printf("ivec[%zu] = %d\n", i, ivec.at(&ivec, i));
	}
	ivec.free(&ivec);

	printf("\n");

	// --- Floats ---
	FloatVec fvec;
	vec_init_FloatVec(&fvec);

	fvec.push(&fvec, 1.23f);
	fvec.push(&fvec, 4.56f);
	fvec.push(&fvec, 7.89f);

	printf("Float vector:\n");
	for (size_t i = 0; i < fvec.count; i++) {
		printf("fvec[%zu] = %.2f\n", i, fvec.at(&fvec, i));
	}
	fvec.del(&fvec, 0);	 // remove 1.23
	printf("After deleting index 0:\n");
	for (size_t i = 0; i < fvec.count; i++) {
		printf("fvec[%zu] = %.2f\n", i, fvec.at(&fvec, i));
	}
	fvec.free(&fvec);

	printf("\n");

	// --- Strings (char*) ---
	StringVec svec;
	vec_init_StringVec(&svec);

	svec.push(&svec, strdup("apple"));
	svec.push(&svec, strdup("banana"));
	svec.push(&svec, strdup("cherry"));

	printf("String vector:\n");
	for (size_t i = 0; i < svec.count; i++) {
		printf("svec[%zu] = %s\n", i, svec.at(&svec, i));
	}

	// Remove "banana"
	free(svec.at(&svec, 1));  // free the string first
	svec.del(&svec, 1);

	printf("After deleting index 1:\n");
	for (size_t i = 0; i < svec.count; i++) {
		printf("svec[%zu] = %s\n", i, svec.at(&svec, i));
	}

	// Free all strings first
	for (size_t i = 0; i < svec.count; i++) {
		free(svec.at(&svec, i));
	}
	svec.free(&svec);

	return 0;
}
