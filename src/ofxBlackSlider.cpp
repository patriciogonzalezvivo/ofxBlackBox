/*
 *  ofxBlackSlider.cpp
 *  tuioPainter
 *
 *  Created by Patricio González Vivo on 09/02/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxBlackSlider.h"

ofxBlackSlider::ofxBlackSlider(bool _bVertical, float _defVal, float _min, float _max){
	over = false;
	val = _defVal;
	vMax = _max;
	vMin = _min;
	bVertical = _bVertical;
	sliderW = 12;
}

void ofxBlackSlider::setSize(float _width, float _height){
	width = w = _width; 
	height = h = _height;
	
	if (bVertical)
		inMousePosition.y = ofMap(val, vMin, vMax, -height*0.5+sliderW*.5, height*0.5-sliderW*.5);
	else
		inMousePosition.x = ofMap(val, vMin, vMax, -width*0.5+sliderW*.5, width*0.5-sliderW*.5);
}

void ofxBlackSlider::draw(){
	reCalcPos();
	
	ofColor fg = *foreground;
	ofColor bg = *background;
	
	ofEnableAlphaBlending();
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofRotateZ(ofRadToDeg(*windowNorth));
	
	ofSetColor(bg.r,bg.g,bg.b,(*alpha)-20);
	ofFill();
	rBox(w,h);
	
	//Draw the slide object
	ofSetColor(fg.r,fg.g,fg.b,*alpha);
	ofFill();
	
	if (bVertical){
		ofTranslate(0,inMousePosition.y);
		rBox(width,sliderW);
	} else {
		ofTranslate(inMousePosition.x,0);
		rBox(sliderW,height);
	}
	
	ofFill();
	ofSetColor(fg.getInverted());
	ofScale(*scale*.4,*scale*.4,1);
	string valor = ofToString( (float)((int)(val * 100))/100 );
	defaultFont->drawString(valor, -defaultFont->stringWidth(valor)*0.5, defaultFont->stringHeight(valor)*0.35);
	
	ofPopMatrix();
}

float ofxBlackSlider::getValue(){
	if (bVertical)
		//val = ofMap(inMousePosition.y, -height*0.5*(*scale), height*0.5*(*scale), vMin, vMax);
		val = ofMap(inMousePosition.y, -height*0.5*(*scale)+sliderW*.5, height*0.5*(*scale)-sliderW*.5, vMin, vMax,true);
	else
		val = ofMap(inMousePosition.x, -width*0.5*(*scale)+sliderW*.5, width*0.5*(*scale)-sliderW*.5, vMin, vMax,true);
	
	return val;
}

bool ofxBlackSlider::isOver(ofVec2f _location){
	ofVec2f dirToCenter = position - _location;
	float theta = atan2(dirToCenter.x,dirToCenter.y)-(PI/2);
	float r = dirToCenter.length();
	float x = r * cos(theta + *windowNorth);
	float y = r * sin(theta + *windowNorth);
	
	if ( (x <= width*0.5*(*scale)-sliderW*.4) && (x >= -width*0.5*(*scale)+sliderW*.4) && (y <= height*0.5*(*scale)-sliderW*.4) && (y >= -height*0.5*(*scale)+sliderW*.4)){
		over = true;
		inMousePosition.set(x,y);
	} else over = false;
	
	return over;
}