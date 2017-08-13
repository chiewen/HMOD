#pragma once  
#include "stdafx.h"

//#ifdef DGEN_EXPORTS  
//#define DGEN_API __declspec(dllexport)   
//#else  
//#define DGEN_API __declspec(dllimport)   
//#endif  

namespace DataGenerator {
	class Network {
	public:
		static int vertex_num();
		static int edge_num();
	};
}
