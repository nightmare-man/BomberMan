#pragma once
class Image;
class DynamicObject {
public:
	enum Type {
		T_1P,
		T_2P,
		T_ENEMY
	};
	enum O_ID {
		I_1P,
		I_2P,
		I_ITEM_BOMB,
		I_ITEM_POWER,
		I_EXPLODE_ROW,
		I_EXPLODE_COL,
		I_ENEMY,
		I_WALL,
		I_BRICK,
		I_BACK,
		I_BOMB,
		I_EXPLODE_CEN
	};
	DynamicObject();
	~DynamicObject();
	void draw(const Image* );
	//传入的x,y网格坐标 1网格16像素
	void set(int x, int y, Type t);
	void update();
private:
	Type mT;
	int mX;//mX mY 是指角色原点的坐标，内部坐标 1像素为1000 内部坐标 1网格16000
	int mY;
	const static int OBJECT_LEN = 16;
};
