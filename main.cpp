#include "GameLib/Framework.h"
using namespace GameLib;
#include "Sequence/parent.h"
#include <sstream>
using namespace std;
using namespace Sequence;
bool win = false;
void Framework::update() {
	if (!Parent::instance()) {
		Parent::create();
		setFrameRate(60);
	}
	Parent::instance()->update();
	if (isKeyTriggered('q')) {
		requestEnd();
	}
	if (isEndRequested()) {
		Parent::destroy();
	}//显示帧率
	stringstream ss;
	ss << frameRate();
	drawDebugString(0, 10, ss.str().c_str());
	ss.str("");//清空ss
}