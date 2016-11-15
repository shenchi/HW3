#pragma once

namespace hw3
{
	struct InvalidIndex {};
	struct AlreadyEmpty {};

	template<typename T>
	class Array
	{
	public:

#pragma region Big-Five

		inline Array(size_t size = 0, size_t capacity = 16)
			:
			data(nullptr),
			capacity(capacity),
			size(size)
		{
			if (capacity < size)
			{
				capacity = size;
			}

			if (capacity > 0)
			{
				data = new T[capacity];
				for (size_t i = 0; i < size; i++)
					data[i] = T();
			}
		}

		inline ~Array()
		{
			if (nullptr != data)
				delete[] data;
		}

		inline Array(Array<T> const & other)
			: data(nullptr),
			capacity(other.capacity),
			size(other.size)
		{
			if (capacity > 0)
			{
				data = new T[capacity];

				for (size_t i = 0; i < size; i++)
					data[i] = other.data[i];
			}
		}

		inline Array(Array<T>&& other)
			: capacity(other.capacity),
			size(other.size),
			data(other.data)
		{
			other.data = nullptr;
		}

		inline Array<T>& operator = (Array<T> const& other)
		{
			if (this != &other)
			{
				if (nullptr != data)
				{
					delete[] data;
					data = nullptr;
				}
				capacity = other.capacity;
				size = other.size;
				if (capacity > 0)
				{
					data = new T[capacity];
					for (size_t i = 0; i < size; i++)
						data[i] = other.data[i];
				}
			}
			return *this;
		}

		inline Array<T>& operator = (Array<T>&& other)
		{
			if (this != &other)
			{
				if (nullptr != data)
				{
					delete[] data;
					data = nullptr;
				}

				capacity = other.capacity;
				size = other.size;
				data = other.data;

				other.data = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Manipulators

		inline T& operator [] (size_t index)
		{
			if (index >= size)
				throw InvalidIndex();

			return data[index];
		}

		inline const T& operator [] (size_t index) const
		{
			if (index >= size)
				throw InvalidIndex();

			return data[index];
		}

		inline void Set(size_t index, T const & element)
		{
			if (index > size)
				throw InvalidIndex();

			if (index == size)
				Push(element);
			else
				data[index] = element;
		}

		inline size_t Size() const
		{
			return size;
		}

		inline bool Empty() const
		{
			return size == 0;
		}

		inline void Push(T const & element)
		{
			if (size == capacity)
				Extend();

			data[size++] = element;
		}

		inline T& Pop()
		{
			if (size == 0)
				throw AlreadyEmpty();

			return data[--size];
		}

		inline void Clear()
		{
			size = 0;
		}

#pragma endregion

	private:

		inline void Extend()
		{
			size_t new_cap = capacity << 1;
			if (0 == new_cap)
				new_cap = 1;

			T* new_data = new T[new_cap];

			if (nullptr != data)
			{
				for (size_t i = 0; i < size; i++)
					new_data[i] = data[i];

				delete[] data;
			}

			capacity = new_cap;
			data = new_data;
		}

	private:
		T*		data;
		size_t	capacity;
		size_t	size;
	};
}
