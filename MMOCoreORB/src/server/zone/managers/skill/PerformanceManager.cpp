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
#include "server/zone/objects/player/sui/callbacks/SelectPerformanceSuiCallback.h"

PerformanceManager::PerformanceManager() :
	Logger("PerformanceManager") {
	loadPerformances();
	loadPerformEffects();
}

PerformanceManager::~PerformanceManager() {
	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i)
			delete performances->getUnsafe(i);

		delete performances;

		performances = nullptr;
	}

	if (performEffects != nullptr) {
		for (int i = 0; i < performEffects->size(); ++i)
			delete performEffects->getUnsafe(i);

		delete performEffects;

		performEffects = nullptr;
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

void PerformanceManager::loadPerformEffects() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/performance/perform_effect.iff");

	if (iffStream == nullptr) {
		error("Could not open performance effect datatable.");
		return;
	}

	DataTableIff dtable;
	dtable.readObject(iffStream);

	delete iffStream;

	performEffects = new Vector<PerformEffect*> ();
	for (int i = 0; i < dtable.getTotalRows(); ++i) {
		DataTableRow* row = dtable.getRow(i);

		PerformEffect* effect = new PerformEffect();
		effect->parseDataTableRow(i+1, row);
		performEffects->add(effect);
	}

	info("Loaded " + String::valueOf(performEffects->size()) + " performance effects.", true);
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

			if (ret->isDance() && ret->getName().toLowerCase() == name.toLowerCase())
				return ret;
		}
	}

	return nullptr;
}

Performance* PerformanceManager::getSong(const String& name, int instrumentType) {
	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* ret = performances->get(i);

			if (ret->isMusic() && ret->getName().toLowerCase() == name.toLowerCase()
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

		if (perf->getType() == performanceType && perf->getName().toLowerCase() == performanceName.toLowerCase() && perf->getInstrumentAudioId() == instrumentType)
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

PerformEffect* PerformanceManager::getPerformEffect(int effectId, int effectLevel) {
	if (performEffects == nullptr)
		return nullptr;

	for (int i = 0; i < performEffects->size(); ++i) {
		PerformEffect* effect = performEffects->get(i);

		if (effect->getEffectId() == effectId && effect->getEffectLevel() == effectLevel)
			return effect;
	}

	return nullptr;
}

String PerformanceManager::getInstrumentFromIndex(int index) {
	Performance* performance = getPerformanceFromIndex(index);

	if (performance == nullptr)
		return "";

	return performance->getRequiredInstrument();
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

		if (perf->getInstrumentAudioId() == instrumentType && perf->getName().toLowerCase() == performanceName.toLowerCase())
			return perf->getPerformanceIndex();
	}

	return 0;
}

void PerformanceManager::sendAvailablePerformances(CreatureObject* player, int performanceType, bool bandCommand) {
	Reference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	Reference<Instrument*> instrument = player->getPlayableInstrument();

	if (performanceType == PerformanceType::MUSIC && instrument == nullptr) {
		performanceMessageToSelf(player, nullptr, "performance", "music_no_instrument"); // You must have an instrument equipped to play music.
		return;
	}

	int instrumentType = 0;

	if (instrument != nullptr)
		instrumentType = instrument->getInstrumentType();

	Reference<SuiListBox*> sui = new SuiListBox(player, SuiWindowType::PERFORMANCE_SELECT);
	sui->setCallback(new SelectPerformanceSuiCallback(player->getZoneServer(), performanceType, bandCommand));

	if (performanceType == PerformanceType::DANCE) {
		sui->setPromptTitle("@performance:available_dances");
		sui->setPromptText("@performance:select_dance");
	} else {
		sui->setPromptTitle("@performance:available_songs"); // Available Songs
		sui->setPromptText("@performance:select_song"); // Select a song to play.
	}

	if (performances != nullptr) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* perf = performances->get(i);

			if (perf->isMusic() && (performanceType != PerformanceType::MUSIC || instrumentType != perf->getInstrumentAudioId()))
				continue;

			if (perf->isDance() && performanceType != PerformanceType::DANCE)
				continue;

			int perfIndex = perf->getPerformanceIndex();

			if (perf->isMusic() && !canPlaySong(player, perfIndex))
				continue;

			if (perf->isDance() && !canPerformDance(player, perfIndex))
				continue;

			String perfName = perf->getName();

			String displayName = perfName.subString(0,1).toUpperCase() + perfName.subString(1);

			sui->addMenuItem(displayName);
		}
	}

	ghost->addSuiBox(sui);
	player->sendMessage(sui->generateMessage());
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
	case Instrument::SLITHERHORN:
		instrument = "slitherhorn";
		break;
	case Instrument::FIZZ:
		instrument = "fizz";
		break;
	case Instrument::FANFAR:
		instrument = "fanfar";
		break;
	case Instrument::KLOOHORN:
		instrument = "kloohorn";
		break;
	case Instrument::MANDOVIOL:
		instrument = "mandoviol";
		break;
	case Instrument::TRAZ:
		instrument = "traz";
		break;
	case Instrument::BANDFILL:
		instrument = "bandfill";
		break;
	case Instrument::FLUTEDROOPY:
		instrument = "flutedroopy";
		break;
	case Instrument::OMNIBOX:
		instrument = "omnibox";
		break;
	case Instrument::NALARGON:
		instrument = "nalargon";
		break;
	default:
		//sendSystemMessage("Bad instrument type.");
		break;
	}

	return instrument;
}

