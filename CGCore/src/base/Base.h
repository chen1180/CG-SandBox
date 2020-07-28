#include"Log.h"
#define CG_CORE_ASSERT(x,...) {if(!x) {CG_CORE_ERROR("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}
#define CG_CLIENT_ASSERT(x,...) {if(!x) {CG_CLIENT_ASSERT("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}