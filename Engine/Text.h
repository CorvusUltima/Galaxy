#pragma once
#include"graphics.h"

 class Text
{
public:

	
	static void Print(Graphics& gfx,std::string str, int x, int y);
	static void DrawChar(Graphics&gfx,char c, int x, int y);
	static int OffSet(char c);


	static const void DrawA(int x,int y, Graphics& gfx);
	static const void DrawB(int x,int y, Graphics& gfx);
	static const void DrawC(int x, int y, Graphics& gfx);


};

