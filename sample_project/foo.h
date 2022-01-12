#pragma once
#include <string>

namespace ssuds
{
	// a class DECLARATION
	class Foo
	{
		// the ATTRIBUTES / FIELDS (data that goes along with each
		//   instance of this class)
	protected:
		int age;
		std::string name;

		// the METHODS (functions associated with an instance of 
		//   a class)
	public:
		void talk();
		Foo(std::string start_name);				// Constructor
		~Foo();						// Destructor
	};
}
