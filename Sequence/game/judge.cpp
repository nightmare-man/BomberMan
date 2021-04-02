#include "Sequence/game/judge.h"
#include "Sequence/game/game_parent.h"
#include "image.h"
#include "state.h"
#include "GameLib/Framework.h"
using namespace GameLib;
namespace Sequence {
	namespace Game {
		Judge::Judge() :image(0) ,gCount(0),selected(0){
			image = new Image("data/image/dummy.dds");
		}
		Judge::~Judge() {
			SAFE_DELETE(image);
		}
		void Judge::update(Parent* p) {
			Framework f = Framework::instance();
			if (f.isKeyTriggered('w')) {
				if (selected == 0) {
					selected = 1;
				}
				else {
					selected--;
				}
			}
			else if (f.isKeyTriggered('s')) {
				if (selected == 1) {
					selected = 0;
				}
				else {
					selected++;
				}
			}
			else if (f.isKeyTriggered(' ')) {
				switch (selected) {
				case 0:p->moveTo(Parent::SEQ_READY); break;
				case 1:p->moveTo(Parent::SEQ_TITLE); break;
				}
			}
			p->state()->draw();
			image->Draw();
			f.drawDebugString(1, 0, "continue");
			f.drawDebugString(1, 1, "back");
			f.drawDebugString(0, selected, ">");
			f.drawDebugString(0, 2, "[1p win]");
		}
	}
}