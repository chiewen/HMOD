#include "stdafx.h"
#include "hybrid_spatial_db.h"
#include "kernel.h"

#include "subnet_shortest_path.cuh"
#include "check_device_info.cuh"
#include "index_.h"

int HySDB::HySDB::initial() {
	return add();
}

int HySDB::HySDB::test() {
	Index::Initialize();
	return 0;
}

int HySDB::HySDB::device_info() {
	check_device_info();
	return 0;
}

int main() {
}