#pragma once

#include <vector>
#include <array>
#include "OTBox.h"
#include "BoundingVolume.h"

namespace octree
{
	class Octree
	{
	public:
		Octree(OTBox& box)
		{
			_box = box;
			_root = new Node;
		}

		void add(BoundingVolume* value);
		bool remove(BoundingVolume* value);
		std::vector<BoundingVolume*> query(OTBox box);

	private:
		struct Node
		{
			std::array<Node*, 4> children;
			std::vector<BoundingVolume*> values;
		};

		OTBox _box;
		Node* _root;

		void split(Node* node, OTBox box);
		int getOctant(OTBox nodeBox, OTBox valueBox);
		OTBox getSubBox(OTBox box, int i); // i is the index of the sub-box: 0-7
		bool isLeaf(Node* node);
		void removeValue(Node* node, BoundingVolume* value);
		bool mergeNode(Node* node);
	};
}

