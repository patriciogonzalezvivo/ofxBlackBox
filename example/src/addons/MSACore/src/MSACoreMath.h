/***********************************************************************
 
 Copyright (c) 2008, 2009, 2010 Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
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

#pragma once

namespace MSA {
#ifndef PI
#define PI       3.14159265358979323846
#endif
	
#ifndef TWO_PI
#define TWO_PI   6.28318530717958647693
#endif
	
#ifndef M_TWO_PI
#define M_TWO_PI   6.28318530717958647693
#endif
	
#ifndef FOUR_PI
#define FOUR_PI 12.56637061435917295385
#endif
	
#ifndef HALF_PI
#define HALF_PI  1.57079632679489661923
#endif
	
#ifndef DEG_TO_RAD
#define DEG_TO_RAD (PI/180.0)
#endif
	
#ifndef RAD_TO_DEG
#define RAD_TO_DEG (180.0/PI)
#endif
	
	// returns always positive modulo
	inline int mod(int dividend, int divisor) {
		dividend %= divisor;
		if(dividend<0) dividend += divisor;
		return dividend;
	}
	
	
	inline float fastInvSquareRoot(float x) {
		float xhalf = 0.5f*x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i>>1);
		x = *(float*)&i;
		x = x*(1.5f - xhalf*x*x);
		return x;
	}
	
	//	inline void fastNormalize(Vec3f &p) {
	//		float f = fastInvSquareRoot(p.lengthSquared());
	//		p *= f;
	//	}
	
	
	template<typename T> void SWAP( T& a, T& b)						{ T tmp = b; b = a; a = tmp; }
	
	template<typename T> 
	float mapRange(T value, T inputMin, T inputMax, T outputMin, T outputMax, bool clamp = false) {
		T outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
		
		if(clamp){
			if(outputMax < outputMin){
				if( outVal < outputMax )outVal = outputMax;
				else if( outVal > outputMin )outVal = outputMin;
			}else{
				if( outVal > outputMax )outVal = outputMax;
				else if( outVal < outputMin )outVal = outputMin;
			}
		}
		return outVal;
	}
	
	template <typename T>
	void bounce(T &pos, T &vel, T min, T max, float bounceFactor = 1) {
		if(pos < min) {
			pos = min;
			vel = fabs(vel) * bounceFactor;
		} else if(pos > max) {
			pos = max;
			vel = -fabs(vel) * bounceFactor;
		}
	}
	
	template <typename T>
	bool inRange(T a, T min, T max) {
		return (a >= min) && (a <= max);
	}

	
}