/*
 *  ofxBlackWindow.cpp
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

#include "ofxBlackWindow.h"

ofxBlackWindow::ofxBlackWindow(){
	close	= true;
	alpha	= 0;
	angle	= 0;
	
	position = Vec2f(0,0);
	
	width	= 500;
	height	= 50;
	margen	= 20;
	
	timer	= 0;
	scale	= 1;
	
	background.set(CM_RGB,Vec3f(0,0,0));
	foreground.set(CM_RGB,Vec3f(255,255,255));
}

bool ofxBlackWindow::setup(string filePath){
	if (XML.loadFile(filePath)){
		cout << "Opening " << filePath;
		XML.pushTag("BOX");
		position		= Vec2f(XML.getValue("X",0),XML.getValue("Y",0));
		width			= XML.getValue("WIDTH",500);
		height			= XML.getValue("HEIGHT",200);
		margen			= XML.getValue("MARGEN",20);
		
		angle			= XML.getValue("ANGLE",0);
		
		close			= XML.getValue("CLOSE",1);
		background.set(CM_RGB,Vec3f(XML.getValue("BACKGROUND:RED", 0),XML.getValue("BACKGROUND:GREEN", 0),XML.getValue("BACKGROUND:BLUE", 0)));
		foreground.set(CM_RGB,Vec3f(XML.getValue("FOREGROUND:RED", 255),XML.getValue("FOREGROUND:GREEN", 255),XML.getValue("FOREGROUND:BLUE", 255)));
		alpha			= XML.getValue("ALPHA",0);
		
		
		setFont(XML.getValue("DEFAULT_FONT:PATH","helvetica.ttf"), XML.getValue("DEFAULT_FONT:SIZE",10));
		
		// ------------------------------------------- OBJECTS
		objects.clear();
		XML.pushTag("OBJECTS");
		int numOfObj = XML.getNumTags("OBJ");
		cout << " with " << numOfObj << " to be load: ";
		
		// --------- load them in to the vector
		for (int i = 0; i < numOfObj; i++){
			XML.pushTag("OBJ", i);
			string typeName = XML.getValue("TYPE","NONE");
			
			if ( typeName == "VIDEO" ){
				ofxBlackVideo * v = new ofxBlackVideo();
				v->setColors(&foreground, &background);
				v->setWindowCenter(&position);
				v->setWindowNorth(&angle);
				v->setScale(&scale);
				v->setAlpha(&alpha);
				
				v->loadVideo(XML.getValue("PATH","raya.mov"));
				v->resize(0.5);
				
				objects.push_back(v);
				cout << "video ";
				
			}else if (typeName == "IMAGE"){
				ofxBlackImage * i = new ofxBlackImage();
				i->setColors(&foreground, &background);
				i->setWindowCenter(&position);
				i->setWindowNorth(&angle);
				i->setScale(&scale);
				i->setAlpha(&alpha);
				
				i->loadImage(XML.getValue("PATH","raya.png"));
				i->resize(0.5);
				
				objects.push_back(i);
				cout << "image ";
			}else if ( typeName == "TEXT" ){
				ofxBlackText * t = new ofxBlackText();
				t->setColors(&foreground, &background);
				t->setWindowCenter(&position);
				t->setWindowNorth(&angle);
				t->setScale(&scale);
				t->setAlpha(&alpha);
				
				if (XML.tagExists("FONT",0))
					t->loadFont(XML.getValue("FONT:PATH","helvetica.ttf"), XML.getValue("FONT:SIZE",10));
				else
					t->setFont(&defaultFont);
				
				t->width	= width-margen*2;
				
				if (XML.tagExists("PATH",0))
					t->loadTextFrom(XML.getValue("PATH","pez1.txt"));
				else if (XML.tagExists("TEXT",0)) t->loadText(XML.getValue("TEXT","EMPTY TEXT"));
				else t->loadText("NO TEXT FOUND");
				
				if (XML.tagExists("ALIGMENT",0)){
					string align = XML.getValue("ALIGMENT","JUSTIFIED");
					if (align == "LEFT")
						t->alignment = OF_TEXT_ALIGN_LEFT;
					else if (align == "RIGHT")
						t->alignment = OF_TEXT_ALIGN_RIGHT;
					else if ( align == "CENTER")
						t->alignment = OF_TEXT_ALIGN_CENTER;
					else if ( align =="JUSTIFIED")
						t->alignment = OF_TEXT_ALIGN_JUSTIFIED;
				}
				
				t->setWidth(width-margen*2);
				t->height = t->getTextHeight();
				
				objects.push_back(t);
				cout << "text ";
			} else if (typeName == "BUTTON"){
				ofxBlackButton * b = new ofxBlackButton();
				b->setScale(&scale);
				b->setFont(&defaultFont);
				b->setWindowNorth(&angle);
				b->setWindowCenter(&position);
				b->setColors(&foreground, &background);
				b->setAlpha(&alpha);
				b->setSize(XML.getValue("WIDTH",50), XML.getValue("HEIGHT",30));
				b->setLetter(XML.getValue("TEXT","no text found"));
				
				objects.push_back(b);
				cout << "button ";
				
			} else cout << "ERROR loading the object number "<< i << endl;
			XML.popTag();
		}
		XML.popTag();
		cout << "done." << endl;
		// ------------------------------- calculate the total Height
		height = margen;
		for (int i = 0; i < numOfObj; i++){
			height += objects[i]->height + margen;
		}
		cout << "Height calculated" << endl;
		
		// ------------------------------- Set positions by order
		float yPos = -height*0.5+margen;
		for (int i = 0; i < numOfObj; i++){
			objects[i]->moveTo(position.x, position.y +yPos+objects[i]->height*0.5);
			yPos += objects[i]->height + margen;
		}
		cout << "Position stablished" << endl;
		XML.popTag();
		return true;
	} else {
		ofxBlackWindow();
		return false;
	}
}

void ofxBlackWindow::update(){
	// Handles the fade out and fade with the closing and opening
	if (close) {
		if (alpha > 0) alpha -= 4;
		if (alpha == 0){
			angle = 0;
		}
	} else {
		if (alpha <= 255) alpha += 2;
	}
	
	if (timer >= 1) timer++;
	if (timer >= 15) timer = 0;
	
	for (int i = 0; i < objects.size(); i++){
		objects[i]->update();
	}
}

void ofxBlackWindow::draw(){
	
	if (alpha > 1){
		glDisable(GL_BLEND);
		ofEnableAlphaBlending();
		ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotateZ(ofRadToDeg(angle));
		
		//Dibuja la caja
		ofSetColor(background.r,background.g,background.b,alpha-70);
		ofFill();
		rBox();
		
		ofPopMatrix();
		ofDisableAlphaBlending();
		
		// Dibuja los objetos
		for (int i = 0; i < objects.size(); i++){
			ofSetColor(255,255,255,alpha);
			objects[i]->draw();
		}
	}
}