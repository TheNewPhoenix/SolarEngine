#include "Node.h"
#include "..\io\Log.h"

namespace solar
{
	Node::Node(Context* context) :
		Object(context),
		m_scene(0),
		m_parent(0),
		m_level(0)
	{

	}

	Node::~Node()
	{

	}

	Node* Node::createChild(const char* name)
	{
		Node* node = new Node(m_context);
		node->setName(name);

		addChild(node);
		return node;
	}

	void Node::addChild(Node* node)
	{
		if (!node || node == this || node->m_parent == this)
			return;
		
		m_children.push_back(node);

		node->m_parent = this;
		node->m_level = m_level + 1;
	}

	void Node::removeChild(Node* node)
	{

	}

	void Node::removeAllChildren()
	{

	}

	void Node::setName(const char* name)
	{
		m_name = name;
	}

	void Node::setLevel(unsigned level) 
	{
		m_level = level;
	}

	void Node::updateWorldMatrix() const
	{

	}

	void Node::printNode()
	{
		SOLAR_LOGINFO() << m_name << ", level: " << m_level;
		std::vector<Node*>::iterator it;
		for (it = m_children.begin(); it != m_children.end(); it++)
		{
			Node* node = *it;
			node->printNode();
		}
	}

}