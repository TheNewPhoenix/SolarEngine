#include "Properties.h"
#include "..\io\Log.h"
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <boost\foreach.hpp>

namespace pt = boost::property_tree;

namespace solar
{

	Properties::Properties()
	{

	}

	Properties::~Properties()
	{

	}

	void Properties::load(const char* filepath) {
		pt::ptree tree;

		SOLAR_LOGDEBUG() << "Loading config: " << filepath;
		pt::read_json(filepath, tree);

		BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("window")) {
			// The data function is used to access the data stored in a node.
			SOLAR_LOGDEBUG() << "name: " << v.first.data() << "value: " << v.second.data();
		}
	}

}