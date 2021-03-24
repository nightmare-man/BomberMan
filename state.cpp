#include "state.h"
#include "GameLib/GameLib.h"
using namespace GameLib;
#include "file.h"
#include "image.h"
class State::Object {
public:
	enum Type {
		O_WALL,
		O_SPACE,
		O_MAN,
		O_BLOCK,
		O_UNKNOWN
	};
	enum O_ID {
		I_MAN,
		I_WALL,
		I_BLOCK,
		I_GOAL,
		I_SPACE
	};
	bool mGoalFlag;
	int mMoveX;
	int mMoveY;
	Type mObject;
	Object():mMoveX(0),mMoveY(0),mObject(O_UNKNOWN),mGoalFlag(false) {

	}
	~Object() {}
	void set(char c) {
		switch (c)
		{
		case ' ':mObject = O_SPACE;break;
		case '#':mObject = O_WALL; break;
		case '.':mObject = O_SPACE; mGoalFlag = true; break;
		case 'o':mObject = O_BLOCK; break;
		case 'O':mObject = O_BLOCK; mGoalFlag = true; break;
		case 'p':mObject = O_MAN; break;
		case 'P':mObject = O_MAN; mGoalFlag = true; break;
		}
	}
	void DrawCell(Image* image,int dstx,int dsty,O_ID id) {
		int length = image->Height();
		image->Draw(dstx, dsty, length * id, 0, length, length);
	}
	void DrawBackground(Image* image,int dstx,int dsty) {
		if (mObject == O_WALL) {
			DrawCell(image, dstx, dsty, I_WALL);
		}
		else {
			if (mGoalFlag) {
				DrawCell(image, dstx, dsty, I_GOAL);
			}
			else {
				DrawCell(image, dstx, dsty, I_SPACE);
			}
		}
		
			
		
	}
	void DrawForeground(Image* image,int dstx, int dsty) {
		if (mObject == O_MAN) {
			DrawCell(image, dstx, dsty, I_MAN);
		}
		else if (mObject == O_BLOCK) {
			DrawCell(image, dstx, dsty, I_BLOCK);
		}
		
	}
	void moveTo(int dx,int dy,Type replace) {
		mMoveX = dx;
		mMoveY = dy;
		mObject = replace;
	}
};
void State::setSize() {
	int x = 0;
	int y = 0;
	for (int i = 0; mStageData[i] != 0; i++) {
		switch (mStageData[i])
		{
		case '#':case ' ':case '.':case 'o':case 'O':case 'p':
		case 'P':x++; break;
		case '\n':y++; 
			mHeight = mHeight > y ? mHeight : y;
			mWidth = mWidth > x ? mWidth : x;
			x = 0;
			break;
		default: break;
		}
	}
}
void State::reset() {
	setSize();
	mdata.setSize(mWidth, mHeight);
	int x = 0,y = 0;
	for (int i = 0; mStageData[i] != 0; i++) {
		Object o;//构造函数初始化O_WALL mgoalflag false
		switch (mStageData[i])
		{
		case '#':o.mObject=Object::O_WALL;  break;
		case ' ':o.mObject = Object::O_SPACE;  break;
		case '.':o.mObject = Object::O_SPACE; o.mGoalFlag = true; break;
		case 'o':o.mObject = Object::O_BLOCK;  break;
		case 'O':o.mObject = Object::O_BLOCK; o.mGoalFlag = true;  break;
		case 'p':o.mObject = Object::O_MAN;  break;
		case 'P':o.mObject = Object::O_MAN; o.mGoalFlag = true;  break;
		case '\n':y++; x = 0; break;
		default:
			break;
		}
		if (o.mObject != Object::O_UNKNOWN) {
			mdata(x, y) = o;
			x++;
		}
	}
}
State::State(const char* stageData,int size):mWidth(0),mHeight(0),
mStageData(0),moveCount(0),image(0)
{
	mStageData = new char[size];
	for (int i = 0; i < size; i++) {
		mStageData[i] = stageData[i];
	}//复制数据
	reset();
	image = new Image("data/image/nimotsuKunImage2.dds");
}
State::~State() {
	SAFE_DELETE(image);
	delete[] mStageData;
}
void State::update(int dx,int dy,int dt) {

	if (moveCount == MAX_MOVE_COUNT) {
		moveCount = 0;
		for (int y = 0; y < mHeight; y++) {
			for (int x = 0; x < mWidth; x++) {
				mdata(x, y).mMoveX = 0;
				mdata(x, y).mMoveY = 0;
			}
		}
		return;
	}
	if (moveCount > 0) {
		moveCount += dt;
		if (moveCount > MAX_MOVE_COUNT) {
			moveCount = MAX_MOVE_COUNT;
		}
		return;
	}
	if (!dx && !dy) {
		return;
	}
	//找到位置
	int x = 0, y = 0;
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			if (mdata(i, j).mObject == Object::O_MAN) {
				x = i;
				y = j;
			}
		}
	}
	int x1 = x + dx,y1 = y + dy;
	if (x1 < 0 || x1 >= mWidth || y1<0 || y1>mHeight) {
		return;
	}
	if (mdata(x1, y1).mObject == Object::O_WALL) {
		return;
	}
	else {
		if (mdata(x1, y1).mObject == Object::O_BLOCK) {
			//箱子 看下一格子
			int x2 = x1 + dx, y2 = y1 + dy;
			if (x2 < 0 || x2 >= mWidth || y2 < 0 || y2 >= mHeight) {
				return;
			}
			if (mdata(x2, y2).mObject == Object::O_WALL ||
				mdata(x2, y2).mObject == Object::O_BLOCK) {
				return;
			}
			mdata(x2, y2).moveTo(dx, dy, Object::O_BLOCK);
			mdata(x1, y1).moveTo(dx, dy, Object::O_MAN);
			mdata(x, y).moveTo(dx, dy, Object::O_SPACE);
			moveCount = 1;
			//实际上O_SPACE的移动，不会有动画，因为作为背景，
			//其dx dy被忽视了，不会产生移动
		}
		else {
			//空的直接走
			mdata(x1, y1).moveTo(dx, dy, Object::O_MAN);
			mdata(x, y).moveTo(dx, dy, Object::O_SPACE);
			moveCount = 1;
		}
	}

}
void State::draw() {
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			Object o = mdata(x, y);
			o.DrawBackground(image, x * 32, y * 32);
			
		}
	}
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			Object o = mdata(x, y);
			if (o.mObject == Object::O_MAN || o.mObject == Object::O_BLOCK) {
					int dx = (32 * o.mMoveX * (MAX_MOVE_COUNT - moveCount)) / MAX_MOVE_COUNT;
					int dy = (32 * o.mMoveY * (MAX_MOVE_COUNT - moveCount)) / MAX_MOVE_COUNT;
					mdata(x, y).DrawForeground(image, x * 32 - dx, y * 32 - dy);
			}
		}
	}
}
bool State::hasClear() {
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			Object o = mdata(x, y);
			if (o.mObject == Object::O_BLOCK && !o.mGoalFlag) {
				return false;
			}
		}
	}
	return true;
}