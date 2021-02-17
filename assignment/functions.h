#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>   // bool
#include <sys/types.h> // size_t

long sum(int a, int b);
bool isFib(int n);
char* fizzbuzz(int i, char* dest, size_t n);

#endif
