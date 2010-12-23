/*
 *  ofxBlackBox.cpp
 *
 *  Created by Patricio González Vivo on 17/12/10.
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

#include "ofxBlackBox.h"

ofxBlackBox::ofxBlackBox(){
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

// ------------------------------------------ Render
void ofxBlackBox::resize(float _resize){
	width *= _resize;
	height *= _resize;
	margen *= _resize;
	scale *= _resize;
}

void ofxBlackBox::draw(){
	
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

void ofxBlackBox::rBox(){
	float a = (height/12);
	float b = a/6;
	
	float W = width/2;
	float H = height/2;
	
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

// ------------------------------------------ Action 
bool ofxBlackBox::isOver(int _x , int _y){
	if ((_x >= position.x - width*0.5) && (_x<= position. x + width*0.5) && (_y >= position.y - height*0.5) && (_y <= position.y + height*0.5)){
		return true;
	} else return false;
}

bool ofxBlackBox::checkObjects(Vec2f _loc){
	bool pressed = false;
	
	if (isOver(_loc))
		for(int i = 0; i< objects.size(); i++)
			if (objects[i]->isOver(_loc)){
				ofNotifyEvent(objectPressed, objects[i]->act,this);
				focusObject = i;
				pressed = true;
			}
	
	return pressed;
}

// ------------------------------------------ TUIO events for MultiTouch interaction
#ifdef USE_TUIO
void ofxBlackBox::setTuioClient (myTuioClient * _tuioClient){
	tuioClient = _tuioClient;
	
	// HELP with this in order to be independent from the main.
	ofAddListener(tuioClient->cursorAdded,this,&ofxBlackBox::tuioAdded);
	ofAddListener(tuioClient->cursorRemoved,this,&ofxBlackBox::tuioRemoved);
	ofAddListener(tuioClient->cursorUpdated,this,&ofxBlackBox::tuioUpdated);
}

void ofxBlackBox::tuioAdded(ofxTuioCursor &tuioCursor){
	Vec2f loc = Vec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
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

void ofxBlackBox::tuioUpdated(ofxTuioCursor &tuioCursor){
	// First it will update the information of the fingers that are over the border
	for ( int i = 0; i < cursorsOnBorder.size(); i++)
		if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
			cursorsOnBorder[i].loc = Vec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
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
			Vec2f Di = oldLoc[sta] - oldLoc[din];		// Get Vector between OLD finger position
			Vec2f Dii = oldLoc[sta] - cursorsOnBorder[din].loc; // Get Vector between NEW finger position
			
			float di = Di.length();						// Get OLD finger distance
			float dii = Dii.length();					// Get NEW finger distance
			
			float scaleF = dii / di;					// Set the scale diference before and after
			
			float ri = -1*atan2(Di.x,Di.y)+(PI/2);		// Get OLD fingers inclination
			float rii = -1*atan2(Dii.x,Dii.y)+(PI/2);	// Get NEW fingers inclination
			
			float rotateF = rii - ri;					// Set the angle diference before and after
			
			Vec2f oldStaCursorToCenter = position - oldLoc[sta] ;	// Get the OLD vector from the static finger to the center of the keyboard
			float oldAngleToCenter = -1*atan2(oldStaCursorToCenter.x,oldStaCursorToCenter.y)+(PI/2);	// Get OLD Angle to the center 
			float oldRadioToCenter = oldStaCursorToCenter.length();		// Get the OLD distance from the static figer to the center
			
			float newRadioToCenter = oldRadioToCenter * scaleF;		// Set the NEW distance to the center
			float newAngleToCenter = oldAngleToCenter + rotateF;	// Set the NEW angle to the center
			Vec2f newStaCursorToCenter = Vec2f(newRadioToCenter*cos(newAngleToCenter),newRadioToCenter*sin(newAngleToCenter)); // Set the NEW vector from the static finger to the center of the keyboard
			
			resize(scaleF);											// RESIZE the scale diference proportion
			rotate(rotateF);										// ROTATE the diference in angle
			position = oldLoc[sta] + newStaCursorToCenter;			// MOVE	the draged distance
		}
		
		oldLoc[0] = cursorsOnBorder[0].loc;
		oldLoc[1] = cursorsOnBorder[1].loc;
	}
}

void ofxBlackBox::tuioRemoved(ofxTuioCursor &tuioCursor){
	Vec2f loc = Vec2f(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	
	for (int i = 0; i < cursorsOnBorder.size(); i++ )
		if (cursorsOnBorder[i].idN == tuioCursor.getSessionId())
			cursorsOnBorder.erase(cursorsOnBorder.begin()+i);
	
	if ( isOver(loc) && (cursorsOnBorder.size() == 0) && (close == false)) {
		if ((timer > 2) && (timer <= 15)) close = true;
		else timer = 1;
	}
}
#endif