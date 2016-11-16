#pragma once

#include "Array.h"
#include "PriorityQueue.h"

namespace hw3
{
	template<typename T>
	struct DummyHeuristic
	{
		inline T operator () (size_t cur, size_t end) const { return T(); }
	};

	template<typename TGraph, typename TWeight, typename THeuristic = DummyHeuristic<TWeight>>
	Array<size_t> Dijkstra(TGraph& graph, size_t start, size_t end, THeuristic& heuristic = DummyHeuristic<TWeight>())
	{
		Array<bool>	closed(graph.Size());
		Array<bool>	queued(graph.Size());
		Array<TWeight> dist(graph.Size());
		Array<size_t> from(graph.Size());

		Array<size_t> path;

		PriorityQueue<size_t, TWeight> queue;

		queue.Enqueue(start, TWeight());
		queued[start] = true;
		dist[start] = TWeight();
		from[start] = start;

		while (!queue.Empty())
		{
			size_t cur = queue.Dequeue().first;

			closed[cur] = true;

			if (cur == end)
			{
				while (from[cur] != cur)
				{
					path.Push(cur);
					cur = from[cur];
				}
				path.Push(cur);
			}

			for (auto iter = graph.GetIterator(cur); iter; ++iter)
			{
				size_t i = *iter;
				if (!closed[i] && graph.Edge(cur, i))
				{
					TWeight new_dist = dist[cur] + graph.Weight(cur, i);
					if (!queued[i])
					{
						queue.Enqueue(i, new_dist + heuristic(cur, end));
						queued[i] = true;
						dist[i] = new_dist;
						from[i] = cur;
					}
					else if (dist[i] > new_dist)
					{
						queue.DecreasePriority(i, new_dist + heuristic(cur, end));
						dist[i] = new_dist;
						from[i] = cur;
					}
				}
			}
		}

		return path;
	}

}
