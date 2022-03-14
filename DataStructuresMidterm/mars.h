#pragma once
#include <iostream>
#include <string>
namespace ssuds
{
	class Mars
	{
	protected:
		std::string mString[3];
		float mValue;

	public:
		Mars();
		
		Mars(std::string mString1, std::string mString2, std::string mString3, float Value);

		Mars(const Mars& other);

		~Mars();

		std::string operator[](int index) const;

		Mars& operator=(const Mars& other);

		friend std::ostream& operator <<(std::ostream& os, const ssuds::Mars& list)
		{
			os << "[";
			for (int i = 0; i < 3; i++)
			{
				os << list[i+1];
				if (i < 3 - 1)
					os << "\\";
			}
			os << ":" << std::to_string(list.mValue) << "]";
			return os;
		}

	};
}