#pragma once
class Image;
namespace Sequence {
	namespace Game {
		class Parent;
		class Next {
		public:
			Next();
			~Next();
			void update(Parent* p);
		private:
			Image* image;
			int gCount;
		};
	}
}
