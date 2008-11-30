
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

	  String performanceName;
	  int instrumentAudioId;
	  String requiredSong;
	  String requiredInstrument;
	  String requiredDance;
	  int danceVisualId;
	  int actionPointsPerLoop;
	  float loopDuration;
	  int type;
	  int baseXp;
	  int flourishXpMod;
	  int healMindWound;
	  int healShockWound;
	  String requiredSkillMod;
	  int requiredSkillModValue;
	  String mainloop;
	  String flourish1;
	  String flourish2;
	  String flourish3;
	  String flourish4;
	  String flourish5;
	  String flourish6;
	  String flourish7;
	  String flourish8;
	  String intro;
	  String outro;
	  
public:
	
	Performance* getDance(String name);
	Performance* getSong(String name, int instrumentType);
	
	inline bool isDance() {
		return type == PerformanceType::DANCE;
	}

	inline bool isMusic() {
		return type == PerformanceType::MUSIC;
	}
	
	// setters
	inline void setName(const String& inString) {
		performanceName = inString;
	}

	inline void setRequiredSong(const String& inString) {
		requiredSong = inString;
	}
	
	inline void setRequiredInstrument(const String& inString) {
		requiredInstrument = inString;
	}
	
	inline void setRequiredDance(const String& inString) {
		requiredDance = inString;
	}

	inline void setRequiredSkillMod(const String& inString) {
		requiredSkillMod = inString;
	}
	
	inline void setMainloop(const String& inString) {
		mainloop = inString;
	}
	
	inline void setFlourish1(const String& inString) {
		requiredDance = inString;
	}
	
	inline void setFlourish2(const String& inString) {
		requiredDance = inString;
	}
	
	inline void setFlourish3(const String& inString) {
		flourish3 = inString;
	}
	
	inline void setFlourish4(const String& inString) {
		flourish4 = inString;
	}
	
	inline void setFlourish5(const String& inString) {
		flourish5 = inString;
	}
	
	inline void setFlourish6(const String& inString) {
		flourish6 = inString;
	}
	
	inline void setFlourish7(const String& inString) {
		flourish7 = inString;
	}
	
	inline void setFlourish8(const String& inString) {
		flourish8 = inString;
	}
	
	inline void setIntro(const String& inString) {
		intro = inString;
	}
	
	inline void setOutro(const String& inString) {
		outro = inString;
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
	inline String& getName() {
		return performanceName;
	}
	
	inline String& getRequiredSong() {
		return requiredSong;
	}
	
	inline String& getRequiredInstrument() {
		return requiredInstrument;
	}
	
	inline String& getRequiredDance() {
		return requiredDance;
	}
	
	inline String& getRequiredSkillMod() {
		return requiredSkillMod;
	}
	
	inline String& getMainloop() {
		return mainloop;
	}
	
	inline String& getFlourish1() {
		return requiredDance;
	}
	
	inline String& getFlourish2() {
		return requiredDance;
	}
	
	inline String& getFlourish3() {
		return flourish3;
	}
	
	inline String& getFlourish4() {
		return flourish4;
	}
	
	inline String& getFlourish5() {
		return flourish5;
	}
	
	inline String& getFlourish6() {
		return flourish6;
	}
	
	inline String& getFlourish7() {
		return flourish7;
	}
	
	inline String& getFlourish8() {
		return flourish8;
	}
	
	inline String& getIntro() {
		return intro;
	}
	
	inline String& getOutro() {
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
