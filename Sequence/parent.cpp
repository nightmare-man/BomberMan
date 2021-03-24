#include "Sequence/parent.h"
#include "Sequence/end.h"
#include "Sequence/pass.h"
#include "Sequence/title.h"
#include "Sequence/game/game_parent.h"
#include "GameLib/Framework.h"
#include <sstream>
using namespace std;
using namespace GameLib;
namespace Sequence {
	Parent::Parent():mTitle(0),mEnd(0),mPass(0),
		mGame(0),mNext(SEQ_NONE),gCount(0) {
		Framework f = Framework::instance();
		f.setFrameRate(60);
		mTitle = new Title();
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
			SAFE_DELETE(mEnd);//��������״̬����ת�Ƶ�title����
			//Ҫ�����delete
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
			mGame = new Game::Parent(1);//Ĭ�Ͻ����һ��
			break;
		case SEQ_NONE:
			break;
		default:
			break;
		}
		mNext = SEQ_NONE;//һ�������˶�Ӧ���࣬��һ֡��ת����
		//���Ҫcz mNext;
		Framework f = Framework::instance();
		stringstream ss;
		ss << f.frameRate();
		f.drawDebugString(8, 8, ss.str().c_str());
		
		
	}
	void Parent::moveTo(Seq next) {
		mNext = next;
	}
}