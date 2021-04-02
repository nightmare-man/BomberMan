#include "Sequence/game/game_parent.h"
#include "Sequence/game/ready.h"
#include "image.h"
#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Ready::Ready():image(0),gCount(0) {
		}
		Ready::~Ready() {
			SAFE_DELETE(image);
		}
		void Ready::update(Parent* p) {
			if (!image) {
				image = new Image("data/image/dummy.dds");
				p->startLoading();
			}
			const char* buffer = "ready";
			if (gCount > 60&&gCount<120) {
				buffer = "go";
			}
			else if (gCount == 120) {
				
				p->moveTo(Parent::SEQ_PLAY);
				gCount = 0;
			}
			gCount++;
			p->state()->draw();
			image->Draw();
			Framework f = Framework::instance();
			f.drawDebugString(0, 0, buffer);
		}
	}
}