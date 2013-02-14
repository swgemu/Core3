/*
 * GCWManagerImplementation.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: root
 */
#include "GCWManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "system/util/SortedVector.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "CheckGCWTask.h"

#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/tangible/terminal/components/TurretControlTerminalDataComponent.h"
#include "server/zone/objects/installation/components/MinefieldDataComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "StartVulnerabilityTask.h"
#include "EndVulnerabilityTask.h"
#include "BaseDestructionTask.h"

#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

#include "server/zone/objects/player/sui/callbacks/HQDefenseStatusSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/HQSendResetVerificationSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/JamUplinkSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/OverrideTerminalSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PowerRegulatorSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/RemoveDefenseSuiCallback.h"

#include "server/zone/managers/structure/StructureManager.h"

#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/creature/AiAgent.h"

#include "server/zone/objects/installation/InstallationObject.h"

#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/objects/player/sui/callbacks/DonateDefenseSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/SelectTurretDonationSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/TurretControlSuiCallback.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"

#define DEBUG_GCW

int GCWManagerImplementation::gcwCheckTimer = 3600;
int GCWManagerImplementation::vulnerabilityDuration = 7200;
int GCWManagerImplementation::vulnerabilityFrequency = 172800;
int GCWManagerImplementation::resetTimer = 604800;
int GCWManagerImplementation::sliceCooldown = 120;
int GCWManagerImplementation::totalDNASamples = 10;
int GCWManagerImplementation::dnaMatchesRequired = 28;
int GCWManagerImplementation::destructionTimer = 600;
int GCWManagerImplementation::maxBases = -1;
int GCWManagerImplementation::overtCooldown = 300;
int GCWManagerImplementation::reactvationTimer = 300;
int GCWManagerImplementation::turretAutoFireTimeout = 120;
int GCWManagerImplementation::maxBasesPerPlayer = 3;
int GCWManagerImplementation::bonusXP = 15;
int GCWManagerImplementation::bonusDiscount = 30;
VectorMap<String, int> GCWManagerImplementation::baseValue;

void GCWManagerImplementation::initialize(){
	// TODO: initialize things

	// TODO: add this to config file
	this->addDNAHash("A","T");
	this->addDNAHash("T","A");

	this->addDNAHash("C","G");
	this->addDNAHash("G","C");


}

void GCWManagerImplementation::start(){

	CheckGCWTask* task = new CheckGCWTask(_this.get());
	loadLuaConfig();
	task->schedule(this->gcwCheckTimer * 1000);
	initialize();
}

void GCWManagerImplementation::loadLuaConfig(){
	if(maxBases >= 0)
		return;

	info("Loading gcw configuration file.", true);

	Lua* lua = new Lua();
	lua->init();
	lua->runFile("scripts/managers/gcw_manager.lua");

	gcwCheckTimer = lua->getGlobalInt("gcwCheckTimer");
	vulnerabilityDuration = lua->getGlobalInt("vulnerabilityDuration");
	vulnerabilityFrequency = lua->getGlobalInt("vulnerabilityFrequency");
	resetTimer = lua->getGlobalInt("resetTimer");
	sliceCooldown = lua->getGlobalInt("sliceCooldown");
	totalDNASamples = lua->getGlobalInt("totalDNASamples");
	dnaMatchesRequired = lua->getGlobalInt("DNAMatchesRequired");
	destructionTimer = lua->getGlobalInt("destructionTimer");
	maxBases = lua->getGlobalInt("maxBases");
	overtCooldown = lua->getGlobalInt("overtCooldown");
	reactvationTimer = lua->getGlobalInt("reactvationTimer");
	turretAutoFireTimeout = lua->getGlobalInt("turretAutoFireTimeout");
	maxBasesPerPlayer = lua->getGlobalInt("maxBasesPerPlayer");
	bonusXP = lua->getGlobalInt("bonusXP");
	bonusDiscount = lua->getGlobalInt("bonusDiscount");

	LuaObject pointsObject = lua->getGlobalObject("HQValues");

	if(pointsObject.isValidTable()){

		for(int i = 1; i <= pointsObject.getTableSize(); ++i){
			LuaObject baseObject = pointsObject.getObjectAt(i);
			if(baseObject.isValidTable()){
				String templateString = baseObject.getStringAt(1);
				int pointsValue = baseObject.getIntAt(2);
				//info("Template: " + templateString + " point value = " + String::valueOf(pointsValue),true);
				addPointValue(templateString, pointsValue);
			}
			baseObject.pop();

		}
	}

	info("Loaded " + String::valueOf(baseValue.size()) + " GCW base scoring values.",true);


}

// PRE: Nothing needs to be locked
// should only be called by the startvulnerabilityTask or when loading from the db in the middle of vuln
void GCWManagerImplementation::startVulnerability(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	info("BASE " + String::valueOf(building->getObjectID()) + " IS NOW VULNERABLE " + Time().getFormattedTime(),true);

	renewUplinkBand(building);

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}

	Locker block(building);
	baseData->setLastVulnerableTime(baseData->getNextVulnerableTime());
	//this->initializeNewVulnerability(baseData);
	block.release();

	if(!this->dropStartTask(building->getObjectID()))
		info("No starttask found to drop while starting vulnerability");

	this->scheduleVulnerabilityEnd(building);
	building->broadcastCellPermissions();


}

void GCWManagerImplementation::initializeNewVulnerability(BuildingObject* building){
	Locker _lock(building);
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	if(baseData == NULL)
		return;

	initializeNewVulnerability(baseData);
	_lock.release();
}

// PRE:  building / objectdatacomponent are locked
void GCWManagerImplementation::initializeNewVulnerability(DestructibleBuildingDataComponent* baseData){
	baseData->setSliceRepairTime(Time(0));
	baseData->setTerminalDamaged(false);
	baseData->setSampleMatches(0);
	baseData->setState(DestructibleBuildingDataComponent::VULNERABLE);
	baseData->setSystemDNAString("");
	baseData->turnAllSwitchesOn();
	baseData->setRebootFinishTime(Time(0));
}

// PRE: nothing needs to be locked!
void GCWManagerImplementation::scheduleVulnerabilityStart(BuildingObject* building){

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if(!this->hasBase(building)){
		//info("Not scheduling start task.  Building is not in the base list");
		return;
	}

	if(baseData == NULL)
		return;

	info("Base " + String::valueOf(building->getObjectID()) + " scheduling next vulnerable time for " + baseData->getNextVulnerableTime().getFormattedTime(),true);

	Time vulnTime = baseData->getNextVulnerableTime();
	int64 vulnDif = vulnTime.miliDifference();
	if(vulnDif >= 0){
		info("Base: " + String::valueOf(building->getObjectID()) + " Cannot schedule start time.  IT has already passed",true);
		return;
	}

	Reference<Task*> newTask = new StartVulnerabilityTask(_this.get(), building);
	newTask->schedule(fabs(vulnDif));
	this->addStartTask(building->getObjectID(),newTask);


}

// changes timers and schedules nextVulnerabilityStart task
void GCWManagerImplementation::endVulnerability(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	if(baseData == NULL){
		return;
	}

	info("BASE " + String::valueOf(building->getObjectID()) + " IS NO LONGER VULNERABLE " + Time().getFormattedTime(),true);

	Locker block(building);

	baseData->setLastVulnerableTime(baseData->getNextVulnerableTime());

	Time nextTime;

	if (baseData->getLastVulnerableTime().getTime() == 0)
		nextTime = baseData->getNextVulnerableTime();
	else
		nextTime = baseData->getLastVulnerableTime();

	int64 intPeriodsPast = (fabs(nextTime.miliDifference())) / (this->vulnerabilityFrequency*1000);

	// TODO: use periodspast to get the amount of time to add and avoid the loop
	while(nextTime.isPast()){
		//info("adding time to nextvuln", true);
		nextTime.addMiliTime(vulnerabilityFrequency*1000);
	}

	baseData->setNextVulnerableTime(nextTime);
	nextTime.addMiliTime(vulnerabilityDuration*1000);
	baseData->setVulnerabilityEndTime(nextTime);
	baseData->setState(DestructibleBuildingDataComponent::INVULNERABLE);
	baseData->clearDNAProfiles();

	block.release();

	// TODO: check the destruction task list and remove the destruction task
	if(!this->dropEndTask(building->getObjectID()))
		info("No endtask found to remove while scheduling new startvulnerability task",true);

	// schedule
	this->scheduleVulnerabilityStart(building);

	building->broadcastCellPermissions();

}

// only call if the last expired time has already past and we need the timers
// back up to date.  usually after a long server down or something
void GCWManagerImplementation::refreshExpiredVulnerability(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		return;
	}

	Time thisStartTime(baseData->getLastVulnerableTime());

#ifdef GCW_DEBUG
	   info("BEfore Refreshed Current time is  " + Time().getFormattedTime(),true);
		info("before Refreshed NextStart is     " + thisStartTime.getFormattedTime(),true);
		info("before Refreshed Next end time is " + baseData->getVulnerabilityEndTime().getFormattedTime(),true);
