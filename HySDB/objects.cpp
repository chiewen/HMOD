#include "stdafx.h"
#include "objects.h"

Object Objects::objects_[Objects::kTotalObjectNum];

void Objects::Initialize() {
	for (int i = 0; i < kTotalObjectNum; ++i) {
		objects_[i].id_ = i;
		
	}	
}
