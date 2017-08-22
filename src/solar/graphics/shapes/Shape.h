#pragma once

#include "..\opengl\Program.h"

namespace solar
{

	class SOLAR_API Shape
	{
	public:
		Shape();

		~Shape();

		void render();

	private:
		Program program;
	};

}