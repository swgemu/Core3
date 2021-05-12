/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "PerformanceManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

PerformanceManager::PerformanceManager() :
	Logger("PerformanceManager") {
	loadPerformances();
}

PerformanceManager::~PerformanceManager() {
	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i)
			delete performances->getUnsafe(i);

		delete performances;

		performances = nullptr;
	}
}

void PerformanceManager::loadPerformances() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/performance/performance.iff");

	if (iffStream == nullptr) {
		error("Could not open performances datatable.");
		return;
	}

	DataTableIff dtable;
	dtable.readObject(iffStream);

	delete iffStream;

	performances = new Vector<Performance*> ();
	for (int i = 0; i < dtable.getTotalRows(); ++i) {
		DataTableRow* row = dtable.getRow(i);

		Performance* performance = new Performance();
		performance->parseDataTableRow(i+1, row);
		performances->add(performance);
	}

	info("Loaded " + String::valueOf(performances->size()) + " performances.", true);
}

Vector<Performance*> PerformanceManager::getPerformanceListFromMod(const String& requiredSkillMod, int playerSkillModValue, int instrument) {
	String instrumentName = "";
	if (instrument != 0)
		instrumentName = getInstrument(instrument);

	Vector<Performance*> performanceList;

	if (performances != nullptr) {

		for (int i = 0; i < performances->size(); ++i) {
			Performance* perform = performances->get(i);

			if (perform->getRequiredSkillMod() != requiredSkillMod || perform->getRequiredSkillModValue() > playerSkillModValue)
				continue;

			if (instrumentName != "") {
				//Should be a music call, look only for performances with that instrument
				if (instrumentName == perform->getRequiredInstrument())
					performanceList.add(perform);
			} else {
				//Should be a dance call
				performanceList.add(perform);
			}
		}

	}

	return performanceList;
}

Performance* PerformanceManager::getDance(const String& name) {
	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* ret = performances->get(i);

			if (ret->isDance() && ret->getName() == name)
				return ret;
		}
	}

	return nullptr;
}

Performance* PerformanceManager::getSong(const String& name, int instrumentType) {
	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* ret = performances->get(i);

			if (ret->isMusic() && ret->getName() == name
					&& ret->getInstrumentAudioId() == instrumentType)
				return ret;
		}
	}
	return nullptr;
}

int PerformanceManager::getPerformanceIndex(int performanceType, const String& performanceName, int instrumentType) {
	if (performances == nullptr)
		return 0;

	for (int i = 0; i < performances->size(); ++i) {
		Performance* perf = performances->get(i);

		if (perf->getType() == performanceType && perf->getName() == performanceName && perf->getInstrumentAudioId() == instrumentType)
			return perf->getPerformanceIndex();
	}

	return 0;
}

Performance* PerformanceManager::getPerformanceFromIndex(int index) {
	if (performances == nullptr)
		return nullptr;

	for (int i = 0; i < performances->size(); ++i) {
		Performance* perf = performances->get(i);

		if (perf->getPerformanceIndex() == index)
			return perf;
	}

	return nullptr;
}

int PerformanceManager::getMatchingPerformanceIndex(int performanceIndex, int instrumentType) {
	if (performances == nullptr)
		return 0;

	Performance* performance = getPerformanceFromIndex(performanceIndex);

	if (performance == nullptr)
		return 0;

	String performanceName = performance->getName();

	for (int i = 0; i < performances->size(); ++i) {
		Performance* perf = performances->get(i);

		if (!perf->isMusic())
			continue;

		if (perf->getInstrumentAudioId() == instrumentType && perf->getName() == performanceName)
			return perf->getPerformanceIndex();
	}

	return 0;
}

void PerformanceManager::sendAvailableSongs(CreatureObject* player) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Reference<Instrument*> instrument = player->getPlayableInstrument();

	if (instrument == nullptr) {
		player->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
		return;
	}

	Reference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::MUSIC_START);
	sui->setPromptTitle("@performance:available_songs"); // Available Songs
	sui->setPromptText("@performance:select_song"); // Select a song to play.

	const AbilityList* list = ghost->getAbilityList();

	for (int i = 0; i < list->size(); ++i) {
		Ability* ability = list->get(i);

		String abilityName = ability->getAbilityName();

		if (abilityName.indexOf("startMusic") != -1) {
			int args = abilityName.indexOf("+");

			if (args != -1) {
				String arg = abilityName.subString(args + 1);

				sui->addMenuItem(arg);
			}
		}
	}

	ghost->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
}

void PerformanceManager::sendAvailableDances(CreatureObject* player) {
	// TODO: Sui callback
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	ManagedReference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::DANCING_START);
	sui->setPromptTitle("@performance:available_dances");
	sui->setPromptText("@performance:select_dance");

	const AbilityList* list = ghost->getAbilityList();

	for (int i = 0; i < list->size(); ++i) {
		Ability* ability = list->get(i);

		String abilityName = ability->getAbilityName();

		if (abilityName.indexOf("startDance") != -1) {
			int args = abilityName.indexOf("+");

			if (args != -1) {
				String arg = abilityName.subString(args + 1);

				sui->addMenuItem(arg);
			}
		}
	}

	ghost->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());

	return;
}

bool PerformanceManager::canPlayInstrument(CreatureObject* player, int instrumentType) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	String instr = getInstrument(instrumentType);

	return ghost->hasAbility(instr);
}

