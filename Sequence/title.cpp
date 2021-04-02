#include "Sequence/title.h"
#include "GameLib/Framework.h"
#include "Sequence/parent.h"
#include "image.h"
using namespace GameLib;
namespace Sequence {
	Title::Title():image(0),selected(0){
		image = new Image("data/image/dummy.dds");
	}
	Title::~Title() {
		SAFE_DELETE(image);
	}
	void Title::update(Parent* p) {
		Framework f = Framework::instance();
		if (f.isKeyTriggered('w')) {
			if (selected == 0) {
				selected = 1;
			}
			else {
				selected--;
			}
		}
		if (f.isKeyTriggered('s')) {
			if (selected == 1) {
				selected = 1;
			}
			else {
				selected++;
			}
		}
		f.drawDebugString(1, 0, "[title]");
		f.drawDebugString(1, 2, "1 player");
		f.drawDebugString(1, 3, "2 player");
		f.drawDebugString(0,selected + 2, ">");
		if (f.isKeyTriggered(' ')) {
			p->moveTo(Parent::SEQ_GAME);
			p->setMode(static_cast<Parent::Mode>(selected));
		}
		image->Draw();
		
	}
}
