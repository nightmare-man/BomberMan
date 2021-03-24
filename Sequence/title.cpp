#include "Sequence/title.h"
#include "GameLib/Framework.h"
#include "Sequence/parent.h"
#include "image.h"
using namespace GameLib;
namespace Sequence {
	Title::Title():image(0){
		image = new Image("data/image/dummy.dds");
	}
	Title::~Title() {
		SAFE_DELETE(image);
	}
	void Title::update(Parent* p) {
		Framework f = Framework::instance();
		if (f.isKeyTriggered(' ')) {
			p->moveTo(Parent::SEQ_GAME);
		}
		image->Draw();
		f.drawDebugString(0, 0, "title");
	}
}
