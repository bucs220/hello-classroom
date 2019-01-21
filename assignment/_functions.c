#include <stdio.h>
#include "functions.h"

const int fizzbuzz(int i){
	if (i % 3 == 0 && i % 5 == 0) return FIZZBUZZ;
	else if (i % 3 == 0) return FIZZ;
	else if (i % 5 == 0) return BUZZ;
	else return i;
}

int isFib(int i){
  
}
