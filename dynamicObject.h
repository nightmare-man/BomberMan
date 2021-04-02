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
	//�����x,y�������� 1����16����
	void set(int x, int y, Type t);
	void update();
private:
	Type mT;
	int mX;//mX mY ��ָ��ɫԭ������꣬�ڲ����� 1����Ϊ1000 �ڲ����� 1����16000
	int mY;
	const static int OBJECT_LEN = 16;
};
