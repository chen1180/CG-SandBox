#pragma once
#include"Log.h"
#include<memory>
#ifdef CG_DEBUG
#define CG_CORE_ASSERT(x,...) {if(!x) {CG_CORE_ERROR("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}
#define CG_CLIENT_ASSERT(x,...) {if(!x) {CG_CLIENT_ASSERT("Assertion error: {0}!",__VA_ARGS__);__debugbreak();}}
#else
#define CG_CORE_ASSERT(x,...)
#define CG_CLIENT_ASSERT(x,...)
#endif // DEBUG


#define BIT(x) (1 << x)
#define  EVENT_CB_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace CGCore {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>

	constexpr Ref<T> CreateRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

//math
#define EPSILON 0.0001f
