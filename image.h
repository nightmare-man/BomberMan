#pragma once
class Image {
public:
	Image(const char* imageFileName);
	~Image();
	void Draw(int dstx = 0, int dsty = 0, int srcx = 0, int srcy = 0, int width = 0, int height = 0);
	int Width();
	int Height();
private:
	int mWidth;
	int mHeight;
	unsigned* mImageData;
};
