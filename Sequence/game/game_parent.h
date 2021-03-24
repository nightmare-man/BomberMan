#pragma once
class State;
namespace Sequence {
	class Parent;
	namespace Game {
		class Parent {
		public:
			enum Seq {
				SEQ_END,
				SEQ_PASS,
				SEQ_GAME,
				SEQ_NONE
			};
			typedef Sequence::Parent GrandParent;
			Parent(int level);
			~Parent();
			void update(GrandParent*);
		private:
			State* mState;
			int mLevel;
		};
	}
	
}
