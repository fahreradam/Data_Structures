#pragma once
#include <map>
#include <ostream>


class Level
{
	class LevelNode
	{
		std::string mName;
		int mX, mY, mRadius;
	};

protected:
	std::map<std::_Invoker_strategy, std::map<std::string, bool>> the_graph;
};