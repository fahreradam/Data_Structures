#pragma once
#include <string>

namespace {
	template <class T>
	class OrderSet 
	{
	protected:
		class node
		{
			T mData;
			node* mPrev;
			node* mRight;
			node* mLeft;

			node(T val) : mData(val), mRight(nullptr), mLeft(nullptr), mPrev(nullptr)
			{

			}

			node(T val, node* prev) : mData(val), mPrev(prev), mRight(nullptr), mLeft(nullptr)
			{

			}
		
			void insert(T val, node* start)
			{
				node* temp = start;
				while (temp != nullptr)
				{
					if (val < temp->mData)
					{
						if (temp->mLeft == nullptr)
						{
							node* new_node = new node(val, temp); // ask jason
							new_node->mPrev = temp;
							new_node->mLeft = nullptr;
							new_node->mRight = nullptr;
							break;
						}
					}
					
				}
			}

		};

	protected:
		node* mStart;
		node* mEnd;
		unsigned int mSize;
	
	public:
		OrderSet() : mSize(0), mStart(nullptr), mEnd(nullptr)
		{

		}

		void insert(T val)
		{
			
		}
	};
}