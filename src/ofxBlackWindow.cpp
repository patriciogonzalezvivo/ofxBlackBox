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
	delay	= 0;
	
	scale	= 1;
	
	background.set(CM_RGB,Vec3f(0,0,0));
	foreground.set(CM_RGB,Vec3f(255,255,255));
}

bool ofxBlackWindow::setup(string filePath){
	if (XML.loadFile(filePath)){
		cout << "Opening " << filePath;
		XML.pushTag("WINDOW");
		position		= Vec2f(XML.getValue("X",0),XML.getValue("Y",0));
		width			= XML.getValue("WIDTH",500);
		height			= XML.getValue("HEIGHT",0);
		margen			= XML.getValue("MARGEN",20);
		
		angle			= XML.getValue("ANGLE",0);
		
		close			= XML.getValue("CLOSE",1);
		background.set(CM_RGB,Vec3f(XML.getValue("BACKGROUND:RED", 0),XML.getValue("BACKGROUND:GREEN", 0),XML.getValue("BACKGROUND:BLUE", 0)));
		foreground.set(CM_RGB,Vec3f(XML.getValue("FOREGROUND:RED", 255),XML.getValue("FOREGROUND:GREEN", 255),XML.getValue("FOREGROUND:BLUE", 255)));
		alpha			= XML.getValue("ALPHA",0);
		
		delay			= XML.getValue("DELAY",0);
		
		
		setFont(XML.getValue("DEFAULT_FONT:PATH","helvetica.ttf"), XML.getValue("DEFAULT_FONT:SIZE",10));
		
		// ------------------------------------------- OBJECTS
		objects.clear();
		XML.pushTag("OBJECTS");
		int numOfObj = XML.getNumTags("OBJ");
		cout << " with " << numOfObj << " to be load: ";
		
		// ------------------------------- Load the data of the object and make the link to the main window
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
				
				if (XML.tagExists("ACTION",0)){
					v->act = XML.getValue("ACTION","no action found");
				}
				
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
				
				if (XML.tagExists("ACTION",0)){
					i->act = XML.getValue("ACTION","no action found");
				}
				
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
				else if (XML.tagExists("TEXT",0)) t->loadText(XML.getValue("TEXT","insert text inside <TEXT> here </TEXT>"));
				else t->loadText("no text found");
				
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
				
				if (XML.tagExists("ACTION",0)){
					t->act = XML.getValue("TEXT","no action found");
				}
				
				objects.push_back(t);
				cout << "text ";
			} else if (typeName == "TEXTINPUT"){
				ofxBlackTextInput * ti = new ofxBlackTextInput();
				ti->setScale(&scale);
				ti->setFont(&defaultFont);
				ti->setWindowNorth(&angle);
				ti->setWindowCenter(&position);
				ti->setColors(&background,&foreground);
				ti->setAlpha(&alpha);
				ti->setSize(XML.getValue("WIDTH",50), XML.getValue("HEIGHT",30));
				ti->label = XML.getValue("TEXT","no text found");
				
				if (XML.tagExists("ACTION",0)){
					ti->act = XML.getValue("ACTION"," ");
				}
				
				objects.push_back(ti);
				cout << "button ";
			} 
			else if (typeName == "BUTTON"){
				ofxBlackButton * b = new ofxBlackButton();
				b->setScale(&scale);
				b->setFont(&defaultFont);
				b->setWindowNorth(&angle);
				b->setWindowCenter(&position);
				b->setColors(&foreground, &background);
				b->setAlpha(&alpha);
				b->setSize(XML.getValue("WIDTH",50), XML.getValue("HEIGHT",30));
				b->setLetter(XML.getValue("TEXT","no text found"));
				
				if (XML.tagExists("ACTION",0)){
					b->act = XML.getValue("ACTION","no action found");
				}
				
				objects.push_back(b);
				cout << "button ";
				
			} else cout << "ERROR loading the object number "<< i << endl;
			XML.popTag();
		}
		
		cout << "done." << endl;
		// ------------------------------- calculate the total Height
		if ( height == 0){		// If height is 0 it´s set on AUTO mode and it will calculate the height
			height = margen;
			for (int i = 0; i < numOfObj; i++){
				XML.pushTag("OBJ", i);
					if (!XML.tagExists("Y",0)) height += objects[i]->height + margen;
				XML.popTag();
			}
		} else height = XML.getValue("HEIGHT",200);
		cout << "Height calculated" << endl;		// Other wise it´s going to put wat is said.
		
		// ------------------------------- Set positions by order
		float yPos = -height*0.5+margen;
		for (int i = 0; i < numOfObj; i++){
			XML.pushTag("OBJ", i);			// IF the position is declarated, it will give automatic positions depending on the position on the vector
			int tempX = position.x;
			int tempY = position.y;
				
			if (XML.tagExists("X",0)) tempX = XML.getValue("X",0);
			if (XML.tagExists("Y",0)) tempY = XML.getValue("Y",0);
			else { tempY += yPos+objects[i]->height*0.5;
				yPos += objects[i]->height + margen;
			}
				
			objects[i]->moveTo(tempX,tempY);
			XML.popTag();
		}
		cout << "Position stablished" << endl;
		XML.popTag();	// OBJECTS
			
		XML.popTag();	// BOX
		return true;
	} else {
		ofxBlackWindow();
		return false;
	}
}

void ofxBlackWindow::update(){
	// Handles the fade out and fade with the closing and opening
	if (close) {
		if (alpha > 0) alpha -= 20;
		if (alpha == 0){
			angle = 0;
		}
	} else {
		if (alpha <= 255) alpha += 20;
	}
	
	if (timer >= 1) timer++;
	//if (timer >= 15) timer = 0;
	
	if (( delay != 0) && (timer >= delay)) {
		close = true;
		timer = 0;
	}
	
	
	for (int i = 0; i < objects.size(); i++){
		objects[i]->update();
	}
}