#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
#include "image.h"
#include "file.h"
#include "staticObject.h"
const int WIDTH = 19;
const int HEIGHT = 15;
struct StageData {
	int mEnemyNumber;
	int mBrickRate;
	int mItemPowerNumber;
	int mItemBombNumber;
};
StageData gStageData[] = { {2,90,4,6},{3,80,1,0},{6,30,0,1} };//关卡信息
State::State(int stageID):image(0),mStageID(stageID){
	Framework f = Framework::instance();
	mStageObjects.setSize(WIDTH, HEIGHT);
	image = new Image("data/image/bakudanBitoImage.dds");
	const StageData& stageData = gStageData[stageID];
	int n = WIDTH * HEIGHT;
	unsigned* brickList = new unsigned[n];
	int brickNumber = 0;
	bool mode2P = (stageID == 0) ? true : false;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			StaticObject& o = mStageObjects(x, y);
			if (x == 0 || y == 0 || (x == WIDTH - 1) || (y == HEIGHT - 1)) {
				o.setFlag(StaticObject::F_WALL);//边缘围墙
			}
			else if ((x % 2 == 0) && (y % 2 == 0)) {
				o.setFlag(StaticObject::F_WALL);
			}
			else if (x + y < 4) {
				//左上角能够自由活动
			}
			else if (mode2P && (y + x > (WIDTH + HEIGHT - 6))) {
				//如果是双人 右下角2p也要自由活动
			}
			else {
				if (f.getRandom(100) > stageData.mBrickRate) {
					o.setFlag(StaticObject::F_BRICK);
					brickList[brickNumber++] = ((x << 16) | y);
				}
			}
		}
	}
	//设置道具
	int bombNumber = stageData.mItemBombNumber, powerNumber = stageData.mItemPowerNumber;
	
		//从brickNumber个砖块中 等概率取出bombNumber + powerNumber个
		//实际操作时，就是先随机取出一个，再随机再剩下的里再取出一个，一个循环即可
		//这就是等概率的
	
	for (int i = 0; i < bombNumber + powerNumber; i++) {
		int swapped = f.getRandom(brickNumber - i) + i;//原文写的brickNumber-1-i
		unsigned t = brickList[i];
		brickList[i] = brickList[swapped];
		brickList[swapped] = t;
		int x = brickList[i] >> 16;
		int y = brickList[i] & 0xffff;
		if (i < powerNumber) {//先选出来的放威力，候选出来的放数量道具
			mStageObjects(x, y).setFlag(StaticObject::F_ITEM_POWER);
		}
		else {
			mStageObjects(x, y).setFlag(StaticObject::F_ITEM_BOMB);
		}
	}
}
State::~State() {

}
void State::update() {

}
void State::draw()const {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mStageObjects(x, y).draw(x,y,image);
		}
	}
}
bool State::hasClear()const{
	return false;
}
bool State::isAlive1P()const {
	return true;
}
bool State::isAlive2P()const {
	return true;
}