#include "staticObject.h"
#include "image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
StaticObject::StaticObject():mFlag(0) {

}
StaticObject::~StaticObject() {

}
void StaticObject::setFlag(unsigned f) {
	mFlag |= f;
	return;
}
void StaticObject::draw(int x, int y,  const Image* image)const {
	//�Ȼ�����
	image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, OBJECT_LEN * (I_BACK % 4),
		OBJECT_LEN * (I_BACK / 4), OBJECT_LEN, OBJECT_LEN);
	//�ٻ�����
	if (checkFlag(F_ITEM_BOMB)) {
		image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, OBJECT_LEN * (I_ITEM_BOMB % 4),
			OBJECT_LEN * (I_ITEM_BOMB / 4), OBJECT_LEN, OBJECT_LEN);
	}
	if (checkFlag(F_ITEM_POWER)) {
		image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, OBJECT_LEN * (I_ITEM_POWER % 4),
			OBJECT_LEN * (I_ITEM_POWER / 4), OBJECT_LEN, OBJECT_LEN);
	}
	//�ٻ�ש��ǽ
	if (checkFlag(F_WALL)) {
		image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, OBJECT_LEN * (I_WALL % 4),
			OBJECT_LEN * (I_WALL / 4), OBJECT_LEN, OBJECT_LEN);
	}
	if (checkFlag(F_BRICK)) {
		image->Draw(x * OBJECT_LEN, y * OBJECT_LEN, OBJECT_LEN * (I_BRICK % 4),
			OBJECT_LEN * (I_BRICK / 4), OBJECT_LEN, OBJECT_LEN);
	}
}
bool StaticObject::checkFlag(unsigned f)const {
	return mFlag & f ? true : false;
}
void StaticObject::resetFlag(unsigned) {
	mFlag = 0;
	return;
}