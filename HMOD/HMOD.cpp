// HMOD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "data_generator.h"
#include "hybrid_spatial_db.h"
#include "index_.h"

using namespace std;

void GenerateZOrder() {
	for (int x = 0; x < 256; x++) {
		int i = (x & 0x80) << 7 |
			(x & 0x40) << 6 |
			(x & 0x20) << 5 |
			(x & 0x10) << 4 |
			(x & 0x08) << 3 |
			(x & 0x04) << 2 |
			(x & 0x02) << 1 |
			(x & 0x01) << 0 ;
		i <<= 1;
		cout << i << ", ";
	}
	cout << endl;
}

int main()
{
	std::cout << "hello world" << endl;
	HySDB::HySDB::test();

//	GenerateZOrder();
    return 0;
}

