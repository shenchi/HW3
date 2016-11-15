#pragma once

#include "Exceptions.h"

namespace hw3
{
	template<typename T>
	class Queue
	{

	private:

		struct Node
		{
			Node*	next;
			Node*	prev;
			T		data;
		};

#pragma region Big-Five

	public:

		inline Queue()
			:
			size(0),
			head(nullptr),
			tail(nullptr)
		{}


		inline ~Queue()
		{
			Clear();
		}

		inline Queue(Queue<T> const & other)
			:
			size(0),
			head(nullptr),
			tail(nullptr)
		{
			if (nullptr != other.head)
			{
				CloneFrom(other.head);
			}
		}

		inline Queue(Queue<T>&& other)
			:
			size(other.size),
			head(other.head),
			tail(other.tail)
		{
			other.size = 0;
			other.head = nullptr;
			other.tail = nullptr;
		}

		inline Queue<T>& operator = (Queue<T> const & other)
		{
			if (this != &other)
			{
				CloneFrom(other.head);
			}
			return *this;
		}

		inline Queue<T>& operator = (Queue<T>&& other)
		{
			if (this != &other)
			{
				Clear();
				size = other.size;
				head = other.head;
				tail = other.tail;
				other.size = 0;
				other.head = nullptr;
				other.tail = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Iterator

	public:

		class Iterator
		{
		public:

			inline operator bool () const
			{
				return nullptr != ptr;
			}

			inline Iterator& operator ++ ()
			{
				if (nullptr != ptr)
					ptr = ptr->next;
				return *this;
			}

			inline Iterator& operator -- ()
			{
				if (nullptr != ptr)
					ptr = ptr->prev;
				return *this;
			}

			inline void operator ++ (int)
			{
				operator ++ ();
			}

			inline void operator -- (int)
			{
				operator -- ();
			}

			inline T& operator * ()
			{
				if (nullptr == ptr)
					throw InvalidIndex();
				return ptr->data;
			}

			inline T const & operator * () const
			{
				if (nullptr == ptr)
					throw InvalidIndex();
				return ptr->data;
			}

			inline T& operator -> ()
			{
				if (nullptr == ptr)
					throw InvalidIndex();
				return ptr->data;
			}

			inline T const & operator -> () const
			{
				if (nullptr == ptr)
					throw InvalidIndex();
				return ptr->data;
			}

		private:
			friend class Queue<T>;
			inline Iterator() = delete;
			inline Iterator(Node* ptr) : ptr(ptr) {}

		private:
			Node* ptr;
		};

#pragma endregion

#pragma region Manipulators

	public:

		inline size_t Size() const { return size; }

		inline bool Empty() const { return nullptr == head; }

		inline void Clear()
		{
			Node* ptr = head;

			while (nullptr != ptr)
			{
				Node* temp = ptr;
				ptr = ptr->next;
				delete temp;
			}

			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		inline void InsertBack(T const & element)
		{
			Node* node = new Node();
			node->data = element;

			if (nullptr == head)
			{
				tail = head = node;
				node->next = nullptr;
				node->prev = nullptr;
				size++;
			}
			else
			{
				tail->next = node;
				node->next = nullptr;
				node->prev = tail;
				tail = node;
				size++;
			}
		}

		inline T RemoveFront()
		{
			if (Empty())
				throw AlreadyEmpty();

			Node* node = head;
			head = head->next;
			size--;

			if (nullptr != head)
			{
				head->prev = nullptr;
			}
			else
			{
				tail = nullptr;
			}

			T data = node->data;
			delete node;

			return data;
		}

		Iterator GetIterator()
		{
			if (Empty())
				return Iterator(nullptr);

			return Iterator(head);
		}

#pragma endregion

	private:

		void CloneFrom(Node* ptr)
		{
			Clear();

			while (nullptr != ptr)
			{
				InsertBack(ptr->data);
				ptr = ptr->next;
			}
		}

	private:
		size_t	size;
		Node*	head;
		Node*	tail;

	};
}
