#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long _sum(int a, int b){
	return (long) a + b;
}

bool _isFib(int n){
	if (n < 0) return false;
	if (n == 0 || n == 1) return true;

	int ns[2] = {0,1};
	while (n >= ns[1]){
	    //printf("ns[]: %d, %d\n", ns[0], ns[1]);
		if (n == ns[1]) {
			return true;
		} else {
		    int next = ns[0] + ns[1];
		    ns[0] = ns[1];
		    ns[1] = next;
		}
	}
	return false;
}

char* _fizzbuzz(int i, char* dest, size_t n){
	if (i % 3 == 0 && i % 5 == 0){
		strncpy(dest,"FIZZBUZZ",n);
	} else if (i % 3 == 0){
		strncpy(dest,"FIZZ", n);
	} else if (i % 5 == 0){
		strncpy(dest,"BUZZ", n);
	} else {
		memset(dest, 0, n);
		sprintf(dest, "%d", i);
	}

	return dest;
}