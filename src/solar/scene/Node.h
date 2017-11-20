#pragma once

#include "..\core\Object.h"

#include <memory>
#include <mathfu\glsl_mappings.h>
#include <mathfu\matrix.h>
#include <mathfu\vector.h>
#include <mathfu\quaternion.h>

namespace solar
{
	class Scene;

	class Node : public Object
	{
		SOLAR_OBJECT(Node);

	public:
		Node(Context* context);
		virtual ~Node();

		Node* createChild(const char* name);
		void addChild(Node* node);
		void removeChild(Node* node);
		void removeAllChildren();

		void setPosition(mathfu::vec3& position);
		void setRotation(mathfu::quat& rotation);
		void setScale(mathfu::vec3& scale);
		void setTransform(mathfu::vec3& position, mathfu::quat& rotation, mathfu::vec3& scale);

		void setWorldPosition(mathfu::vec3& position);
		void setWorldRotation(mathfu::quat& rotation);
		void setWorldScale(mathfu::vec3& scale);
		void setWorldTransform(mathfu::vec3& position, mathfu::quat& rotation, mathfu::vec3& scale);

		void translate(mathfu::vec3& translation);
		
		void rotate(mathfu::quat& rotation);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		void lookAt(mathfu::vec3& target, mathfu::vec3& up);
		
		void scale(float scale);
		void scale(mathfu::vec3& scale);

		void setParent(Node* parent);
		void setName(const char* name);
		void setLevel(unsigned level);

		const std::string& getName() { return m_name; }
		unsigned getLevel() const { return m_level; }
		Node* getParent() const { return m_parent; }
		Scene* getScene() const { return m_scene; }

		mathfu::mat4 getLocalTransform() const { return m_localTransform; }
		
		mathfu::mat4 getWorldTransform() const
		{ 
			if (m_dirty)
				updateWorldMatrix();

			return m_worldTransform; 
		}

		void makeDirty();
		void updateWorldMatrix() const;

		void printNode();

	protected:
		std::string m_name;

		Scene* m_scene;
		Node* m_parent;
		std::vector<Node*> m_children;
		unsigned m_level;

		mathfu::mat4 m_localTransform;
		mathfu::mat4 m_worldTransform;

		bool m_dirty;

	};

}