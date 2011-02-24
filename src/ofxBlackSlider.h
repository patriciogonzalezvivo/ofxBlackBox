/*
 *  ofxBlackSlider.h
 *  tuioPainter
 *
 *  Created by Patricio González Vivo on 09/02/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef _ofxBLACKSLIDER
#define _ofxBLACKSLIDER

#include "ofxBlackButton.h"

class ofxBlackSlider : public ofxBlackButton{	
public:
	bool bVertical;
	
	float w,h,sliderW;
	void  setSize(float _width, float _height);
	ofVec2f inMousePosition;
	
	float val, vMin, vMax;
	float setMin(float m){vMin = m;};
	float setMax(float m){vMax = m;};
	float setValue(float d){val = d;};
	float getValue();

	ofxBlackSlider(bool _bVertical, float _defVal, float _min, float _max);
	
	bool isOver(ofVec2f _location);
	void draw();
};
#endif