#include <unwind.h>

#include <cstddef>
#include <cstdint>
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

void *__cxa_allocate_exception(size_t thrown_size) { return nullptr; }

void __cxa_free_exception(void *thrown_exception) {}

void __cxa_throw(void *thrown_exception, std::type_info *tinfo,
                 void (*dest)(void *)) {}

void *__cxa_begin_catch(void *exceptionObject) {}

void __cxa_end_catch() {}

_Unwind_Reason_Code __gxx_personality_v0(
    int version, _Unwind_Action actions, uint64_t exceptionClass,
    struct _Unwind_Exception *exceptionObject,
    struct _Unwind_Context *context) {}
}