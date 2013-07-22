/*
 * DnaSampleRange.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: swgemu
 */

#include "DnaSampleRange.h"

DnaSampleRange::DnaSampleRange(LuaObject& obj) {
	// Load data from teh lua object
	vhqMax = obj.getIntField("vhqMax");
	vhqMin = obj.getIntField("vhqMin");
	hqMax  = obj.getIntField("hqMax");
	hqMin  = obj.getIntField("hqMin");
	aaMax  = obj.getIntField("aaMax");
	aaMin  = obj.getIntField("aaMin");
	aMax   = obj.getIntField("aMax");
	aMin   = obj.getIntField("aMin");
	baMax  = obj.getIntField("baMax");
	baMin  = obj.getIntField("baMin");
	lqMax  = obj.getIntField("lqMax");
	lqMin  = obj.getIntField("lqMin");
	vlqMax = obj.getIntField("vlqMax");
	vlqMin = obj.getIntField("vlqMin");

}

DnaSampleRange::~DnaSampleRange() {
}
int DnaSampleRange::generateValue(int quality){
	uint32 max,min;
	switch(quality) {
		case VHQ: {
			max = vhqMax;
			min = vhqMin;
			break;
		}
		case HQ: {
			max = hqMax;
			min = hqMin;
			break;
		}
		case AA: {
			max = aaMax;
			min = aaMin;
			break;
		}
		case A: {
			max = aMax;
			min = aMin;
			break;
		}
		case BA: {
			max = baMax;
			min = baMin;
			break;
		}
		case LQ: {
			max = lqMax;
			min = lqMin;
			break;
		}
		case VLQ: {
			max = vlqMax;
			min = vlqMin;
			break;
		}
		default:{
			return 0;
		}
		return (int)(System::random(max-min) + min);
	}
}
