#include "cpp.hpp"
#include "malloc.h"
#include "platform/fatal.h"

#ifndef ATEXIT_MAX_DESTRUCTORS
#define ATEXIT_MAX_DESTRUCTORS 128
#endif

#if defined _MSC_VER

int __cdecl _purecall(void){
    OS216_FATAL("Pure virtual method call!");
}

#elif defined __GNUC__

typedef void *cxa_destructor_arg;
typedef void(*cxa_destructor)(cxa_destructor_arg);

extern "C" {

void __cxa_pure_virtual(void);
int __cxa_atexit(cxa_destructor destructor, void *arg, void *);
void __cxa_finalize(void*);

}

void __cxa_pure_virtual(void){
    OS216_FATAL("Pure virtual method call!");
}

static cxa_destructor_arg destructor_args[ATEXIT_MAX_DESTRUCTORS];
static cxa_destructor destructors[ATEXIT_MAX_DESTRUCTORS];
static unsigned num_destructors = 0;

int __cxa_atexit(cxa_destructor destructor, void *arg, void *){
    
    if(!destructor)
        return 0;
    
    destructor_args[num_destructors] = arg;
    destructors[num_destructors] = destructor;
    num_destructors++;
    return 0;
}

void __cxa_finalize(void *f){
    unsigned i = 0;
    if(!f){
        while(i < num_destructors){
            destructors[i](destructor_args[i]);
        }
    }
    else{
        while(i < num_destructors){
            cxa_destructor destructor = destructors[i];
            if(destructor == (cxa_destructor)f){
                destructor(destructor_args[i]);
                destructors[i] = (cxa_destructor)0;
                return;
            }
        }
    }
}

#else
#error Add a C++ calls for your compiler here!
#endif

void *operator new(size_t size){
    return malloc(size);
}

void *operator new[](size_t size){
    return malloc(size);
}

void operator delete(void *mem){
    free(mem);
}

void operator delete[](void *mem){
    free(mem);
}
