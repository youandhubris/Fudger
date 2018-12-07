#include "ofMain.h"
#include "ofApp.h"
#include "fudgerMacros.h"

//========================================================================
int main()
{
	ofGLFWWindowSettings settings;

	settings.visible = true;
	settings.windowMode = OF_WINDOW;
	settings.setGLVersion(4, 1);
	settings.setSize(1920, 1080);
	settings.resizable = true;
	//settings.setPosition(ofVec2f(400, 100));
	settings.doubleBuffering = true;
	settings.decorated = true;

	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
