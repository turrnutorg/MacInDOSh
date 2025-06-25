#ifndef STDLIB_H
#define STDLIB_H

#pragma once
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

void  memory_init(void);
void* malloc(size_t);
void  free(void*);

#define ENOMEM -12  // hack error code for oom

#endif
