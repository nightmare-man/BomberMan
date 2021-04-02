#include "Sequence/game/next.h"
#include "Sequence/game/game_parent.h"
#include "image.h"
#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Next::Next() :image(0),gCount(0) {
			image = new Image("data/image/dummy.dds");
		}
		Next::~Next() {
			SAFE_DELETE(image);
		}
		void Next::update(Parent* p) {
			if (gCount == 60) {
				if (p->isFinalStage()) {
					p->moveTo(Parent::SEQ_PASS);
				}
				else {
					p->moveTo(Parent::SEQ_READY);
				}
				gCount = 0;
			}
			gCount++;
			p->state()->draw();
			image->Draw();
			Framework::instance().drawDebugString(0, 0, "congratulations!");
		}
	}
}