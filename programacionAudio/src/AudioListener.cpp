#include "AudioListener.h"
#include "al.h"

void setListenerPosition(float _x, float _y, float _z) {
	alListener3f(AL_POSITION, _x, _y, _z);
}


void setListenerVelocity(float _x, float _y, float _z) {
	alListener3f(AL_VELOCITY, _x, _y, _z);
}


void setListenerOrientation(float _x, float _y, float _z) {
	alListener3f(AL_ORIENTATION, _x, _y, _z);
}
