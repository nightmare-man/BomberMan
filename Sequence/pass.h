#pragma once
class Image;
namespace Sequence {
	class Parent;
	class Pass {
	public:
		Pass();
		~Pass();
		void update(Parent*);
	private:
		Image* image;
		int gCount;
	};
}
