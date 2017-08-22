#pragma once

#include <glm\glm.hpp>

namespace solar
{

	class Camera
	{
	public:
		Camera();
		virtual ~Camera() { }

		void update();

		void setProjection(glm::mat4& projection) { m_projection = projection; }
		glm::mat4 getProjection() const { return m_projection; }
		glm::mat4 getView() const { return m_view; }
		glm::mat4 getProjView() const { return m_projView; }

		void normalizeUp();
		void lookAt(glm::vec3& target);
		void rotate(float angle, float xAxis, float yAxis, float zAxis);
		void rotate(glm::vec3& axis, float angle);
		void rotateAround(glm::vec3& point, glm::vec3& axis, float angle);
		void translate(float x, float y, float z);
		void translate(glm::vec3& translation);

		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_projView;

		glm::vec3 m_position;
		glm::vec3 m_direction;
		glm::vec3 m_upAxis;
	
	};

}