#pragma once
#include <map>
#include <ostream>


class Level
{
	class LevelNode
	{
	public:
		std::string mName;
		int mX, mY, mRadius;
	};

protected:
	std::map<std::string, std::map<LevelNode, float>> the_graph;

public:
	Level();
	void load_map_file(std::string fname);
};