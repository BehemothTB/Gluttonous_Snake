#pragma once

class Location;
typedef Location Direction;//方向类与坐标类定义相同

class Location
{
protected:
	int x;
	int y;
public:
	Location(int x = 0, int y = 0);
	void SetLocation(int x, int y);
	void SetLocation(Location locate);
	int GetX();//获取x坐标
	int GetY();//获取y坐标
	Location operator+(Direction direct);
	Location operator+=(Direction direct);
	Location operator-(Direction direct);
	Location operator-=(Direction direct);
	bool operator==(Location locate);
};