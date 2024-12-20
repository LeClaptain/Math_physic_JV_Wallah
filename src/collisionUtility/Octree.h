#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include "OTBox.h"
#include "BoundingVolume.h"

//	Réalisé en s'appuyant sur le projet Quadtree de Pierre Vigier (pvigier) sur GitHub:
//	https://github.com/pvigier/Quadtree

namespace octree
{
	class Octree
	{
	public:
		Octree(OTBox& box)
		{
			_box = box;
			_root = std::make_unique<Node>();
		}

		void add(BoundingVolume* value);
		void remove(BoundingVolume* value);
		std::vector<BoundingVolume*> query(OTBox queryBox) const; // returns all elements contained within the queryBox

		OTBox getBox() { return _box; }

		void draw();

	private: 
		struct Node
		{
			std::array<std::unique_ptr<Node>, 8> children;
			std::vector<BoundingVolume*> values;
		};

		OTBox _box; // base box of the octree, should encompass the entire area where there could be collisions
		std::unique_ptr<Node> _root; // base node
		const int _THRESHOLD = 2; // maximum amount of elements a node can contain
		const int _MAXDEPTH = 8; // maximum amount of levels the tree can contain: this means there can be at most 8^_MAXDEPTH + 1 nodes in the tree, which equals to at most (8^_MAXDEPTH + 1) * _THRESHOLD objects in the tree

		bool isLeaf(Node* node) const
		{
			return !static_cast<bool>(node->children[0]);
		}

		bool remove(Node* node, OTBox box, BoundingVolume* value);
		void add(Node* node, int depth, OTBox box, BoundingVolume* value);
		void query(Node* node, OTBox box, OTBox queryBox, std::vector<BoundingVolume*> &values) const;

		OTBox getBoxFromBV(BoundingVolume* bv) const; // returns a OTBox fitted to the BoundingVolume
		void split(Node* node, OTBox box);
		int getOctant(OTBox nodeBox, OTBox valueBox); // returns the index of the octant the value is in, indices are detailed below
		OTBox getSubBox(OTBox box, int i) const; // i is the index of the sub-box: 0 -> top front left, 1 -> top front right, 2 -> bottom front left, 3 -> bottom front right, 4 -> top back left, 5 -> top back right, 6 -> bottom back left, 7 -> bottom back right
		bool removeValue(Node* node, BoundingVolume* value);
		bool mergeNode(Node* node);

		void drawNode(Node* node, OTBox box);
	};
}