#endif

	while( (thisStartTime.getTime() + vulnerabilityFrequency) <= Time().getTime() ){
		//info("looped",true);
		thisStartTime.addMiliTime(vulnerabilityFrequency*1000);
	}

	info("Looped starttime to get " + thisStartTime.getFormattedTime(),true);

	// test time is the vulnerability end time for this current period.  it can be past or presetnt.
	Time testTime(thisStartTime);
	testTime.addMiliTime(vulnerabilityDuration*1000);


	Locker block(building);

	if(!testTime.isPast()) {
		// if we're still in a vuln period

		info("Loaded while vulnerable in refresh",true);
		baseData->setLastVulnerableTime(thisStartTime);

		// testTime should the same thing as vEnd
		Time vEnd(thisStartTime);
		vEnd.addMiliTime((vulnerabilityDuration*1000));
		baseData->setVulnerabilityEndTime(vEnd);


		Time nStartTime(thisStartTime);
		nStartTime.addMiliTime(vulnerabilityFrequency*1000);
		baseData->setNextVulnerableTime(nStartTime);

		if(baseData == NULL){
			error("ERROR:  could not get base data for base");
			return;
		}

		this->initializeNewVulnerability(baseData);
		bool wasDropped = gcwStartTasks.drop(building->getObjectID());

		/*
		info("after Chaging data lastStart to      " + baseData->getLastVulnerableTime().getFormattedTime(),true);
		info("after Changing ddata current time is " + Time().getFormattedTime(),true);
		info("after Changing data nextStart to     " + baseData->getNextVulnerableTime().getFormattedTime(),true);
		info("after changing data nextEnd  to      " + baseData->getVulnerabilityEndTime().getFormattedTime(),true);
		*/

		block.release();

		this->scheduleVulnerabilityEnd(building);


	} else{
		info("Loaded " + String::valueOf(building->getObjectID()) + " while invulnerable between vuln and the next start",true);
		baseData->setLastVulnerableTime(thisStartTime);
		Time nStartTime(thisStartTime);
		nStartTime.addMiliTime(vulnerabilityFrequency*1000);
		baseData->setNextVulnerableTime(nStartTime);

		Time vEnd(nStartTime);
		vEnd.addMiliTime(vulnerabilityDuration*1000);
		baseData->setVulnerabilityEndTime(vEnd);

		baseData->setState(DestructibleBuildingDataComponent::INVULNERABLE);
		/*
		info("after Chaging data lastStart to  " + baseData->getLastVulnerableTime().getFormattedTime(),true);
		info("after changing current tm  is    " + Time().getFormattedTime(),true);
		info("after Changing data nextStart to " + baseData->getNextVulnerableTime().getFormattedTime(),true);
		info("after changing data nextEnd  to  " + baseData->getVulnerabilityEndTime().getFormattedTime(),true);
		*/

		block.release();

		this->scheduleVulnerabilityStart(building);
	}

	renewUplinkBand(building);

}

// PRE:  nothing needs to be locked... building NOT locked
void GCWManagerImplementation::scheduleVulnerabilityEnd(BuildingObject* building){

	if(!this->hasBase(building)){
		info("Not scheduling end task.  Building is not in the base list");
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if(baseData == NULL)
		return;

	Time endTime = baseData->getVulnerabilityEndTime();
	int64 endDif = endTime.miliDifference();

	if (endDif >= 0){
		info("error scheduing end time.  it has already passed");
		return;
	}

	info("Scheduling end  vulnerability for " + String::valueOf(endDif));
	Reference<Task*> newTask = new EndVulnerabilityTask(_this.get(), building);

	newTask->schedule(fabs(endDif));

	this->addEndTask(building->getObjectID(),newTask);
}

// no locks needed
void GCWManagerImplementation::scheduleBaseDestruction(BuildingObject* building, CreatureObject* creature){
	info("Scheduling destruction",true);

	if(this->isBaseVulnerable(building) && !this->hasDestroyTask(building->getObjectID()) ){


		DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

		if(baseData == NULL){
			error("ERROR:  could not get base data for base");
			return;
		}

		if(!baseData->getRebootFinishTime().isPast()){
			creature->sendSystemMessage("You must wait for the facility to finish rebooting before activating the overload again");
			return;
		}

		Locker block(building,creature);

		StringIdChatParameter destroyMessage("@faction/faction_hq/faction_hq_response:terminal_response40"); // COUNTDOWN INITIATED: estimated time to detonation: %DI minutes.
		int minutesRemaining = ceil(this->destructionTimer/60);
		destroyMessage.setDI(minutesRemaining);
		broadcastBuilding(building, destroyMessage);
		baseData->setState(DestructibleBuildingDataComponent::SHUTDOWNSEQUENCE);
		block.release();


		Locker _lock(_this.get(),creature);

		Reference<Task*> newTask = new BaseDestructionTask(_this.get(), building);
		//newTask->schedule(this->destructionTimer*1000);
		newTask->schedule(60000);
		this->addDestroyTask(building->getObjectID(),newTask);

	}
}

void GCWManagerImplementation::abortShutdownSequence(CreatureObject* creature, BuildingObject* building){

	if(!creature->checkCooldownRecovery("declare_overt_cooldown")){
		StringIdChatParameter params("@faction/faction_hq/faction_hq_response:terminal_response42"); // Before issuing the shutdown, you must have been in special forces for at least %TO
		int timer = overtCooldown / 60;
		params.setTO(String::valueOf(timer) + " minutes");
		creature->sendSystemMessage(params); // Before issuing the shutdown, you must hve beenin Special forces for at least %TO
		return;
	}

	if(this->isBaseVulnerable(building) && this->hasDestroyTask(building->getObjectID())){
		//Reference<Task*> oldDestroyTask = gcwDestroyTasks.get(building->getObjectID());
		Reference<Task*> oldDestroyTask = this->getDestroyTask(building->getObjectID());
		if(oldDestroyTask != NULL){
			info("deleting destroy task",true);
			oldDestroyTask->cancel();
			this->dropDestroyTask(building->getObjectID());
		}

		DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

		if(baseData == NULL){
			error("ERROR:  could not get base data for base");
			return;
		}

		Locker block(building, creature);

		baseData->setState(DestructibleBuildingDataComponent::OVERLOADED);
		Time finishTime = Time();
		finishTime.addMiliTime(reactvationTimer * 1000);
		baseData->setRebootFinishTime(finishTime);

		StringIdChatParameter reloadMessage;
		reloadMessage.setStringId("@faction/faction_hq/faction_hq_response:terminal_response07"); // COUNTDOWN ABORTED: FACILITY SHUTTIGN DOWN
		broadcastBuilding(building, reloadMessage);
	}
}

void GCWManagerImplementation::doBaseDestruction(StructureObject* structure){
	if(structure == NULL)
		return;

	BuildingObject* building = cast<BuildingObject*>(structure);

	if(building != NULL)
		doBaseDestruction(building);
}
void GCWManagerImplementation::doBaseDestruction(BuildingObject* building){
	if(building == NULL)
		return;

	Reference<Task*> oldEndTask = this->getDestroyTask(building->getObjectID());

	if(oldEndTask != NULL){
			BaseDestructionTask* dTask = cast<BaseDestructionTask*>(oldEndTask.get());
			if(dTask != NULL && dTask->getCountdown() > 0){
				oldEndTask->reschedule(60000);
				StringIdChatParameter msg("@faction/faction_hq/faction_hq_response:terminal_response39"); // Countdown: Estimated time to detonation: %DI minutes
				int minutesRemaining = dTask->getCountdown();
				msg.setDI(minutesRemaining);
				broadcastBuilding(building, msg);
				return;
			}

	}
	info("Destroying Base " + String::valueOf(building->getObjectID()),true);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}
	Locker locker(_this.get());
	Locker block(building,_this.get());

	this->unregisterGCWBase(building);

	// need to lock both.  building must be locked for destroyStructure() and then _this is locked when it calls unregister.
	StructureManager::instance()->destroyStructure(building);
}

void GCWManagerImplementation::unregisterGCWBase(BuildingObject* building){

	if(hasBase(building)){
		dropBase(building);

		if(building->getFaction() == IMPERIALHASH)
			imperialBases--;

		else if (building->getFaction() == REBELHASH)
			rebelBases--;

		String templateString = building->getObjectTemplate()->getFullTemplateString();

		int pointsValue = getPointValue(templateString);

		if(pointsValue > -1){
			if(building->getFaction() == REBELHASH)
				setRebelScore(getRebelScore() - pointsValue);
			else if (building->getFaction() == IMPERIALHASH)
				setImperialScore(getImperialScore() - pointsValue);

		} else
			info("ERROR looking up value for GCW Base: " + templateString, true);

	}
	Reference<Task*> oldStartTask = this->getStartTask(building->getObjectID());

	if(oldStartTask != NULL){
		oldStartTask->cancel();
		this->dropStartTask(building->getObjectID());
		info("deleting start task for building " + String::valueOf(building->getObjectID()),true);
	}

	Reference<Task*> oldEndTask = this->getEndTask(building->getObjectID());
	if(oldEndTask != NULL){
		info("deleting the end task for building " + String::valueOf(building->getObjectID()), true);
		oldEndTask->cancel();
		this->dropEndTask(building->getObjectID());
	}

	Reference<Task*> oldDestroyTask = this->getDestroyTask(building->getObjectID());
	if(oldDestroyTask != NULL){
		info("deleting destroy task for building " + String::valueOf(building->getObjectID()),true);
		oldDestroyTask->cancel();
		this->dropDestroyTask(building->getObjectID());
	}

	info("Base " + String::valueOf(building->getObjectID()) + " has been removed",true);
}

