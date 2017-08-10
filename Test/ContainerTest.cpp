#include "stdafx.h"

#include <gtest/gtest.h>
#include "DataGenerator.h"
#include "HySDB.h"

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