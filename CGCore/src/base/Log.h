#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace CGCore {
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}
#ifdef CG_DEBUG || CG_RELEASE
	#define CG_CORE_INFO(...) CGCore::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define CG_CORE_WARN(...) CGCore::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define CG_CORE_ERROR(...) CGCore::Log::GetCoreLogger()->error(__VA_ARGS__);

	#define CG_CLIENT_INFO(...) CGCore::Log::GetClientLogger()->info(__VA_ARGS__);
	#define CG_CLIENT_WARN(...) CGCore::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define CG_CLIENT_ERROR(...) CGCore::Log::GetClientLogger()->error(__VA_ARGS__);
#else
	#define CG_CORE_INFO(...) 
	#define CG_CORE_WARN(...)
	#define CG_CORE_ERROR(...) 

	#define CG_CLIENT_INFO(...)
	#define CG_CLIENT_WARN(...) 
	#define CG_CLIENT_ERROR(...)
#endif
