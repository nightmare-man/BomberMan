#include "GameLib/Framework.h"
using namespace GameLib;
#include "Sequence/parent.h"
using namespace std;
using namespace Sequence;
Parent* p;
bool win = false;
void Framework::update() {
	if (!p) {
		p = new Parent();
	}
	p->update();
}