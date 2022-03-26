#include <array_list.h>
#include <fstream>
#include <vector>


namespace ssuds
{
	enum class NodeType { Pre, Post, In_Order };
	template <class T>

	class OrderedSet
	{
	protected:
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;
			ssuds::NodeType mType;

			Node(const T& val) : mData(val), mLeft(nullptr),
				mRight(nullptr) {}

			int insert_recursive(const T& val)
			{
				if (val < mData)
				{
					// The value is less than me, so it should
					// go to my left.
					// Two sub-posibilities: 
					if (mLeft)
					{
						//    we have a left child -- it should be
						//       told to handle the rest of insert
						return mLeft->insert_recursive(val);
					}
					else
					{
						//    we don't have a left child -- make
						//       one!
						mLeft = new Node(val);
						return 1;
					}
				}
				else if (val > mData)
				{
					// The value is greater than me, so it should
					// go to my right.
					if (mRight)
					{
						return mRight->insert_recursive(val);
					}
					else
					{
						mRight = new Node(val);
						return 1;
					}
				}
				else
				{
					// The value is equal to me -- duplicate!!
					// nothing to do...or is there?
					return 0;
				}
			}

			void print_all_recursive()
			{
				// If we had the tree on slide 11, we would
				// get this output
				// M, G, B, A, D, C, S, P, Q -- pre-order
				//std::cout << mData << std::endl;
				if (mLeft)
					mLeft->print_all_recursive();
				// If we were to put the cout here...
				std::cout << mData << std::endl;
				// ... instead of where it was, we get this:
				// .......M......
				// ...G...M..S...
				// A, BCDGMPSQ -- in-order traversal
				if (mRight)
					mRight->print_all_recursive();

			}

			void traversal_recursive(ssuds::ArrayList<T>& alist, NodeType tp)
			{
				if (tp == NodeType::Pre)
				{
					alist.append(mData);
					if (mLeft)
						mLeft->traversal_recursive(alist, tp);
					if (mRight)
						mRight->traversal_recursive(alist, tp);

				}
				if (tp == NodeType::Post)
				{
					if (mLeft)
						mLeft->traversal_recursive(alist, tp);
					if (mRight)
						mRight->traversal_recursive(alist, tp);
					alist.append(mData);
				}
				if (tp == NodeType::In_Order)
				{
					if (mLeft)
						mLeft->traversal_recursive(alist, tp);

					alist.append(mData);
					
					if (mRight)
						mRight->traversal_recursive(alist, tp);

				}
			}

			void clear_recursive()
			{
				if (mLeft)
				{
					mLeft->clear_recursive();
					delete mLeft;
				}
				if (mRight)
				{
					mRight->clear_recursive();
					delete mRight;
				}
			}

			bool contains_recursive(const T& val)
			{
				if (mData == val)
					return true;
				if (mLeft)
				{
					return mLeft->contains_recursive(val);
				}
				else if (mRight)
				{
					return mRight->contains_recursive(val);
				}
				else
					return false;
			}
			
			int get_height_recursive()
			{
				// I couldn't for the life of me understand how to formate this method so I did research a bit to understand it
				// https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
				int R = 0;
				int	L = 0;

				if (mLeft)
					L = mLeft->get_height_recursive();

				if (mRight)
					R = mRight->get_height_recursive();

				if (L > R)
					return (++L);
				else
					return (++R);
			}

