#include <iostream>
#include <string.h>

class Foo
{
protected:
	std::string str;
	int mSize;
public:
	Foo(std::string s) : str(s)
	{
		mSize = str.size();
	}

public:
	class FooListIterator
	{
	protected:
		int mCurPosition;
		Foo* mFooPtr;

	public:
		FooListIterator()
		{
			mCurPosition = 0;
		}
		FooListIterator(Foo* list, int start = 0)
		{
			mCurPosition = start;
			mFooPtr = list;
		}
		bool operator == (const FooListIterator& other) const
		{
			return (mCurPosition == other.mCurPosition && mFooPtr == other.mFooPtr);

		}

		bool operator!=(const FooListIterator& other) const
		{
			// Are we not equal to this other iterator?

			return !((*this) == other);
		}
		void operator++()
		{
			mCurPosition++;
		}
		char operator *() const
		{
			return mFooPtr-> str[mCurPosition];
		}
	};
	FooListIterator begin()
	{
		return FooListIterator(this, 0);
	}
	FooListIterator end()
	{
		return FooListIterator(this, mSize);
	}
	
};


int main()
{
	Foo x("Hello");

	for (char c : x)
	{
		std::cout << c << std::endl;
	}
}