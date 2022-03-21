#pragma once
#include <iostream>

namespace ssuds
{
	template <class T>
	/// A LinkedList is a collection of non-contiguous nodes.  To get to
	/// a certain spot, you must traverse the list.
	class LinkedList
	{
	protected:
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
		// @ LINKED-LIST-NODE CLASS                       @ //
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ // 
		/// This is a *hidden* class.  It is used to represent a single
		/// "link" in the list.  It contains the data (payload) and pointers
		/// to the next and previous nodes.
		class node
		{
		public:
			/// The actual data we're storing in each element of the list
			T mData;

			/// A pointer to the next node in the list (or nullptr if there is none)
			node * mNext;

			/// A pointer to the previous node in the list (or nullptr if there is none)
			node * mPrev;

			/// Constructor that initializes this node, but sets both pointers to nullptr
			node(T val) : mData(val), mNext(nullptr), mPrev(nullptr)
			{
				// Intentionally blank
			}

			/// Constructor that sets all the values of the node
			node(T val, node * prev, node * next) : mData(val), mNext(next), mPrev(prev)
			{
				// Intentionally blank
			}
		};      // END of node class


	public:
		/// The iterator used to traverse our linked list
		class LinkedListIterator
		{
		protected:
			/// The node we're currently at in our traversal
			node* mCurrent;

			/// Are we going forward or backwards?
			bool mForward;

			/// The "position" of the iterator if this were an array (forward iterators start at 0, reverse at mSize-1)
			int mCurIndex;

			/// A pointer to the owning LinkedList
			const LinkedList* mParent;

		public:
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
			// @ LINKED-LIST-ITERATOR CLASS                   @ //
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ // 
			/// Constructor that sets the current node to either the beginning (if is_forward is true) or end (if not)
			LinkedListIterator(const LinkedList* L, bool is_forward) : mParent(L), mForward(is_forward)
			{
				if (is_forward)
				{
					mCurrent = L.mStart;
					mCurIndex = L->size() - 1;
				}
				else
				{
					mCurrent = L.mEnd;
					mCurIndex = 0;
				}
			}

			/// Constructor that's meant to be called internally that sets the current node to NULL
			LinkedListIterator(const LinkedList* L) : mParent(L), mForward(true), mCurrent(NULL), mCurIndex(-1)
			{
				// intentionally empty
			}

			/// Constructor for when the user just wants to create an iterator not really referring to anything
			LinkedListIterator() : mParent(NULL), mForward(true), mCurrent(NULL), mCurIndex(-1)
			{
				// intentionally empty
			}

		protected:
			/// Meant to only be used internally
			LinkedListIterator(const LinkedList* L, node* cur, int index, bool is_forward) : mParent(L), mCurrent(cur), mForward(is_forward), mCurIndex(index)
			{
				// intentionally empty
			}

		public:
			/// Advances the iterator.  Note this goes in the direction of mForward (so if mForward is false, this
			/// actually goes to the previous node in the list).
			void operator++()
			{
				if (mForward)
					mCurrent = mCurrent->mNext;
				else
					mCurrent = mCurrent->mPrev;
			}

			/// Advances the iterator using post-fix notation (just in case you want to try it) -- it normally does just
			/// what the prefix++ operator does
			void operator++(int dummy)
			{
				// The "dummy" parameter is just a "hack" -- it's so the compiler can distinguish between the two ++ operators
				// You never do anything with it
				if (mForward)
					mCurrent = mCurrent->mNext;
				else
					mCurrent = mCurrent->mPrev;
			}


			/// Returns an iterator that's offset spots away from the current (possibly setting to the sentinel value)
			/// This value is relative to the direction (i.e. in a forward iterator -3 would move us 3 steps back)
			LinkedListIterator operator+(int offset) const
			{
				bool add = (mForward && offset > 0) || (!mForward && offset < 0);
				int amt = abs(offset);
				node* cur = mCurrent;

				for (int i = 0; i < amt; i++)
				{
					if (add)
						cur = cur->mNext;
					else
						cur = cur->mPrev;

					if (cur == NULL)
						return LinkedListIterator(mParent, NULL, -1, true);
				}

				return LinkedListIterator(mParent, cur, mCurIndex + offset, mForward);
			}


			/// Is this iterator equal to the given one?
			bool operator==(const LinkedListIterator& it) const
			{
				// Note: No need to check that the list is the same -- each list has its
				// own nodes, so we couldn't have the same node* but a different list.
				return (mParent == it.mParent) && (mCurrent == it.mCurrent) && (mForward == it.mForward);
			}


			/// Is this iterator not equal to the given one?
			bool operator!=(const LinkedListIterator& it) const
			{
				return (mParent != it.mParent) || (mCurrent != it.mCurrent) || (mForward != it.mForward);
			}

