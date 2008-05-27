
/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef ENTERTAINERSKILL_H_
#define ENTERTAINERSKILL_H_

#include "engine/engine.h"

class PerformanceType {
public:
	static const int DANCE  = -1788534963;
	static const int MUSIC  = 866729052;
	
};

class Performance {

	  string performanceName;
	  int instrumentAudioId;
	  string requiredSong;
	  string requiredInstrument;
	  string requiredDance;
	  int danceVisualId;
	  int actionPointsPerLoop;
	  float loopDuration;
	  int type;
	  int baseXp;
	  int flourishXpMod;
	  int healMindWound;
	  int healShockWound;
	  string requiredSkillMod;
	  int requiredSkillModValue;
	  string mainloop;
	  string flourish1;
	  string flourish2;
	  string flourish3;
	  string flourish4;
	  string flourish5;
	  string flourish6;
	  string flourish7;
	  string flourish8;
	  string intro;
	  string outro;
	  
public:
	
	Performance* getDance(string name);
	Performance* getSong(string name, int instrumentType);
	
	inline bool isDance() {
		return type == PerformanceType::DANCE;
	}

	inline bool isMusic() {
		return type == PerformanceType::MUSIC;
	}
	
	// setters
	inline void setName(const string& instring) {
		performanceName = instring;
	}

	inline void setRequiredSong(const string& instring) {
		requiredSong = instring;
	}
	
	inline void setRequiredInstrument(const string& instring) {
		requiredInstrument = instring;
	}
	
	inline void setRequiredDance(const string& instring) {
		requiredDance = instring;
	}

	inline void setRequiredSkillMod(const string& instring) {
		requiredSkillMod = instring;
	}
	
	inline void setMainloop(const string& instring) {
		mainloop = instring;
	}
	
	inline void setFlourish1(const string& instring) {
		requiredDance = instring;
	}
	
	inline void setFlourish2(const string& instring) {
		requiredDance = instring;
	}
	
	inline void setFlourish3(const string& instring) {
		flourish3 = instring;
	}
	
	inline void setFlourish4(const string& instring) {
		flourish4 = instring;
	}
	
	inline void setFlourish5(const string& instring) {
		flourish5 = instring;
	}
	
	inline void setFlourish6(const string& instring) {
		flourish6 = instring;
	}
	
	inline void setFlourish7(const string& instring) {
		flourish7 = instring;
	}
	
	inline void setFlourish8(const string& instring) {
		flourish8 = instring;
	}
	
	inline void setIntro(const string& instring) {
		intro = instring;
	}
	
	inline void setOutro(const string& instring) {
		outro = instring;
	}
	
	inline void setInstrumentAudioId(int inInt) {
		instrumentAudioId = inInt;
	}
	
	inline void setDanceVisualId(int inInt) {
		danceVisualId = inInt;
	}

	inline void setActionPointsPerLoop(int inInt) {
		actionPointsPerLoop = inInt;
	}

	inline void setType(int inInt) {
		type = inInt;
	}

	inline void setBaseXp(int inInt) {
		baseXp = inInt;
	}

	inline void setFlourishXpMod(int inInt) {
		flourishXpMod = inInt;
	}

	inline void setHealMindWound(int inInt) {
		healMindWound = inInt;
	}
	
	inline void setHealShockWound(int inInt) {
		healShockWound = inInt;
	}
	
	inline void setRequiredSkillModValue(int inInt) {
		requiredSkillModValue = inInt;
	}
	
	inline void setLoopDuration(float inFloat) {
		loopDuration = inFloat;
	}
	
	
	// getters
	inline string& getName() {
		return performanceName;
	}
	
	inline string& getRequiredSong() {
		return requiredSong;
	}
	
	inline string& getRequiredInstrument() {
		return requiredInstrument;
	}
	
	inline string& getRequiredDance() {
		return requiredDance;
	}
	
	inline string& getRequiredSkillMod() {
		return requiredSkillMod;
	}
	
	inline string& getMainloop() {
		return mainloop;
	}
	
	inline string& getFlourish1() {
		return requiredDance;
	}
	
	inline string& getFlourish2() {
		return requiredDance;
	}
	
	inline string& getFlourish3() {
		return flourish3;
	}
	
	inline string& getFlourish4() {
		return flourish4;
	}
	
	inline string& getFlourish5() {
		return flourish5;
	}
	
	inline string& getFlourish6() {
		return flourish6;
	}
	
	inline string& getFlourish7() {
		return flourish7;
	}
	
	inline string& getFlourish8() {
		return flourish8;
	}
	
	inline string& getIntro() {
		return intro;
	}
	
	inline string& getOutro() {
		return outro;
	}
	
	inline int getInstrumentAudioId() {
		return instrumentAudioId;
	}
	inline int getDanceVisualId() {
		return danceVisualId;
	}

	inline int getActionPointsPerLoop() {
		return actionPointsPerLoop;
	}

	inline int getType() {
		return type;
	}

	inline int getBaseXp() {
		return baseXp;
	}

	inline int getFlourishXpMod() {
		return flourishXpMod;
	}

	inline int getHealMindWound() {
		return healMindWound;
	}
	
	inline int getHealShockWound() {
		return healShockWound;
	}
	
	inline int getRequiredSkillModValue() {
		return requiredSkillModValue;
	}

	inline float getLoopDuration() {
		return loopDuration;
	}
	
};


#endif /*ENTERTAINERSKILL_H_*/
