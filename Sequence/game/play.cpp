#include "Sequence/game/play.h"
#include "Sequence/game/game_parent.h"
#include "image.h"
#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Play::Play()  {
		}
		Play::~Play() {
		}
		void Play::update(Parent* p) {
			Framework f = Framework::instance();
#ifndef NDEBUG
			if (f.isKeyTriggered('x')) {
				if (p->mode() == Parent::M_1P) {
					p->moveTo(Parent::SEQ_FAIL);
				}
				else {
					p->moveTo(Parent::SEQ_JUDGE);
				}
				
			}
			else if (f.isKeyTriggered('c')) {
				if (p->mode() == Parent::M_1P) {
					p->moveTo(Parent::SEQ_NEXT);
				}
				else {
					p->moveTo(Parent::SEQ_JUDGE);
				}
				
			}
#endif // !NDEBUG

			p->state()->update();
			p->state()->draw();
		}
	}
}