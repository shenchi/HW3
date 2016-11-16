#pragma once

#include "BinaryHeap.h"

namespace hw3
{

	template<typename K, typename V>
	struct PriorityQueuePair
	{
		K	first;
		V	second;

		inline bool operator == (PriorityQueuePair<K, V> const & other) const { return first == other.first; }
	};

	template<typename K, typename V>
	class PriorityQueue
	{
	public:
		typedef PriorityQueuePair<K, V> PairType;

	private:

		struct CampFunc
		{
			inline bool operator () (PairType const& p1, PairType const& p2) const
			{
				return p1.second < p2.second;
			}
		};

		struct HashFunc
		{
			DefaultHashFunc<K> hash_func;

			inline size_t operator () (PairType const& p) const
			{
				return hash_func(p.first);
			}
		};

		typedef BinaryHeap<PairType, CampFunc, HashMap<PairType, size_t, 128, HashFunc>> HeapType;

	public:

		inline void Enqueue(K const & key, V const & value)
		{
			heap.Insert(PairType{ key, value });
		}

		inline PairType Dequeue()
		{
			return heap.Delete();
		}

		inline void DecreasePriority(K const & key, V const & value)
		{
			heap.DecreaseKey(PairType{ key, value });
		}

		inline bool Empty() const
		{
			return heap.Empty();
		}

	private:
		HeapType heap;
	};
}