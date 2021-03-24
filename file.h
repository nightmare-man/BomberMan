#pragma once
class File {
public:
	File(const char* fileName);
	~File();
	char* data();
	int size();
	unsigned getUnsigned(char* p);
private:
	char* mData;
	int mSize;
};