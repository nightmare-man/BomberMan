#pragma once
#include "array.h"
class Image;
class StaticObject;
class State {
public:
	static const int STAGE_ID_2PLAYS = 0;
	State(int stageID);
	~State();
	void update();//���뼰����
	void draw()const;//����
	bool hasClear()const;//����ǲ���Ӯ��
	bool isAlive1P()const;
	bool isAlive2P()const;
private:
	Array2D<StaticObject> mStageObjects;
	Image* image;//ͼƬ
	int mStageID;
};