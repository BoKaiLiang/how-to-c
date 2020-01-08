/* credit from : https://github.com/zauonlok/renderer/blob/master/renderer/core/darray.c */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
	union {
		struct { float x, y, z; };
		float arr[3];
	};
} vec3_t;

static const vec3_t pos[] = {
	{ 0.0f,  0.0f,  0.0f},
	{ 2.0f,  5.0f, -15.0f},
	{-1.5f, -2.2f, -2.5f},
	{-3.8f, -2.0f, -12.3f},
	{ 2.4f, -0.4f, -3.5f},
	{-1.7f,  3.0f, -7.5f},
	{ 1.3f, -2.0f, -2.5f},
	{ 1.5f,  2.0f, -2.5f},
	{ 1.5f,  0.2f, -1.5f},
	{-1.3f,  1.0f, -1.5f}
};

#define dyarray_push(arr, val)						\
do {												\
	(arr) = dyarray_grow((arr), 1, sizeof(*(arr))); \
	(arr)[dyarray_count(arr) - 1] = (val);			\
} while(0)

#define dyarray_last(arr) (arr)[dyarray_count(arr) - 1]

#define dyarray_pop(arr) ((((int*)(arr)-2)[1])--, (arr)[(((int*)(arr)-2)[1])])


int dyarray_count(void* arr) {
	return arr == NULL ? 0 : (((int*)(arr)-2)[1]);
}

int dyarray_size(void* arr) {
	return arr == NULL ? 0 : (((int*)(arr)-2)[0]);
}

void* dyarray_grow(void* arr, int count, int itemsz)
{
	int header_sz = sizeof(int) * 2; // two int, one for count, one for capacity
	int needed_sz = dyarray_count(arr) + count;
	int curr_sz = dyarray_size(arr);
	assert(0 < count && 0 < itemsz);
	if (arr == NULL) {
		int raw_sz = itemsz * count + header_sz;
		int* p = malloc(raw_sz);
		p[0] = needed_sz; // 0 for size
		p[1] = needed_sz; // 1 for count
		return p + 2;
	}
	else if (curr_sz <= needed_sz) {
		int dbl_sz = 2 * curr_sz;
		int sz = dbl_sz > needed_sz ? dbl_sz : needed_sz;
		int raw_sz = itemsz * sz + header_sz;
		int* p = realloc((int*)(arr)-2, raw_sz);
		p[0] = sz;
		p[1] = needed_sz;
		return p + 2;
	}

	((int*)(arr)-2)[1] = needed_sz;

	return arr;
}

void dyarray_release(void* arr) {
	if (arr != NULL) {
		int* p = ((int*)(arr)) - 2;
		free(p);
	}
}

int main()
{
	vec3_t* vecs = NULL;

	for (int i = 0; i < 10; i++) {
		dyarray_push(vecs, pos[i]);
	}

	int count = dyarray_count(vecs);
	printf("Elements count: %d\n", count);

	int sz = dyarray_size(vecs);
	printf("Elements capacity: %d\n", sz);

	vec3_t v = dyarray_pop(vecs);
	printf("pos[last] = [ %f, %f, %f ]\n", v.x, v.y, v.z);
	
	vec3_t v3 = vecs[3];
	printf("pos[4] = [ %f, %f, %f ]\n", v3.x, v3.y, v3.z);
	
	int count_after_del = dyarray_count(vecs);
	printf("Elements count: %d\n", count_after_del);

	int sz_after_del = dyarray_size(vecs);
	printf("Elements capacity: %d\n", sz_after_del);

	dyarray_release(vecs);

	// getchar();

	return 0;
}