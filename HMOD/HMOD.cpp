// HMOD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DataGenerator.h"
#include "HySDB.h"

using namespace std;

int main()
{
	std::cout << "hello world" << endl;
	cout << DataGenerator::Network::vertex_num() << endl;
	cout << DataGenerator::Network::edge_num() << endl;

	HySDB::HySDB::test();
	HySDB::HySDB::device_info();
    return 0;
}

