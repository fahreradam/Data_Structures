#include <string>
#include <iostream>

namespace ssuds
{
	enum class LinkedListIteratorType { forward, backward};

	template <class T>
	class LinkedList
	{
	protected:
		/// Making Node Class
		class Node		// Important design goal: user should not be aware Node exists!
		{
		/// Attributes of Node
		public:
			T mData;
			Node* mNext;// Pointer to the following node (NULL if there is none)
			Node* mPrev;// Similar for preceding.  This makes our Llist a doubly-linked list.
		};
		/// Attributes of LinkedList
		Node* mStart;   // Sometimes called the head
		Node* mEnd;     // Sometimes called the tail
		int mSize;     // Number of nodes

	public:

		/// Making the LinkedListIterator
		class LinkedListIterator
		{
		/// Attributes of LinkedListIterator
		protected:
			Node* mCurPos;
			LinkedListIteratorType mType;
			friend class LinkedList;
			int CurIndex;
			
		public:
			/// LinkedListIterator Defaul Constructor
			LinkedListIterator() : mType(LinkedListIteratorType::forward), CurIndex(0), mCurPos(nullptr)
			{

			}

			/// LinkedListIterator Constructor (Used most of the time) 
			LinkedListIterator(LinkedListIteratorType tp, int start_index, Node* position) : mCurPos(position), mType(tp), CurIndex(start_index)
			{	}

			/// Overloaded == operator
			bool operator==(const LinkedListIterator& other) const
			{
				return mCurPos == other.mCurPos;
			}

			/// Overloaded != operator 
			bool operator !=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}

			/// overloaded ++ operator for iteratoring the iterator
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


			/// Overloaded ++ operator incase the iterator is on the other side if the ++  
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

			/// Returns the current value that mCurPos is at  
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
		/// LinkedList default constructor
		LinkedList() : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			// empty, on purpose
		}

		/// LinkedList Copy Constructor 
		LinkedList(const LinkedList& other) : mStart(nullptr), mEnd(nullptr), mSize(0) // Copy Constructor
		{
			Node* other_cur = other.mStart;
	
			while (other_cur != nullptr)
			{
				append(other_cur->mData);
				other_cur = other_cur->mNext;
			}
		}
		
		/// LinkedList Initializer-list constructor 
		LinkedList(std::initializer_list<T> ilist) : mSize(0), mStart(nullptr), mEnd(nullptr) // Initializer-list constructor
		{
			for (T val : ilist)
			{
				append(val);
			}
		}

		/// LinkedList Move Constructor 
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

		/// LinkedList deconstructor
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

		/// Returns an iterator at the begining of the linked list 
		LinkedListIterator begin() const
		{
			return LinkedListIterator(LinkedListIteratorType::forward, 0, mStart);
		}

		/// Returns an iterator at the null pointer in the end of the LinkedList
		LinkedListIterator end() const
		{
			return LinkedListIterator(LinkedListIteratorType::forward, mSize, nullptr);
		}

		/// Return an iterator at the end of an LinkedList and allows reverse iteration 
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(LinkedListIteratorType::backward, mSize-1, mEnd);
		}

		/// Returns an iterator at the null pointer in the begining of the LinkedList 
		LinkedListIterator rend() const
		{
			return LinkedListIterator(LinkedListIteratorType::backward, -1, nullptr);
		}

		/// adds a given type T value to the end of the LinkedList 
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

		/// adds a given type T value to the begining of the LinkedList 
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
		
		/// inserts a given type T value into a designated index in the LinkedList 
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

		/// Returns an int that is the current size of the LinkedList 
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

		/// Returns an LinkListIterator that holds the position at the requested value if there
		LinkedListIterator find(T search_val)
		{
			return find(search_val, LinkedListIterator(LinkedListIteratorType::forward, 0, mStart));
		}

		/// Returns an LinkListIterator that holds the position at the requested value if there
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

		/// Overloaded [] operator which returns the mData to the given index 
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

		/// Overloaded = operator
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

		/// Overloaded stream operator for std::cout 
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