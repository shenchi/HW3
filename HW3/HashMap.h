#pragma once

#include "Array.h"
#include "Queue.h"

namespace hw3
{
	template<typename T>
	struct DefaultHashFunc
	{
		inline size_t operator () (T const& t) const
		{
			return static_cast<size_t>(&t);
		}
	};

	template<>
	struct DefaultHashFunc<size_t> {
		inline size_t operator () (size_t v) const { return v; }
	};

	template<>
	struct DefaultHashFunc<int> {
		inline size_t operator () (int v) const { return static_cast<size_t>(v); }
	};

	template<typename K, typename V>
	struct KeyValuePair
	{
		K	key;
		V	value;

		inline bool operator == (K const & otherKey) const { return key == otherKey; }
	};

	template<typename K, typename V, size_t size = 128, typename HashFunc = DefaultHashFunc<K>>
	class HashMap
	{
	public:
		HashMap() : data(size) {}

		typedef	KeyValuePair<K, V> PairType;
		typedef typename Queue<PairType>::Iterator Iterator;

		inline void Set(K const & key, V const & value)
		{
			auto iter = Find(key);
			if (iter)
			{
				iter->value = value;
			}
			else
			{
				size_t hash = hash_func(key);
				size_t idx = hash % data.Size();
				data[idx].InsertBack(PairType{ key, value });
			}
		}

		inline Iterator operator [] (K const & key)
		{
			return Find(key);
		}

		inline Iterator Find(K const & key)
		{
			size_t hash = hash_func(key);
			size_t idx = hash % data.Size();

			for (auto i = data[idx].GetIterator(); i; ++i)
			{
				if (*i == key)
					return i;
			}

			return Iterator();
		}

		inline void Remove(K const & key)
		{
			size_t hash = hash_func(key);
			size_t idx = hash % data.Size();

			for (auto i = data[idx].GetIterator(); i; ++i)
			{
				if (*i == key)
				{
					data[idx].Remove(i);
					break;
				}
			}
		}

	private:
		HashFunc				hash_func;
		Array<Queue<PairType>>	data;
	};
}
