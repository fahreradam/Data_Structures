#include <string>

namespace ssuds
{
	template <class T>
	class LinkedList
	{
	protected:
		class Node		// Important design goal: user should not be aware Node exists!
		{
		public:
			T mData;
			Node* mNext;// Pointer to the following node (NULL if there is none)
			Node* mPrev;// Similar for preceding.  This makes our Llist a doubly-linked list.
		};

		Node* mStart;   // Sometimes called the head
		Node* mEnd;     // Sometimes called the tail
		int mSize;     // Number of nodes
	public:
		LinkedList() : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			// empty, on purpose
		}

		~LinkedList()
		{
			Node* cur = mStart;
			while (cur != nullptr)
			{
				delete(cur->mData);
				cur = cur->mNext;
			}
			mStart = nullptr;
			mEnd = nullptr;
		}

		void append(const T& new_val)
		{
			// ... make a new (disconnected) node
			Node* new_node = new Node;
			new_node->mData = new_val;
			new_node->mNext = nullptr;
			new_node->mPrev = nullptr;
			if (mSize == 0)
			{
				// Case1: This list is empty.  The new node will be the starting
				//   and ending node (until we add more nodes)
				// ... make it a part of the list
				mStart = mEnd = new_node;
			}
			else
			{
				// Case2: This list already has stuff.  Add a new node to the
				//  end (tail).
				mEnd->mNext = new_node;			// green line (in paint)
				new_node->mPrev = mEnd;			// blue line
				mEnd = new_node;				// purple line
			}
			mSize++;
		}

		T& operator[] (int index) const
		{
			Node* cur = mStart;
			int i = 0
			while (cur != nullptr)
			{
				if (i == index)
					return cur->mData;
				cur = cur->mNext;
				i++
			}
		}

		int size()
		{
			return mSize;
		}

		friend std::ostream& operator <<(std::ostream& os, const LinkedList<T>& alist)
		{
			os << "[";
			Node* cur = mStart;
			int i = 0;
			while (cur != nullptr)
			{
				os << alist[i];
				if (i < alist.size() - 1)
					os << ", ";
				
				i++;
			}

			os << "]";
			return os;
		}
	};
}