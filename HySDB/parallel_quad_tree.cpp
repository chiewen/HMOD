#include "stdafx.h"
#include "parallel_quad_tree.h"
#include "index.h"

QuadTree QuadTree::root_tree_{make_unique<Bucket>(), LEFT, RIGHT, FLOOR, CEILING};

unordered_set<QuadTree *> QuadTree::quad_leafs{};

QuadTree::QuadTree(unique_ptr<Bucket>&& bucket, int left, int right, int floor, int ceiling) :
	children{}, ptr_bucket_{move(bucket)}, left(left), right(right), floor(floor), ceiling(ceiling),
	x_middle((left + right) / 2), y_middle((floor + ceiling) / 2) {}

//TODO call cuda code
void QuadTree::Balance() { }


void QuadTree::AddSite(int id, int x, int y) {
	auto added = AddToLeaf(id, x, y);
	auto& si = Index::get_instance();
	assert(si.find(id) == si.end());
	si.emplace(make_pair(id, Element(added.first, added.second)));
}

QuadTree* QuadTree::GetLeaf(int x, int y) {
	if (IsLeaf())
		return this;
	else {
		if (x >= x_middle) {
			if (y >= y_middle) return children[0]->GetLeaf(x, y);
			else return children[3]->GetLeaf(x, y);
		}
		else {
			if (y >= y_middle) return children[1]->GetLeaf(x, y);
			else return children[2]->GetLeaf(x, y);
		}
	}
}

pair<Bucket*, unsigned> QuadTree::AddToLeaf(int id, int x, int y) {
	auto p_quad_tree = root_tree_.GetLeaf(x, y);

	if (p_quad_tree->ptr_bucket_->is_full()) {
		auto new_bucket = make_unique<Bucket>();
		new_bucket->next_ = move(p_quad_tree->ptr_bucket_);
		p_quad_tree->ptr_bucket_ = move(new_bucket);
	}
	return p_quad_tree->ptr_bucket_->Add(id, x, y);
}

void QuadTree::DelSite(int id) {
	auto& element = Index::get_instance().find(id)->second;
	RemoveFromLeaf(id, element.p_bucket);
}

bool QuadTree::RemoveFromLeaf(int id, Bucket* p_bucket) {
	return true;
}

void QuadTree::MoveSite(int id, int x_new, int y_new) {
	auto& element = Index::get_instance().find(id)->second;
	auto site = element.p_bucket->sites_[element.index].Value();
	auto p_old = root_tree_.GetLeaf(site.x, site.y);
	auto p_new = root_tree_.GetLeaf(x_new, y_new);

	//LATER concurrency control
	if (p_new == p_old) {
		element.p_bucket->sites_[element.index].SetValue(id, site.x, site.y, static_cast<int>(time(nullptr)));
	}
	else {
		auto added = p_new->AddToLeaf(id, x_new, y_new);
		p_old->RemoveFromLeaf(id, p_old->ptr_bucket_.get());
		element.p_bucket = added.first;
		element.index = added.second;
	}
}

void QuadTree::Query(vector<SiteValue>& result, int x1, int y1, int x2, int y2, int tq) {
	if (x1 > RIGHT || x2 < LEFT || y1 > CEILING || y2 < FLOOR)
		return;

	Bucket* p_bucket = ptr_bucket_.get();
	while (p_bucket) {
		for (unsigned i = 0; i < p_bucket->current_; ++i) {
			auto site = p_bucket->sites_[i].Value();
			if (site.x >= x1 && site.x <= x2 && site.y >= y1 && site.y <= y2)
				result.emplace_back(site);
		}
		p_bucket = p_bucket->next_.get();
	}

	if (!IsLeaf()) {
		children[0]->Query(result, x1, y1, x2, y2, tq);
		children[1]->Query(result, x1, y1, x2, y2, tq);
		children[2]->Query(result, x1, y1, x2, y2, tq);
		children[3]->Query(result, x1, y1, x2, y2, tq);
	}
}

void QuadTree::Split() {
	//LATER concurrency control
	auto p0 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, y_middle, ceiling);
	auto p1 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, y_middle, ceiling);
	auto p2 = make_unique<QuadTree>(make_unique<Bucket>(), left, x_middle, floor, y_middle);
	auto p3 = make_unique<QuadTree>(make_unique<Bucket>(), x_middle, right, floor, y_middle);
	children[0] = move(p0);
	children[1] = move(p1);
	children[2] = move(p2);
	children[3] = move(p3);

	children[0]->ptr_parent = this;
	children[1]->ptr_parent = this;
	children[2]->ptr_parent = this;
	children[3]->ptr_parent = this;

	auto f = quad_leafs.find(ptr_parent);
	if (f != quad_leafs.end())
		quad_leafs.erase(f);
	quad_leafs.insert(this);
}

void QuadTree::linkBuckets(QuadTree* child) {
	lock_guard<mutex>{child->mutex_};
	Bucket* p_bucket = child->ptr_bucket_.get();
	while (p_bucket->next_) p_bucket = p_bucket->next_.get();
	p_bucket->next_ = move(ptr_bucket_);
	ptr_bucket_ = move(child->ptr_bucket_);
}

void QuadTree::Merge() {
	assert(children[0]->IsLeaf());
	assert(children[1]->IsLeaf());
	assert(children[2]->IsLeaf());
	assert(children[3]->IsLeaf());

	//LATER concurrency control
	linkBuckets(children[0].get());
	linkBuckets(children[1].get());
	linkBuckets(children[2].get());
	linkBuckets(children[3].get());

	children[0].reset();
	children[1].reset();
	children[2].reset();
	children[3].reset();

	Bucket* p_bucket = ptr_bucket_.get();
	while (p_bucket) {
		while (p_bucket->next_ && p_bucket->next_->current_ == 0)
			p_bucket->next_ = move(p_bucket->next_->next_);
		p_bucket = p_bucket->next_.get();
	}
	if (ptr_bucket_->next_ && ptr_bucket_->current_ == 0)
		ptr_bucket_ = move(ptr_bucket_->next_);

	auto f = quad_leafs.find(this);
	if (f != quad_leafs.end())
		quad_leafs.erase(f);
	if (ptr_parent && ptr_parent->children[0]->IsLeaf() &&
		ptr_parent->children[1]->IsLeaf() &&
		ptr_parent->children[2]->IsLeaf() &&
		ptr_parent->children[3]->IsLeaf())
		quad_leafs.insert(ptr_parent);
}
