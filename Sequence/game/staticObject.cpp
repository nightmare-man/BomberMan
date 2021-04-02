#include "staticObject.h"
#include "image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
StaticObject::StaticObject():mFlag(0) ,mFloor(true){

}
StaticObject::~StaticObject() {

}
void StaticObject::setFlag(unsigned f) {
	mFlag |= f;
	return;
}
void StaticObject::draw(int x, int y,  const Image* image)const {
	//先画背景 或者墙 砖
	int srcX = -1;
	int srcY = -1;
	if (checkFlag(F_WALL)) {
		srcX = (I_WALL % 4) * OBJECT_LEN;
		srcY = (I_WALL / 4) * OBJECT_LEN;
	}
	else if (checkFlag(F_BRICK)) {
		srcX = (I_BRICK % 4) * OBJECT_LEN;
		srcY = (I_BRICK / 4) * OBJECT_LEN;
	}
	else {
		srcX = (I_BACK % 4) * OBJECT_LEN;
		srcY = (I_BACK / 4) * OBJECT_LEN;
	}
	image->Draw(x * OBJECT_LEN, y * OBJECT_LEN,srcX,srcY, OBJECT_LEN, OBJECT_LEN);
	//再画道具
	if (mFloor) {
	
		if (checkFlag(F_ITEM_BOMB)) {
			srcX = (I_ITEM_BOMB % 4) * OBJECT_LEN;
			srcY = (I_ITEM_BOMB / 4) * OBJECT_LEN;
		}
		else if (checkFlag(F_ITEM_POWER)) {
			srcX = (I_ITEM_POWER % 4) * OBJECT_LEN;
			srcY = (I_ITEM_POWER / 4) * OBJECT_LEN;
		}
		image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, srcX, srcY, OBJECT_LEN, OBJECT_LEN);

	}
	
}
bool StaticObject::checkFlag(unsigned f)const {
	return mFlag & f ? true : false;
}
void StaticObject::resetFlag(unsigned) {
	mFlag = 0;
	return;
}