			/// Gets a reference to the data held by the current node.
			T& operator*() const
			{
				if (mCurrent)
					return mCurrent->mData;
				else
					throw std::out_of_range("can't dereference an \"end\" iterator");
			}

			/// Returns the "index" of this iterator's current value in the main list
			int index() const
			{
				return mCurIndex;
			}

			// Make the LinkedList a friend of this class so it can access our protected/private members
			friend class LinkedList;
		};	// END of LinkedListIterator class


	protected:
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
		// @ LINKED-LIST ATTRIBUTES                       @ //
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ // 
		/// This is the pointer to the first node in the linked list (NULL if the list is empty)
		node * mStart;

		/// This is the pointer to the last node in the linked list (NULL if the list is empty)
		node * mEnd;

		/// The number of elements in the list
		unsigned int mSize;


	public:
		/// The default constructor
		LinkedList() : mSize(0), mStart(NULL), mEnd(NULL)
		{
			// Intentionally blank
		}


		/// Copy constructor.  Makes a deep copy of the given LinkedList
		LinkedList(const LinkedList& L) : mStart(NULL), mEnd(NULL), mSize(0)
		{
			LinkedListIterator it = L.begin();
			while (it != L.end())
			{
				append(*it);
				++it;
			}
		}

		/// Initializer-list constructor
		LinkedList(const std::initializer_list<T>& initial_vals) : mStart(nullptr), mEnd(nullptr), mSize(0)
		{
			for (T val : initial_vals)
				append(val);
		}

		/// Move constructor (the noexcept "decorator" indicates we won't be throwing exceptions -- customary for move-constructors)
		LinkedList(LinkedList&& other) noexcept : mSize(other.mSize), mStart(other.mStart), mEnd(other.mEnd)
		{
			// Since we're "stealing" the data from the other one, we set their array pointers to
			// NULL (so when the destructor runs, it won't free up what is now our memory)
			other.mStart = other.mEnd = nullptr;
			other.mSize = 0;
		}

		/// Destructor
		~LinkedList()
		{
			// Very important -- we have to clean up all our memory!
			clear();
		}


		/// Gets an element at the given "position".  Note: since LinkedList's don't support
		/// random-access (unlike ArrayList), this is a costly operation
		T& operator[](int index) const
		{
			if (index < 0 || index >= (int)mSize)
				throw std::out_of_range("Invalid index");
			node* cur = mStart;
			for (int i = 0; i <= index; i++)
			{
				if (i == index)
					return cur->mData;
				cur = cur->mNext;
			}
			// We should ever get here, but if we do, it means something's wrong with our mSize
			throw std::out_of_range("Invalid index");
		}


		/// Replaces this linked list with a copy of the data in the other LinkedList.  This *should* work
		/// even if the (silly) user assigns a LinkedList to itself
		LinkedList& operator=(const LinkedList& L)
		{
			if (&L != this)
			{
				clear();
				for (T val : L)
					append(val);
			}

			// Return a reference to ourself
			return *this;
		}


		/// Stream operator definition for our linked list class
		friend std::ostream& operator<<(std::ostream& os, const LinkedList& L)
		{
			os << "[";
			int i = 0;
			for (T val : L)
			{
				os << val;
				i++;
				if (i < L.size())
					os << ", ";
			}
			os << "]";
			return os;
		}


		/// Adds a new node containing this data to the end of the linked list
		void append(T val)
		{
			if (mStart == NULL)
			{
				// Case I: This is the first node.  start and end will both point towards it
				mStart = mEnd = new node(val);
			}
			else
			{
				// Case II -- we already have a head -- add the new node to the end
				node* new_node = new node(val);
				new_node->mPrev = mEnd;
				mEnd->mNext = new_node;
				mEnd = new_node;
			}
			mSize++;
		}


		/// Returns an iterator to the beginning of the list
		LinkedListIterator begin() const
		{
			return LinkedListIterator(this, mStart, 0, true);
		}


		/// Resets the linked list back to its original state
		void clear()
		{
			node* temp = mStart;
			while (temp != nullptr)
			{
				// We need this because after we delete temp, the memory isn't ours anymore!
				node* next = temp->mNext;

				// Delete the current node
				delete temp;

				// Advance to the next node (if any) using the saved pointer.
				temp = next;
			}

			// Reset all of our attributes
			mStart = mEnd = nullptr;
			mSize = 0;
		}


		/// Returns a "sentinel" value -- if an iterator is equal to this, we're done traversing
		LinkedListIterator end() const
		{
			return LinkedListIterator(this, NULL, -1, true);
		}


