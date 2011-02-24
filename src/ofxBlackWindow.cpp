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
	
	position = ofVec2f(0,0);
	
	width	= 500;
	height	= 50;
	margen	= 20;
	
	timer	= 0;
	delay	= 0;
	
	scale	= 1;
	
	background.r = 0;
	background.g = 0;
	background.b = 0;
	
	foreground.r = 255;
	foreground.g = 255;
	foreground.b = 255;
}

//------------------------------------------------------------ SETUP
void ofxBlackWindow::setup(string filePath, int _instance){
	if (XML.loadFile(filePath)){
		XML.pushTag("WINDOW", _instance);
			initialWindowSetup();
		XML.popTag();
	} else 
		cout << "File " << filePath << " not found" << endl;
}

void ofxBlackWindow::initialWindowSetup(){
	// It have to bee pushed into a WINDOW tag
	bool success = true;
	
	// INITIAL VARIABLES
	position		= ofVec2f(XML.getValue("X",0),XML.getValue("Y",0));
	width			= XML.getValue("WIDTH",500);
	height			= XML.getValue("HEIGHT",0);
	margen			= XML.getValue("MARGEN",20);
	angle			= XML.getValue("ANGLE",0);
	scale			= XML.getValue("SCALE", 1);
	delay			= XML.getValue("DELAY",0);
	close			= XML.getValue("CLOSE",0);
	alpha			= XML.getValue("ALPHA",0);
	
	background.r = XML.getValue("BACKGROUND:RED", 0);
	background.g = XML.getValue("BACKGROUND:GREEN", 0);
	background.b = XML.getValue("BACKGROUND:BLUE", 0);
	
	foreground.r = XML.getValue("FOREGROUND:RED", 255);
	foreground.g = XML.getValue("FOREGROUND:GREEN", 255);
	foreground.b = XML.getValue("FOREGROUND:BLUE", 255);
	
	setFont(XML.getValue("DEFAULT_FONT:PATH","helvetica.ttf"), XML.getValue("DEFAULT_FONT:SIZE",10));
	
	// ------------------------------------------- OBJECTS LOADING
	objects.clear();
	XML.pushTag("OBJECTS");
	
		for (int i = 0; i < XML.getNumTags("OBJ"); i++)
			loadObject(i);

		if ( height == 0)						// If height is 0 it´s set on AUTO mode and it will calculate the height
			autoVerticalArrange();
	
	XML.popTag();
} 

