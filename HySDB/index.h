#pragma once

#include <unordered_map>
#include "element.h"

class Bucket;
class QuadTree;
using namespace std;

class Index : public unordered_map<int, Element>{
	FRIEND_TEST(ParallelMOD, QuadTree);
	static Index index;
public:
	static Index& get_instance();
};