void GCWManagerImplementation::performGCWTasks(){


	Locker locker(_this.get());

	if(gcwBaseList.size() == 0) {
		setRebelBaseCount(0);
		setImperialBaseCount(0);
		return;
	}



	info("Performing gcw maintenance for "+ zone->getZoneName());
	int totalBase = gcwBaseList.size();
	int startCount = gcwStartTasks.size();
	int endCount = gcwEndTasks.size();
	int destroyCount = gcwDestroyTasks.size();

	info(String::valueOf(totalBase) + " bases ", true);
	//info("Size of start list is " + String::valueOf(startCount), true);
	//info("Size of end list is   " + String::valueOf(endCount),true);
	//info("Size of destroy list is   " + String::valueOf(destroyCount),true);

	uint64  thisOid;

		int rebelCheck = 0;
	int imperialCheck = 0;

	for(int i = 0; i< gcwBaseList.size();i++){
		thisOid = this->getBase(i)->getObjectID();

		BuildingObject* building = cast<BuildingObject*>(zone->getZoneServer()->getObject(thisOid));

		if(building == NULL)
			continue;

		if(building->getFaction() == REBELHASH)
			rebelCheck++;

		else if (building->getFaction() == IMPERIALHASH)
			imperialCheck++;

		info("Base " + String::valueOf(i) + " id: " + String::valueOf(thisOid) + " - " +   " Start: " + String::valueOf( this->hasStartTask(thisOid) )
				+ " End: " + String::valueOf(this->hasEndTask(thisOid)) + " DESTROY: " + String::valueOf(this->hasDestroyTask(thisOid))
				+ " FACTION:  " + String::valueOf(building->getFaction()),true );

	}

	setRebelBaseCount(rebelCheck);
	setImperialBaseCount(imperialCheck);

	/*
	for(int i = gcwBaseList.size() -1; i >= 0; i--){
		// TODO Sanity check on the task lists etc.
	}
	*/

	CheckGCWTask* task = new CheckGCWTask(_this.get());
	task->schedule(this->gcwCheckTimer * 1000);
}

void GCWManagerImplementation::registerGCWBase(BuildingObject* building, bool initializeBase){
	info("Registering base on " + zone->getZoneName() +  " " + String::valueOf(building->getObjectID()) + " " + String::valueOf(building->getPositionX()) + ", " + String::valueOf(building->getPositionY()),true);
	//info("CurrentTime is " + Time().getFormattedTime(),true);
	if ( !this->hasBase(building)){


		if(building->getFaction() == IMPERIALHASH)
			imperialBases++;
		else if (building->getFaction() == REBELHASH)
			rebelBases++;

		if(initializeBase){

			DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

			if(baseData == NULL){
				info("baseData is null in initialize", true);
				return;
			}

			Locker block(building);
			this->initializeBaseTimers(building);
			this->initializeNewVulnerability(baseData);
			block.release();
			this->addBase(building);
			this->startVulnerability(building);


		} else {
			this->addBase(building);
			checkVulnerabilityData(building);

		}
		//info("contains " + String::valueOf(baseValue.contains(templateString)),true);

		String templateString = building->getObjectTemplate()->getFullTemplateString();

		int pointsValue = getPointValue(templateString);
		info("point value is " + String::valueOf(pointsValue),true);
		if(pointsValue > -1){
			if(building->getFaction() == REBELHASH)
				setRebelScore(getRebelScore() + pointsValue);
			else if (building->getFaction() == IMPERIALHASH)
				setImperialScore(getImperialScore() + pointsValue);

		} else
			info("ERROR looking up value for GCW Base: " + templateString, true);


	}else
		error("Building already in gcwBaseList");

}

// PRE: nothing locked
void GCWManagerImplementation::checkVulnerabilityData(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}

	info("checking vulnerability and verifying.  making necessary changes");
	Time currentTime;

	Time vulnTime = baseData->getNextVulnerableTime();
	Time nextEnd = baseData->getVulnerabilityEndTime();

	int64 vulnDif = vulnTime.miliDifference();
	int64 endDif = nextEnd.miliDifference();



	if(!vulnTime.isPast()) {
		info(zone->getZoneName() + " scheduling building " + String::valueOf(building->getObjectID()) + "vulnerability start " + String::valueOf(fabs(endDif)));
		this->scheduleVulnerabilityStart(building);
	} else if (vulnTime.isPast() && !nextEnd.isPast()) {
		info(zone->getZoneName() + " loading vulnerable base " + String::valueOf(building->getObjectID()) + " with vulnerability in progress");

		// TODO: use old state from the DB im the event of server restart during vuln.
		renewUplinkBand(building);
		this->startVulnerability(building);

	} else if (nextEnd.isPast()) {

		info(zone->getZoneName() + " base " + String::valueOf(building->getObjectID()) + " vuln end time has already passed... need to refresh next vuln times " + String::valueOf(vulnDif));
		this->refreshExpiredVulnerability(building);

	}



}

// PRE: no locks or only lock on building
// sets the bandwidth to guess during jamming of the uplink
void GCWManagerImplementation::renewUplinkBand(BuildingObject* building){

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL) {
		error("ERROR:  could not get base data for base");
		return;
	}

	// 10 possible codes bands to guess
	int secretCode = System::random(0x9);
	//info("New uplink band is " + String::valueOf(secretCode), true);

	Locker block(building);
	baseData->setUplinkBand(secretCode);


}

// pre: building is locked
// initializes times when a base is placed for the first time
void GCWManagerImplementation::initializeBaseTimers(BuildingObject* building){

	// THESE WORK IF YOU DONT WANT A BASE VULN ON PLANT
	// IT DOES THE NEXT ONE
	/*
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL) {
		error("ERROR:  could not get base data for base");
		return;
	}

	baseData->setPlacementTime(Time());
	baseData->setLastVulnerableTime(Time());

	Time nextTime;

	nextTime.addMiliTime(GCWManager::VULNERABILITYFREQUENCY*1000);
	baseData->setNextVulnerableTime(nextTime);

	nextTime.addMiliTime(GCWManager::VULNERABILITYDURATION*1000);
	baseData->setVulnerabilityEndTime(nextTime);

	baseData->setTerminalDamaged(false);
	baseData->setSliceRepairTime(Time(0)); //
	baseData->setLastResetTime(Time(0)); // set it to a long, long time ago
	*/

	// try to do initial vuln on plant
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL) {
		error("ERROR:  could not get base data for base");
		return;
	}

	baseData->setPlacementTime(Time());
	baseData->setLastVulnerableTime(Time());

	Time endTime(baseData->getPlacmenetTime());
	endTime.addMiliTime(this->vulnerabilityDuration*1000);
	baseData->setVulnerabilityEndTime(endTime);

	Time nextVuln(baseData->getPlacmenetTime());
	nextVuln.addMiliTime(this->vulnerabilityFrequency*1000);

	baseData->setTerminalDamaged(false);
	baseData->setSliceRepairTime(Time(0));
	baseData->setLastResetTime(Time(0)); // set it to a long, long time ago


}

DestructibleBuildingDataComponent* GCWManagerImplementation::getDestructibleBuildingData(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = NULL;

	if (building != NULL){
		if(building->isGCWBase()){
			DataObjectComponentReference* data = building->getDataObjectComponent();

			if(data != NULL)
				baseData = cast<DestructibleBuildingDataComponent*>(data->get());
		}
	}

		return baseData;
}

// PRE: nothing is locked
// time of the day
void GCWManagerImplementation::resetVulnerability(CreatureObject* creature, BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;

	if (isBaseVulnerable(building)){
		if(creature != NULL)
			creature->sendSystemMessage("Cannot reset vulnerability while base is vulnerable");

		return;
	}

	Time ttime = baseData->getLastResetTime();

	ttime.addMiliTime(resetTimer*1000);

	if(!ttime.isPast())
	{
		if(creature != NULL)
			creature->sendSystemMessage("Can't reset yet again.  You must wait " + String::valueOf(ttime.miliDifference()/1000));
		return;
	}

	Locker clock(building,creature);

	//info("Resetting vulnerability timer",true);
	baseData->setLastResetTime(Time());

	Time nextTime = Time();

	clock.release();

	Locker glock(_this.get(),creature);
	baseData->setLastVulnerableTime(nextTime);

	nextTime.addMiliTime(vulnerabilityFrequency*1000);
	baseData->setNextVulnerableTime(nextTime.getTime()); // working()

	nextTime.addMiliTime(vulnerabilityDuration*1000);
	baseData->setVulnerabilityEndTime(nextTime.getTime()); // (working)


	Reference<Task*> task = this->getStartTask(building->getObjectID());
	if(task == NULL)
		info("no task scheduled to get in cancel");
	else
	{
		task->cancel();
		this->dropStartTask(building->getObjectID());
	}

	this->scheduleVulnerabilityStart(building);

	if(creature != NULL)
		creature->sendSystemMessage("@hq:vulnerability_reset"); // the vulnerability of this structure has been reset

}

