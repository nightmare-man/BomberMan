#pragma once
class Image;
namespace Sequence {
	namespace Game {
		class Parent;
		class Pause {
		public:
			Pause();
			~Pause();
			void update(Parent* p);
		private:
			Image* image;
			int selected;
		};
	}
}
