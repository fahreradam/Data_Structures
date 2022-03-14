#include "mars.h"
#include <iostream>
#include <string>


ssuds::Mars::Mars()
{
	std::string A = "A";
	std::string B = "B";
	std::string C = "C";

	mString[0] = A;
	mString[1] = B;
	mString[2] = C;

	mValue = 1.5f;
}

ssuds::Mars::Mars(std::string mString1, std::string mString2, std::string mString3, float Value)
{
	mString[0] = mString1;
	mString[1] = mString2;
	mString[2] = mString3;

	mValue = Value;
}

ssuds::Mars::Mars(const ssuds::Mars& other) : mValue(-other.mValue)
{
	for (int i = 0; i < 3; i++)
		mString[i] = other.mString[2-i];
}

ssuds::Mars::~Mars()
{
	std::cout << "Goodbye" << std::endl;
}

std::string ssuds::Mars::operator[](int index) const
{
	if (index > 0 && index < 4)
		return mString[index-1];
	else if (index == -1)
		return std::to_string(index);
	else
		throw std::out_of_range("Invalid Index" + std::to_string(index));
}

ssuds::Mars& ssuds::Mars::operator=(const Mars& other)
{
	for (int i = 0; i < 3; i++)
		mString[i] = other.mString[2 - i];
	mValue = -other.mValue;
	return *this;
}

