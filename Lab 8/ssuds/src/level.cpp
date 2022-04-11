#include <level.h>
#include <fstream>

Level::Level()
{
	std::map<std::string, std::map<std::string, float>> the_graph;
}

void Level::load_map_file(std::string fname)
{
	std::ifstream fp;
	fp.open("maps\\" + fname);

	if (fp.is_open())
	{
		std::string line_type;
		LevelNode temp;

		while (!fp.eof())
		{
			if (line_type == "n")
			{
				fp >> temp.mName >> temp.mX >> temp.mY >> temp.mRadius;
			}
		}
	}
}