void ofxBlackWindow::loadObject(int _instance){
	cout << "ONE OBJECT ADD" << endl;
	XML.pushTag("OBJ", _instance);
	
		string typeName = XML.getValue("TYPE","NONE");
	
		if ( typeName == "VIDEO" ){
			ofxBlackVideo * v = new ofxBlackVideo();
		
			v->setColors(&foreground, &background);
			v->setWindowCenter(&position);
			v->setWindowNorth(&angle);
			v->setScale(&scale);
			v->setAlpha(&alpha);
		
			v->loadVideo(XML.getValue("PATH","raya.mov"));
			v->resize(XML.getValue("SCALE",0.5));
		
			v->act = XML.getValue("ACTION","no action found");
		
			objects.push_back(v);
		
		}else if (typeName == "IMAGE"){
			ofxBlackImage * i = new ofxBlackImage();
		
			i->setColors(&foreground, &background);
			i->setWindowCenter(&position);
			i->setWindowNorth(&angle);
			i->setScale(&scale);
			i->setAlpha(&alpha);
		
			i->loadImage(XML.getValue("PATH","raya.png"));
			i->resize(XML.getValue("SCALE",0.5));
		
			i->act = XML.getValue("ACTION","no action found");
		
			objects.push_back(i);
		
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
		
			if (XML.tagExists("PATH",0))
				t->loadTextFrom(XML.getValue("PATH","pez1.txt"));
			else if (XML.tagExists("TEXT",0)) 
				t->loadText(XML.getValue("TEXT","insert text inside <TEXT> here </TEXT>"));
			else 
				t->loadText("no text found");
		
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
				else 
					cout << align << " it´s not a valid alignment for object " << _instance << endl; 
			} else	
				t->alignment = OF_TEXT_ALIGN_JUSTIFIED;
		
			if (XML.tagExists("WIDTH",0))
				t->setWidth(XML.getValue("WIDTH",500));
			else
				t->setWidth(width-margen*2);
		
			t->act = XML.getValue("ACTION","no action found");
		
			objects.push_back(t);
			
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
		
			ti->act = XML.getValue("ACTION"," ");
		
			objects.push_back(ti);
	
		} else if (typeName == "BUTTON"){
			ofxBlackButton * b = new ofxBlackButton();
		
			b->setScale(&scale);
			b->setFont(&defaultFont);
			b->setWindowNorth(&angle);
			b->setWindowCenter(&position);
			
			b->setColors(&foreground, &background);
			if (XML.tagExists("BACKGROUND",0)){
				b->color = new ofColor();
				
				b->color->r = XML.getValue("BACKGROUND:RED", 0);
				b->color->g = XML.getValue("BACKGROUND:GREEN", 0);
				b->color->b = XML.getValue("BACKGROUND:BLUE", 0);
				b->setIndependentColor();
			}
				
			b->setAlpha(&alpha);
		
			b->setSize(XML.getValue("WIDTH",50), XML.getValue("HEIGHT",30));
			b->setLetter(XML.getValue("TEXT"," "));
		
			b->act = XML.getValue("ACTION","no action found");
		
			objects.push_back(b);
		} else if (typeName == "SLIDER"){
			ofxBlackSlider * s = new ofxBlackSlider(XML.getValue("VERTICAL",true), 
													XML.getValue("VALUE",0.5),
													XML.getValue("MIN",0.1),
													XML.getValue("MAX",10.2));
			s->setScale(&scale);
			s->setFont(&defaultFont);
			s->setWindowNorth(&angle);
			s->setWindowCenter(&position);
			
			s->setColors(&foreground, &background);
			if (XML.tagExists("BACKGROUND",0)){
				s->color = new ofColor();
				
				s->color->r = XML.getValue("BACKGROUND:RED", 0);
				s->color->g = XML.getValue("BACKGROUND:GREEN", 0);
				s->color->b = XML.getValue("BACKGROUND:BLUE", 0);
				s->setIndependentColor();
			}
			
			s->setAlpha(&alpha);
			
			s->setSize(XML.getValue("WIDTH",50), XML.getValue("HEIGHT",30));
			s->setLetter(XML.getValue("TEXT"," "));
			
			s->act = XML.getValue("ACTION","no action found");
			
			objects.push_back(s);
		} else {
			cout << "ERROR loading the object number "<< _instance << endl;
		}
	
	XML.popTag();
}

void ofxBlackWindow::autoVerticalArrange(){
	//	It have to be pushed into WINDOW:OBJECT tags
	
	// -------------------------------	Get the total WINDOW:HEIGHT from OBJ that don´t have a fixed position
	height = margen;
	for (int i = 0; i < objects.size(); i++){
		XML.pushTag("OBJ", i);
			if (!XML.tagExists("Y",0)) 
				height += objects[i]->height + margen;	// IF the OBJ have a fixed position it will not calculate his HEIGHT
		XML.popTag();
	}
	
	// ------------------------------- Set the OBJ positions inside the given WINDOW:HEIGHT
	float yPos = -height*0.5+margen;
	
	for (int i = 0; i < objects.size(); i++){ 
		XML.pushTag("OBJ", i);			
		
		int tempX = position.x;
		int tempY = position.y;
		
		if (XML.tagExists("X",0)) 
			tempX += XML.getValue("X",0);
		
		if (XML.tagExists("Y",0))
			tempY += XML.getValue("Y",0);
		else { 
			tempY += yPos+objects[i]->height*0.5;		// IF the OBJ position isn´t declarated, it will give one automatic
			yPos += objects[i]->height + margen;
		}
		
		objects[i]->moveTo(tempX,tempY);
		XML.popTag();
	}
}

