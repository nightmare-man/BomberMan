#include "dynamicObject.h"
#include "image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
DynamicObject::DynamicObject() :mX(0),mY(0),mT(T_1P){

}
DynamicObject::~DynamicObject() {

}
void DynamicObject::draw(const Image* image) {
	int dstX = (mX - 8000 + 500) / 1000;//四舍五入（0.8像素 归到1像素里取）
	int dstY = (mY - 8000 + 500) / 1000;
	int srcX = -1;
	int srcY = -1;
	switch (mT)
	{
	case DynamicObject::T_1P:
		srcX = (I_1P % 4) * OBJECT_LEN;
		srcY = (I_1P / 4) * OBJECT_LEN;
		break;
	case DynamicObject::T_2P:
		srcX = (I_2P % 4) * OBJECT_LEN;
		srcY = (I_2P / 4) * OBJECT_LEN;
		break;
	case DynamicObject::T_ENEMY:
		srcX = (I_ENEMY % 4) * OBJECT_LEN;
		srcY = (I_ENEMY / 4) * OBJECT_LEN;
		break;
	}
	image->Draw(dstX, dstY, srcX, srcY, OBJECT_LEN, OBJECT_LEN);
}
void DynamicObject::set(int x, int y, Type t) {
	mX = x*16000+8000;
	mY = y*16000+8000;
	mT = t;
}
void DynamicObject::update() {
	if (mT == T_1P) {
		Framework f = Framework::instance();
		int dx = 0, dy = 0;
		if (f.isKeyOn('a')) {
			dx = -1000;
		}
		else if (f.isKeyOn('d')) {
			dx = 1000;
		}
		else if (f.isKeyOn('w')) {
			dy = -1000;
		}
		else if (f.isKeyOn('s')) {
			dy = 1000;
		}
		mX += dx;
		mY += dy;
	
	
	}
	else if(mT==T_ENEMY){

	}
	
}