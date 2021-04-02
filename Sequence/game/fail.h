#pragma once
class Image;
namespace Sequence {
	namespace Game {
		class Parent;
		class Fail {
		public:
			Fail();
			~Fail();
			void update(Parent* p);
		private:
			Image* image;
			int gCount;
		};
	}
}
