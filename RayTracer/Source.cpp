
#include "Engine.h"
#include "iostream"

using namespace std;

int main()
{
	RenderOptions options;
	options.height = 720;
	options.width = 1280;
	options.fov = 90;
	options.maxDepth = 50;
	options.aspectRatio = (float)options.width / (float)options.height; 
	Engine engine(options);
	engine.run();
	return 0;
}