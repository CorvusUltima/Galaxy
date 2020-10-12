#pragma once
#include"RectF.h"
#include"Vec2.h"
#include"Surface.h"
#include"Colors.h"
#include"Graphics.h"
#include"Mouse.h"
#include"Keyboard.h"
class Menu
{
public:
	
private:
	class Button
	{
	public:
		enum class Type
		{
			uninitialized, //Needed something to stop constructor from complaining
			sound,
			soundSelect
		};

		Button() = default;
		Button(Vec2& topLeft);
		void Draw(Graphics& gfx);

	
		RectF rect = { 0, 0, 0, 0 };
		Type type = Type::uninitialized;
		bool IsSelected = false;
		static constexpr float width = 200.0f;
		static constexpr float height = 100.0f;


		Surface sound = Surface("sound.bmp");
		Surface soundSelect = Surface("soundSelect.bmp");
	};

public:
	Menu(const Vec2& topleft, int nbuttons);
	void DrawMenu(Graphics& gfx);
	void Update(Keyboard& kbd, float dt);	
	
private:

	Vec2 topleft;
    int nbuttons=0;
	Button buttons[10];
	Vec2 selector;
	float fSelectorMoveCooldown = 0;

};