			Node* erase_recursive(const T& val, bool& erased)
			{
				//if (mData == val)
				//{
				//	return true;
				//}
				//if (mData < val)
				//{
				//	if (mRight->erase_recursive(val))
				//	{
				//		if (mRight->mRight == nullptr && mRight->mLeft == nullptr)
				//		{
				//			delete mRight;
				//			mRight = nullptr;
				//		}
				//		if (mRight->mRight == nullptr && mRight->mLeft)
				//		{
				//			Node* temp = mRight->mLeft;
				//			delete mRight;
				//			next = temp;
				//			return True;
				//		}
				//		if (mRight->mRight && mRight->mLeft)
				//		{
				//			Node* temp = mRight;
				//			while (temp->mLeft)
				//			{
				//				temp = temp->mLeft;
				//			}
				//			mRight->mData = temp->mData;
				//			return mRight->erase_recursive(temp->mData, next);
				//		}
				//	}
				//}
				//if (mData > val)
				//{
				//	if (mLeft->erase_recursive(val))
				//	{
				//		if (mLeft->mRight == nullptr && mLeft->mLeft == nullptr)
				//		{
				//			delete mLeft;
				//			mLeft = nullptr;
				//		}
				//		if (mLeft->mRight == nullptr && mLeft->mLeft)
				//		{
				//			Node* temp = mLeft->mLeft;
				//			delete mLeft;
				//			next = temp;
				//			return True;
				//		}
				//		if (mLeft->mRight && mLeft->mLeft)
				//		{
				//			Node* temp = mLeft;
				//			while (temp->mLeft)
				//			{
				//				temp = temp->mLeft;
				//			}
				//			mLeft->mData = temp->mData;
				//			return mLeft->erase_recursive(temp->mData, next);
				//		}
				//	}
				//}
				
				if (this == nullptr)
				{
					erased = false;
					return this;
				}

				if (val < mData)
					mLeft = mLeft->erase_recursive(val, erased);
				else if (val > mData)
					mRight = mRight->erase_recursive(val, erased);
				else
				{
					if (mLeft == nullptr && mRight == nullptr)
						return nullptr;
					else if (mLeft == nullptr)
					{
						Node* temp = mLeft;
						delete this;
						erased = true;
						return temp;
					}
					else if (mRight == nullptr)
					{
						Node* temp = mLeft;
						delete this;
						erased = true;
						return temp;
					}

					Node* current = mRight;
					while (current && current->mLeft != nullptr)
						current = current->mLeft;
					Node* temp = current;
					mData = temp->mData;
					mRight = mRight->erase_recursive(temp->mData, erased);
					erased = true;
				}
				return this;
			}
		};

		Node* mRoot;
		int mSize;

	public:
		OrderedSet() : mRoot(nullptr), mSize(0) {}

		~OrderedSet()
		{
			// super-important!!
			clear();
		}

		// The user is calling this method
		void insert(const T& val)
		{
			if (mRoot)
			{
				// We have elements already -- tell the root
				// to handle it!
				mSize += mRoot->insert_recursive(val);
			}
			else
			{
				mRoot = new Node(val);
				mSize = 1;
			}
		}

		void traversal(ssuds::ArrayList<T>& alist, NodeType tp)
		{
			if (mRoot)
			{
				alist.clear();
				mRoot->traversal_recursive(alist, tp);
			}
		}


		void print_all()
		{
			if (mRoot)
				mRoot->print_all_recursive();
		}

		int size()
		{
			return mSize;
		}

		void clear()
		{
			mRoot->clear_recursive();
			delete mRoot;
			mRoot = nullptr;
			mSize = 0;
		}

		bool contains(const T& val)
		{
			bool con = false;
			return mRoot->contains_recursive(val);
		}

		void rebalance()
		{
			ssuds::ArrayList<T> alist;
			traversal(alist, NodeType::In_Order);
			clear();
			rebalance_recursive(0, alist.size() - 1, alist);
		}

		void rebalance_recursive(int starting_point, int end_point, ssuds::ArrayList<T> alist)
		{
			int mid = (starting_point + end_point) / 2;

			if (starting_point > end_point)
				return;

			insert(alist[mid]);
			rebalance_recursive(starting_point, mid-1, alist);
			rebalance_recursive(mid+1, end_point, alist);

		}

		int get_height()
		{
			return (mRoot->get_height_recursive());
		}

		bool erase(const T& val)
		{
			bool erased = false;
			mRoot = mRoot->erase_recursive(val, erased);
			if (erased)
				mSize -= 1;
			return erased;
		}
	};
}