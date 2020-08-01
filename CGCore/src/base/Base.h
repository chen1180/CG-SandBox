#include"Log.h"
#ifdef CG_DEBUG
	#define CG_CORE_ASSERT(x,...) {if(!x) {CG_CORE_ERROR("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}
	#define CG_CLIENT_ASSERT(x,...) {if(!x) {CG_CLIENT_ASSERT("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}
#else
	#define CG_CORE_ASSERT(x,...)
	#define CG_CLIENT_ASSERT(x,...)
#endif // DEBUG


#define BIT(x) (1 << x)
#define  EVENT_CB_FUNC(x) std::bind(&x, this, std::placeholders::_1)