String PerformanceManager::getProperInstrumentName(int instrumentType) {
	String instrument;

	switch (instrumentType) {
	case Instrument::SLITHERHORN:
		instrument = "Slitherhorn";
		break;
	case Instrument::FIZZ:
		instrument = "Fizzz";
		break;
	case Instrument::FANFAR:
		instrument = "Fanfar";
		break;
	case Instrument::KLOOHORN:
		instrument = "Kloo Horn";
		break;
	case Instrument::MANDOVIOL:
		instrument = "Mandoviol";
		break;
	case Instrument::TRAZ:
		instrument = "Traz";
		break;
	case Instrument::BANDFILL:
		instrument = "Bandfill";
		break;
	case Instrument::FLUTEDROOPY:
		instrument = "Chidinkalu Horn";
		break;
	case Instrument::OMNIBOX:
		instrument = "Ommni Box";
		break;
	case Instrument::NALARGON:
		instrument = "Nalargon";
		break;
	default:
		break;
	}

	return instrument;
}

int PerformanceManager::getInstrumentId(const String& instrument) {
	if (instrument == "traz") {
		return InstrumentImplementation::TRAZ;
	} else if (instrument == "slitherhorn") {
		return InstrumentImplementation::SLITHERHORN;
	} else if (instrument == "fanfar") {
		return InstrumentImplementation::FANFAR;
	} else if (instrument == "chidinkalu") {
		return InstrumentImplementation::FLUTEDROOPY;
	} else if (instrument == "kloohorn") {
		return InstrumentImplementation::KLOOHORN;
	} else if (instrument == "fizz") {
		return InstrumentImplementation::FIZZ;
	} else if (instrument == "bandfill") {
		return InstrumentImplementation::BANDFILL;
	} else if (instrument == "omnibox") {
		return InstrumentImplementation::OMNIBOX;
	} else if (instrument == "nalargon") {
		return InstrumentImplementation::NALARGON;
	} else if (instrument == "mandoviol") {
		return InstrumentImplementation::MANDOVIOL;
	} else {
		return -1;
	}
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

void PerformanceManager::performanceMessageToDroidOwner(CreatureObject* droid, CreatureObject* target, const String& table, const String& text) {
	ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();

	if (owner == nullptr)
		return;

	performanceMessageToPlayer(owner, droid, target, table, text);
}