void GCWManagerImplementation::sendTurretAttackListTo(CreatureObject* creature, SceneObject* turretControlTerminal){

	if(turretControlTerminal == NULL || creature == NULL || creature->isInCombat() )
		return;

	PlayerObject* ghost = creature->getPlayerObject();

	if(ghost == NULL)
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TURRET_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(turretControlTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return;

	// get the base data component
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if(baseData == NULL)
		return;

	TurretControlTerminalDataComponent* controlData = getTurretControlDataComponent(turretControlTerminal);

	if(controlData == NULL)
		return;

	uint64 tindex = baseData->getTurretID(controlData->getTurrteIndex());

	if(tindex == 0 || controlData->getTurrteIndex() < 0) {
		creature->sendSystemMessage("@hq:none_active");  //  There are no available turrets to control using this terminal.
		return;
	}
	ZoneServer* server = zone->getZoneServer();

	if(server == NULL)
		return;

	SceneObject* turret = server->getObject(tindex);

	if(turret == NULL || !turret->isTurret()) {
		creature->sendSystemMessage("@hq:none_active"); // There are no available turrets to control using this terminal.
		return;
	}

	TangibleObject* turretObject = cast<TangibleObject*>(turret);
	if(turretObject == NULL)
		return;

	TurretDataComponent* turretData = this->getTurretDataComponent(turret);

	if(turretData == NULL)
		return;

	if(!canUseTurret(turretData, controlData, creature)){
		creature->sendSystemMessage("@hq:in_use");  //  This turret control terminal is already in use."
		return;
	}

	this->generateTurretControlBoxTo(creature, turretObject, turretControlTerminal);

}

TurretDataComponent* GCWManagerImplementation::getTurretDataComponent(SceneObject* turret){
	DataObjectComponentReference* turretComponent = turret->getDataObjectComponent();

	if(turretComponent == NULL)
		return NULL;

	return cast<TurretDataComponent*>(turretComponent->get());
}

TurretControlTerminalDataComponent* GCWManagerImplementation::getTurretControlDataComponent(SceneObject* terminal){
	DataObjectComponentReference* terminalData  = terminal->getDataObjectComponent();

	if(terminalData == NULL)
		return NULL;

	return cast<TurretControlTerminalDataComponent*>(terminalData->get());
}

void GCWManagerImplementation::generateTurretControlBoxTo(CreatureObject* creature, TangibleObject* turret, SceneObject* terminal){
	TurretControlTerminalDataComponent* controlData = getTurretControlDataComponent(terminal);
	if(controlData == NULL)
		return;

	TurretDataComponent* turretData = this->getTurretDataComponent(turret);
	if(turretData == NULL)
		return;

	PlayerObject* ghost = creature->getPlayerObject();
	if(ghost == NULL)
		return;

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TURRET_TERMINAL);
	status->setPromptTitle("@hq:control_title"); //"Turret Control Consule"
	status->setCancelButton(true, "@cancel");
	status->setCallback(new TurretControlSuiCallback(zone->getZoneServer(), turret,terminal));
	status->setOtherButton(true,"@ui:refresh"); // refresh
	status->setOkButton(true,"@hq:btn_attack"); // Attack

	StringIdChatParameter params;
	params.setStringId(("@hq:attack_targets")); // Turret is now attacking %TO.");
	StringBuffer msg;
	msg << "Turret is now targeting: ";

	if(turretData->getManualTarget() != NULL){
		msg << turretData->getManualTarget()->getFirstName();
	}

	status->setPromptText(msg.toString());

	CloseObjectsVector* vec = (CloseObjectsVector*)turret->getCloseObjects();

	SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;

	vec->safeCopyTo(closeObjects);
	WeaponObject* weapon = cast<WeaponObject*>(turret->getSlottedObject("hold_r"));

	if(weapon == NULL)
		return;

	int targetTotal = 0;

	for(int i = 0; i < closeObjects.size(); ++i){
		CreatureObject* creo = closeObjects.get(i).castTo<CreatureObject*>();

		if(creo != NULL && creo->isAttackableBy(turret)){
			if(!CollisionManager::checkLineOfSight(creo, turret)){
				continue;
			}

			if(creo->isPlayerCreature() && turret->getDistanceTo(creo) <= weapon->getMaxRange()) {
				status->addMenuItem(creo->getFirstName() + " - " + String::valueOf((int)turret->getDistanceTo(creo)) + "m",creo->getObjectID());
				targetTotal++;
			}
		}

		if(targetTotal > 20)
			break;
	}

	if( status->getMenuSize() > 0 ) {
		ghost->addSuiBox(status);
		creature->sendMessage(status->generateMessage());

		Locker _lock(terminal, creature);
		controlData->setSuiBoxID(status->getBoxID());
		_lock.release();

		Locker tlock(turret, creature);
		turretData->setController(creature);
		turretData->updateAutoCooldown(turretAutoFireTimeout);

	} else
		creature->sendSystemMessage("@hq:no_targets"); // This turret has no valid targets.
}


bool GCWManagerImplementation::canUseTurret(TurretDataComponent* turretData, TurretControlTerminalDataComponent* controlData, CreatureObject* creature){

	if(turretData->getController() != NULL && turretData->getController() != creature){

		CreatureObject* controllerCreature = turretData->getController();
		PlayerObject* controllerGhost = controllerCreature->getPlayerObject();

		// if there is no manual target, give it to the new guy, close it from the old guy
		if(turretData->getManualTarget() == NULL) {
			// try to close it from the old controller if it's still up
			controllerGhost->closeSuiWindowType(SuiWindowType::HQ_TURRET_TERMINAL);
		}else if(controllerGhost != NULL){

			// if the controller creatures has the same window up
			if(turretData->getManualTarget() != NULL) {
				int controllingSuiBoxID = controlData->getSuiBoxID();

				if(controllingSuiBoxID >= 0){
					// get the sui from the controllerGhost to see if it's still up
					if(controllerGhost->hasSuiBox(controllingSuiBoxID)){
						return false;
					}
				}
			}
		}
	}

	return true;
}

void GCWManagerImplementation::sendStatus(BuildingObject* building, CreatureObject* creature){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(creature==NULL || baseData == NULL)
		return;

	uint64 dif = 0;

	if(isBaseVulnerable(building)) {
		dif = baseData->getVulnerabilityEndTime().getTime() - time(0);
	} else {
		dif = baseData->getNextVulnerableTime().getTime() - time(0);
	}

	int days = floor(dif/86400);
	dif = dif - (days*86400);
	int hours = floor(dif/3600);
	dif = dif - (hours*3600);
	int minutes = ceil(dif/60);

	if(!(building->getPvpStatusBitmask() & CreatureFlag::OVERT)) {
		creature->sendSystemMessage("PvE base is always vulnerable");

	} else if(isBaseVulnerable(building)){
		creature->sendSystemMessage("Vulnerability ends in " + String::valueOf(hours) + " hours and " + String::valueOf(minutes) + " minutes.");
		creature->sendSystemMessage("End time " + baseData->getVulnerabilityEndTime().getFormattedTime());
	} else {
		creature->sendSystemMessage("Base will be vulnerable in " + String::valueOf(days) + " days, " + String::valueOf(hours) + " hours, and " + String::valueOf(minutes) + " minutes");
		creature->sendSystemMessage("Start time " + baseData->getNextVulnerableTime().getFormattedTime());
	}
}

void GCWManagerImplementation::sendBaseDefenseStatus(CreatureObject* creature, BuildingObject* building){
	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	if(ghost==NULL || baseData == NULL)
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("@hq:mnu_defense_status"); //Defense status
	status->setPromptText("@faction/faction_hq/faction_hq_response:terminal_response21"); // If you want to remove a defense select it and press remove
	status->setUsingObject(building);
	status->setCancelButton(true, "@cancel");
	if(creature == building->getOwnerCreatureObject()){
		status->setOtherButton(true,"@ui:permission_remove");
	}
	status->setOkButton(true, "@ok");
	status->setCallback(new HQDefenseStatusSuiCallback(zone->getZoneServer()));

	ZoneServer* zoneServer = zone->getZoneServer();
	if(zoneServer != NULL){
		for(int i =0; i < baseData->getTotalTurretCount();i++){
			ManagedReference<SceneObject*> sceno = zoneServer->getObject(baseData->getTurretID(i));
			if(sceno != NULL && sceno->isTurret()) {

				status->addMenuItem(sceno->getDisplayedName(),sceno->getObjectID());
			} else {
				//status->addMenuItem("Turret " + String::valueOf(i+1) + ": EMPTY");
			}
		}
	}
	//status->addMenuItem("X credits in reserve.");
	//status->addMenuItem("X troops in reserve.");
	//status->addMenuItem("X resources in reserve");
	//status->addMenuItem("X turrets in reserve");
	status->addMenuItem("Child Objects: " + String::valueOf(building->getChildObjects()->size()));
	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());
}

void GCWManagerImplementation::sendJamUplinkMenu(CreatureObject* creature, BuildingObject* building){
	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(ghost==NULL || baseData == NULL)
		return;

	if(!isBaseVulnerable(building))
	{
		creature->sendSystemMessage("Cannot jam uplink now");
		return;
	}

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);

	if(!this->isBandIdentified(building)){

		status->setPromptTitle("@hq:mnu_defense_status"); //Defense status
		status->setPromptText("Select the correct channel"); // DEfense status
		status->setUsingObject(building);
		status->setOkButton(true, "@ok");
		status->setCancelButton(true, "@cancel");
		status->setCallback( new JamUplinkSuiCallback(this->zone->getZoneServer()) );

		for(int i =0;i<10;i++)
			status->addMenuItem("Channel: " + String::valueOf(i+1),9);

	} else{

		status->setPromptTitle("@hq:mnu_defense_status"); //Defense status
		status->setPromptText("Select the correct frequency bandwidth within the channel"); // DEfense status
		status->setUsingObject(building);
		status->setOkButton(true, "@ok");
		status->setCancelButton(true, "@cancel");
		status->setCallback( new JamUplinkSuiCallback(this->zone->getZoneServer()) );

		for(int i =0;i<10;i++)
			status->addMenuItem("Channel " + String::valueOf(i+1),9);

	}


	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());

}

