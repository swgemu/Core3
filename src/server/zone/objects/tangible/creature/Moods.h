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

#ifndef MOODS_H_
#define MOODS_H_

const static char* MoodNames[][2]= {
	{"none", "neutral"},
	{"absentminded", "neutral"},
	{"amazed", "neutral"},
	{"amused", "happy"},
	{"angry", "angry"},
	{"approving", "neutral"},
	{"bitter", "neutral"},
	{"bloodthirsty", "neutral"},
	{"brave", "neutral"},
	{"callous", "neutral"},
	{"careful", "neutral"},
	{"careless", "neutral"},
	{"casual", "neutral"},
	{"clinical", "neutral"},
	{"cocky", "neutral"},
	{"cold", "neutral"},
	{"compassionate", "neutral"},
	{"condescending", "neutral"},
	{"confident", "neutral"},
	{"confused", "neutral"},
	{"content", "happy"},
	{"courtly", "neutral"},
	{"coy", "neutral"},
	{"crude", "neutral"},
	{"cruel", "neutral"},
	{"curious", "neutral"},
	{"cynical", "neutral"},
	{"defensive", "neutral"},
	{"depressed", "unhappy"},
	{"devious", "neutral"},
	{"dimwitted", "neutral"},
	{"disappointed", "unhappy"},
	{"discreet", "neutral"},
	{"disgruntled", "disgruntled"},
	{"disgusted", "neutral"},
	{"dismayed", "unhappy"},
	{"disoriented", "neutral"},
	{"distracted", "neutral"},
	{"doubtful", "neutral"},
	{"dramatic", "neutral"},
	{"dreamy", "neutral"},
	{"drunk", "neutral"},
	{"earnest", "neutral"},
	{"ecstatic", "happy"},
	{"embarrassed", "neutral"},
	{"emphatic", "neutral"},
	{"encouraging", "neutral"},
	{"enthusiastic", "neutral"},
	{"evil", "neutral"},
	{"exasperated", "disgruntled"},
	{"exuberant", "happy"},
	{"fanatical", "neutral"},
	{ "forgive", "neutral"},
	{"frustrated", "neutral"},
	{"guilty", "neutral"},
	{"happy", "happy"},
	{"honest", "neutral"},
	{"hopeful", "neutral"},
	{"hopeless", "neutral"},
	{"humble", "neutral"},
	{"hysterical", "neutral"},
	{"imploring", "neutral"},
	{"indifferent", "neutral"},
	{"indignant", "angry"},
	{"interested", "neutral"},
	{"jealous", "neutral"},
	{"joyful", "happy"},
	{"lofty", "neutral"},
	{"loud", "neutral"},
	{"loving", "neutral"},
	{"lustful", "neutral"},
	{"mean", "neutral"},
	{"mischievous", "neutral"},
	{"nervous", "neutral"},
	{"neutral", "neutral"},
	{"offended", "neutral"},
	{"optimistic", "neutral"},
	{"pedantic", "neutral"},
	{"pessimistic", "neutral"},
	{"petulant", "neutral"},
	{"philosophical", "neutral"},
	{"pitying", "neutral"},
	{"playful", "happy"},
	{"polite", "neutral"},
	{"pompous", "neutral"},
	{"proud", "neutral"},
	{"provocative", "neutral"},
	{"puzzled", "neutral"},
	{"regretful", "unhappy"},
	{"relieved", "neutral"},
	{"reluctant", "neutral"},
	{"resigned", "neutral"},
	{"respectful", "neutral"},
	{"romantic", "neutral"},
	{"rude", "neutral"},
	{"sad", "unhappy"},
	{"sarcastic", "neutral"},
	{"scared", "neutral"},
	{"scolding", "neutral"},
	{"scornful", "neutral"},
	{"serious", "neutral"},
	{"shameless", "neutral"},
	{"shocked", "neutral"},
	{"shy", "neutral"},
	{"sincere", "neutral"},
	{"sleepy", "neutral"},
	{"sly", "neutral"},
	{"smug", "neutral"},
	{"snobby", "neutral"},
	{"sorry", "neutral"},
	{"spiteful", "neutral"},
	{"stubborn", "neutral"},
	{"sullen", "neutral"},
	{"suspicious", "neutral"},
	{"taunting", "neutral"},
	{"terrified", "neutral"},
	{"thankful", "neutral"},
	{"thoughtful", "neutral"},
	{"tolerant", "neutral"},
	{"uncertain", "neutral"},
	{"unhappy", "unhappy"},
	{"unwilling", "neutral"},
	{"warm", "neutral"},
	{"whiny", "neutral"},
	{"wicked", "neutral"},
	{"wistful", "neutral"},
	{"worried", "worried"},
	{"tired", "neutral"},
	{"exhausted", "neutral"},
	{"friendly", "happy"},
	{"timid", "neutral"},
	{"lazy", "neutral"},
	{"surprised", "worried"},
	{"innocent", "happy"},
	{"wise", "neutral"},
	{"youthful", "neutral"},
	{"adventurous", "neutral"},
	{"annoyed", "angry"},
	{"perturbed", "unhappy"},
	{"sedate", "neutral"},
	{"calm", "neutral"},
	{"suffering", "unhappy"},
	{"hungry", "neutral"},
	{"thirsty", "neutral"},
	{"alert", "neutral"},
	{"shifty", "neutral"},
	{"relaxed", "neutral"},
	{"crotchety", "angry"},
	{"surly", "angry"},
	{"painful", "unhappy"},
	{"wounded", "unhappy"},
	{"bubbly", "happy"},
	{"heroic", "neutral"},
	{"quiet", "neutral"},
	{"remorseful", "unhappy"},
	{"grumpy", "angry"},
	{"logical", "neutral"},
	{"emotional", "neutral"},
	{"troubled", "unhappy"},
	{"panicked", "worried"},
	{"nice", "happy"},
	{"cheerful", "happy"},
	{"emotionless", "neutral"},
	{"gloomy", "unhappy"},
	{"ambivalent", "neutral"},
	{"envious", "neutral"},
	{"vengeful", "angry"},
	{"fearful", "worried"},
	{"enraged", "angry"},
	{"sheepish", "happy"},
	{"belligerent", "angry"},
	{"obnoxious", "neutral"},
	{"fastidious", "neutral"},
	{"squeamish", "unhappy"},
	{"dainty", "neutral"},
	{"dignified", "neutral"},
	{"haughty", "neutral"},
	{"obscure", "neutral"},
	{"goofy", "happy"},
	{"silly", "happy"},
	{"disdainful", "neutral"},
	{"contemptuous", "neutral"},
	{"diplomatic", "neutral"},
	{"wary", "neutral"},
	{"malevolent", "angry"},
	{"hurried", "neutral"},
	{"patient", "neutral"},
	{"firm", "neutral"},
	{"meditating", "meditating"},
	{"entertained", "entertained"}
};

class Moods {
public:
	static const char* getName(uint8 moodid) {
		return MoodNames[moodid][0];
	}
};

#endif /* MOODS_H_ */
