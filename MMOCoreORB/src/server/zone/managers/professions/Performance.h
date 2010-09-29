/*
 * Performance.h
 *
 *  Created on: 19/08/2010
 *      Author: victor
 */

#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_


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



#endif /* PERFORMANCE_H_ */
