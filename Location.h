#pragma once

class Location;
typedef Location Direction;//�������������ඨ����ͬ

class Location
{
protected:
	int x;
	int y;
public:
	Location(int x = 0, int y = 0);
	void SetLocation(int x, int y);
	void SetLocation(Location locate);
	int GetX();//��ȡx����
	int GetY();//��ȡy����
	Location operator+(Direction direct);
	Location operator+=(Direction direct);
	Location operator-(Direction direct);
	Location operator-=(Direction direct);
	bool operator==(Location locate);
};