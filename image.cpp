#include "image.h"
#include "file.h"
#include "GameLib/Framework.h"
using namespace GameLib;
Image::Image(const char* imageFileName) {
	File f(imageFileName);
	mHeight = f.getUnsigned(&(f.data()[12]));
	mWidth = f.getUnsigned(&(f.data()[16]));
	mImageData = new unsigned[mHeight * mWidth];
	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			mImageData[y * mWidth + x] = f.getUnsigned(&(f.data()[128 + 4 * (y * mWidth + x)]));
		}
	}
}
Image::~Image() {
	SAFE_DELETE(mImageData);
}
namespace {
	unsigned blend(unsigned dst, unsigned src) {
		unsigned srcA = (src & 0xff000000) >> 24;
		unsigned srcR = (src & 0x00ff0000);
		unsigned srcG = (src & 0x0000ff00);
		unsigned srcB = (src & 0x000000ff);
		unsigned dstR = (dst & 0x00ff0000);
		unsigned dstG = (dst & 0x0000ff00);
		unsigned dstB = (dst & 0x000000ff);
		dstR = dstR + ((srcR - dstR) * srcA) / 255;//颜色混合 srcA 255不透明 0全透明
		dstG = dstG + ((srcG - dstG) * srcA) / 255;
		dstB = dstB + ((srcB - dstB) * srcA) / 255;
		return (dstR & 0x00ff0000) | (dstG & 0xff00) | dstB;
	}
}
void Image::Draw(int dstx,int dsty,int srcx,int srcy,int width,int height) {
	if (!width || !height) {
		width = mWidth;
		height = mHeight;
	}
	Framework f = Framework::instance();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned src = mImageData[(srcy+y)*mWidth+srcx+x];
			unsigned* dst =&( f.videoMemory()[(dsty + y) * f.width() + dstx + x]);
			*dst = blend(*dst, src);
		}
	}
}
int Image::Width() {
	return mWidth;
}
int Image::Height() {
	return mHeight;
}