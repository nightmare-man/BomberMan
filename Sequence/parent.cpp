#include "Sequence/parent.h"
#include "Sequence/end.h"
#include "Sequence/pass.h"
#include "Sequence/title.h"
#include "Sequence/game/game_parent.h"
#include "GameLib/Framework.h"
using namespace std;
using namespace GameLib;
namespace Sequence {
	Parent* Parent::mInstance = 0;
	void Parent::create() {
		ASSERT(!mInstance && "不能连续调用create()");
		mInstance = new Parent();
	}
	void Parent::destroy() {
		SAFE_DELETE(mInstance);
	}
	Parent* Parent::instance() {
		return mInstance;
	}
	Parent::Parent():mTitle(0),mEnd(0),mPass(0),
		mGame(0),mNext(SEQ_NONE),mMode(M_1P) {
		Framework f = Framework::instance();
		f.setFrameRate(60);
		mTitle = new Title();
	}
	void Parent::setMode(Mode m) {
		mMode = m;
	}
	Parent::Mode Parent::mode()const {
		return mMode;
	}
	Parent::~Parent() {
		SAFE_DELETE(mTitle);
		SAFE_DELETE(mEnd);
		SAFE_DELETE(mPass);
		SAFE_DELETE(mGame);
	}
	void Parent::update() {
		if (mTitle) {
			mTitle->update(this);
		}
		else if (mEnd) {
			mEnd->update(this);
		}
		else if (mPass) {
			mPass->update(this);
		}
		else if (mGame) {
			mGame->update(this);
		}
		else {
			HALT("not exist sequence!");
		}
		switch (mNext)
		{
		case SEQ_TITLE:
			SAFE_DELETE(mGame);
			SAFE_DELETE(mPass);
			SAFE_DELETE(mEnd);//有这三种状态都能转移到title所以
			//要在这儿delete
			mTitle = new Title();
			break;
		case SEQ_END:
			SAFE_DELETE(mGame);
			mEnd = new End();
			break;
		case SEQ_PASS:
			SAFE_DELETE(mGame);
			mPass = new Pass();
			break;
		case SEQ_GAME:
			SAFE_DELETE(mTitle);
			mGame = new Game::Parent(1);//默认进入第一关
			break;
		case SEQ_NONE:
			break;
		default:
			break;
		}
		mNext = SEQ_NONE;//一旦生成了对应的类，下一帧就转移了
		//因此要cz mNext;
		
		
		
	}
	void Parent::moveTo(Seq next) {
		mNext = next;
	}
}