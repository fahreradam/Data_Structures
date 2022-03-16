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

			Node* mCurPos;
			LinkedListIteratorType mType;
			friend class LinkedList;
			int CurIndex;
			
		public:
			LinkedListIterator() : mType(LinkedListIteratorType::forward), CurIndex(0), mCurPos(nullptr)
			{

			}
			
			LinkedListIterator(LinkedListIteratorType tp, int start_index, Node* position) : mCurPos(position), mType(tp), CurIndex(start_index)
			{	}

			bool operator==(const LinkedListIterator& other) const
			{
				return mCurPos == other.mCurPos;
			}

			bool operator !=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}

			void operator++()
			{
				if (mType == LinkedListIteratorType::forward)
				{
					mCurPos = mCurPos->mNext;
					CurIndex++;
				}
				else
				{
					mCurPos = mCurPos->mPrev;
					CurIndex--;
				}
			}

			void operator++(int dummy)
			{
				if (mType == LinkedListIteratorType::forward)
				{
					mCurPos = mCurPos->mNext;
					CurIndex++;
				}
				else
				{
					mCurPos = mCurPos->mPrev;
					CurIndex--;
				}
			}

			T& operator*()
			{
				return mCurPos->mData;	
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

		LinkedList(const LinkedList& other) : mStart(nullptr), mEnd(nullptr), mSize(0) // Copy Constructor
		{
			Node* other_cur = other.mStart;
	
			while (other_cur != nullptr)
			{
				append(other_cur->mData);
				other_cur = other_cur->mNext;
			}
		}
		
		LinkedList(std::initializer_list<T> ilist) : mSize(0), mStart(nullptr), mEnd(nullptr) // Initializer-list constructor
		{
			for (T val : ilist)
			{
				append(val);
			}
		}

		LinkedList(LinkedList&& other) : mStart(other.mStart), mEnd(other.mEnd), mSize(other.mSize) // Move Constructor
		{
			Node* other_cur = other.mStart;
			Node* cur = mStart;

			while (other_cur != nullptr)
			{
				cur->mData = other_cur->mData;
				cur = cur->mNext;
				other_cur = other_cur->mNext;
			}
			other.mEnd = nullptr;
			other.mStart = nullptr;
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
			return LinkedListIterator(LinkedListIteratorType::forward, 0, mStart);
		}

		LinkedListIterator end() const
		{
			return LinkedListIterator(LinkedListIteratorType::forward, mSize, nullptr);
		}

		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(LinkedListIteratorType::backward, mSize-1, mEnd);
		}

		LinkedListIterator rend() const
		{
			return LinkedListIterator(LinkedListIteratorType::backward, -1, nullptr);
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
		
		void insert(int index, const T& val)
		{
			if (index < 0 || index >= mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			if (index == 0 || mSize == 0)
				prepend(val);
			else if (index == mSize)
				append(val);
			else
			{
				Node* node_node = new Node;
				node_node->mData = val;
				Node* cur = mStart;
				int curPos = 0;
				while (curPos != index && cur != nullptr)
				{
					cur = cur->mNext;
					curPos++;
				}
				node_node->mNext = cur;
				node_node->mPrev = cur->mPrev;
				cur->mPrev->mNext = node_node;
				cur->mPrev = node_node;
				mSize++;
			}
		}

		int size() const
		{
			return mSize;
		}

		void clear()
		{
			Node* cur = mStart;
			while (cur != nullptr)
			{
				Node* temp = cur->mNext;
				delete cur;
				cur = temp;
			}
			mStart = nullptr;
			mEnd = nullptr;
			mSize = 0;
		}

		LinkedListIterator find(T search_val)
		{
			return find(search_val, LinkedListIterator(LinkedListIteratorType::forward, 0, mStart));
		}

		LinkedListIterator find(T search_val, LinkedListIterator llist)
		{
			while (llist.mCurPos != nullptr)
			{
				if (llist.mCurPos->mData == search_val)
					return (llist);
				llist.mCurPos = llist.mCurPos->mNext;
				llist.CurIndex++;
			}
			return end();
		}

		T& operator[] (int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else
			{
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

		LinkedList<T>& operator= (const LinkedList<T>& other)
		{
			clear();
			Node* other_cur = other.mStart;
			while (other_cur != nullptr)
			{
				append(other_cur->mData);
			}
			return *this;
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