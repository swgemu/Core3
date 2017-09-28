local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsIntro = ScreenPlay:new {
	OLDMANWAIT = 1,
	OLDMANMEET = 2,
	SITHWAIT = 3,
	SITHATTACK = 4,
	USEDATAPADONE = 5,
	SITHTHEATER = 6,
	USEDATAPADTWO = 7,
	VILLAGE = 8,

	stepDelay = {
		[1] = { 43200, 129600 }, -- Old man visit, 12-36 hours
		[3] = { 3600, 43200 } -- Sith shadow attack, 1 hour to 12 hours
	}
}

function FsIntro:getCurrentStep(pPlayer)
	local curStep = readScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroStep")

	if (curStep == "") then
		curStep = 1
		self:setCurrentStep(pPlayer, self.OLDMANWAIT)
	end

	return tonumber(curStep)
end

function FsIntro:setCurrentStep(pPlayer, step)
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroStep", step)
end

function FsIntro:isOnIntro(pPlayer)
	return VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_GLOWING) and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_VILLAGE_ELDER)
end

function FsIntro:hasDelayPassed(pPlayer)
	local stepDelay = tonumber(readScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroDelay"))

	if (stepDelay == nil or stepDelay == 0) then
		return true
	end

	return os.time() >= stepDelay
end

function FsIntro:startStepDelay(pPlayer, step)
	local stepData = self.stepDelay[step]

	if (stepData == nil) then
		printLuaError("FsIntro:startStepDelay, invalid step data.")
		return
	end

	self:setCurrentStep(pPlayer, step)
	local stepDelay = getRandomNumber(stepData[1], stepData[2])

	if (step == 1) then
		local oldManVisits = tonumber(readScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroOldManVisits"))

		if oldManVisits ~= nil then
			if (oldManVisits == 2) then
				stepDelay = stepDelay + (1 * 24 * 60 * 60)
			elseif (oldManVisits >= 3) then
				stepDelay = stepDelay + (oldManVisits * 24 * 60 * 60)
			end
		end
	end

	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroDelay", stepDelay + os.time())
	createEvent(stepDelay * 1000, "FsIntro", "doDelayedStep", pPlayer, "")
end

function FsIntro:doDelayedStep(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):isOnline()) then
		return
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated() or not Encounter:isPlayerInPositionForEncounter(pPlayer)) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "doDelayedStep", pPlayer, "")
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	if (not OldManIntroEncounter:hasForceCrystal(pPlayer)) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)

		if (self:hasFirstDatapad(pPlayer)) then
			QuestManager.resetQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
			self:removeFirstDatapad(pPlayer)
		end

		if (self:hasSecondDatapad(pPlayer)) then
			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2)
			self:removeSecondDatapad(pPlayer)
		end


		self:setCurrentStep(pPlayer, self.OLDMANWAIT)
		curStep = self.OLDMANWAIT
	end

	local encounterResult = true
	if (curStep == self.OLDMANWAIT) then
		encounterResult = OldManIntroEncounter:start(pPlayer)
	elseif (curStep == self.SITHWAIT) then
		encounterResult = SithShadowEncounter:start(pPlayer)
	end

	if (not encounterResult) then
		local rescheduleDelay = getRandomNumber(15, 30) * 60 * 1000
		createEvent(rescheduleDelay, "FsIntro", "doDelayedStep", pPlayer, "")
	end
end

function FsIntro:startPlayerOnIntro(pPlayer)
	if (not self:isOnIntro(pPlayer)) then
		return
	end

	self:startStepDelay(pPlayer, 1)
end

