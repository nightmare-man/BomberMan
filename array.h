#pragma once
#include "GameLib/GameLib.h"
template <typename T> class Array2D {
public:
	Array2D():mWidth(0),mHeight(0),mData(0) {

	}
	~Array2D() {
		SAFE_DELETE(mData);
	}
	void setSize(int x, int y) {
		mWidth = x;
		mHeight = y;
		mData = new T[mWidth * mHeight];
	}
	void Width();
	void Height();
	T& operator()(int x, int y) {
		return mData[y * mWidth + x];
	}
	const T& operator()(int x, int y)const {
		return mData[y * mWidth + x];
	}
private:
	int mWidth;
	int mHeight;
	T* mData;
};