#include "baseLayer.h"



baseLayer::baseLayer(int index)
{
	name = "Layer " + to_string(index);
	name.resize(20, '\0');
}


baseLayer::~baseLayer()
{
}
