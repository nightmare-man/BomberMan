#include "Sequence/pass.h"
#include "GameLib/Framework.h"
#include "Sequence/parent.h"
#include "image.h"
using namespace GameLib;
namespace Sequence {
	Pass::Pass() :image(0),gCount(0) {
		image = new Image("data/image/dummy.dds");
	}
	Pass::~Pass() {
		SAFE_DELETE(image);
	}
	void Pass::update(Parent* p) {
		Framework f = Framework::instance();
		if (gCount == 60) {
			gCount = 0;
			p->moveTo(Parent::SEQ_TITLE);
		}
		gCount++;
		image->Draw();
		f.drawDebugString(0, 0, "pass");
	}
}
