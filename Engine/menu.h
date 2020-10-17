#pragma once
#include"RectF.h"
#include"Vec2.h"
#include"Surface.h"
#include"Colors.h"
#include"Graphics.h"
#include"Mouse.h"
#include"Keyboard.h"
#include"img.h"
class Menu
{
public:
	
private:

	class Bar
	{
	public:

		enum class Type
		{
			uninitialized, //Needed something to stop constructor from complaining i quess so :) 
			sfx,
			music,
			back // the fuck is this ? you asked for its not my fault :)

		};

	    Bar() = default;
	  	Bar(Vec2 & topLeft);
		void Draw(Graphics & gfx);


		RectF rect = { 0, 0, 0, 0 };
		Type type = Type::uninitialized;
		bool  BarIsSelected = false;
		static constexpr float width = 200.0f;
		static constexpr float height = 30.0f;
		static constexpr float separator = 10.0f;
		static constexpr float  MaxSfxVolume = 1.0f;
		float SfxVolume = MaxSfxVolume;
		static constexpr float  MaxMusicVolume = 1.0f;
		float  MusicVolume = MaxMusicVolume;
		Surface sfx = Surface("sfx.bmp");
		Surface sfxSelect = Surface("sfxSelect.bmp");
		Surface music = Surface("music.bmp");
		Surface musicSelect = Surface("musicSelect.bmp");
	};





	class Button
	{


	public:
		enum class Type
		{
			uninitialized, //Needed something to stop constructor from complaining
			sound,
			resume
			
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
		Surface resume = Surface("resume.bmp");
		Surface resumeSelect = Surface("resumeSelect.bmp");
	};

public:
	Menu(const Vec2& topleft, int nbuttons,int nbars);
	void DrawMenu(Graphics& gfx);
	void DrawBar(Graphics& gfx);
	void Update(Keyboard& kbd, float dt);
	void BarUpdate(Keyboard& kbd, float dt);
	Vec2 GetSelector();
	bool bResume = false;
	bool bSound = false;
	bool soundBarON = false;
	bool bSfx = false;

private:


	RectF SFX;
	Vec2 topleft;
    int nbuttons=0;
	Button buttons[10];
	int nbars = 0;
	Bar bars[10];
	Vec2 selector;
	Vec2 BarSelector;
	bool IsSelected = false; 
	bool barIsSelected = false;
	float fSelectorMoveCooldown = 0.0f;


};

