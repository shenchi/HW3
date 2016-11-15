#pragma once

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

	public:

#pragma region Big-Five

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

#pragma region Manipulators

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
			

		}

		inline T RemoveFront()
		{
			return T();
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
