#pragma once
#include "Character.h"

#include "Array.h"

namespace hw3
{
	class Enemy :
		public Character
	{
	public:
		Enemy();

		inline void SetTarget(Character* t) { target = t; }

		virtual void Update();

		virtual void Draw();

	protected:
		Character*	target;

		Sprite			frameSprite;
		Array<size_t>	path;
	};

}
