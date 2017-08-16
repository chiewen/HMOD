#include "stdafx.h"
#include "objects.h"
#include "index_.h"

Object Objects::objects_[Objects::kTotalObjectNum];

void Objects::Initialize() {
	for (int i = 0; i < kTotalObjectNum; ++i) {
		objects_[i].id_ = i;

		objects_[i].cell_id = rand() % Index::kCellNum;

		objects_[i].vertex_pos_ = rand() % Index::grid_[objects_[i].cell_id].vertex_num;
		auto& vertex = Index::grid_[objects_[i].cell_id].vertex_[objects_[i].vertex_pos_];

		objects_[i].edge_pos_ = rand() % vertex.edge_num_;
		auto& edge = vertex.edges_[objects_[i].edge_pos_];
		objects_[i].edge_id_ = edge.id_;

		objects_[i].position_ = rand() % edge.length_;
		objects_[i].speed_ = kMinSpeed + rand() % (kMaxSpeed - kMinSpeed);
	}
}

void Objects::Step() {
	for (int i = 0; i < kTotalObjectNum; ++i) {
		auto& o = objects_[i];
		o.position_ += o.speed_;

		auto& edge = Index::grid_[o.cell_id].vertex_[o.vertex_pos_].edges_[o.edge_pos_];
		auto edge_length = edge.length_;
		while (o.position_ >= edge_length) {
			o.position_ -= edge_length;
			o.cell_id = edge.to_cell_;
			o.vertex_pos_ = edge.to_vertex_pos_;
			int new_edge_pos = rand() % Index::grid_[o.cell_id].vertex_[o.vertex_pos_].edge_num_;
			auto& new_edge = Index::grid_[o.cell_id].vertex_[o.vertex_pos_].edges_[new_edge_pos];
			o.edge_pos_ = new_edge_pos;
			o.edge_id_ = new_edge.id_;
		}
	}
}
