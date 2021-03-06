#include <solar\core\Application.h>
#include <solar\core\Context.h>
#include <solar\graphics\StaticModel.h>
#include <solar\graphics\Graphics.h>
#include <solar\graphics\Camera.h>
#include <solar\graphics\opengl\Program.h>
#include <solar\graphics\Color.h>
#include <solar\io\Log.h>
#include <solar\resource\Model.h>

#include <iostream>
#include <string>
#include <memory>

namespace solar
{

	class Game : public ApplicationAdapter
	{
	public:
		Game(Context* context) :
			ApplicationAdapter(context)
		{
		}

		virtual ~Game()
		{
		}

		virtual void setup()
		{

		}

		virtual void start()
		{
			SOLAR_LOGINFO() << "Started Log Test";
			SOLAR_LOGDEBUG() << "Started Log Test";
			SOLAR_LOGDEBUG() << "Log numbers: " << 1;
		}

		virtual void stop()
		{
		}

		virtual void handleUpdate(const char* eventType, EventParameters& params)
		{

		}

		virtual void handleRender(const char* eventType, EventParameters& params)
		{
		}

		virtual void handleResize(const char* eventType, EventParameters& params)
		{
		}
	};
}

int main(int, char**)
{
	solar::Context* context = new solar::Context();
	solar::Game* game = new solar::Game(context);
	solar::Application* app = new solar::Application(context, game);
	return app->run();

	return 0;
}