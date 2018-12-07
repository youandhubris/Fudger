#pragma once
#include "ofMain.h"
#include "fudgerMacros.h"
#include "fudgerSettings.h"
#include "baseLayer.h"
#include "ofxImGui.h"
#include "imgui.h"
#include "imgui_internal.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		/*   SETTINGS   */
		fudgerSettings settings;

		/*   GUI   */
		ofxImGui::Gui gui;

		ImFont * font;

		vector<baseLayer> layers;

		int layerNameMax = 10;
		
		static void Spacing(glm::vec2 v, bool sameLine = false);
		static void ShowHelpMarker(const char* desc);
};
