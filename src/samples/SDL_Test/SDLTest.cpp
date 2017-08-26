#include <solar\core\Application.h>
#include <solar\core\Context.h>
#include <solar\window\Window.h>
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

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
			Graphics* graphics = GetSubsystem<Graphics>();
			graphics->setWindowTitle("hello");
			graphics->setMode(1280, 720, false, false, false, false, 0, 60);

		}

		virtual void start()
		{
			SOLAR_LOGINFO() << "Started SDL Test";
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

	private:
	};
}

int main(int, char**)
{
	solar::Context* context = new solar::Context();
	solar::Game* game = new solar::Game(context);
	solar::Application* app = new solar::Application(context, game);
	return app->run();
}