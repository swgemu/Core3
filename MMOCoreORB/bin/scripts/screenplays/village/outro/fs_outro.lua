local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsOutro = ScreenPlay:new {
	OLDMANWAIT = 1,
	OLDMANMEET = 2,
	MELLICHAETHEATER = 3,
	FORCESHRINE = 4,

	stepDelay = {
		[1] = { 15600, 86400 }, -- Old man visit, 1 hour to 1 day
	}
}

function FsOutro:getCurrentStep(pPlayer)
	local curStep = readScreenPlayData(pPlayer, "VillageJediProgression", "FsOutroStep")

	if (curStep == "") then
		curStep = 1
		self:setCurrentStep(pPlayer, self.OLDMANWAIT)
	end

	return tonumber(curStep)
end

function FsOutro:setCurrentStep(pPlayer, step)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsOutroStep", step)
end

function FsOutro:isOnOutro(pPlayer)
	return VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE) and not VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE)
end

function FsOutro:hasDelayPassed(pPlayer)
	local stepDelay = tonumber(readScreenPlayData(pPlayer, "VillageJediProgression", "FsOutroDelay"))

	if (stepDelay == nil or stepDelay == 0) then
		return true
	end
	
	return os.time() >= stepDelay
end

function FsOutro:onLoggedIn(pPlayer)
	if (not self:isOnOutro(pPlayer)) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	if (curStep == self.OLDMANWAIT) then
		if (self:hasDelayPassed(pPlayer)) then
			createEvent(getRandomNumber(300, 900) * 1000, "FsOutro", "doOldManSpawn", pPlayer, "")
		end
	elseif (curStep == self.OLDMANMEET) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL)
		createEvent(getRandomNumber(300, 900) * 1000, "FsOutro", "doOldManSpawn", pPlayer, "")
		self:setCurrentStep(pPlayer, self.OLDMANWAIT)
	elseif (curStep == self.MELLICHAETHEATER) then
		if (MellichaeOutroTheater:hasTaskStarted(pPlayer)) then
			MellichaeOutroTheater:finish(pPlayer)
		end

		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
		local result = MellichaeOutroTheater:start(pPlayer)
	end
end

function FsOutro:startOldMan(pPlayer)
	local curStep = self:getCurrentStep(pPlayer)

	if (curStep ~= self.OLDMANWAIT) then
		return
	end

	local stepData = self.stepDelay[self.OLDMANWAIT]
	
	if (stepData == nil) then
		printLuaError("FsOutro:startOldMan, invalid step data.")
		return
	end

	local stepDelay = getRandomNumber(stepData[1], stepData[2])

	QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsOutroDelay", stepDelay + os.time())
	createEvent(stepDelay * 1000, "FsOutro", "doOldManSpawn", pPlayer, "")
end

function FsOutro:onLoggedOut(pPlayer)
	if (not self:isOnOutro(pPlayer)) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	if (curStep == self.MELLICHAETHEATER) then
		MellichaeOutroTheater:finish(pPlayer)
	end
end

function FsOutro:doOldManSpawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	if (curStep == self.OLDMANMEET) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):isOnline()) then
		return
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated() or not Encounter:isPlayerInPositionForEncounter(pPlayer)) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsOutro", "doOldManSpawn", pPlayer, "")
		return
	end

	local result = OldManOutroEncounter:start(pPlayer)

	if (not result) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsOutro", "doOldManSpawn", pPlayer, "")
		return
	end
end

function FsOutro:completeVillageOutroFrog(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_FINAL)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_THEATER_FINAL)

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE)

	PadawanTrials:doPadawanTrialsSetup(pPlayer)
end