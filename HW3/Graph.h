#pragma once


namespace hw3
{
	template<typename T>
	class Graph
	{
	public:
		Graph(size_t size)
			:
			size(size),
			weights(size * size),
			edges(size * size)
		{}

		inline size_t Size() const { return size; }

		inline bool Edge(size_t a, size_t b) const { return edges[a * size + b]; }

		inline T Weight(size_t a, size_t b) const { return weights[a * size + b]; }

		class Iterator
		{
		public:

			inline operator bool() const
			{
				return !finish;
			}

			inline void operator ++ ()
			{
				if (finish)
					return;

				do
				{
					n++;
				} while (n < g.Size() && !g.Edge(v, n));

				if (n >= g.Size())
					finish = true;
			}

			inline size_t operator * () const
			{
				return n;
			}

		private:
			friend class Graph<T>;
			inline Iterator(Graph<T> const & g, size_t v) : finish(false), g(g), v(v), n(0)
			{
				if (!g.Edge(v, n))
					operator ++ ();
			}

			bool finish;
			Graph<T> const & g;
			size_t v;
			size_t n;
		};

		inline Iterator GetIterator(size_t v) const
		{
			return Iterator(*this, v);
		}

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
