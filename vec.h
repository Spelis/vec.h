#pragma once

#define NEW_VEC_TYPE(type, name, init_capacity)                               \
	typedef struct name {                                                     \
		type* data;                                                           \
		size_t count;                                                         \
		size_t capacity;                                                      \
		size_t min_cap;                                                       \
	} name;                                                                   \
	static inline void vec_append_##name(name* v, type x) {                   \
		if (v->count >= v->capacity) {                                        \
			if (v->capacity == 0) v->capacity = v->min_cap;                   \
			v->capacity *= 2;                                                 \
			type* tmp = realloc(v->data, v->capacity * sizeof(*v->data));     \
			if (!tmp) {                                                       \
				perror("realloc");                                            \
				exit(EXIT_FAILURE);                                           \
			}                                                                 \
			v->data = tmp;                                                    \
		}                                                                     \
		v->data[v->count++] = x;                                              \
	}                                                                         \
	static inline void vec_udelete_##name(                                    \
		name* v, size_t i) { /* O(1), swaps with last */                      \
		if (i >= v->count) return;                                            \
		v->data[i] = v->data[v->count - 1];                                   \
		v->count--;                                                           \
	}                                                                         \
	static inline void vec_delete_##name(                                     \
		name* v, size_t i) { /* O(n), preserves order */                      \
		if (i >= v->count) return;                                            \
		for (size_t j = i; j + 1 < v->count; j++) {                           \
			v->data[j] = v->data[j + 1]; /* shift elements left */            \
		}                                                                     \
		v->count--;                                                           \
	}                                                                         \
	static inline void vec_insert_##name(name* v, size_t i, type x) {         \
		if (i > v->count) return;                                             \
		if (v->count >= v->capacity) {                                        \
			if (v->capacity == 0) v->capacity = v->min_cap;                   \
			v->capacity *= 2;                                                 \
			type* tmp = realloc(v->data, v->capacity * sizeof(*v->data));     \
			if (!tmp) {                                                       \
				perror("realloc");                                            \
				exit(EXIT_FAILURE);                                           \
			}                                                                 \
			v->data = tmp;                                                    \
		}                                                                     \
                                                                              \
		for (size_t j = v->count; j > i; j--) {                               \
			v->data[j] = v->data[j - 1];                                      \
		}                                                                     \
                                                                              \
		v->data[i] = x;                                                       \
		v->count++;                                                           \
	}                                                                         \
	static inline void vec_shrink_##name(name* v) {                           \
		if (v->count < v->capacity / 3 && v->capacity > v->min_cap) {         \
			v->capacity /= 2;                                                 \
			type* tmp = realloc(v->data, v->capacity * sizeof(*v->data));     \
			if (!tmp) {                                                       \
				perror("realloc");                                            \
				exit(EXIT_FAILURE);                                           \
			}                                                                 \
			v->data = tmp;                                                    \
		}                                                                     \
	}                                                                         \
	static inline type vec_at_##name(name* v, size_t i) {                     \
		if (i >= v->count) {                                                  \
			fprintf(stderr, "vec_at: index %zu out of bounds (count=%zu)\n",  \
					i, v->count);                                             \
			exit(EXIT_FAILURE);                                               \
		}                                                                     \
		return v->data[i];                                                    \
	}                                                                         \
	static inline type vec_front_##name(name* v) {                            \
		if (v->count == 0) {                                                  \
			fprintf(stderr, "vec_front: empty vector\n");                     \
			exit(EXIT_FAILURE);                                               \
		}                                                                     \
		return v->data[0];                                                    \
	}                                                                         \
	static inline type vec_back_##name(name* v) {                             \
		if (v->count == 0) {                                                  \
			fprintf(stderr, "vec_back: empty vector\n");                      \
			exit(EXIT_FAILURE);                                               \
		}                                                                     \
		return v->data[v->count - 1];                                         \
	}                                                                         \
	static inline ssize_t vec_find_##name(name* v, type x) {                  \
		for (size_t i = 0; i < v->count; i++)                                 \
			if (v->data[i] == x) return (ssize_t)i;                           \
		return -1;                                                            \
	}                                                                         \
	static inline unsigned int vec_contains_##name(name* v, type x) {         \
		return vec_find_##name(v, x) >= 0;                                    \
	}                                                                         \
	static inline size_t vec_size_##name(name* v) { return v->count; }        \
	static inline size_t vec_capacity_##name(name* v) { return v->capacity; } \
	static inline size_t vec_minimum_capacity_##name(name* v) {               \
		return v->min_cap;                                                    \
	}                                                                         \
	static inline void vec_free_##name(name* v) {                             \
		free(v->data);                                                        \
		v->data = NULL;                                                       \
		v->count = 0;                                                         \
		v->capacity = 0;                                                      \
	}                                                                         \
	static inline void vec_clear_##name(name* v) { v->count = 0; }            \
	static inline void vec_init_##name(name* v) {                             \
		v->data = NULL;                                                       \
		v->count = 0;                                                         \
		v->capacity = 0;                                                      \
		v->min_cap = init_capacity;                                           \
		if (v->min_cap <= 0) v->min_cap = 1;                                  \
	}
