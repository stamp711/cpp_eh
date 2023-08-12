#include "throw.h"

#include <stdio.h>

struct AnotherException {};

void raise() { throw Exception(); }

void dont_catch() {
  try {
    raise();
  } catch (AnotherException const&) {
    printf("Caught AnotherException\n");
  }

  printf("dont_catch continuing after exception\n");
}

void test_exception() {
  try {
    raise();
  } catch (Exception const&) {
    printf("Caught exception\n");
  }

  printf("test_exception continuing after exception\n");
}