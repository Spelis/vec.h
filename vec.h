#pragma once

#define NEW_VEC_TYPE(type, name)                                              \
	typedef struct name {                                                     \
		type* data;                                                           \
		size_t count;                                                         \
		size_t capacity;                                                      \
	} name;                                                                   \
	static inline void vec_append_##name(name* v, type x) {                   \
		if (v->count >= v->capacity) {                                        \
			if (v->capacity == 0) v->capacity = 256;                          \
			v->capacity *= 2;                                                 \
			v->data = realloc(v->data, v->capacity * sizeof(*v->data));       \
		}                                                                     \
		v->data[v->count++] = x;                                              \
	}                                                                         \
	static inline void vec_delete_##name(name* v, size_t i) {                 \
		if (i >= v->count) return;                                            \
		v->data[i] = v->data[v->count - 1];                                   \
		v->count--;                                                           \
	}                                                                         \
	static inline void vec_insert_##name(name* v, size_t i, type x) {         \
		if (i > v->count) return;                                             \
		if (v->count >= v->capacity) {                                        \
			if (v->capacity == 0) v->capacity = 256;                          \
			v->capacity *= 2;                                                 \
			v->data = realloc(v->data, v->capacity * sizeof(*v->data));       \
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
		if (v->count < v->capacity / 3 && v->capacity > 256) {                \
			v->capacity /= 2;                                                 \
			v->data = realloc(v->data, v->capacity * sizeof(*v->data));       \
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
	static inline type vec_front_##name(name* v) { return v->data[0]; }       \
	static inline type vec_back_##name(name* v) {                             \
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
	}
