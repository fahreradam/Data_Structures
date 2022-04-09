#include <level.h>
#include <fstream>
void Level::load_map_file(std::string fname)
{
	std::ifstream fp;
	fp.open("maps\\" + fname);

	if (fp.is_open())
	{
		std::string line_type, name;
		int x, y, radius;

		while (!fp.eof())
		{
			if (line_type == "n")
			{
				fp >> name >> x >> y >> radius;
				
			}
		}
	}
}