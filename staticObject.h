#pragma once
class Image;
class StaticObject {
public:
	//背景
	//静态物品 混凝土（炸不动） 砖块 炸弹 冲击波 道具（暂无）
	//动态物品 角色

	//绘制时先绘制背景 再绘制 静态物品/动态物品  (静态物品又分层 先道具 再砖块)
	enum Flag {
		F_WALL=(1<<0),//混凝土 （不能炸）
		F_BRICK=(1<<1),//砖块
		F_ITEM_BOMB=(1<<2),//炸弹
		F_ITEM_POWER=(1<<3)//冲击波
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
	StaticObject();
	~StaticObject();
	void draw(int x, int y, const Image*)const;
	bool checkFlag(unsigned)const;
	void setFlag(unsigned);
	void resetFlag(unsigned);
private:
	unsigned mFlag;
	static const int OBJECT_LEN = 16;
};
