#include "file.h"
#include <fstream>
#include "GameLib/Framework.h"
using namespace GameLib;
using namespace std;
File::File(const char* fileName) {
	ifstream in(fileName, ifstream::binary);
	ASSERT(in && "文件打开失败");
	in.seekg(0, ifstream::end);
	mSize = static_cast<int>(in.tellg());
	in.seekg(0, ifstream::beg);
	mData = new char[mSize];
	in.read(mData, mSize);
}
File::~File() {
	SAFE_DELETE(mData);
}
char* File::data() {
	return mData;
}
int File::size() {
	return mSize;
}
unsigned File::getUnsigned(char* p) {
	unsigned char* p1 = reinterpret_cast<unsigned char*>(p);
	unsigned ret = p1[0];
	ret += p1[1] << 8;
	ret += p1[2] << 16;
	ret += p1[3] << 24;
	return ret;
}