#pragma once
#include "stdafx.h"

struct Object {
	int id_;
	int edge_;
	int position_;
};
class Objects {
public:
	static const int kTotalObjectNum = 1000;
	static Object objects_[];

	static void Initialize();
};
