#include <array_list.h>
#include <fstream>
#include <stack>
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
			/// Node Attributes
			T mData;
			Node* mLeft;
			Node* mRight;
			ssuds::NodeType mType;

			/// Node Class Constructor 
			Node(const T& val) : mData(val), mLeft(nullptr), mType(ssuds::NodeType::In_Order),
				mRight(nullptr) {}

			/// Recursive insert method 
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

			/// Recursive Method that prints everything in the OrderSet
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

			/// Recersive Method For Traversal that fulls a given ArrayList
			/// in the order of the given NodeType
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

			/// Recursive Clear Method
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

			/// Recursive Method that returns a bool whether the 
			/// given value is in the orderset or not 
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
			
			/// Reclusive Method that return an int that is the 
			// size of the lowest point in the orderset, (the root counts as 1 level deep)  
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

			/// Recursive Method that can remove three types of node
			/// Leaf Node - no children
			/// Node with one child
			/// Node with two children
			Node* erase_recursive(const T& val, bool& erased)
			{				
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
	public:
		// REFERENCE: https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
		class OrderedSetIterator
		{
		protected:
			/// OrderSetIterator Attributes
			Node* mCurrent;
			std::stack<Node*> mNodeStack;

			// bool used to track if the first iteration has been done
			// used for checking if right side iteration is possible. 
			// this isn't what I wanted to do, but I couldn't find another solution
			bool first_it;

		public:
			/// Iterator Constructor 
			OrderedSetIterator(Node* root) : mCurrent(root), first_it(false)
			{

			}

			/// Overloaded ++ operator
			/// used for iterating through the orderset
			void operator++()
			{
				if (first_it)
					mCurrent = mCurrent->mRight;
				if (mCurrent || mNodeStack.empty() == false)
				{
					while (mCurrent)
					{
						mNodeStack.push(mCurrent);
						mCurrent = mCurrent->mLeft;
					}
					mCurrent = mNodeStack.top();
					mNodeStack.pop();
					if (first_it == false)
						first_it = true;
				}
			}

			/// Overloaded ++ operator 
			/// an addition dummy argument that is used for right sided ++ 
			/// used for iterating through the orderset
			void operator++(int dummy)
			{
				
				if (first_it)
					mCurrent = mCurrent->mRight;
				if (mCurrent || mNodeStack.empty() == false)
				{
					while (mCurrent)
					{
						mNodeStack.push(mCurrent);
						mCurrent = mCurrent->mLeft;
					}
					mCurrent = mNodeStack.top();
					mNodeStack.pop();	
					if (first_it == false)
						first_it = true;
				}

			}

			/// Returns the value of the current node 
			T& operator*()
			{
				return mCurrent->mData;
			}

			/// Overloaded != operator 
			bool operator != (const OrderedSetIterator& other)
			{
				return (mCurrent != other.mCurrent) || (mNodeStack != other.mNodeStack);
			}

			/// Overloaded == operator 
			bool operator ==(const OrderedSetIterator& other)
			{
				return (mCurrent == other.mCurrent) && (mNodeStack == other.mNodeStack);
			}
		};




	protected:
		/// OrderSet Attributes
		Node* mRoot;
		int mSize;

	public:
		/// OrderSet Default constructor
		OrderedSet() : mRoot(nullptr), mSize(0) {}

		/// OrderSet deconstructor
		~OrderedSet()
		{
			// super-important!!
			clear();
		}

		/// Returns an OrderSetIterator at the begining of the set 
		OrderedSetIterator begin()
		{
			return OrderedSetIterator(mRoot);
		}

		/// Returns an OrderSetIterator at a nullptr after the last value in the set
		OrderedSetIterator end()
		{
			Node* temp = mRoot->mRight;
			while (temp)
				temp = temp->mRight;
			return OrderedSetIterator(temp);
		}

		/// Called by the user to begin the recursive insert method 
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

		/// Called by the user to begin the recursive traversal method 
		void traversal(ssuds::ArrayList<T>& alist, NodeType tp)
		{
			if (mRoot)
			{
				alist.clear();
				mRoot->traversal_recursive(alist, tp);
			}
		}

		/// Called by the user to begin the recursive print_all method
		void print_all()
		{
			if (mRoot)
				mRoot->print_all_recursive();
		}

		/// returns the current size of the set 
		int size()
		{
			return mSize;
		}

		/// Called by the user to begin the recursive clear method
		void clear()
		{
			mRoot->clear_recursive();
			delete mRoot;
			mRoot = nullptr;
			mSize = 0;
		}

		/// Called by the user to begin the recursive contains method 
		bool contains(const T& val)
		{
			bool con = false;
			return mRoot->contains_recursive(val);
		}

		/// Called by the user to begin the recusive rebalance method
		void rebalance()
		{
			ssuds::ArrayList<T> alist;
			traversal(alist, NodeType::In_Order);
			clear();
			rebalance_recursive(0, alist.size() - 1, alist);
		}

	/// Privated because we don't want the user to potentially call this 
	private:
		/// Recursive rebalance method used to reoganize the OrderSet to get an optimal set 
		void rebalance_recursive(int starting_point, int end_point, ssuds::ArrayList<T> alist)
		{
			int mid = (starting_point + end_point) / 2;

			if (starting_point > end_point)
				return;

			insert(alist[mid]);
			rebalance_recursive(starting_point, mid-1, alist);
			rebalance_recursive(mid+1, end_point, alist);
		}
	public:
		/// Called by the user to return the given value of the recursive get_height method 
		int get_height()
		{
			return (mRoot->get_height_recursive());
		}

		/// Called by the user to begin the recersive earse method
		/// returns whether not the node was erased from the set
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