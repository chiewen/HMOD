#pragma once
#include "stdafx.h"

class ZOrder {
	FRIEND_TEST(Index, ZOrder);
	static const int kLength = 256;
	static const int z_order_x[];
	static const int z_order_y[];
public:

	static void GenerateZOrder();

	static int CellIdFromXY(int x, int y) {
		return z_order_x[x] + z_order_y[y];
	}

	static std::pair<int, int> GetXYFromCellId(int cell_id);
	
	static std::vector<int> NeighborsOf(int cell_id);
};
