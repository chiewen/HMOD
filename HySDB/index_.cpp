#include "stdafx.h"
#include "index_.h"

Index Index::index_;
Index::Cell Index::grid_[Index::kCellNum];

Index::Cell& Index::get_cell(int x, int y) {
	return grid_[z_order_x[x] + z_order_y[y]];
}

void Index::Initialize() {
	int id = 0;
	for (int i = 0; i < kCellNum; ++i) {
		int vertex_num = kMaxVerticesPerCell - rand() % (kMaxVerticesPerCell / 2);
		grid_[i].vertex_num = vertex_num;
		for (int j = 0; j < vertex_num; ++j) {
			grid_[i].vertex_[j].id_ = id++;
		}
	}
}
