#pragma once

#include "..\core\Object.h"

#include <set>

namespace solar
{

	class Input : public Object
	{
		SOLAR_OBJECT(Input)
	public:
		Input(Context* context);
		virtual ~Input();

		void update();

		bool getKeyDown(int key) const;
		bool getKeyPressed(int key) const;



	};

}