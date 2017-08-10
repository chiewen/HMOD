#include "stdafx.h"
#include "HySDB.h"
#include "kernel.h"

#include "SubNetSP.cuh"
#include "checkDeviceInfo.cuh"

int HySDB::HySDB::initial() {
	return add();
}

int HySDB::HySDB::test() {
	return tt();
}

int HySDB::HySDB::device_info() {
	check_device_info();
	return 0;
}
