#include <string>
#include <iostream>

namespace ssuds
{
	enum class LinkedListIteratorType { forward, backward};

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
		class LinkedListIterator
		{
		protected:
			const LinkedList& mLinkedList;
			Node* mCurPos;
			LinkedListIteratorType mType;
			friend class LinkedList;
			int CurIndex;
			
		public:
			
			LinkedListIterator(const LinkedList& arr, LinkedListIteratorType tp, int start_index, Node* position) : mCurPos(position), mLinkedList(arr), mType(tp), CurIndex(0)
			{	}
			bool operator==(const LinkedListIterator& other) const
			{
				return &mLinkedList == &other.mLinkedList && mCurPos == other.mCurPos;
			}

			bool operator !=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}

			void operator++()
			{
				if (mType == LinkedListIteratorType::forward)
				{
					mCurPos->mNext;
					CurIndex++;
				}
				else
				{
					mCurPos->mPrev;
					CurIndex--;
				}
			}
			T& operator*()
			{
				return mLinkedList->mData;	
			}
			int index()
			{
				return CurIndex;
			}
		};

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
				Node* temp = cur->mNext;
				delete cur;
				cur = temp;
			}
		}

		LinkedListIterator begin() const
		{
			return LinkedListIterator(*this, LinkedListIteratorType::forward, mStart)
		}

		LinkedListIterator end() const
		{
			return LinkedListIterator(*this, LinkedListIteratorType::backward, mEnd)
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

		void prepend(const T& new_val)
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
				mStart->mPrev = new_node;			// green line (in paint)
				new_node->mNext = mStart;			// blue line
				mStart = new_node;				// purple line
			}
			mSize++;
		}

		T& operator[] (int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else
			{
				}
				Node* cur = mStart;
				int i = 0;
				while (cur != nullptr)
				{
					if (i == index)
						return cur->mData;
					cur = cur->mNext;
					i++;
				}
			}
		}

		int size() const
		{
			return mSize;
		}

		friend std::ostream& operator <<(std::ostream& os, const LinkedList<T>& alist)
		{
			os << "[";
			Node* cur = alist.mStart;
			int i = 0;
			while (cur != nullptr)
			{
				os << cur->mData;
				if (i < alist.size() - 1)
					os << ", ";
				cur = cur->mNext;
				i++;
			}

			os << "]";
			return os;
		}
	};
}