#pragma once
#include "array.h"
class Image;
class State {
public:
	State(const char* stageData,int size);
	~State();
	void setSize();
	void update(int x,int y,int dt);
	void draw();
	bool hasClear();
	void reset();
private:
	class Object;
	int mWidth;
	int mHeight;
	char* mStageData;
	Array2D<Object> mdata;
	Image* image;
	int moveCount;
	static const int MAX_MOVE_COUNT = 300;//移动一格的时间
};