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
		enum Mode {
			M_1P,
			M_2P
		};
		enum Seq {
			SEQ_TITLE,
			SEQ_END,
			SEQ_PASS,
			SEQ_GAME,
			SEQ_NONE
		};
		
		void update();
		void moveTo(Seq next);
		void setMode(Mode m);
		Mode mode()const;
		static void create();
		static void destroy();
		static Parent* instance();
	private:
		Parent();
		Parent(Parent&);
		~Parent();
		Title* mTitle;
		End* mEnd;
		Pass* mPass;
		Game::Parent* mGame;
		Seq mNext;
		Mode mMode;
		static Parent* mInstance;
		
	};
}
