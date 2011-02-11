/*ofxBlackVideo
 *  ofxBlackVideo.h
 *
 *  Created by Patricio González Vivo on 18/12/10.
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

#ifndef _ofxVIDEO
#define _ofxVIDEO

#include "ofxBlackObject.h"

//#define	OF_VIDEO_WITH_ALPHA			// Coment this if you don´t have ofxAlpaVideoPlayer
#ifdef OF_VIDEO_WITH_ALPHA			
#include "ofxAlphaVideoPlayer.h"	// You can get it at: http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=364&p=19620#p19620
#endif

class ofxBlackVideo : public ofxBlackObject{	
public:
	ofxBlackVideo();
	
#ifdef OF_VIDEO_WITH_ALPHA
	ofxAlphaVideoPlayer video;
#else
	ofVideoPlayer	video;
#endif
	
	void			loadVideo(string videoPath){video.loadMovie(videoPath.c_str()); width = video.width; height = video.height; video.play();};
	
	void			resize(float _resize){ width *= _resize; height *= _resize;};
	
	void			update(){video.idleMovie();};
	void			draw();
};

#endif