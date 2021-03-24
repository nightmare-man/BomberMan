#include "Sequence/game/game_parent.h"
#include "Sequence/parent.h"
#include "GameLib/Framework.h"
#include "file.h"
#include "state.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Parent::Parent(int level):mLevel(1),mState(0) {
			File f("data/stageData/1.txt");
			mState = new State(f.data(),f.size());
		}
		Parent::~Parent() {
			SAFE_DELETE(mState);
		}
		void Parent::update(GrandParent* p) {
			int dx = 0, dy = 0;
			Framework f = Framework::instance();
			bool inputA = f.isKeyTriggered('a');
			bool inputD = f.isKeyTriggered('d');
			bool inputW = f.isKeyTriggered('w');
			bool inputS = f.isKeyTriggered('s');
			if (inputA) {
				dx = -1;
			}
			else if (inputD) {
				dx = 1;
			}
			else if (inputW) {
				dy = -1;
			}
			else if (inputS) {
				dy = 1;
			}
#ifndef NDBUG
			bool killed = f.isKeyTriggered('x');
			bool passed = f.isKeyTriggered('c');
			if (killed) {
				p->moveTo(GrandParent::SEQ_END);
			}
			if (passed) {
				p->moveTo(GrandParent::SEQ_PASS);
			}

#endif
			if (mState->hasClear()) {
				p->moveTo(GrandParent::SEQ_PASS);
			}
			mState->update(dx, dy, f.previousFrameInterval());
			mState->draw();
		}
	}
}