		/// Finds the first occurrence of the given value starting at the given iterator
		LinkedListIterator find(T val, LinkedListIterator start) const
		{
			if (start.mCurrent == NULL)
				return end();
			node* cur = start.mCurrent;
			for (int i = start.mCurIndex; i < (int)mSize; i++)
			{
				if (cur->mData == val)
					return LinkedListIterator(this, cur, i, true);
				cur = cur->mNext;
			}
			return end();
		}


		/// Finds the first occurrence of the value, starting at the beginning of the list
		LinkedListIterator find(T val) const
		{
			return find(val, begin());
		}



		/// Inserts the given value at the currently occupied spot.  There's some extra overhead
		/// here to get to the given spot
		void insert(const T& item, int index)
		{
			if (index == 0)
				prepend(item);
			else if (index == mSize)
				append(item);
			else if (index < 0 || index > (int)mSize)
				throw std::out_of_range("Invalid index");
			else
			{
				// Get to the node at spot "index"
				node* cur = mStart;
				for (int i = 0; i < index; i++)
					cur = cur->mNext;

				insert_internal(item, cur);
			}
		}


		/// This is an alternate version of insert.  It skips the iteration step (nice if we
		/// were to already have an iterator pointing to the correct spot for insertion)
		void insert(const T& item, LinkedListIterator iter)
		{
			if (iter.index() == 0)
				prepend(item);
			else if (iter.index() == mSize)
				append(item);
			else if (iter.mCurrent == nullptr)
				throw std::out_of_range("Invalid iterator");
			else
				insert_internal(item, iter.mCurrent);
		}

	protected:
		/// An internal method to insert a new value before an existing node -- this node should not
		/// be either the start / end node (use prepend/append in these situtations)
		void insert_internal(const T& item, node* cur)
		{
			// Because of our initial checks, we can be sure that this node will be between two 
			// existing nodes
			node* new_node = new node(item);
			new_node->mPrev = cur->mPrev;
			new_node->mNext = cur;
			cur->mPrev->mNext = new_node;
			cur->mPrev = new_node;

			// Increase our size
			mSize++;
		}

	public:
		

		/// Adds a new node containing this data to the beginning of the linked list
		void prepend(T val)
		{
			if (mStart == NULL)
			{
				// Case I: This is the first node.  start and end will both point towards it
				mStart = mEnd = new node(val);
			}
			else
			{
				// Case II -- we already have a head -- add the new node before it
				node * new_node = new node(val);
				new_node->mNext = mStart;
				mStart->mPrev = new_node;
				mStart = new_node;
			}
			mSize++;
		}


		/// Returns a reverse iterator starting at the end of the list.
		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(this, mEnd, mSize - 1, false);
		}


		/// Returns a "sentinel" value -- if a reverse-iterator is equal to this, we're done traversing
		LinkedListIterator rend() const
		{
			return LinkedListIterator(this, NULL, -1, true);
		}



		/// Removes the node at the given iterator "position".  
		LinkedListIterator remove(LinkedListIterator spot)
		{
			if (spot.mCurrent == nullptr || this != spot.mParent)
				throw std::invalid_argument("Invalid iterator");

			if (mSize == 1)
			{
				// There's only one element here.  We're clearing the list
				T val = mStart->mData;
				delete mStart;
				mStart = mEnd = NULL;
				mSize = 0;
				return end();
			}
			else if (spot.mCurIndex == 0)
			{
				// Remove the first element
				node* next = mStart->mNext;
				next->mPrev = NULL;
				T val = mStart->mData;
				delete mStart;
				mStart = next;
				mSize--;
				if (spot.mForward)
					return LinkedListIterator(this, mStart, 0, true);
				else
					return rend();
			}
			else if (spot.mCurIndex == mSize - 1)
			{
				// Remove the last element
				node* prev = mEnd->mPrev;
				prev->mNext = NULL;
				T val = mEnd->mData;
				delete mEnd;
				mEnd = prev;
				mSize--;
				if (spot.mForward)
					return end();
				else
					return LinkedListIterator(this, mEnd, mSize - 1, false);
			}
			else
			{
				node* next = spot.mCurrent->mNext;
				node* prev = spot.mCurrent->mPrev;
				next->mPrev = prev;
				prev->mNext = next;
				node* goner = spot.mCurrent;
				LinkedListIterator rv;
				if (spot.mForward)
					rv = LinkedListIterator(this, goner->mNext, spot.mCurIndex, true);
				else
					rv = LinkedListIterator(this, goner->mPrev, spot.mCurIndex, false);
				delete goner;
				mSize--;
				return rv;
			}
		}

	public:


		/// Gets the number of elements in the linked list.  Don't implement it this way, but interesting
		/// challenge: how would you get the size of a linked-list if you weren't storing our mSize int?
		int size() const
		{
			return mSize;
		}

		


		

		
	};	// END of LinkedList class
}	// END of ssuge namespace