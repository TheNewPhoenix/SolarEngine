#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

namespace solar
{

	Camera::Camera() :
		m_direction(0, 0, -1),
		m_upAxis(0, 1, 0)
	{
	}

	void Camera::update()
	{
		m_view = glm::lookAt(m_position, m_position + m_direction, m_upAxis);
		m_projView = m_projection * m_view;
	}

	void Camera::normalizeUp()
	{
		glm::vec3 tempVec = m_direction;
		tempVec = glm::cross(tempVec, m_upAxis);
		glm::normalize(tempVec);

		m_upAxis = tempVec;
		m_upAxis = glm::cross(m_upAxis, m_direction);
		glm::normalize(m_upAxis);
	}

	void Camera::lookAt(glm::vec3& target)
	{
		glm::vec3 tempVec = target - m_position;
		glm::normalize(tempVec);
		if (tempVec != glm::zero<glm::vec3>())
		{
			float dot = glm::dot(tempVec, m_upAxis);
			if (std::abs(dot - 1) < 0.000000001f)
			{
				m_upAxis = m_direction;
				m_upAxis *= -1;
			}
			else if (std::abs(dot + 1) < 0.000000001f)
			{
				m_upAxis = m_direction;
			}
			m_direction = tempVec;
			normalizeUp();
		}
	}

	void Camera::rotate(float angle, float xAxis, float yAxis, float zAxis)
	{
		rotate(glm::vec3(xAxis, yAxis, zAxis), angle);
	}

	void Camera::rotate(glm::vec3& axis, float angle)
	{
		glm::mat4 tempMat = glm::rotate(glm::mat4(), glm::radians(angle), axis);
		m_direction = glm::mat3(tempMat) * m_direction;
	}

	void Camera::rotateAround(glm::vec3& point, glm::vec3& axis, float angle)
	{
		glm::vec3 tempVec = point;
		tempVec -= m_position;
		translate(tempVec);
		rotate(axis, angle);
		glm::mat4 tempMat = glm::rotate(glm::mat4(), glm::radians(angle), axis);
		tempVec = glm::mat3(tempMat) * tempVec;
		translate(-tempVec.x, -tempVec.y, -tempVec.z);
	}

	void Camera::translate(float x, float y, float z)
	{
		translate(glm::vec3(x, y, z));
	}
	
	void Camera::translate(glm::vec3& translation)
	{
		m_position += translation;
	}

}