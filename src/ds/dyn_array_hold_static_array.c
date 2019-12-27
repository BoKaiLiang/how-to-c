#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_SIZE 4

typedef float vec4[4];

typedef struct {
    vec4* arr;
    size_t count;
    size_t size;
} vec4_dynarr;

void dynarr_init(vec4_dynarr* dynarr) {
    dynarr->count = 0;
    dynarr->size = INIT_SIZE;
    if (NULL == (dynarr->arr = calloc(INIT_SIZE, sizeof(vec4)))){
        perror("Failed to initialize vec4 dynamic array.\n");
        exit(EXIT_FAILURE);
    }
}

void dynarr_free(vec4_dynarr* dynarr) {
    if (NULL != dynarr->arr) {
        free(dynarr->arr);
    }
}

void dynarr_push(vec4_dynarr* dynarr, const vec4 vec) {

    if (NULL == dynarr || NULL == dynarr->arr) {
        return;
    }

    if ((dynarr->count * 2) >= dynarr->size) {
        dynarr->size *= 2;
        vec4* temp = realloc(dynarr->arr,
                        sizeof *dynarr->arr * dynarr->size);
        if (NULL == temp) {
            perror("Unable to reallocate.\n");
            return;
        } 
        else {
            dynarr->arr = temp;
        }
    }

    memcpy(dynarr->arr[dynarr->count], vec, sizeof(vec4));
    dynarr->count++;
}

void dynarr_pop(vec4_dynarr* dynarr, vec4 dst) {

    if (NULL == dynarr || NULL == dynarr->arr) {
        perror("Dynamic array is empty.\n");
        return;
    }

    dynarr->count--;
    memcpy(dst, &dynarr->arr[dynarr->count], sizeof(vec4));

    if (dynarr->count * 2 < dynarr->size) {
        dynarr->size /= 2;
        vec4* temp = realloc(dynarr->arr,
                        sizeof *dynarr->arr * dynarr->size);
        if (NULL == temp) {
            perror("Unable to reallocate.\n");
            return;
        } 
        else {
            dynarr->arr = temp;
        }
    }
}

void dynarr_debug(const vec4_dynarr* dynarr) {
    for (size_t i = 0; i < dynarr->count; i++) {

        printf("(%d) vector = [\t", i + 1);

        for (size_t j = 0; j < 4; j++) {
            printf("%.2f\t", dynarr->arr[i][j]);
        }

        printf("]\n");
    }
}

int main() {

    vec4_dynarr arr;
    dynarr_init(&arr);

    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });
    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });
    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });
    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });
    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });
    dynarr_push(&arr, (vec4){ 1.0f, 2.0f, 3.0f, 4.0f });


    vec4 out1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    vec4 out2 = { 0.0f, 0.0f, 0.0f, 0.0f };
    dynarr_pop(&arr, out1);
    dynarr_pop(&arr, out2);

    dynarr_debug(&arr);

    printf("Out 1: = [ %f\t%f\t%f\t%f ]\n", out1[0], out1[1], out1[2], out1[3]);
    printf("Out 2: = [ %f\t%f\t%f\t%f ]\n", out2[0], out2[1], out2[2], out2[3]);

    dynarr_free(&arr);

    return 0;
}