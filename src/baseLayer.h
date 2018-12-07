#pragma once
#include "ofMain.h"

class baseLayer
{
public:
	baseLayer(int index);
	~baseLayer();

	string name;
	bool isHidden = false;
	bool isLocked = false;
	ofTexture in;
	ofTexture own;
	ofTexture out;
};

