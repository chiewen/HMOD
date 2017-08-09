#pragma once  
#include "stdafx.h"

#ifdef DGEN_EXPORTS  
#define DGEN_API __declspec(dllexport)   
#else  
#define DGEN_API __declspec(dllimport)   
#endif  

namespace DataGenerator {
	class Network {
	public:
		static DGEN_API int vertex_num();
		static DGEN_API int edge_num();
	};
}