ofxBlackObject *ofxBlackWindow::operator[](unsigned int i){
	if (i >= 0 && i < objects.size() )
		return objects[i];
	else 
		return 0;
}
			
// --------------------------------------------------- RENDER
void ofxBlackWindow::resize(float _resize){
	width *= _resize;
	height *= _resize;
	margen *= _resize;
	scale *= _resize;
}

void ofxBlackWindow::update(){
	// Handles the fade out and fade with the closing and opening
	if (close) {
		if (alpha > 0) alpha -= 20;
		/*if (alpha == 0){
			angle = 0;
		}*/
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

void ofxBlackWindow::draw(){
	
	if (alpha > 1){
		//glDisable(GL_BLEND);
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

void ofxBlackWindow::rBox(){
	float W = width/2;
	float H = height/2;
	
	float a = (  (H < W)? H : W )/4;//*(*scale);
	float b = a/3;//*(*scale);
	
	/*
	float a, b;
	
	if (W <= 100){
		a = height/24;
		b = a/12;
	} else {
		a = height/12;
		b = a/6;
	}*/
	
	ofEnableAlphaBlending();	
	ofBeginShape(); 
	ofVertex(		W -a,	-H );
    
	ofBezierVertex( W -b ,	-H,
				   W    ,	-H +b, 
				   W    ,	-H +a);
	
	ofVertex(       W    ,	H -a);
    
	ofBezierVertex( W    ,	H -b,
				   W -b ,	H,
				   W -a ,	H);
	
	ofVertex(       -W +a , H );
    
	ofBezierVertex( -W +b , H,
				   -W    , H -b,
				   -W    , H -a );
	
	ofVertex(       -W    , -H +a );
    
	ofBezierVertex( -W    ,	-H +b,
				   -W +b , -H,
				   -W +a , -H );
	ofVertex(		W -a,	-H );
	ofEndShape();
	ofDisableAlphaBlending();
}

// ------------------------------------------------------ ACTIONS 
bool ofxBlackWindow::isOver(ofVec2f _location){
	bool over;
	
	ofVec2f dirToCenter = position - _location;
	float theta = atan2(dirToCenter.x,dirToCenter.y)-(PI/2);
	float r = dirToCenter.length();
	float x = r * cos(theta + angle);
	float y = r * sin(theta + angle);
	
	if ( (x <= width*0.5) && (x >= -width*0.5) && (y <= height*0.5) && (y >= -height*0.5)) 
		over = true;
	else 
		over = false;
	
	return over;
}

bool ofxBlackWindow::checkObjects(ofVec2f _loc){
	bool pressed = false;
	
	if (isOver(_loc))
		for(int i = 0; i< objects.size(); i++)
			if (objects[i]->isOver(_loc)){
				focusObject = i;
				pressed = true;
				ofNotifyEvent(objectPressed, objects[i]->act,this);
			}
	
	return pressed;
}

// ------------------------------------------ TUIO events for MultiTouch interaction
#ifdef USE_TUIO
void ofxBlackWindow::setTuioClient (myTuioClient * _tuioClient){
	tuioClient = _tuioClient;
	
	// HELP with this in order to be independent from the main.
	ofAddListener(tuioClient->cursorAdded,this,&ofxBlackWindow::tuioAdded);
	ofAddListener(tuioClient->cursorRemoved,this,&ofxBlackWindow::tuioRemoved);
	ofAddListener(tuioClient->cursorUpdated,this,&ofxBlackWindow::tuioUpdated);
}

void ofxBlackWindow::tuioAdded(ofxTuioCursor &tuioCursor){
	ofVec2f loc = ofVec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
	if (isOver(loc)){
		timer = 1;
		checkObjects(loc);
		
		tCursor c;
		c.idN = tuioCursor.getSessionId();
		c.loc = loc;
		
		if (cursorsOnBorder.size() == 0){	// If it´s the first finger over the border it will save remember it
			cursorsOnBorder.push_back(c);
		} else if (cursorsOnBorder.size() == 1){	// If it´s the second one it will check if it´s at the right distance
			cursorsOnBorder.push_back(c);
			
			oldLoc[0] = cursorsOnBorder[0].loc;
			oldLoc[1] = cursorsOnBorder[1].loc;
		}
		
	}
}

void ofxBlackWindow::tuioUpdated(ofxTuioCursor &tuioCursor){
	ofVec2f loc = ofVec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	if (isOver(loc) && (!close)){
		checkObjects(loc);
	
		// First it will update the information of the fingers that are over the border
		for ( int i = 0; i < cursorsOnBorder.size(); i++)
			if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
				cursorsOnBorder[i].loc = ofVec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
		// Then check if there is two fingers over it
		if (cursorsOnBorder.size() == 2){
			int sta = -1;	// a NULL parameter
			int din = -1;	// a NULL parameter
		
		// First it will watch witch one is the static finger and witch one is the dinamic
			for ( int i = 0; i < cursorsOnBorder.size(); i++)
				if (cursorsOnBorder[i].loc == oldLoc[i]) sta = i;
				else din = i;
		
		// If one it´s the dinamic and the other one the static it´s all OK and it´s time to calculate new parameters
			if ((sta != -1) && (din != -1) && (din != sta)){
				ofVec2f Di = oldLoc[sta] - oldLoc[din];		// Get Vector between OLD finger position
				ofVec2f Dii = oldLoc[sta] - cursorsOnBorder[din].loc; // Get Vector between NEW finger position
			
				float di = Di.length();						// Get OLD finger distance
				float dii = Dii.length();					// Get NEW finger distance
			
				float scaleF = dii / di;					// Set the scale diference before and after
			
				float ri = -1*atan2(Di.x,Di.y)+(PI/2);		// Get OLD fingers inclination
				float rii = -1*atan2(Dii.x,Dii.y)+(PI/2);	// Get NEW fingers inclination
			
				float rotateF = rii - ri;					// Set the angle diference before and after
			
				ofVec2f oldStaCursorToCenter = position - oldLoc[sta] ;	// Get the OLD vector from the static finger to the center of the keyboard
				float oldAngleToCenter = -1*atan2(oldStaCursorToCenter.x,oldStaCursorToCenter.y)+(PI/2);	// Get OLD Angle to the center 
				float oldRadioToCenter = oldStaCursorToCenter.length();		// Get the OLD distance from the static figer to the center
			
				float newRadioToCenter = oldRadioToCenter * scaleF;		// Set the NEW distance to the center
				float newAngleToCenter = oldAngleToCenter + rotateF;	// Set the NEW angle to the center
				ofVec2f newStaCursorToCenter = ofVec2f(newRadioToCenter*cos(newAngleToCenter),newRadioToCenter*sin(newAngleToCenter)); // Set the NEW vector from the static finger to the center of the keyboard
			
				resize(scaleF);											// RESIZE the scale diference proportion
				rotate(rotateF);										// ROTATE the diference in angle
				position = oldLoc[sta] + newStaCursorToCenter;			// MOVE	the draged distance
			}
		
			oldLoc[0] = cursorsOnBorder[0].loc;
			oldLoc[1] = cursorsOnBorder[1].loc;
		}
	}
}

void ofxBlackWindow::tuioRemoved(ofxTuioCursor &tuioCursor){
	ofVec2f loc = ofVec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
	for (int i = 0; i < cursorsOnBorder.size(); i++ )
		if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
			cursorsOnBorder.erase(cursorsOnBorder.begin()+i);
	
	if ( isOver(loc) && (cursorsOnBorder.size() == 0) && (close == false) && (alpha >= 200)) {
		if ((timer > 2) && (timer <= 15)) close = true;
		else timer = 1;
	}
}
#endif