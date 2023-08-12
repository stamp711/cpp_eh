#include "throw.h"

#include <stdio.h>

struct Exception {};

struct AnotherException {};

void raise() { throw Exception(); }

void raise_but_cant_catch() {
  try {
    raise();
  } catch (AnotherException const&) {
    printf("Caught AnotherException\n");
  }
  printf("cant_catch continuing after exception???\n");
}

void test_exception() {
  try {
    raise_but_cant_catch();
  } catch (Exception const&) {
    printf("Caught exception\n");
  }
  printf("test_exception continuing after exception\n");
}