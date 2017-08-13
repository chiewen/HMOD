#include "stdafx.h"
#include "index_.h"
#include "z_order.h"

using namespace std;

Index::Cell Index::grid_[Index::kCellNum];

int Index::vertex_num;

int Index::VertexNumInCell() { return kMaxVerticesPerCell - rand() % (kMaxVerticesPerCell / 2); }

int Index::EdgeNumInVertex() { return kMaxEdgesPerVertex - rand() % (kMaxEdgesPerVertex / 2); }

int Index::EdgeLength() { return rand() % 200 + 30; }

void Index::Initialize() {
	//clear all data in Index
	memset(&grid_, 0, sizeof(grid_));
	vertex_num = 0;

	//generate vertices
	int vertex_id = 1;
	for (int i = 0; i < kCellNum; ++i) {
		int vertex_num_in_cell = VertexNumInCell();
		vertex_num += vertex_num_in_cell;
		grid_[i].vertex_num = vertex_num_in_cell;
		for (int j = 0; j < vertex_num_in_cell; ++j) {
			grid_[i].vertex_[j].id_ = vertex_id++;
		}
	}

	//generate edges
	int edge_id = 1;
	for (int i = 0; i < kCellNum; ++i) {
		for (int j = 0; j < grid_[i].vertex_num; ++j) {
			int edge_num_in_vertex = EdgeNumInVertex();
			grid_[i].edge_num += edge_num_in_vertex;
			grid_[i].vertex_[j].edge_number_ = edge_num_in_vertex;
			for (int k = 0; k < edge_num_in_vertex; ++k) {
				auto& edge = grid_[i].vertex_[j].edges_[k];
				edge.id_ = edge_id++;
				edge.length_ = EdgeLength();
				int id_candidate = grid_[i].vertex_[rand() % grid_[i].vertex_num].id_;
				if (id_candidate == grid_[i].vertex_[j].id_) {
					//requires more than one vertex in a cell
					id_candidate = grid_[i].vertex_[(j + 1) % grid_[i].vertex_num].id_;
				}
				edge.to_vertex_ = id_candidate;
				edge.to_cell_ = i;
			}
		}
	}


	for (int i = 0; i < kCellNum; ++i) {
		auto neighbors = ZOrder::NeighborsOf(i);
		for (int j = 0; j < grid_[i].vertex_num; ++j) {
//			neighbors.
		}
	}
}
