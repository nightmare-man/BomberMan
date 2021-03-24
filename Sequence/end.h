#pragma once
class Image;
namespace Sequence {
	class Parent;
	class End {
	public:
		End();
		~End();
		void update(Parent*);
	private:
		Image* image;
		int gCount;
	};
}
