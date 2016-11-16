#pragma once

#include "MapGraph.h"

#include <cmath>

namespace hw3
{
	class TiledSprite;

	class TiledMap
	{
	public:
		TiledMap();
		~TiledMap();

		void LoadFromFile(char const * filename);

		void SetTileSize(int tileWidth, int tileHeight);

		inline void SetSprite(TiledSprite* s) { sprite = s; }

		void Draw();

		inline bool IsAir(int x, int y) const {
			if (x < 0 || x >= width || y < 0 || y >= height)
				return false;
			return data[y*width + x] == -1;
		}

		inline bool IsClimable(int x, int y) const {
			if (x < 0 || x >= width || y < 0 || y >= height)
				return false;
			return data[y*width + x] == 31;
		}

		inline int Width() const { return width; }
		inline int Height() const { return height; }

		inline size_t Coord2Hash(int x, int y) const { return static_cast<size_t>(y * width + x); }
		inline void Hash2Coord(size_t hash, int& x, int& y) const
		{
			x = static_cast<int>(hash) % width;
			y = static_cast<int>(hash) / width;
		}

#pragma region Interface for Graph

		inline size_t Size() const
		{
			return static_cast<size_t>(width * height);
		}

		inline bool Edge(size_t a, size_t b) const
		{
			int sx = static_cast<int>(a) % width, sy = static_cast<int>(a) / width;
			int tx = static_cast<int>(b) % width, ty = static_cast<int>(b) / width;

			bool inAir = IsAir(sx, sy);
			bool inLadder = IsClimable(sx, sy);

			bool toAir = IsAir(tx, ty);
			bool toLadder = IsClimable(tx, ty);

			if (!inAir && !inLadder)
				return false;

			if (abs(sx - tx) == 1 && abs(sy - ty) == 0)
			{
				if (!IsAir(sx, sy + 1))
					return toAir || toLadder;
			}
			else if (abs(sx - tx) == 0)
			{
				if (sy - ty == 1)
				{
					if (inLadder && (toLadder || toAir))
						return true;
				}
				else if (sy - ty == -1)
				{
					return toAir || toLadder;
				}
			}

			return false;
		}

		inline int Weight(size_t a, size_t b) const
		{
			return Edge(a, b) ? 1 : -1;
		}

		class Iterator
		{
		public:

			inline operator bool() const
			{
				return !finish;
			}

			inline void operator ++ ()
			{
				do
				{
					next();
				} while (n < 0 && !finish);
			}

			inline size_t operator * () const
			{
				return static_cast<size_t>(n);
			}

		private:

			inline void next()
			{
				if (n == v - w)
					n = v + 1;
				else if (n == v + 1)
					n = v + w;
				else if (n == v + w)
					n = v - 1;
				else
					finish = true;
			}

		private:
			friend class TiledMap;
			inline Iterator(int v, int w) : finish(false), v(v), w(w), n(v - w) 
			{
				if (n < 0)
					operator ++ ();
			}

			bool finish;
			int v;
			int w;
			int n;
		};

		inline Iterator GetIterator(size_t v) const
		{
			return Iterator(static_cast<int>(v), width);
		}

#pragma endregion

#pragma region Interface for Pathfinding

		struct Heuristic
		{
			TiledMap* map;
			inline int operator () (size_t cur, size_t end) const 
			{
				int cx = 0, cy = 0;
				int ex = 0, ey = 0;
				map->Hash2Coord(cur, cx, cy);
				map->Hash2Coord(end, ex, ey);

				return abs(cx - ex) + abs(cy - ey);
			}
		};

		Heuristic GetHeuristicFunc()
		{
			return Heuristic{ this };
		}

#pragma endregion


	private:
		int		width;
		int		height;
		int*	data;

		int		tileWidth;
		int		tileHeight;

		TiledSprite* sprite;

	};

}
