#pragma once


namespace hw3
{
	template<typename T>
	class Graph
	{
	public:
		Graph<T>(size_t size)
			:
			size(size),
			weights(size * size),
			edges(size * size)
		{}

		inline size_t Size() const { return size; }

		inline bool Edge(size_t a, size_t b) const { return edges[a * size + b]; }

		inline T Weight(size_t a, size_t b) const { return weights[a * size + b]; }

		inline void SetEdge(size_t a, size_t b, bool connected, bool directed = false)
		{
			edges[a * size + b] = connected;
			if (!directed)
				edges[b * size + a] = connected;
		}

		inline void SetWeight(size_t a, size_t b, T weight, bool directed = false)
		{
			SetEdge(a, b, true, directed);
			weights[a * size + b] = weight;
			if (!directed)
				weights[b * size + a] = weight;
		}

	private:
		size_t		size;
		Array<bool>	edges;
		Array<T>	weights;
	};
}
