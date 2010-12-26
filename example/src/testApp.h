#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxBlackBox.h"

#define USE_TUIO

#ifdef USE_TUIO
#define tuioCursorSpeedMult				0.5	// the iphone screen is so small, easy to rack up huge velocities! need to scale down 
#define tuioStationaryForce				0.001f	// force exerted when cursor is stationary
#include "ofxTuio.h"
#endif

class testApp : public ofBaseApp{
public:
	ofxBlackWindow		window;
	void				windowPressed(string & letter);
	
	ofxBlackKeyboard	keyboard;
	void				keyboardPressed(string & letter);
		
	ofImage fondo;
		
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
#ifdef USE_TUIO
	myTuioClient tuioClient;
	
	void	tuioAdded(ofxTuioCursor & tuioCursor);
	void	tuioRemoved(ofxTuioCursor & tuioCursor);
	void	tuioUpdated(ofxTuioCursor & tuioCursor);
#endif

};

#endif
