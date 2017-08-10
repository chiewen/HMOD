#include "stdafx.h"
#include "index.h"

Index Index::index;

Index& Index::get_instance() {
	return index;
}
