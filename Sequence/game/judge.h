#pragma once
class Image;
namespace Sequence {
	namespace Game {
		class Parent;
		class Judge {
			public:
			Judge();
			~Judge();
			void update(Parent* p);
		private:
			Image* image;
			int gCount;
			int selected;

		};
	}
}
