#pragma once

#include "../maths/vec3.h"

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

	maths::vec3 getPosition() { return position; }
	maths::vec3 getExtent() { return extent; }

	bool contains(float box);

private:
	maths::vec3 position;
	maths::vec3 extent;
};

