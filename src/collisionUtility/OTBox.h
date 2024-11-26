#pragma once

#include "../maths/vec3.h"

namespace octree
{
	class OTBox
	{
	public:
		OTBox(float x, float y, float z, float w, float h, float d)
		{
			position = maths::vec3(x, y, z);
			extent = maths::vec3(w, h, d);
		}

		OTBox(maths::vec3 pos, maths::vec3 ext)
		{
			position = pos;
			extent = ext;
		}

		OTBox(float x, float y, float z, maths::vec3 ext)
		{
			position = maths::vec3(x, y, z);
			extent = ext;
		}

		OTBox()
		{
			position = maths::vec3(0.0f);
			extent = maths::vec3(1.0f);
		}

		maths::vec3 getPosition() { return position; }
		maths::vec3 getExtent() { return extent; }
		maths::vec3 getMaxEdge() { return maths::vec3(position.x() + extent.x() / 2.0f, position.y() + extent.y() / 2.0f, position.z() + extent.z() / 2.0f); }
		maths::vec3 getMinEdge() { return maths::vec3(position.x() - extent.x() / 2.0f, position.y() - extent.y() / 2.0f, position.z() - extent.z() / 2.0f); }

		bool contains(OTBox& other);
		bool intersects(OTBox& other);

	private:
		maths::vec3 position;
		maths::vec3 extent;
	};
}

