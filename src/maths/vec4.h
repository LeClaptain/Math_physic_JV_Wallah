#pragma once

#include <string>
#ifndef IGNORE_GLM
#include <glm/vec4.hpp>
#endif

namespace maths {
	class vec4
	{
	public:
		vec4();

		vec4(float v);

		vec4(float x, float y, float z, float w);

		vec4(const vec4& other);

#ifndef IGNORE_GLM
		vec4(const glm::vec4& other);
#endif

	private:
		float _x, _y, _z, _w;
	};
}

