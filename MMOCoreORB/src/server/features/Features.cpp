/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "Features.h"

Features::Features()
	: HashTable<String, String>() {
}

Features::~Features() {
}

bool Features::loadFeatures() {
	Lua* lua = new Lua();

	if (!lua->runFile("conf/features.lua"))
		return false;

	delete lua;

	return true;
}