void GCWManagerImplementation::verifyUplinkBand(CreatureObject* creature, BuildingObject* building, int band){
	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	if(ghost==NULL || baseData == NULL)
		return;

	if( band == baseData->getUplinkBand()){

		Locker block(building,creature);

		if(this->isBandIdentified(building))
			baseData->setState(DestructibleBuildingDataComponent::JAMMED);
		else
			baseData->setState(DestructibleBuildingDataComponent::BAND);

		this->renewUplinkBand(building);
		creature->sendSystemMessage("SUCCESS");
		block.release();


	} else if ( band < baseData->getUplinkBand()) {
		if(this->isUplinkJammed(building))
			creature->sendSystemMessage("The selected bandwidth is too low");
		else
			creature->sendSystemMessage("The selected channel is too low");

	} else {
		if(this->isUplinkJammed(building))
			creature->sendSystemMessage("The selected bandwidth is too high");
		else
			creature->sendSystemMessage("The selected channel is too high");
	}

}

void GCWManagerImplementation::sendResetVerification(CreatureObject* creature, BuildingObject* building){

	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );
	if(ghost==NULL || baseData == NULL)
		return;

	if(isBaseVulnerable(building)){
		creature->sendSystemMessage("Cannot reset vulnerability while base is vulnerable");
		return;
	}

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, SuiWindowType::HQ_TERMINAL);
	suiBox->setCallback(new HQSendResetVerificationSuiCallback(this->zone->getZoneServer()));
	suiBox->setPromptTitle("@hq:mnu_reset_vulnerability");
	suiBox->setPromptText("@hq:mnu_reset_vulnerability");
	suiBox->setUsingObject(building);
	suiBox->setCancelButton(true, "@cancel");
	suiBox->setOkButton(true, "@yes");

	ghost->addSuiBox(suiBox);
	creature->sendMessage(suiBox->generateMessage());
}

bool GCWManagerImplementation::isBaseVulnerable(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return false;
	}

	return (baseData->getState() > DestructibleBuildingDataComponent::INVULNERABLE || !(building->getPvpStatusBitmask() & CreatureFlag::OVERT));
}

bool GCWManagerImplementation::isBandIdentified(BuildingObject* building) {
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::BAND);
}
bool GCWManagerImplementation::isUplinkJammed(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::JAMMED);
}

bool GCWManagerImplementation::isSecurityTermSliced(BuildingObject* building){

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

		if(baseData == NULL){
			error("ERROR:  could not get base data for base");
			return false;
		}

		return (baseData->getState() >= DestructibleBuildingDataComponent::SLICED);
}

bool GCWManagerImplementation::isDNASampled(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return false;
	}

	return (baseData->getState() >= DestructibleBuildingDataComponent::DNA);

}

bool GCWManagerImplementation::isPowerOverloaded(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return false;
	}

	return(baseData->getState() >= DestructibleBuildingDataComponent::OVERLOADED);
}

bool GCWManagerImplementation::isShutdownSequenceStarted(BuildingObject* building){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		info("ERROR:  could not get base data for base",true);
		return false;
	}
	//info("State of the base is " + String::valueOf(baseData->getState()),true);

	return(baseData->getState() == DestructibleBuildingDataComponent::SHUTDOWNSEQUENCE);
}

bool GCWManagerImplementation::canStartSlice(CreatureObject* creature, TangibleObject* tano){
		Locker _lock(creature);
		Locker clocker(tano, creature);

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(tano->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

		if(!isBaseVulnerable(building))
			return false;

		if(creature->getFaction() == building->getFaction()){
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_tamper"); // You are not an enemy of this structure.  Why would you want to tamper
			return false;
		}

		ManagedReference<PlayerObject*> ghost = NULL;

		if(creature->isPlayerCreature())
			ghost = creature->getPlayerObject();

		if(ghost == NULL)
			return false;

		if(!canUseTerminals(creature, building, tano))
			return false;

		if(isTerminalDamaged(tano)){
			creature->sendSystemMessage("@hq:terminal_disabled");
			return false;
		}

		if(!isUplinkJammed(building)){
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:other_objectives"); // Other objectives must be disabled prior to gaining access to this one
			return false;
		}

		if(!isSecurityTermSliced(building) && creature->getFaction() != building->getFaction())
			return true;

		return false;
}

// @pre: player is locked since called from Slicing session
// @post: player is locked
void GCWManagerImplementation::completeSecuritySlice(CreatureObject* creature, TangibleObject* securityTerminal){
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}

	creature->sendSystemMessage("@slicing/slicing:hq_security_success"); // YOu have managed to slice into the temrina.  The security protocl for the override terminal has been relaxed
	Locker block(building);
	baseData->setState(DestructibleBuildingDataComponent::SLICED);


}

bool GCWManagerImplementation::isTerminalDamaged(TangibleObject* securityTerminal){
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
		return true;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		info("ERROR:  could not get base data for base",true);
		return true;
	}

	if(!baseData->isTerminalDamanged())
		return false;

	// check to see if it's cooled down
	Time t = baseData->getSliceRepairTime();
	t.addMiliTime(sliceCooldown*1000);

	// if cooldown hasn't passed since repairing, then it's still damaged
	if(t.isPast()) {
		// repair time has past... change it back to false
		Locker block(building);
		baseData->setTerminalDamaged(false);
		baseData->setTerminalBeingRepaired(false);
		return false;
	}
	else
		return true;

}
void GCWManagerImplementation::repairTerminal(CreatureObject* creature, TangibleObject* securityTerminal){
	if(securityTerminal == NULL)
			return;
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL){
		info("Bulding is null while failing slice",true);
		return;
	}

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}

	if(!this->isBaseVulnerable(building))
		return;

	Time repairFinishTime = baseData->getSliceRepairTime();
	repairFinishTime.addMiliTime(sliceCooldown*1000);


	if(baseData->isTerminalDamanged()) {

		if(baseData->isTerminalBeingRepaired())
		{
			creature->sendSystemMessage("Terminal is already in the process of being repaired.");
			return;
		} else {
			//info("repairing slice",true);
			Locker block(building,creature);
			baseData->setSliceRepairTime(Time());
			baseData->setTerminalBeingRepaired(true);
		}

	}
}
void GCWManagerImplementation::failSecuritySlice(TangibleObject* securityTerminal){
	if(securityTerminal == NULL)
		return;

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(securityTerminal->getParentRecursively(SceneObjectType::FACTIONBUILDING).get().get());

	if(building == NULL)
	{
		info("Bulding is null while failing slice",true);
		return;

	}

	if(!this->isBaseVulnerable(building))
		return;

	Locker block(building);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}
	//info("Failing slice",true);
	baseData->setTerminalBeingRepaired(false);
	baseData->setSliceRepairTime(baseData->getVulnerabilityEndTime()); // set it to the future
	baseData->setTerminalDamaged(true);

}

void GCWManagerImplementation::sendDNASampleMenu(CreatureObject* creature, BuildingObject* building){
	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(ghost==NULL || baseData == NULL)
		return;

	if(!this->isBaseVulnerable(building))
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("@hq:mnu_dna"); //Defense status

	status->setUsingObject(building);
	status->setOkButton(true, "@ok");
	status->setCancelButton(true, "@cancel");


	Locker block(building,creature);

	// TODO: use with dnaHash


	//baseData->setDNASample(tstring.toString());
	//tstring.deleteAll();

	char providedSequence[] = "CGAT";
	//info("The existing system data string is " + baseData->getSystemDNAString(),true);

	int chainLength = 3;
	if(creature->hasSkill("outdoors_bio_engineer_master"))
		chainLength = 8;

	String newSampledChain = this->refreshDNA(baseData, chainLength);

	status->setCallback( new OverrideTerminalSuiCallback(this->zone->getZoneServer(), newSampledChain) );



	String controlSequence = ""; // display string for full sample chain - configurable length

	if(!baseData->isDNAInitialized()){

		// temporary buffer for generating random letters
		StringBuffer dnaString;

		for(int i =0; i < totalDNASamples; i++) {
			dnaString << providedSequence[System::random(0x3)];
			baseData->addDNAProfile(i,dnaString.toString());   // add one of 4 random letters one at a time
			status->addMenuItem(dnaString.toString(),i);      // add them to the menu
			controlSequence = controlSequence + dnaString.toString();
			dnaString.deleteAll();
		}

	} else {
		// populate the user chains to display colored matches match
		for(int i =0; i < totalDNASamples; i++) {
			String chain = baseData->getDNAProfile(i);
			String seq = baseData->getDNAProfile(i);

			if(chain.length() > 1)
			{
				chain = "\\#008000" + chain;
				StringBuffer tstring;
				tstring << "\\#008000" << seq.charAt(0) << "\\#FFFFFF";
				seq = tstring.toString();
			}
			status->addMenuItem( chain,i);
			controlSequence = controlSequence + seq;

			chain = "";
			seq = "";
		}
	}

	String pairString = "\\#FFFFFFSuitable Pairs: AT,TA,GC,CG	\r\n";
	String completed = "Matched Pairs: " + String::valueOf(baseData->getSampleMatches()) + "\r\n";
	controlSequence = "Control Sequence: " + controlSequence + "\r\n";
	String sampleChain = "Sampled Chain: " + newSampledChain + "\r\n";

	String instructionString = "\r\nSelect a DNA marker in the control sequence as the starting point for where the sampled chain will be sliced onto it.\r\n";
    String dashes = "--------------------\r\n";
	String notes = "\r\nRESEARCH NOTES: \r\n You must match the DNA markers provided in the control sequence with the DNA from a sampled chain in order to form suitable pairs.  Continue until all of the DNA markers in the control sequence have been paired.\r\n\r\n";

	String example = "For example, if the control sequence was ATGGTTCGCA and the sample chain was GATGA, you could chooose to splice the sampled chain to the following section of the control sequence:";
	String example2 = "ATG\\#FF0000GTTCG\\#FFFFFFCA.  This would result in the splice shown below and \\#008000 2 suitable pair\\#FFFFFF:\r\n";
	String example3 = "\r\nA\r\nT\r\nG\r\n\\#FF0000GC\r\n\\#008000TA\r\n\\#FF0000TT\r\n\\#008000CG\r\n\\#FF0000GA\\#FFFFFF\r\nC\r\nA";


	status->setPromptText(pairString + completed + controlSequence + sampleChain + instructionString + dashes + dashes + notes + example + example2 + example3);
	//status->setPromptText("DNA Sequence Processing... \r\nComplete the missing pairs: AT, TA, GC, CG \r\n Matched Pairs: " +
	//		String::valueOf(baseData->getSampleMatches()) + "\r\nSampled Chain: " + baseData->getSystemDNAString());

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());

}

