#pragma once
namespace Sequence {
	namespace Game {
		class Parent;
	}
	class Title;
	class End;
	class Pass;
	class Parent {
	public:
		enum Seq {
			SEQ_TITLE,
			SEQ_END,
			SEQ_PASS,
			SEQ_GAME,
			SEQ_NONE
		};
		Parent();
		~Parent();
		void update();
		void moveTo(Seq next);
	private:
		Title* mTitle;
		End* mEnd;
		Pass* mPass;
		Game::Parent* mGame;
		Seq mNext;
		int gCount;
	};
}
