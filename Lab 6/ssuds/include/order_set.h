#include <array_list.h>

namespace ssuds
{
	template <class T>
	class OrderedSet
	{
	protected:
		enum class NodeType {Pre, Post, In_Order};
		class Node
		{
		public:
			T mData;
			Node* mLeft;
			Node* mRight;
			NodeType mType;

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


				// tangent: LISP: (- (+ 3 4) (* 2 3))  => 6
				//    equiv. to (3 + 4) - (2 * 3)   -- a pre-order language
			}

			void traversal_recursive(ssuds::ArrayList<T> alist, NodeType tp)
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
				if (tp == NodeType::In_Order);
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
					mLeft->clear_recursive();
				}
				if (mRight)
				{
					mRight->clear_recursive();
				}
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

		void traversal(ssuds::ArrayList<T> alist, NodeType tp)
		{
			if (mRoot)
			{
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
			mSize = 0
		}

		bool contains(const T& val)
		{
			return mRoot->contains_recursive(val);
		}
	};
}