﻿#pragma once
#include "stdafx.h"
#include "gtest_prod.h"

class Index {
	FRIEND_TEST(Index, Initialization);

	static int VertexNumInCell();
	static int EdgeNumInVertex();
	static int EdgeLength();

public:
	static const int kCellNum = 1 << 4;
	static const int kMaxVerticesPerCell = 1 << 3;
	static const int kMaxEdgesPerVertex = 1 << 3;

	static int vertex_num;

	struct Vertex {
		int id_;
		int edge_number_;

		struct Edge {
			int id_;
			int length_;
			int to_vertex_;
			int to_cell_;
		} edges_[kMaxEdgesPerVertex];
	};

	struct Cell {
		int vertex_num;
		int edge_num;
		Vertex vertex_[kMaxVerticesPerCell];
	};

	static Cell grid_[kCellNum];

	static void Initialize();
};
