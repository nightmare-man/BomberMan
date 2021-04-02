#pragma once
class Image;
namespace Sequence {
	namespace Game {
		class Parent;
		class Ready{
		public:
			Ready();
			~Ready();
			void update(Parent* p);
		private:
			Image* image;
			int gCount;
		};
	}
}
