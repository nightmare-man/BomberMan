#include "GameLib/Framework.h"
using namespace GameLib;
#include "image.h"
Image* image;
void Framework::update() {
	if (!image) {
		image = new Image("bar.dds");
	}
	image->Draw();
}