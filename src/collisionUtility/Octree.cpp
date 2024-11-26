#include "Octree.h"

namespace octree
{
	void Octree::remove(BoundingVolume* value)
	{
		remove(_root, _box, value);
	}

	bool Octree::remove(Node* node, OTBox box, BoundingVolume* value)
	{
		if (node != nullptr && box.contains(getBoxFromBV(value)))
		{
			if (isLeaf(node))
			{
				return removeValue(node, value);
			}
			else
			{
				auto i = getOctant(box, getBoxFromBV(value));
				if (i != -1)
				{
					if (remove(node->children[i], getSubBox(box, i), value))
					{
						return mergeNode(node);
					}
				}
				else
				{
					return removeValue(node, value);
				}
			}
		}
		else
		{
			return false;
		}
	}

	void Octree::add(BoundingVolume* value)
	{
		add(_root, 0, _box, value);
	}

	void Octree::add(Node* node, int depth, OTBox box, BoundingVolume* value)
	{
		if (node != nullptr && box.contains(getBoxFromBV(value)))
		{
			if (isLeaf(node))
			{
				if (depth >= _MAXDEPTH || node->values.size() < _THRESHOLD)
				{
					node->values.push_back(value);
				}
				else
				{
					split(node, box);
					add(node, depth, box, value);
				}
			}
			else
			{
				auto i = getOctant(box, getBoxFromBV(value));
				if (i != -1)
				{
					add(node->children[i], depth + 1, getSubBox(box, i), value);
				}
				else
				{
					node->values.push_back(value);
				}
			}
		}
	}

	std::vector<BoundingVolume*> Octree::query(OTBox queryBox)
	{
		auto values = std::vector<BoundingVolume*>();
		query(_root, _box, queryBox, values);
		return values;
	}

	void Octree::query(Node* node, OTBox box, OTBox queryBox, std::vector<BoundingVolume*> values)
	{
		if (node != nullptr && queryBox.intersects(box))
		{
			for (auto& value : node->values)
			{
				if (queryBox.intersects(getBoxFromBV(value)))
				{
					values.push_back(value);
				}
			}
			if (!isLeaf(node))
			{
				for (int i = 0; i < node->children.size(); i++)
				{
					auto childBox = getSubBox(box, i);
					if (queryBox.intersects(childBox))
					{
						query(node->children[i], childBox, queryBox, values);
					}
				}
			}
		}
	}

	OTBox Octree::getBoxFromBV(BoundingVolume* bv)
	{
		return OTBox(bv->getCenter(), maths::vec3(bv->getRadius() * 2.0f));
	}

	void Octree::split(Node* node, OTBox box)
	{
		if (node != nullptr && isLeaf(node))
		{
			for (auto& child : node->children)
			{
				child = new Node;
			}
			auto newValues = std::vector<BoundingVolume*>();
			for (auto& value : node->values)
			{
				auto i = getOctant(box, getBoxFromBV(value));
				if (i != -1)
				{
					node->children[i]->values.push_back(value);
				}
				else
				{
					newValues.push_back(value);
				}
			}
			node->values = std::move(newValues);
		}
	}

	int Octree::getOctant(OTBox nodeBox, OTBox valueBox)
	{
		auto center = nodeBox.getPosition();
		auto front = valueBox.getMinEdge().z();
		auto back = valueBox.getMaxEdge().z();
		auto top = valueBox.getMaxEdge().y();
		auto bottom = valueBox.getMinEdge().y();
		auto left = valueBox.getMinEdge().x();
		auto right = valueBox.getMaxEdge().x();

		// front
		if (back <= center.z())
		{
			// top
			if (bottom >= center.y())
			{
				// left
				if (right <= center.x())
				{
					return 0;
				}
				// right
				else if (left > center.x())
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
			// bottom
			else if (top < center.y())
			{
				// left
				if (right <= center.x())
				{
					return 2;
				}
				// right
				else if (left > center.x())
				{
					return 3;
				}
				else
				{
					return - 1;
				}
			}
			else
			{
				return -1;
			}
		}
		// back
		else if (front > center.z())
		{
			// top
			if (bottom >= center.y())
			{
				// left
				if (right <= center.x())
				{
					return 4;
				}
				// right
				else if (left > center.x())
				{
					return 5;
				}
				else
				{
					return -1;
				}
			}
			// bottom
			else if (top < center.y())
			{
				// left
				if (right <= center.x())
				{
					return 6;
				}
				// right
				else if (left > center.x())
				{
					return 7;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}

	OTBox Octree::getSubBox(OTBox box, int i)
	{
		auto origin = box.getPosition();
		auto size = box.getExtent() / 2.0f;
		
		switch (i)
		{
			// top front left
			case 0:
				return OTBox(origin.x() - size.x() / 2.0f, origin.y() + size.y() / 2.0f, origin.z() - size.z() / 2.0f, size);

			// top front right
			case 1:
				return OTBox(origin.x() + size.x() / 2.0f, origin.y() + size.y() / 2.0f, origin.z() - size.z() / 2.0f, size);

			// bottom front left
			case 2:
				return OTBox(origin.x() - size.x() / 2.0f, origin.y() - size.y() / 2.0f, origin.z() - size.z() / 2.0f, size);

			// bottom front right
			case 3:
				return OTBox(origin.x() + size.x() / 2.0f, origin.y() - size.y() / 2.0f, origin.z() - size.z() / 2.0f, size);

			// top back left
			case 4:
				return OTBox(origin.x() - size.x() / 2.0f, origin.y() + size.y() / 2.0f, origin.z() + size.z() / 2.0f, size);

			// top back right
			case 5:
				return OTBox(origin.x() + size.x() / 2.0f, origin.y() + size.y() / 2.0f, origin.z() + size.z() / 2.0f, size);

			// bottom back left
			case 6:
				return OTBox(origin.x() - size.x() / 2.0f, origin.y() - size.y() / 2.0f, origin.z() + size.z() / 2.0f, size);

			// bottom back right
			case 7:
				return OTBox(origin.x() + size.x() / 2.0f, origin.y() - size.y() / 2.0f, origin.z() + size.z() / 2.0f, size);

			default:
				return OTBox();
		}
	}

	bool Octree::removeValue(Node* node, BoundingVolume* value)
	{
		if (std::find(node->values.begin(), node->values.end(), value) != node->values.end())
		{
			value = std::move(node->values.back());
			node->values.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Octree::mergeNode(Node* node)
	{
		if (node != nullptr && isLeaf(node))
		{
			auto nbValues = node->values.size();
			for (auto& child : node->children)
			{
				if (!isLeaf(child))
				{
					return false;
				}
				nbValues += child->values.size();
			}
			if (nbValues <= _THRESHOLD)
			{
				node->values.reserve(nbValues);
				for (auto& child : node->children)
				{
					for (auto& value : child->values)
					{
						node->values.push_back(value);
					}
				}
				for (auto& child : node->children)
				{
					delete child;
				}

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

