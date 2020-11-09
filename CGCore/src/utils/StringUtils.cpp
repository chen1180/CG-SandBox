#include "pch.h"
#include "StringUtils.h"
namespace CGCore {
	std::string& SlashesToBackSlashes(std::string& string)
	{
		size_t len = string.length();
		for (size_t i = 0; i < len; i++)
		{
			if (string[i] == '/')
			{
				string[i] = '\\';
			}
		}
		return string;
	}
	std::string& BackSlashesToSlashes(std::string& string)
	{
		size_t len = string.length();
		for (size_t i = 0; i < len; i++)
		{
			if (string[i] == '\\')
			{
				string[i] = '/';
			}
		}
		return string;
	}

}