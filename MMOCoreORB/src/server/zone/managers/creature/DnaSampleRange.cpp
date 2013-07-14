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
int DnaSampleRange::generateValue(int series){
	return 0;
}
