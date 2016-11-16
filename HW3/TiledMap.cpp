#include "TiledMap.h"

#include "Array.h"

#include "TiledSprite.h"

#include <fstream>
#include <sstream>

using namespace std;

namespace
{
	hw3::Array<string> split(const string& str, char delimiter)
	{
		hw3::Array<string> ret;
		stringstream ss(str);

		string substr;
		while (getline(ss, substr, delimiter))
		{
			if (substr.empty())
				continue;
			ret.Push(substr);
		}

		return ret;
	}

	int string_to_int(const string& str)
	{
		int ret = 0;
		stringstream ss(str);
		ss >> ret;
		return ret;
	}

	float string_to_float(const string& str)
	{
		float ret = 0;
		stringstream ss(str);
		ss >> ret;
		return ret;
	}

	const string NA("N/A");
}

namespace hw3
{

	TiledMap::TiledMap()
		:
		width(0),
		height(0),
		data(nullptr),
		sprite(nullptr)
	{
	}


	TiledMap::~TiledMap()
	{
		if (nullptr != data)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void TiledMap::LoadFromFile(char const * map_file)
	{
		ifstream fin(map_file);

		string line;

		hw3::Array<hw3::Array<string>> arr;

		while (getline(fin, line))
		{
			arr.Push(split(line, ','));
		}

		fin.close();

		width = static_cast<int>(arr[0].Size());
		height = static_cast<int>(arr.Size());

		data = new int[width * height];

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				data[y * width + x] = string_to_int(arr[y][x]);
			}
		}
	}

	void TiledMap::SetTileSize(int tileWidth, int tileHeight)
	{
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;

		sprite->SetRect(SDL_Rect{ 0, 0, tileWidth, tileHeight });
	}

	void TiledMap::Draw()
	{
		if (nullptr == sprite)
			return;

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				int tileId = data[y * width + x];

				if (tileId < 0)
					continue;

				sprite->SetPosition(tileWidth * x, tileHeight * y);
				sprite->SetTileId(tileId);
				sprite->Draw();
			}
		}
	}

}
