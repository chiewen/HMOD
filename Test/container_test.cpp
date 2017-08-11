#include "stdafx.h"

#include <gtest/gtest.h>
#include "data_generator.h"
#include "hybrid_spatial_db.h"
#include "index_.h"

TEST(Container, Test0) {
	EXPECT_EQ(3, 3);
}

TEST(Container, Test2) {
	EXPECT_EQ(2, 2);
}

TEST(Container, Test1) {
	EXPECT_EQ(1, 1);
}

TEST(Modify, Add) {
	EXPECT_EQ(4, DataGenerator::Network::edge_num());
}

TEST(CUDA, Add) {
	EXPECT_EQ(0, HySDB::HySDB::initial());
}

TEST(Index, Common) {
	EXPECT_EQ(Index::kCellNum, 256);
	EXPECT_EQ(Index::kMaxVerticesPerCell, 256);
	EXPECT_EQ(Index::kMaxEdgesPerVertex, 8);
	EXPECT_EQ(sizeof(int), 4);
	EXPECT_EQ(sizeof(Index::grid_), 
		sizeof(int) * 
		Index::kCellNum * (2 +
		Index::kMaxVerticesPerCell * (2 +
		Index::kMaxEdgesPerVertex * 3)));
	EXPECT_EQ(z_order_x[5] + z_order_y[6], 57);
}
