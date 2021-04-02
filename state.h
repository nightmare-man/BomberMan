#pragma once
#include "array.h"
class Image;
class StaticObject;
class State {
public:
	static const int STAGE_ID_2PLAYS = 0;
	State(int stageID);
	~State();
	void update();//输入及更新
	void draw()const;//绘制
	bool hasClear()const;//检测是不是赢了
	bool isAlive1P()const;
	bool isAlive2P()const;
private:
	Array2D<StaticObject> mStageObjects;
	Image* image;//图片
	int mStageID;
};