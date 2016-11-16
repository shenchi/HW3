#pragma once

#include "Array.h"
#include "HashMap.h"

namespace hw3
{
	template<typename T>
	struct DefaultCampFunc { bool operator () (T const & a, T const & b) const { return a < b; } };

	template<typename T>
	struct DummyHashMap
	{
		struct Iterator
		{
			inline operator bool() const { return false; }
		};

		inline void Set(T const&, size_t) {}
		inline Iterator Find(T const&) { return Iterator(); }
		inline void Remove(T const&) {}
	};

	template<typename T, typename CampFunc = DefaultCampFunc<T>, typename HashMapType = DummyHashMap<T>>
	class BinaryHeap
	{
	public:

		inline void Insert(T const & element)
		{
			size_t cur = data.Size();
			size_t par = (cur - 1) / 2;

			while (cur > 0 && campFunc(element, data[par]))
			{
				data.Set(cur, data[par]);
				hash_table.Set(data[par], cur);

				cur = par;
				par = (cur - 1) / 2;
			}

			data.Set(cur, element);
			hash_table.Set(element, cur);
		}

		inline T& Delete()
		{
			if (data.Size() == 0)
				throw AlreadyEmpty();

			if (data.Size() > 1)
			{
				size_t max = data.Size() - 1;

				T t = data[max];
				data[max] = data[0];
				hash_table.Remove(data[max]);

				size_t i = 0;
				size_t j = i * 2 + 1;

				while (j < max)
				{
					if (j + 1 < max && campFunc(data[j + 1], data[j]))
						j++;

					if (campFunc(data[j], t))
					{
						data[i] = data[j];
						hash_table.Set(data[i], i);
					}
					else
						break;

					i = j;
					j = i * 2 + 1;
				}

				data[i] = t;
				hash_table.Set(t, i);
			}

			return data.Pop();
		}

		inline void DecreaseKey(T const & element)
		{
			auto iter = hash_table.Find(element);
			if (iter)
			{
				size_t cur = iter->second;
				size_t par = (cur - 1) / 2;

				while (cur > 0 && campFunc(element, data[par]))
				{
					data.Set(cur, data[par]);
					hash_table.Set(data[par], cur);

					cur = par;
					par = (cur - 1) / 2;
				}

				data.Set(cur, element);
				hash_table.Set(element, cur);
			}
		}

		inline bool Empty() const
		{
			return data.Empty();
		}

	private:
		Array<T>		data;
		HashMapType		hash_table;
		CampFunc		campFunc;
	};
}
