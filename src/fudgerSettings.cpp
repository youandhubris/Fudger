#include "fudgerSettings.h"

fudgerSettings::fudgerSettings()
{
}


fudgerSettings::~fudgerSettings()
{
}

void fudgerSettings::setup()
{
	general = { "General", title, version };
	layersWindow = { "Menu Bar", layersWindowFlags };

	params = { "Fudger", general, layersWindow };
}

bool fudgerSettings::load(string filename)
{
	ofFile file(filename);

	if (file.exists())
	{
		jsonFile = ofLoadJson(filename);
		ofDeserialize(jsonFile, params);
		return true;
	}
	return false;
}

bool fudgerSettings::save(string filename)
{
	ofSerialize(jsonFile, params);
	return ofSaveJson(filename, jsonFile);
}

ImGuiWindowFlags fudgerSettings::GetWindowFlags(bool titlebar, bool scrollbar, bool menu, bool move, bool resize, bool collapse, bool nav)
{
	ImGuiWindowFlags windowFlags = 0;

	if (!titlebar)  windowFlags |= ImGuiWindowFlags_NoTitleBar;
	if (!scrollbar) windowFlags |= ImGuiWindowFlags_NoScrollbar;
	if (menu)       windowFlags |= ImGuiWindowFlags_MenuBar;
	if (!move)      windowFlags |= ImGuiWindowFlags_NoMove;
	if (!resize)    windowFlags |= ImGuiWindowFlags_NoResize;
	if (!collapse)  windowFlags |= ImGuiWindowFlags_NoCollapse;
	if (!nav)       windowFlags |= ImGuiWindowFlags_NoNav;

	return windowFlags;
}