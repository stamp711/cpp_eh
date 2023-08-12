#include <unwind.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <typeinfo>

namespace __cxxabiv1 {
struct __class_type_info {
  virtual void foo() {}
};

__class_type_info __si_class_type_info;
}  // namespace __cxxabiv1

#define EXCEPTION_BUFFER_SIZE 1024
std::byte exception_buffer[EXCEPTION_BUFFER_SIZE];

extern "C" {

typedef void (*unexpected_handler)();
typedef void (*terminate_handler)();

struct __cxa_exception {
  std::type_info *exceptionType;
  void (*exceptionDestructor)(void *);
  unexpected_handler unexpectedHandler;
  terminate_handler terminateHandler;
  __cxa_exception *nextException;

  int handlerCount;
  int handlerSwitchValue;
  const char *actionRecord;
  const char *languageSpecificData;
  void *catchTemp;
  void *adjustedPtr;

  _Unwind_Exception unwindHeader;
};

void *__cxa_allocate_exception(size_t thrown_size) {
  if (thrown_size > EXCEPTION_BUFFER_SIZE) {
    printf("Exception too large\n");
    exit(1);
  }

  auto res = exception_buffer;
  return res;
}

void __cxa_free_exception(void *thrown_exception) {
  printf("Freeing exception %p\n", thrown_exception);
}

void __cxa_throw(void *thrown_exception, std::type_info *tinfo,
                 void (*dest)(void *)) {
  printf("> cxa_throw\n");
  printf("Throwing exception %p\n", thrown_exception);
  if (tinfo) {
    printf("Exception type: %s\n", tinfo->name());
  }
  printf("Exception destructor: %p\n", dest);

  __cxa_exception *header = ((__cxa_exception *)thrown_exception - 1);
  _Unwind_RaiseException(&header->unwindHeader);

  printf("__cxa_throw exiting\n");
  exit(0);
}

void *__cxa_begin_catch(void *exceptionObject) {}

void __cxa_end_catch() {}

_Unwind_Reason_Code __gxx_personality_v0(
    int version, _Unwind_Action actions, uint64_t exceptionClass,
    struct _Unwind_Exception *exceptionObject,
    struct _Unwind_Context *context) {
  printf("> __gxx_personality_v0\n");

  if (actions & _UA_SEARCH_PHASE) {
    printf("search phase\n");
    return _URC_HANDLER_FOUND;
  } else if (actions & _UA_CLEANUP_PHASE) {
    printf("cleanup phase\n");
    return _URC_INSTALL_CONTEXT;
  } else {
    printf("unknown action\n");
    return _URC_FATAL_PHASE1_ERROR;
  }

  return _URC_CONTINUE_UNWIND;
}
}