void GCWManagerImplementation::processDNASample(CreatureObject* creature, BuildingObject* building, const String& sampleChain, const int indx){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(creature==NULL || baseData == NULL)
			return;

	if(baseData == NULL){
		error("ERROR:  could not get base data for base");
		return;
	}

	if(!this->isBaseVulnerable(building))
		return;

	Locker block(building, creature);

	int currentMatchCount = 0;
	int j = -1;

	// don't enter loop if user didn't select anything
	for(int i = indx; i < indx+sampleChain.length() && i >= 0;i++){
		j++;

		// this is the individual letters from the control sequence
		String userProvidedSample = baseData->getDNAProfile(i);

		if(userProvidedSample.length() == 1){


			String transLatedUserString = this->getDNAHash(userProvidedSample);
			char currentPlayerLetter = sampleChain.charAt(j);

			StringBuffer newstring;
			newstring << currentPlayerLetter;

			if(currentPlayerLetter == transLatedUserString.charAt(0)){
				baseData->modifySampleAt(i,userProvidedSample + transLatedUserString);
				baseData->incrementSampleMatches();
				currentMatchCount++;
			}

		} else {
			// selected one with two values.  going to change the system string
			this->refreshDNA(baseData, 3);
			break;
		}

	}

	if ( baseData->getSampleMatches() <  dnaMatchesRequired)
	{
		this->sendDNASampleMenu(creature, building);
	}
	else
	{
		creature->sendSystemMessage("DNA Profiles complete");
		baseData->setState(DestructibleBuildingDataComponent::DNA);
	}

}

// PRE: basedata /building is locked
String GCWManagerImplementation::refreshDNA(DestructibleBuildingDataComponent* baseData, int chainLength){
	//info("Refreshing the string given by the system");
	char providedSequence[] = "CGAT";
	StringBuffer tstring;
	for(int i = 0; i < chainLength; i++)
		tstring << providedSequence[System::random(0x3)];

	baseData->setSystemDNAString(tstring.toString());
	return tstring.toString();
}

void GCWManagerImplementation::sendPowerRegulatorControls(CreatureObject* creature, BuildingObject* building){
	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(ghost==NULL || baseData == NULL)
				return;

	if(!this->isBaseVulnerable(building))
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> status = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	status->setPromptTitle("@hq:mnu_set_overload"); //Set to Overload

	status->setUsingObject(building);

	status->setOkButton(true, "OFF");
	status->setCancelButton(true, "OFF");

	status->setPromptText("@hq:mnu_set_overload");
	status->setCallback( new PowerRegulatorSuiCallback(this->zone->getZoneServer()) );

	for(int i =0; i < 8; i++) {

		if(baseData->getPowerPosition(i))
			status->addMenuItem("Power Switch " + String::valueOf(i+1) + ": ON",i);
		else
			status->addMenuItem("Power Switch " + String::valueOf(i+1) + ": OFF",i);
	}

	ghost->addSuiBox(status);
	creature->sendMessage(status->generateMessage());

}

void GCWManagerImplementation::handlePowerRegulatorSwitch(CreatureObject* creature, BuildingObject* building, int indx){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;

	if(!this->isBaseVulnerable(building))
			return;

	Locker block(building,creature);

	if(indx > -1){
		int change = System::random(0x2); // 0-2 to give a little more weight to the switch changing
		//info("handlign the switch ... change another = " + String::valueOf(change), true);

		baseData->turnSwitchOff(indx);

		if(change){
			int impactedSwitch = System::random(0x7);
			if(impactedSwitch != indx) {
				if(!baseData->getPowerPosition(impactedSwitch)){
					baseData->turnSwitchOn(impactedSwitch);
				}
			}
		}
	}


	if(baseData->getOnSwitchCount() == 0) {
		StringIdChatParameter msg("@faction/faction_hq/faction_hq_response:alignment_complete");  // Alignment complete!  The facility may now be set to overload from the primary terminal.
		broadcastBuilding(building, msg);
		baseData->setState(DestructibleBuildingDataComponent::OVERLOADED);
	}
	else {
		block.release();
		this->sendPowerRegulatorControls(creature,building);
	}

}

void GCWManagerImplementation::notifyInstallationDestruction(InstallationObject* installation){
	if(installation == NULL)
		return;

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", zone->getZoneName(), installation->getPositionX(), installation->getPositionZ(), installation->getPositionY());
	installation->broadcastMessage(explodeLoc, false);

	uint64 ownerid = installation->getOwnerObjectID();
	BuildingObject* building = NULL;

	ZoneServer* server = zone->getZoneServer();

	if(server == NULL) {
		info("server is null for the installation",true);
		return;
	}

	SceneObject* ownerObject = server->getObject(ownerid);

	if(ownerObject == NULL){
		info("owner object for the turret is null",true);
		PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/lair_damage_heavy.cef", zone->getZoneName(), installation->getPositionX(), installation->getPositionZ(), installation->getPositionY());
		installation->broadcastMessage(explodeLoc, false);

		Locker _lock(installation);
		installation->destroyObjectFromWorld(true);
		installation->destroyObjectFromDatabase(true);

		return;
	}
	/// confirmed

	//info("object type of the owner is " + ownerObject->getObjectNameStringIdName(),true);
	if(ownerObject->isGCWBase()){
		building = cast<BuildingObject*>(ownerObject);

		Locker _lock(building);
		Locker clock(installation,building);

		DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

		if(baseData != NULL){
			if(building->containsChildObject(installation)){
				//info("removed child",true);
				building->getChildObjects()->removeElement(installation);
			}
		}

		if( baseData->hasTurret(installation->getObjectID())){
			if(installation->isTurret())
				notifyTurretDestruction(building, installation);

		} else if (baseData->hasMinefield(installation->getObjectID())){

			if (installation->isMinefield())
				notifyMinefieldDestruction(building, installation);


		} else {

			//info("owner is a creature... need to remvoe the lots",true);
			Locker plock(ownerObject);
			Locker tlock(installation, ownerObject);
			StructureManager::instance()->destroyStructure(installation);
			tlock.release();
			plock.release();
		}


	} else if (ownerObject->isCreatureObject()){
		info("Destroying faction installation not part of a base",true);
		Locker plock(ownerObject);
		Locker tlock(installation, ownerObject);
		StructureManager::instance()->destroyStructure(installation);
		tlock.release();
		plock.release();
	}

}

void GCWManagerImplementation::notifyTurretDestruction(BuildingObject* building, InstallationObject* turret){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);

	if(baseData == NULL)
		return;

	int indx = baseData->getIndexOfTurret(turret->getObjectID());

	if(indx < 0)
		return;

	baseData->setTurretID(indx,0);

	// see if all the turrets are destroyed
	int defensecount = 0;

	for(int i = 0; i < baseData->getTotalTurretCount();i++){
		if(baseData->getTurretID(i))
			defensecount++;
	}

	info("Base " + String::valueOf(building->getObjectID()) + " turret destroyed.  Remaining turrets: " + String::valueOf(defensecount),true);

	if(!defensecount) {
		baseData->setDefense(false);
		building->broadcastCellPermissions();
	}

	turret->destroyObjectFromWorld(true);
	turret->destroyObjectFromDatabase(true);

	if(building != NULL)
		verifyTurrets(building);

}

void GCWManagerImplementation::notifyMinefieldDestruction(BuildingObject* building, InstallationObject* minefield){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData(building);
	if(baseData == NULL)
		return;

	int indx = baseData->getIndexOfMinefield(minefield->getObjectID());

	if(indx < 0 )
		return;

	baseData->setMinefieldID(indx,0);

	// see if all the turrets are destroyed
	int defensecount = 0;

	for(int i = 0; i < baseData->getTotalMinefieldCount();i++){
		if(baseData->getMinefieldOID(i))
			defensecount++;
	}

	info("Base " + String::valueOf(building->getObjectID()) + " minefield destroyed.  Remaining minefields: " + String::valueOf(defensecount),true);

	if(!defensecount) {
		//baseData->setDefense(false);
		//building->broadcastCellPermissions();
	}

	minefield->destroyObjectFromWorld(true);
	minefield->destroyObjectFromDatabase(true);
}