bool PerformanceManager::canPlaySong(CreatureObject* player, const String& name) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	String fullString = String("startMusic") + "+" + name;

	return ghost->hasAbility(fullString);
}

bool PerformanceManager::canPlaySong(CreatureObject* player, int performanceIndex) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	Performance* performance = getPerformanceFromIndex(performanceIndex);

	if (performance == nullptr)
		return false;

	return ghost->hasAbility(performance->getRequiredSong());
}

bool PerformanceManager::canPerformDance(CreatureObject* player, int performanceIndex) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	Performance* performance = getPerformanceFromIndex(performanceIndex);

	if (performance == nullptr)
		return false;

	return ghost->hasAbility(performance->getRequiredDance());
}

String PerformanceManager::getDanceAnimation(int performanceIndex) {
	Performance* performance = getPerformanceFromIndex(performanceIndex);

	if (performance == nullptr)
		return "";

	return "dance_" + String::valueOf(performance->getDanceVisualId());
}

String PerformanceManager::getInstrumentAnimation(int instrumentType) {
	String instrumentAnimation = "";

	switch (instrumentType) {
	case Instrument::SLITHERHORN:
		instrumentAnimation = "music_3";
		break;
	case Instrument::FIZZ:
		instrumentAnimation = "music_3";
		break;
	case Instrument::FANFAR:
		instrumentAnimation = "music_3";
		break;
	case Instrument::KLOOHORN:
		instrumentAnimation = "music_3";
		break;
	case Instrument::MANDOVIOL:
		instrumentAnimation = "music_5";
		break;
	case Instrument::TRAZ:
		instrumentAnimation = "music_3";
		break;
	case Instrument::BANDFILL:
		instrumentAnimation = "music_1";
		break;
	case Instrument::FLUTEDROOPY:
		instrumentAnimation = "music_3";
		break;
	case Instrument::OMNIBOX:
		instrumentAnimation = "music_4";
		break;
	case Instrument::NALARGON:
		instrumentAnimation = "music_2";
		break;
	default:
		break;
	}

	return instrumentAnimation;
}

String PerformanceManager::getInstrument(int instrumentType) {
	String instrument;

	switch (instrumentType) {
	case Instrument::SLITHERHORN: //SLITHERHORN: yeah!
		instrument = "slitherhorn";
		break;
	case Instrument::FIZZ: // yeah
		instrument = "fizz";
		break;
	case Instrument::FANFAR: //FANFAR yeah
		instrument = "fanfar";
		break;
	case Instrument::KLOOHORN: // yeah
		instrument = "kloohorn";
		break;
	case Instrument::MANDOVIOL: //MANDOVIOL
		instrument = "mandoviol";
		break;
	case Instrument::TRAZ: //TRAZ yeah
		instrument = "traz";
		break;
	case Instrument::BANDFILL: // yeah
		instrument = "bandfill";
		break;
	case Instrument::FLUTEDROOPY: //
		instrument = "flutedroopy";
		break;
	case Instrument::OMNIBOX: //OMNIBOX:
		instrument = "omnibox";
		break;
	case Instrument::NALARGON: //NALARGON:
		instrument = "nalargon";
		break;
	default:
		//sendSystemMessage("Bad instrument type.");
		break;
	}

	return instrument;
}


void PerformanceManager::performanceMessageToSelf(CreatureObject* actor, CreatureObject* target, const String& table, const String& text) {
	performanceMessageToPlayer(actor, actor, target, table, text);
}

void PerformanceManager::performanceMessageToBand(CreatureObject* actor, CreatureObject* target, const String& table, const String& text) {
	ManagedReference<GroupObject*> group = actor->getGroup();

	if (group == nullptr)
		return;

	for (int i = 0; i < group->getGroupSize(); i++) {
		ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

		if (groupMember == nullptr || !groupMember->isPlayerCreature() || groupMember == actor)
			continue;

		performanceMessageToPlayer(groupMember, actor, target, table, text);
	}
}

void PerformanceManager::performanceMessageToBandPatrons(CreatureObject* actor, CreatureObject* target, const String& table, const String& text) {
	ManagedReference<GroupObject*> group = actor->getGroup();

	if (group == nullptr)
		return;

	for (int i = 0; i < group->getGroupSize(); i++) {
		ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

		if (groupMember == nullptr || !groupMember->isPlayerCreature() || groupMember == actor)
			continue;

		performanceMessageToPatrons(groupMember, target, table, text);
	}
}

void PerformanceManager::performanceMessageToPatrons(CreatureObject* actor, CreatureObject* target, const String& table, const String& text) {
	ManagedReference<EntertainingSession*> session = actor->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

	if (session == nullptr)
		return;

	SortedVector<ManagedReference<CreatureObject*> > patrons = session->getPatrons();

	if (patrons.size() == 0)
		return;

	for (int i = 0; i < patrons.size(); i++) {
		ManagedReference<CreatureObject*> patron = patrons.get(i);

		if (patron == nullptr)
			continue;

		performanceMessageToPlayer(patron, actor, target, table, text);
	}
}

void PerformanceManager::performanceMessageToPlayer(CreatureObject* player, CreatureObject* actor, CreatureObject* target, const String& table, const String& text) {
	StringIdChatParameter message;
	message.setStringId(table, text);

	if (actor != nullptr)
		message.setTU(actor->getCustomObjectName());

	if (target != nullptr)
		message.setTT(target->getCustomObjectName());

	player->sendSystemMessage(message);
}
