#include "Shape.h"
#include "..\Graphics.h"
#include "..\opengl\Shader.h"
#include "..\opengl\Program.h"

#include <string>
#include <iostream>
#include <vector>

namespace solar
{

	Shape::Shape()
	{
		// Dark blue background

		// Create and compile our GLSL program from the shaders

		Shader vertexShader(GL_VERTEX_SHADER);
		vertexShader.setSource("data/shaders/SimpleVertex.glsl");
		vertexShader.compile();

		Shader fragmentShader(GL_FRAGMENT_SHADER);
		fragmentShader.setSource("data/shaders/SimpleFragment.glsl");
		fragmentShader.compile();

		program.attach(vertexShader);
		program.attach(fragmentShader);
		program.link();

		float g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};

		

	}

	Shape::~Shape()
	{

	}

	void Shape::render()
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
	}

}