#include "stdlib.h"
#include <stdint.h>
#include <stddef.h>

extern uint8_t __heap_start;
extern uint8_t __heap_end;

#define ALIGNMENT 8

typedef struct block_header {
    size_t size;
    int free;
    struct block_header* next;
} block_header;

static block_header* head = NULL;

static size_t align(size_t size) {
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

void memory_init(void) {
    if (head) return;
    head = (block_header*)&__heap_start;
    size_t total = (&__heap_end - &__heap_start);

    head->size = total - sizeof(block_header);
    head->free = 1;
    head->next = NULL;
}

void* malloc(size_t size) {
    if (!head) memory_init();
    if (!size) return NULL;

    size = align(size);

    block_header* curr = head;
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + sizeof(block_header) + ALIGNMENT) {
                block_header* new_block = (block_header*)((uint8_t*)curr + sizeof(block_header) + size);
                new_block->size = curr->size - size - sizeof(block_header);
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }
            curr->free = 0;
            return (uint8_t*)curr + sizeof(block_header);
        }
        curr = curr->next;
    }
    return NULL;
}

void free(void* ptr) {
    if (!ptr) return;
    block_header* block = (block_header*)((uint8_t*)ptr - sizeof(block_header));
    block->free = 1;

    // coalesce with next block if free
    if (block->next && block->next->free) {
        block->size += sizeof(block_header) + block->next->size;
        block->next = block->next->next;
    }

    // optional: coalesce backwards? not unless you track prev
}
