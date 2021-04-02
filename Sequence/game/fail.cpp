#include "Sequence/game/fail.h"
#include "Sequence/game/game_parent.h"
#include "image.h"
#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Fail::Fail():image(0),gCount(0) {
			image = new Image("data/image/dummy.dds");
		}
		Fail::~Fail() {
			SAFE_DELETE(image);
		}
		void Fail::update(Parent* p) {
			if (gCount == 60) {
				if (p->lifeNumber() == 0) {
					p->moveTo(Parent::SEQ_END);
				}
				else {
					p->moveTo(Parent::SEQ_READY);
				}
				gCount = 0;
			}
			gCount++;
			p->state()->draw();
			image->Draw();
			Framework::instance().drawDebugString(0, 0, "Ah!");
		}
	}
}