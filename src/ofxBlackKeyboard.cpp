/*
 *  ofxBlackKeyboard.cpp
 *
 *  Copyright 2010 Patricio Gonzalez Vivo http://www.patriciogonzalezvivo.com
 *	All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

#include "ofxBlackKeyboard.h"

ofxBlackKeyboard::ofxBlackKeyboard(){
	close	= false;
	alpha	= 255;
	angle	= 0;
	
	position = Vec2f(ofGetWidth()*0.5,ofGetHeight()*0.5);
	
	width	= 500;
	height	= 50;
	margen	= 20;
	
	timer	= 0;
	scale	= 1;
	
	background.set(CM_RGB,Vec3f(0,0,0));
	foreground.set(CM_RGB,Vec3f(255,255,255));
}

void ofxBlackKeyboard::loadMap(const string& path){
	ifstream	fs( ofToDataPath(path).c_str());
	
	//cKey = NULL;
	//nKeys = 0;
	
	string line;
	int lineCounter = 0;
	
	while(!(fs >> line).fail()){
		vector <string> values = ofSplitString(line, ",");
		
		if ( (lineCounter == 0) && (values.size()) == 4) {
			width = ofToFloat(values[2]);								// The first line of the file have information about the 
			height = ofToFloat(values[3]);								// the width and the height of the keyboard. (The first two values are a relative position of the keyboard center when was draw)
		} else if ((values.size() == 5)) {
			string _letter = values[0];
			float _radio	= ofToFloat(values[1].c_str());             // the first value is the Letter or Key, the second one is radio from the center
			float _angle = ofToFloat(values[2].c_str());				// the 3th is the angle on radians from the center (this last to parameters are the ones that let the keabord be redraw in any angle and continue working)
			int	_width	= ofToInt(values[3].c_str());               // the 4th and 5th are the with and height of each key. 
			int	_height	= ofToInt(values[4].c_str());
			
			ofxBlackButton * k = new ofxBlackButton();
			
			k->setScale(&scale);
			k->setFont(&defaultFont);
			k->setWindowNorth(&angle);
			k->setWindowCenter(&position);
			k->setColors(&foreground, &background);
			k->setAlpha(&alpha);
			k->setSize(_width, _height);
			k->setLetter(_letter);
			k->act = _letter;
			k->setRadio(_radio);
			k->setAngle(_angle);
			k->reCalcPos();
			
			objects.push_back(k);
		}
		lineCounter++;
	}

	fs.seekg(0,ios::beg);
	fs.clear();
	fs.close();
}

void ofxBlackKeyboard::addKey(string _letter, int _x, int _y, int _width, int _height){
	ofxBlackButton * k = new ofxBlackButton();
	k->setScale(&scale);
	k->setFont(&defaultFont);
	k->setWindowNorth(&angle);
	k->setWindowCenter(&position);
	k->setColors(&foreground, &background);
	k->setAlpha(&alpha);
	k->setSize(_width, _height);
	k->setLetter(_letter);
	k->act = _letter;
	k->moveTo(_x, _y);
		
	objects.push_back(k);
}

void ofxBlackKeyboard::saveMap(const string& path){
	ofstream	fs( ofToDataPath(path).c_str());
	
	fs << position.x << "," << position.y << "," << width << "," << height << endl; 
	for (int i = 0; i < objects.size(); i++){
		fs << objects[i]->act << "," << objects[i]->radio << "," << objects[i]->angle << "," << objects[i]->width << "," << objects[i]->height << endl;
	}
	
	fs.close();
}

bool ofxBlackKeyboard::isOnBorder(Vec2f _loc){
	float dist = position.distance(_loc);
	
	if ( (dist <= width*0.5) && (dist >= width*0.4)) return true;
    else return false;
}