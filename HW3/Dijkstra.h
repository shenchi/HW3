#pragma once

#include "Array.h"
#include "BinaryHeap.h"

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

	template<template<typename> typename TGraph, typename TWeight>
	Array<size_t> Dijkstra(TGraph<TWeight>& graph, size_t start, size_t end)
	{
		Array<bool>	closed(graph.Size());
		Array<bool>	queued(graph.Size());
		Array<TWeight> dist(graph.Size());
		Array<size_t> from(graph.Size());

		Array<size_t> path;

		BinaryHeap<PathNode<TWeight>> queue;

		queue.Insert(PathNode<TWeight>(start, &dist));
		queued[start] = true;
		dist[start] = 0;
		from[start] = start;

		while (!queue.Empty())
		{
			auto node = queue.Delete();
			size_t cur = node.node;

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

			for (size_t i = 0; i < graph.Size(); ++i)
			{
				if (!closed[i] && graph.Edge(cur, i))
				{
					TWeight new_dist = dist[cur] + graph.Weight(cur, i);
					if (!queued[i])
					{
						queue.Insert(PathNode<TWeight>(i, &dist));
						queued[i] = true;
						dist[i] = new_dist;
						from[i] = cur;
					}
					else if (dist[i] > new_dist)
					{
						dist[i] = new_dist;
						from[i] = cur;
					}
				}
			}
		}

		return path;
	}

}
