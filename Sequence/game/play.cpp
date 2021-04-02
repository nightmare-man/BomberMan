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
			int dx = 0, dy = 0;
			if (f.isKeyTriggered('a')) {
				dx = -1;
			}
			else if (f.isKeyTriggered('d')) {
				dx = 1;
			}
			else if (f.isKeyTriggered('w')) {
				dy = -1;
			}
			else if (f.isKeyTriggered('s')) {
				dy = 1;
			}
			else if (f.isKeyTriggered(' ')) {
				p->moveTo(Parent::SEQ_PAUSE);
			}
			if (p->state()->hasClear()) {
				if (p->mode() == Parent::M_1P) {
					p->moveTo(Parent::SEQ_NEXT);//´ıĞø
				}
				else {
					p->moveTo(Parent::SEQ_JUDGE);
				}
			}
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