#pragma once
class State;
namespace Sequence {
	class Parent;
	namespace Game {
		class Fail;
		class Judge;
		class Next;
		class Pause;
		class Play;
		class Ready;
		class Parent {
		public:
			enum Mode {
				M_1P,
				M_2P
			};
			enum Seq {
				SEQ_JUDGE,
				SEQ_FAIL,
				SEQ_NEXT,
				SEQ_PLAY,
				SEQ_PAUSE,
				SEQ_READY,
				SEQ_PASS,
				SEQ_END,
				SEQ_TITLE,
				SEQ_NONE
			};
			typedef Sequence::Parent GrandParent;
			Parent(int level);
			~Parent();
			void update(GrandParent*);
			Mode mode()const;
			bool isFinalStage()const;
			int lifeNumber()const;
			void startLoading();
			void moveTo(Seq m);
			State* state();
		private:
			State* mState;
			int mLevel;
			int mStageID;
			int mLife;
			Seq mSEQ;
			static const int FINAL_STAGE_ID = 2;
			static const int MAX_LIFE = 2;
			Fail* mFail;
			Judge* mJudge;
			Next* mNext;
			Pause* mPause;
			Play* mPlay;
			Ready* mReady;
		};
	}
	
}
