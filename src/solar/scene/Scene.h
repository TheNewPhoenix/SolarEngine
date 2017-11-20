#pragma	once

#include "..\core\Object.h"
#include "Node.h"

namespace solar
{

	class Scene : public Node
	{
	public:
		Scene(Context* context);
		virtual ~Scene();
	};

}