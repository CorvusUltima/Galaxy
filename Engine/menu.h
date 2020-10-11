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
			sound,
			soundSelect
		};

	public:
		Button() = default;
		Button(Vec2& topLeft);
		void Draw(Graphics& gfx, int x,int y);
		void Update(Vec2& selector);
		bool IsInside(const RectF& button, Mouse& mouse);
		
	public:
	
		RectF rect;
		Type type;
		bool ButtonIsAddet = false;
		bool IsSelected = false;
		static constexpr float width = 200.0f;
		static constexpr float height = 100.0f;

	public:
		Surface sound = Surface("sound.bmp");
		Surface soundSelect = Surface("soundSelect.bmp");
	};

public:
	Menu(const Vec2& topleft, int nbuttons);
	void DrawMenu(Graphics& gfx);
	void Update(Keyboard& kbd);
	
	
	
private:


	Vec2 topleft;
    int nbuttons=1;
	Button buttons[10];
	Vec2 selector;




};

