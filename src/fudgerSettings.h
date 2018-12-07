#pragma once
#include "ofMain.h"
#include "fudgerMacros.h"
#include "ofxImGui.h"

class fudgerSettings
{
public:

	fudgerSettings();
	~fudgerSettings();

	void setup();
	bool load(string filePath);
	bool save(string filePath);

	ofParameterGroup general;
	ofParameterGroup layersWindow;
	bool layersWindowOpen = true;

private:

	ImGuiWindowFlags GetWindowFlags(bool titlebar, bool scrollbar, bool menu, bool move, bool resize, bool collapse, bool nav);
	


	ofJson jsonFile;

	/*   GENERAL   */
	ofParameter<string> title {"Title", "Fudger"};
	ofParameter<string> version {"Version", "0.0"};

	/*   LAYERS WINDOW   */
	ofParameter<int> layersWindowFlags{ "Window Flags", GetWindowFlags(true, true, false, true, true, true, true) };

	ofParameter<bool> enabled{ "Enabled", true };
	ofParameter<float> sizeMin{ "Size Min", 10.0f, 0.0f, 1000.0f };
	ofParameter<float> sizeMax{ "Size Max", 200.0f, 0.0f, 1000.0f };
	ofParameter<float> speed{ "Speed", 0.1f, 0.0f, 1.0f };
	ofParameter<string> text{ "Title", "Fudger" };

	
	ofParameterGroup params;


};

