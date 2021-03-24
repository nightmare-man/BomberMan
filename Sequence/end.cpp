#include "Sequence/end.h"
#include "GameLib/Framework.h"
#include "Sequence/parent.h"
#include "image.h"
using namespace GameLib;
namespace Sequence {
	End::End() :image(0) ,gCount(0){
		image = new Image("data/image/dummy.dds");
	}
	End::~End() {
		SAFE_DELETE(image);
	}
	void End::update(Parent* p) {
		Framework f = Framework::instance();
		if (gCount == 60) {
			gCount = 0;
			p->moveTo(Parent::SEQ_TITLE);
		}
		gCount++;
		image->Draw();
		f.drawDebugString(0, 0, "end");
	}
}