void GCWManagerImplementation::sendSelectDeedToDonate(BuildingObject* building, CreatureObject* creature, int turretIndex){
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(creature ==NULL || baseData == NULL)
			return;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if(ghost == NULL)
		return;

	if(isBaseVulnerable(building) && !ghost->isPrivileged() ) {
		creature->sendSystemMessage("@hq:under_attack"); // You cannot add defenses while the HQ is under attack.
		return;
	}


	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SceneObject*> inv = creature->getSlottedObject("inventory");

	if(inv == NULL)
		return;

	ManagedReference<SuiListBox*> donate = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);


	donate->setPromptTitle("@hq:mnu_defense_status");
	donate->setPromptText("Donate a deed");
	donate->setUsingObject(building);
	donate->setOkButton(true, "Donate");
	donate->setCancelButton(true, "@cancel");
	donate->setCallback( new DonateDefenseSuiCallback(zone->getZoneServer(), turretIndex) );

	for(int i =0;i < inv->getContainerObjectsSize(); ++i){
		ManagedReference<SceneObject*> inventoryObject = inv->getContainerObject(i);
		if(inventoryObject->isDeedObject() || inventoryObject->getGameObjectType() == SceneObjectType::MINE){
			donate->addMenuItem(inventoryObject->getDisplayedName(),inventoryObject->getObjectID());
		}
	}

	ghost->addSuiBox(donate);
	creature->sendMessage(donate->generateMessage());

}

void GCWManagerImplementation::sendSelectTurretToDonate(BuildingObject* building, CreatureObject* creature){
	if(creature == NULL)
		return;

	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(ghost==NULL || baseData == NULL)
		return;


	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SceneObject*> inv = creature->getSlottedObject("inventory");

	ManagedReference<SuiListBox*> donate = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	donate->setPromptTitle("TURRET SELECT");
	donate->setPromptText("SELECT TURRET");
	donate->setUsingObject(building);
	donate->setOkButton(true, "@select");
	donate->setCancelButton(true, "@cancel");
	donate->setCallback( new SelectTurretDonationSuiCallback(zone->getZoneServer()));

	ZoneServer* zoneServer = zone->getZoneServer();
	if(zoneServer != NULL){

		for(int i = 0; i < baseData->getTotalTurretCount();++i){
			ManagedReference<SceneObject*> sceno = zoneServer->getObject(baseData->getTurretID(i));
			if(sceno != NULL && sceno->isTurret()) {
				donate->addMenuItem("Turret " + String::valueOf(i+1) + " : " + sceno->getDisplayedName());
			} else {
				donate->addMenuItem("Turret " + String::valueOf(i+1) + ": EMPTY");
			}

		}
	}
	ghost->addSuiBox(donate);
	creature->sendMessage(donate->generateMessage());
}

void GCWManagerImplementation::sendRemoveDefenseConfirmation(BuildingObject* building, CreatureObject* creature, uint64 deedOID){
	ZoneServer* zoneServer = zone->getZoneServer();
	if(zoneServer == NULL)
		return;

	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(ghost==NULL || baseData == NULL)
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::HQ_TERMINAL))
		ghost->closeSuiWindowType(SuiWindowType::HQ_TERMINAL);

	ManagedReference<SuiListBox*> removeDefense = new SuiListBox(creature, SuiWindowType::HQ_TERMINAL);
	removeDefense->setPromptTitle("TURRET SELECT");
	removeDefense->setPromptText("@faction/faction_hq/faction_hq_response:terminal_response25"); // are you sure you want to remove the selected defense?
	removeDefense->setUsingObject(building);
	removeDefense->setOkButton(true, "@ok");
	removeDefense->setCancelButton(true, "@cancel");
	removeDefense->setCallback( new RemoveDefenseSuiCallback(zone->getZoneServer(),deedOID));

	ghost->addSuiBox(removeDefense);
	creature->sendMessage(removeDefense->generateMessage());
}

void GCWManagerImplementation::removeDefense(BuildingObject* building, CreatureObject* creature, uint64 deedOID){
	//info("remove defense " + String::valueOf(deedOID),true);

	ZoneServer* zoneServer = zone->getZoneServer();

	if(zoneServer == NULL)
			return;

	ManagedReference<SceneObject*> defense = zoneServer->getObject(deedOID);

	if(defense == NULL || !defense->isTurret())
		return;


	InstallationObject* turret = cast<InstallationObject*>(defense.get());

	this->notifyInstallationDestruction(turret);
	//Locker clock(defense,creature);
	//TangibleObject* tano = cast<TangibleObject*>(defense.get());
	//tano->inflictDamage(creature,0,999999,true,true);

}

void GCWManagerImplementation::performDefenseDontation(BuildingObject* building, CreatureObject* creature, uint64 deedOID, int turretIndex){
	//info("deed oid is " + String::valueOf(deedOID),true);

	ZoneServer* zoneServer = zone->getZoneServer();
	if(zoneServer == NULL)
		return;

	ManagedReference<SceneObject*> defenseObj = zoneServer->getObject(deedOID);

	if(defenseObj == NULL)
		return;

	if(defenseObj->getGameObjectType() == SceneObjectType::MINE) {

		performDonateMine(building, creature, defenseObj);
		return;
	}

	if(defenseObj->isDeedObject()){


		ManagedReference<Deed*> deed = dynamic_cast<Deed*>(defenseObj.get());
		if(deed != NULL){

			Reference<SharedObjectTemplate* > generatedTemplate = TemplateManager::instance()->getTemplate(deed->getGeneratedObjectTemplate().hashCode());
			if(generatedTemplate == NULL){
				info("Generated template is null",true);
				return;
			}
			if(generatedTemplate->getGameObjectType() == SceneObjectType::MINEFIELD) {
				performDonateMinefield(building,creature,deed);
				return;
			} else if (generatedTemplate->getGameObjectType() == SceneObjectType::TURRET){
				performDonateTurret(building,creature,deed);
				return;
			}
		}
	}

	StringIdChatParameter param("@faction/faction_hq/faction_hq_response:terminal_response43"); // This facility does not accept deeds of type '%TO'. Cancelling donation..."
	param.setTO(defenseObj->getObjectName());
	creature->sendSystemMessage(param);
	return;


}

void GCWManagerImplementation::performDonateMine(BuildingObject* building, CreatureObject* creature, SceneObject* mine){
// search the building for a minefield that isn't full

	Locker _lock(building, creature);

	for(int i =0; i < building->getChildObjects()->size(); i++){
		ManagedReference<SceneObject*> obj = building->getChildObjects()->get(i);

		int precount = obj->getContainerObjectsSize();


		if(obj->isMinefield() && precount < 20){
			_lock.release();
			Locker clock(obj,creature);

			obj->transferObject(mine,-1,true);


			if(precount < obj->getContainerObjectsSize()){
				StringIdChatParameter param("@faction/faction_hq/faction_hq_response:terminal_response46"); // YOu sucessfully donate a %TO
				param.setTO(mine->getObjectNameStringIdFile(),mine->getObjectNameStringIdName());

				creature->sendSystemMessage(param);
				// broadcast the fact that the minefield is no longer attackable since it just donated
				TangibleObject* tano = cast<TangibleObject*>(obj.get());
				if(tano == NULL)
					return;

				int newbitmask = tano->getPvpStatusBitmask() & (255 - CreatureFlag::ATTACKABLE);
				tano->setPvpStatusBitmask(newbitmask);

				//UpdatePVPStatusMessage* upvpsm = new UpdatePVPStatusMessage(tano);
				//tano->broadcastMessage(upvpsm, true, true);
				return;
			}
		}
	}

	creature->sendSystemMessage("Unable to donate mines at this time.  Full or no minefields");

}

void GCWManagerImplementation::performDonateMinefield(BuildingObject* building, CreatureObject* creature,  Deed* deed){

	String serverTemplatePath = deed->getGeneratedObjectTemplate();
	TemplateManager* templateManager = TemplateManager::instance();
	Reference<SharedObjectTemplate*> baseServerTemplate = building->getObjectTemplate();
	Reference<SharedObjectTemplate*> minefieldTemplate = NULL;
	ChildObject* child = NULL;

	int currentMinefieldIndex = 0;

	Locker block(building,creature);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;

	// go through it and inf the first available mine
	int minefieldIndex = 0;
	for(minefieldIndex = 0; minefieldIndex < baseData->getTotalMinefieldCount(); minefieldIndex++){
		if(baseData->getMinefieldOID(minefieldIndex) == 0 )
			break;
	}

	creature->sendSystemMessage("Minefield open at postiion " + String::valueOf(minefieldIndex));

	// this is turret donation
	int nextAvailableMinefield = 0;
	for(nextAvailableMinefield = 0; nextAvailableMinefield < baseData->getTotalTurretCount(); nextAvailableMinefield++){
		if(baseData->getMinefieldOID(nextAvailableMinefield) == 0)
			break;
	}

	if ( nextAvailableMinefield >= baseData->getTotalMinefieldCount() ){
		return;
	}

	// now find the coords of the nth turret

	for (int i = 0; i < baseServerTemplate->getChildObjectsSize(); ++i) {
		 child = baseServerTemplate->getChildObject(i);
		 minefieldTemplate = NULL;
		if(child != NULL){

			minefieldTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());
			if(minefieldTemplate->getGameObjectType() == SceneObjectType::MINEFIELD){
				if(currentMinefieldIndex == nextAvailableMinefield){
					break;
				} else{
					currentMinefieldIndex++;
				}
			}
		}
	}

	if(child == NULL || minefieldTemplate == NULL || minefieldTemplate->getGameObjectType() != SceneObjectType::MINEFIELD)
		return;

	uint64 minefieldID = addChildInstallationFromDeed(building, child, creature, deed);
	if(minefieldID > 0) {
		baseData->setMinefieldID(currentMinefieldIndex,minefieldID);

		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response45");  //"You successfully donate a %TO deed to the current facility."
		params.setTO(deed->getObjectNameStringIdFile(),deed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);
		// TODO: Implement .. verify minefields

		block.release();

		if(deed != NULL) {
			Locker clock(deed, creature);
			deed->destroyObjectFromWorld(true);
		}
	}
}

