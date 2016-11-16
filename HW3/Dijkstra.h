#pragma once

#include "Array.h"
#include "PriorityQueue.h"

namespace hw3
{
	template<typename T>
	struct PathNode
	{
		size_t		node;
		Array<T>*	dist;

		PathNode() : node(0), dist(nullptr) {}
		PathNode(size_t node, Array<T>* dist) : node(node), dist(dist) {}

		inline bool operator < (PathNode const & other) const
		{
			return (*dist)[node] < (*dist)[other.node];
		}
	};

	template<typename TGraph, typename TWeight>
	Array<size_t> Dijkstra(TGraph& graph, size_t start, size_t end)
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
						queue.Enqueue(i, new_dist);
						queued[i] = true;
						dist[i] = new_dist;
						from[i] = cur;
					}
					else if (dist[i] > new_dist)
					{
						queue.DecreasePriority(i, new_dist);
						dist[i] = new_dist;
						from[i] = cur;
					}
				}
			}
		}

		return path;
	}

}
