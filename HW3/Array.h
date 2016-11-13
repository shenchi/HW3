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

		inline Array<T>(size_t capacity = 16)
			:
			data(nullptr),
			capacity(capacity),
			length(0)
		{
			if (capacity > 0)
				data = new T[capacity];
		}

		inline ~Array<T>()
		{
			if (nullptr != data)
				delete[] data;
		}

		inline Array<T>(Array<T> const & other)
			: data(nullptr),
			capacity(other.capacity),
			length(other.length)
		{
			if (capacity > 0)
			{
				data = new T[capacity];

				for (size_t i = 0; i < length; i++)
					data[i] = other.data[i];
			}
		}

		inline Array<T>(Array<T>&& other)
			: capacity(other.capacity),
			length(other.length),
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
				length = other.length;
				if (capacity > 0)
				{
					data = new T[capacity];
					for (size_t i = 0; i < length; i++)
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
				length = other.length;
				data = other.data;

				other.data = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Manipulators

		inline T& operator [] (size_t index)
		{
			if (index >= length)
				throw InvalidIndex();

			return data[index];
		}

		inline const T& operator [] (size_t index) const
		{
			if (index >= length)
				throw InvalidIndex();

			return data[index];
		}

		inline void Set(T const & elemeent)
		{
			if (index > length)
				throw InvalidIndex();

			if (index == length)
				Push(element);
			else
				data[index] = element;
		}

		inline size_t Length() const
		{
			return length;
		}

		inline bool Empty() const
		{
			return length == 0;
		}

		inline void Push(T const & element)
		{
			if (length == capacity)
				Extend();

			data[length++] = element;
		}

		inline T& Pop()
		{
			if (length == 0)
				throw AlreadyEmpty();

			return data[--length];
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
				for (size_t i = 0; i < length; i++)
					new_data[i] = data[i];

				delete[] data;
			}

			capacity = new_cap;
			data = new_data;
		}

	private:
		T*		data;
		size_t	capacity;
		size_t	length;
	};
}
