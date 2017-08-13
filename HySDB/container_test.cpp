#include "stdafx.h"

#include <gtest/gtest.h>
#include "hybrid_spatial_db.h"
#include "index_.h"
#include "z_order.h"

using namespace std;

TEST(Index, Common) {
	EXPECT_EQ(Index::kCellNum, 16);
	EXPECT_EQ(Index::kMaxVerticesPerCell, 8);
	EXPECT_EQ(Index::kMaxEdgesPerVertex, 8);
	EXPECT_EQ(sizeof(int), 4);
	EXPECT_EQ(sizeof(Index::grid_),
		sizeof(int) *
		Index::kCellNum * (2 +
			Index::kMaxVerticesPerCell * (2 +
				Index::kMaxEdgesPerVertex * 4)));
}

TEST(Index, ZOrder) {
	EXPECT_EQ(ZOrder::z_order_x[6] + ZOrder::z_order_y[4], 52);
	auto xy = ZOrder::GetXYFromCellId(52);
	EXPECT_EQ(xy.first, 6);
	EXPECT_EQ(xy.second, 4);
	EXPECT_EQ(ZOrder::z_order_x[5] + ZOrder::z_order_y[6], 57);
	xy = ZOrder::GetXYFromCellId(57);
	EXPECT_EQ(xy.first, 5);
	EXPECT_EQ(xy.second, 6);

	auto neighbors = ZOrder::NeighborsOf(50);
	set<int> should_be{ 37, 45, 49, 57, 48, 56, 39, 51 };
	EXPECT_EQ(neighbors, should_be);

	neighbors = ZOrder::NeighborsOf(18);
	should_be = {5, 13, 17, 25, 16, 24, 7, 19};
	EXPECT_EQ(neighbors, should_be);
}

TEST(Index, Initialization) {
	Index::Initialize();

	//vertex number
	int vertex_sum = 0;
	for (auto& cell : Index::grid_) {
		int count = count_if(begin(cell.vertex_), end(cell.vertex_), [=](const Index::Vertex& v) {
		                     return v.id_ != 0;
	                     });
		EXPECT_EQ(cell.vertex_num, count);
		vertex_sum += count;
	}
	EXPECT_EQ(vertex_sum, Index::vertex_num);

	//edges not pointing to their containing vertices
	for (auto& cell : Index::grid_) {
		for (auto& vertex : cell.vertex_) {
			if (vertex.id_ != 0)
				for (auto& edge : vertex.edges_) {
					if (edge.id_ != 0)
					EXPECT_TRUE(edge.to_vertex_ != vertex.id_);
				}
		}
	}
	ZOrder::GenerateZOrder();
	HySDB::HySDB::test();
}