function FsIntro:onLoggedIn(pPlayer)
	if (not self:isOnIntro(pPlayer)) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	-- Extra check in case the player's current step gets messed up
	if ((curStep == self.OLDMANWAIT or curStep == self.OLDMANMEET) and OldManIntroEncounter:hasForceCrystal(pPlayer)) then
		self:setCurrentStep(pPlayer, self.SITHWAIT)
		curStep = self.SITHWAIT
	end

	if (curStep ~= self.OLDMANWAIT and curStep ~= self.OLDMANMEET and not OldManIntroEncounter:hasForceCrystal(pPlayer)) then
		if (SithShadowIntroTheater:hasTaskStarted(pPlayer)) then
			SithShadowIntroTheater:finish(pPlayer)
		end

		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)

		if (self:hasFirstDatapad(pPlayer)) then
			QuestManager.resetQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
			self:removeFirstDatapad(pPlayer)
		end

		if (self:hasSecondDatapad(pPlayer)) then
			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2)
			self:removeSecondDatapad(pPlayer)
		end

		if (self:hasDelayPassed(pPlayer)) then
			createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startOldMan", pPlayer, "")
		end

		self:setCurrentStep(pPlayer, self.OLDMANWAIT)
		return
	end

	if (curStep == self.OLDMANWAIT) then
		if (self:hasDelayPassed(pPlayer)) then
			createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startOldMan", pPlayer, "")
			self:setCurrentStep(pPlayer, curStep + 1)
		end
	elseif (curStep == self.OLDMANMEET) then
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
		createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startOldMan", pPlayer, "")
	elseif (curStep == self.SITHWAIT) then
		if (self:hasDelayPassed(pPlayer)) then
			createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startSithAttack", pPlayer, "")
			self:setCurrentStep(pPlayer, curStep + 1)
		end
	elseif (curStep == self.SITHATTACK) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startSithAttack", pPlayer, "")
	elseif (curStep == self.USEDATAPADONE) then
		if (not self:hasFirstDatapad(pPlayer)) then
			QuestManager.resetQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
			self:setCurrentStep(pPlayer, curStep - 1)
			createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startSithAttack", pPlayer, "")
		end
	elseif (curStep == self.SITHTHEATER) then
		if (SithShadowIntroTheater:hasTaskStarted(pPlayer)) then
			SithShadowIntroTheater:finish(pPlayer)
		end

		QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
		QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2)
		SithShadowIntroTheater:start(pPlayer)
	elseif (curStep == self.USEDATAPADTWO) then
		if (not self:hasSecondDatapad(pPlayer)) then
			if (SithShadowIntroTheater:hasTaskStarted(pPlayer)) then
				SithShadowIntroTheater:finish(pPlayer)
			end

			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2)
			self:setCurrentStep(pPlayer, curStep - 1)
			SithShadowIntroTheater:start(pPlayer)
		end
	elseif (curStep == self.VILLAGE and not QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_VILLAGE_ELDER)) then
		GoToDathomir:finish(pPlayer)
		GoToDathomir:start(pPlayer)
	end
end

function FsIntro:onLoggedOut(pPlayer)
	if (not self:isOnIntro(pPlayer)) then
		return
	end

	local curStep = self:getCurrentStep(pPlayer)

	if (curStep == self.SITHTHEATER) then
		SithShadowIntroTheater:finish(pPlayer)
	end
end

function FsIntro:hasFirstDatapad(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/waypoint_datapad.iff", true) ~= nil
end

function FsIntro:hasSecondDatapad(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/theater_datapad.iff", true) ~= nil
end

function FsIntro:removeFirstDatapad(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/waypoint_datapad.iff", true)

	if (pDatapad ~= nil) then
		SceneObject(pDatapad):destroyObjectFromWorld()
		SceneObject(pDatapad):destroyObjectFromDatabase()
	end
end

function FsIntro:removeSecondDatapad(pPlayer)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pDatapad = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/force_sensitive/theater_datapad.iff", true)

	if (pDatapad ~= nil) then
		SceneObject(pDatapad):destroyObjectFromWorld()
		SceneObject(pDatapad):destroyObjectFromDatabase()
	end
end

function FsIntro:startOldMan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):isOnline()) then
		return
	end

	local result = OldManIntroEncounter:start(pPlayer)

	if (not result) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startOldMan", pPlayer, "")
		return
	end
end

function FsIntro:startSithAttack(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil or not PlayerObject(pGhost):isOnline()) then
		return
	end

	local result = SithShadowEncounter:start(pPlayer)

	if (not result) then
		createEvent(getRandomNumber(300, 900) * 1000, "FsIntro", "startSithAttack", pPlayer, "")
		return
	end
end

function FsIntro:completeVillageIntroFrog(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_GLOWING)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)

	giveItem(pInventory, "object/tangible/loot/quest/force_sensitive/force_crystal.iff", -1)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.TWO_MILITARY)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_1)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.GOT_DATAPAD)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_THEATER_CAMP)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.GOT_DATAPAD_2)
	QuestManager.completeQuest(pPlayer, QuestManager.quests.LOOT_DATAPAD_2)

	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_VILLAGE_ELDER)

	VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS)

	if (not PlayerObject(pGhost):isJedi()) then
		PlayerObject(pGhost):setJediState(1)
	end

	awardSkill(pPlayer, "force_title_jedi_novice")
end
