#pragma once

namespace solar
{

	class Properties
	{
	public:
		Properties();
		~Properties();

		void load(const char* filepath);				
	};

}