#pragma once

#include "Array.h"

namespace hw3
{
	template<typename T>
	struct DefaultCampFunc { bool operator () (T const & a, T const & b) const { return a < b; } };


	template<typename T, typename CampFunc = DefaultCampFunc<T>>
	class BinaryHeap
	{
	public:

		inline void Insert(T const & element)
		{
			size_t cur = data.Length();
			size_t par = (cur - 1) / 2;

			while (cur > 0 && campFunc(element, data[par]))
			{
				data.Set(cur, data[par]);

				cur = par;
				par = (cur - 1) / 2;
			}

			data.Set(cur, element);
		}

		inline T& Delete()
		{
			if (data.Length() == 0)
				throw AlreadyEmpty();

			if (data.Length() > 1)
			{
				size_t max = data.Length() - 1;

				T t = data[max];
				data[max] = data[0];

				size_t i = 0;
				size_t j = i * 2 + 1;

				while (j < max)
				{
					if (j + 1 < max && campFunc(data[j + 1], data[j]))
						j++;

					if (campFunc(data[j], t))
						data[i] = data[j];
					else
						break;

					i = j;
					j = i * 2 + 1;
				}

				data[i] = t;
			}

			return data.Pop();
		}

		inline bool Empty() const
		{
			return data.Empty();
		}

	private:
		Array<T>	data;
		CampFunc	campFunc;
	};
}