void GCWManagerImplementation::performDonateTurret(BuildingObject* building, CreatureObject* creature,  Deed* turretDeed){
	String serverTemplatePath = turretDeed->getGeneratedObjectTemplate();
	TemplateManager* templateManager = TemplateManager::instance();
	Reference<SharedObjectTemplate*> baseServerTemplate = building->getObjectTemplate();

	Reference<SharedObjectTemplate*> turretTemplate = NULL;
	ChildObject* child = NULL;
	int currentTurretIndex = 0;

	// search through the baseData to find the first empty turret index

	Locker block(building,creature);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;


	// this is turret donation
	int nextAvailableTurret = 0;
	for(nextAvailableTurret = 0; nextAvailableTurret < baseData->getTotalTurretCount(); nextAvailableTurret++){
		if(baseData->getTurretID(nextAvailableTurret) == 0)
			break;
	}

	if ( nextAvailableTurret >= baseData->getTotalTurretCount() ){
		return;
	}

	// now find the coords of the nth turret

	for (int i = 0; i < baseServerTemplate->getChildObjectsSize(); ++i) {
		 child = baseServerTemplate->getChildObject(i);
		 turretTemplate = NULL;
		if(child != NULL){

			turretTemplate = TemplateManager::instance()->getTemplate(child->getTemplateFile().hashCode());
			if(turretTemplate->getGameObjectType() == SceneObjectType::TURRET){
				if(currentTurretIndex == nextAvailableTurret){
					break;
				} else{
					currentTurretIndex++;
				}
			}
		}
	}

	if(child == NULL || turretTemplate == NULL || turretTemplate->getGameObjectType() != SceneObjectType::TURRET)
		return;

	uint64 turretID= addChildInstallationFromDeed(building, child, creature, turretDeed);

	if(turretID > 0) {
		baseData->setTurretID(currentTurretIndex,turretID);

		StringIdChatParameter params;
		params.setStringId("@faction/faction_hq/faction_hq_response:terminal_response45");  // "You successfully donate a %TO deed to the current facility."
		params.setTO(turretDeed->getObjectNameStringIdFile(),turretDeed->getObjectNameStringIdName());
		creature->sendSystemMessage(params);

		verifyTurrets(building);
		block.release();

		if(turretDeed != NULL) {
			Locker clock(turretDeed, creature);
			turretDeed->destroyObjectFromWorld(true);
		}
	}
}

uint64 GCWManagerImplementation::addChildInstallationFromDeed(BuildingObject* building, ChildObject* child, CreatureObject* creature, Deed* deed){
	Vector3 position = building->getPosition();

	Quaternion* direction = building->getDirection();
	Vector3 childPosition = child->getPosition();
	float angle = direction->getRadians();

	float x = (Math::cos(angle) * childPosition.getX()) + (childPosition.getY() * Math::sin(angle));
	float y = (Math::cos(angle) * childPosition.getY()) - (childPosition.getX() * Math::sin(angle));

	x += position.getX();
	y += position.getY();

	float z = position.getZ() + childPosition.getZ();

	float degrees = direction->getDegrees();
	Quaternion dir = child->getDirection();

	ManagedReference<SceneObject*> obj = zone->getZoneServer()->createObject(deed->getGeneratedObjectTemplate().hashCode(), 1);
	obj->initializePosition(x, z, y);
	obj->setDirection(dir.rotate(Vector3(0, 1, 0), degrees));

	if(!obj->isTangibleObject())
		return 0;

	TangibleObject* tano = cast<TangibleObject*>(obj.get());

	if(tano != NULL)
		tano->setFaction(building->getFaction());

	tano->setPvpStatusBitmask(building->getPvpStatusBitmask() | tano->getPvpStatusBitmask());

	if(tano->isTurret())
		tano->setDetailedDescription("Donated Turret");

	if(tano->isInstallationObject()){
		InstallationObject* turret = cast<InstallationObject*>(tano);
		if(turret != NULL) {
			turret->setOwnerObjectID(building->getObjectID());
			turret->createChildObjects();
		}
	}

	zone->transferObject(obj, -1, false);
	building->getChildObjects()->put(obj);
	return obj->getObjectID();
}

void GCWManagerImplementation::addMinefield(BuildingObject* building, SceneObject* minefield){
	if(building == NULL || minefield == NULL || !minefield->isMinefield())
			return;
	//info("adding minefield",true);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;
	Locker _lock(building);
	baseData->addMinefield(baseData->getTotalMinefieldCount(), minefield->getObjectID());
}

void GCWManagerImplementation::addScanner(BuildingObject* building, SceneObject* scanner){
	if(building == NULL || scanner == NULL || !scanner->isDetector())
		return;

	//info("adding scanner",true);
	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;
	Locker _lock(building);

	baseData->addScanner(baseData->getTotalScannerCount(), scanner->getObjectID());

}

void GCWManagerImplementation::addTurret(BuildingObject* building, SceneObject* turret){
	if(building == NULL || turret == NULL)
		return;

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;
	Locker _lock(building);

	baseData->addTurret(baseData->getTotalTurretCount(), turret->getObjectID());
	this->verifyTurrets(building);
}

void GCWManagerImplementation::verifyTurrets(BuildingObject* building){
	//info("verify turrets",true);

	DestructibleBuildingDataComponent* baseData = getDestructibleBuildingData( building );

	if(baseData == NULL)
		return;

	int turrets = 0;
	Locker blocker(building);
	for(int i = 0; i < baseData->getTotalTurretCount(); ++i){
		if(baseData->getTurretID(i)){
				turrets++;
		}
	}

	baseData->setDefense(turrets);
}

bool GCWManagerImplementation::canPlaceMoreBases(CreatureObject* creature){
	if(creature == NULL || !creature->isPlayerCreature())
		return false;

	PlayerObject* ghost = creature->getPlayerObject();
	if(ghost == NULL)
		return false;
	if(zone == NULL || zone->getZoneServer() == NULL)
		return false;

	ZoneServer* server = zone->getZoneServer();
	int baseCount = 0;
	for(int i =0; i < ghost->getTotalOwnedStructureCount(); ++i){
		ManagedReference<SceneObject*> structure = server->getObject(ghost->getOwnedStructure(i));
		if(structure != NULL && structure->isGCWBase())
			baseCount++;

	}

	if(baseCount >= maxBasesPerPlayer){
		creature->sendSystemMessage("You own " + String::valueOf(baseCount) + " bases.  The maximum amount is " + String::valueOf(maxBasesPerPlayer));
		return false;
	}

	return true;

}
bool GCWManagerImplementation::canUseTerminals(CreatureObject* creature, BuildingObject* building, SceneObject* terminal){
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if(ghost == NULL)
		return false;

	// Make sure the player is in the same cell
	ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
	uint64 parentid = validPosition->getParent();

	if (parentid != terminal->getParentID()) {
		creature->sendSystemMessage("@pvp_rating:ch_terminal_too_far");  // you are too far away from the terminal to use it
		return false;
	}

	if(creature->getFaction() == 0) {
		creature->sendSystemMessage("@faction_recruiter:must_be_declared_use"); // Your faction affiliation must be delcared in order to use that item.
		return false;
	}

	if (ghost == NULL)
		return false;

	// check for PvP base
	if (building->getPvpStatusBitmask() & CreatureFlag::OVERT ){
		if( ghost->getFactionStatus() != FactionStatus::OVERT){
			creature->sendSystemMessage("@faction/faction_hq/faction_hq_response:declared_personnel_only"); // Only Special Forces personnel may access this terminal
			return false;
		}
	}
	// check for PvE base
	else{
		if(ghost->getFactionStatus() < FactionStatus::COVERT) {
			creature->sendSystemMessage("You must be at least combatant");
			return false;
		}
	}
	return true;
}


void GCWManagerImplementation::broadcastBuilding(BuildingObject* building, StringIdChatParameter& params){
	//Default range of broadcast
	float range = 64;

	if(zone == NULL)
		return;

	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	if (building->getCloseObjects() == NULL) {
		zone->getInRangeObjects(building->getPositionX(), building->getPositionY(), range, &closeObjects, true);
	} else {
		CloseObjectsVector* closeVector = (CloseObjectsVector*) building->getCloseObjects();
		closeVector->safeCopyTo(closeObjects);
	}

	// send message to all the players in range
	for (int i = 0; i < closeObjects.size(); i++) {
		SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

		if (targetObject->isPlayerCreature() && building->isInRange(targetObject, range)) {
			CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);

			if (targetPlayer != NULL)
				targetPlayer->sendSystemMessage(params);
		}
	}
}

