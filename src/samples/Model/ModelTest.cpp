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
			window = new Window(context);
		}

		virtual ~Game()
		{
			delete window;
			delete program;
		}

		virtual void setup()
		{
			window->createWindow();
			window->setTitle(std::string("MODEL TEST"));

			Graphics* graphics = GetSubsystem<Graphics>();
			graphics->enable(GL_DEPTH_TEST);

			Shader vertexShader(GL_VERTEX_SHADER);
			vertexShader.setSource("data/shaders/LightingVertex.glsl");
			vertexShader.compile();

			Shader fragmentShader(GL_FRAGMENT_SHADER);
			fragmentShader.setSource("data/shaders/LightingFragment.glsl");
			fragmentShader.compile();

			program = new Program();
			program->attach(vertexShader);
			program->attach(fragmentShader);
			program->link();

			Model model;
			model.load("data/models/sponza.obj");

			sModel.setModel(model);

			camera.setProjection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f));
			camera.m_position = glm::vec3(0, 4, 0);
			camera.lookAt(glm::vec3(2, 4, 0));

		}

		virtual void start()
		{
			SOLAR_LOGINFO("Started Model Test");
		}

		virtual void stop()
		{
			window->close();
		}

		virtual void handleUpdate(const char* eventType, EventParameters& params)
		{

		}

		virtual void handleRender(const char* eventType, EventParameters& params)
		{
			Graphics* graphics = GetSubsystem<Graphics>();

			camera.update();
			camera.rotate(camera.m_upAxis, 0.01f);

			graphics->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			graphics->clearColor(0.0f, 0.0f, 0.0f, 1.0f);

			program->setUniformVec3fv("u_camPos", camera.m_position);

			program->setUniformVec3f("u_light.position", 0.0f, 1.0f, 4.0f);
			program->setUniformColorRGB("u_light.color", Color(Color::WHITE));

			glm::mat4 model;

			program->setUniformMatrix4fv("u_projView", camera.m_projView);
			program->setUniformMatrix4fv("u_model", model);

			sModel.draw(program);
		}

		virtual void handleResize(const char* eventType, EventParameters& params)
		{
			int width = boost::get<int>(params["width"]);
			int height = boost::get<int>(params["height"]);
			camera.setProjection(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f));
		}

	private:
		Window* window;
		Program* program;

		StaticModel sModel;
		glm::mat4 MVP;
		Camera camera;
		int count;
	};
}

int main(int, char**)
{
	solar::Context* context = new solar::Context();
	solar::Game* game = new solar::Game(context);
	solar::Application* app = new solar::Application(context, game);
	return app->run();
}