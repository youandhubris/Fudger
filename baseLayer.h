#pragma once
#include "ofMain.h"

class baseLayer
{
public:
	baseLayer();
	~baseLayer();

	string name;
	bool lock;
	bool hide;

	ofTexture in;
	ofTexture own;
	ofTexture out;
};

