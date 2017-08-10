#pragma once  
#include "stdafx.h"

#ifdef HYS_EXPORTS  
#define HYS_API __declspec(dllexport)   
#else  
#define HYS_API __declspec(dllimport)   
#endif  

namespace HySDB {
	class HySDB {
	public:
		static int HYS_API initial();
		static int HYS_API test();
		static int HYS_API device_info();
	};
}

