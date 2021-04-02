#include "Sequence/game/game_parent.h"
#include "Sequence/game/fail.h"
#include "Sequence/game/judge.h"
#include "Sequence/game/next.h"
#include "Sequence/game/pause.h"
#include "Sequence/game/play.h"
#include "Sequence/game/ready.h"
#include "Sequence/parent.h"
#include "GameLib/Framework.h"
#include "file.h"
#include "state.h"
#include <sstream>

using namespace std;
using namespace GameLib;
namespace Sequence {
	namespace Game {
		 State* Parent::state() {
			return mState;
		}
		void Parent::moveTo(Seq m) {
			mSEQ = m;
		}
		Parent::Parent(int level):mLevel(1),mState(0),mLife(MAX_LIFE)
		,mStageID(1),mFail(0),mJudge(0),mNext(0),mPause(0),mPlay(0),
		mReady(0),mSEQ(SEQ_NONE){
			mReady = new Ready();
		}
		void Parent::startLoading() {
			stringstream ss;
			switch (mode()) {
			case M_1P:
				ss << "data/stageData/" << mStageID << ".txt";
				break;
			case M_2P:
				ss << "data/stageData/fight.txt";
				break;
			}
			File f(ss.str().c_str());
			mState = new State(mStageID);
		}
		bool Parent::isFinalStage()const {
			return mStageID>FINAL_STAGE_ID;
		}
		int Parent::lifeNumber()const {
			return mLife;
		}
		Parent::~Parent() {
			SAFE_DELETE(mState);
			SAFE_DELETE(mFail);
			SAFE_DELETE(mNext);
			SAFE_DELETE(mJudge);
			SAFE_DELETE(mPause);
			SAFE_DELETE(mPlay);
			SAFE_DELETE(mReady);
		}
		Parent::Mode Parent::mode()const {
			Mode r;
			switch (GrandParent::instance()->mode())
			{
			case GrandParent::M_1P:r = Parent::M_1P; break;
			case GrandParent::M_2P:r = Parent::M_2P; break;
			default:
				break;
			}
			return r;
		}
		void Parent::update(GrandParent* p) {
			if (mFail) {
				mFail->update(this);
			}
			else if (mJudge) {
				mJudge->update(this);
			}
			else if (mNext) {
				mNext->update(this);
			}
			else if (mPause) {
				mPause->update(this);
			}
			else if (mPlay) {
				mPlay->update(this);
			}
			else if (mReady) {
				mReady->update(this);
			}
			else {
				HALT("not exist this state!");
			}
			switch (mSEQ) {
				//怎么delete 取决于有可能从哪几个状态转移过来，就delete哪几个
			case SEQ_PLAY:SAFE_DELETE(mReady); SAFE_DELETE(mPause); mPlay = new Play(); break;
			case SEQ_FAIL:SAFE_DELETE(mPlay); mFail = new Fail(); mLife--; break;
			case SEQ_JUDGE:SAFE_DELETE(mPlay); mJudge = new Judge(); break;
			case SEQ_NEXT:SAFE_DELETE(mPlay); mNext = new Next(); mStageID++; break;
			case SEQ_PAUSE:SAFE_DELETE(mPlay); mPause = new Pause(); break;
			case SEQ_READY:SAFE_DELETE(mJudge); SAFE_DELETE(mNext); SAFE_DELETE(mFail); mReady = new Ready(); break;
			case SEQ_END:SAFE_DELETE(mFail); p->moveTo(GrandParent::SEQ_END); break;
			case SEQ_PASS:SAFE_DELETE(mNext); p->moveTo(GrandParent::SEQ_PASS); break;
			case SEQ_TITLE:SAFE_DELETE(mPause); SAFE_DELETE(mJudge); p->moveTo(GrandParent::SEQ_TITLE); break;
			}
			mSEQ = SEQ_NONE;
		}
	}
}