#pragma once

#define NEW_VEC_TYPE(type, name)                                               \
	typedef struct name {                                                      \
		type* data;                                                            \
		size_t count;                                                          \
		size_t capacity;                                                       \
		void (*push)(struct name*, type);                                      \
		void (*free)(struct name*);                                            \
		void (*del)(struct name*, size_t);                                     \
		type (*at)(struct name*, size_t);                                      \
	} name;                                                                    \
	static inline void vec_push_##name(name* v, type x) {                      \
		if (v->count >= v->capacity) {                                         \
			if (v->capacity == 0) v->capacity = 256;                           \
			v->capacity *= 2;                                                  \
			v->data = realloc(v->data, v->capacity * sizeof(*v->data));        \
		}                                                                      \
		v->data[v->count++] = x;                                               \
	}                                                                          \
	static inline void vec_del_##name(name* v, size_t i) {                     \
		if (i >= v->count) return;                                             \
		for (size_t j = i; j + 1 < v->count; j++) {                            \
			v->data[j] = v->data[j + 1];                                       \
		}                                                                      \
		v->count--;                                                            \
	}                                                                          \
	static inline type vec_at_##name(name* v, size_t i) { return v->data[i]; } \
	static inline void vec_free_##name(name* v) {                              \
		free(v->data);                                                         \
		v->data = NULL;                                                        \
		v->count = 0;                                                          \
		v->capacity = 0;                                                       \
	}                                                                          \
	static inline void vec_init_##name(name* v) {                              \
		v->data = NULL;                                                        \
		v->count = 0;                                                          \
		v->capacity = 0;                                                       \
		v->push = &vec_push_##name;                                            \
		v->free = &vec_free_##name;                                            \
		v->del = &vec_del_##name;                                              \
		v->at = &vec_at_##name;                                                \
	}
