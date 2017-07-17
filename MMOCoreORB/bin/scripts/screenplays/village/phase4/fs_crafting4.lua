local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

FsCrafting4 = {
	waypoints = {
		keren = { 1215, 2740, "naboo" },
		coronet = { 19, -4775, "corellia" },
		mosentha = { 1209, 2923, "tatooine" }
	},

	NOWIRE = 0,
	REDWIRE = 1,
	BLUEWIRE = 2,
	YELLOWWIRE = 3
}

function FsCrafting4:activateQuest(pPlayer)
	if (VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		return
	end

	local lastCompleted = self:getLastCompletedQuest(pPlayer)

	if (lastCompleted >  -1) then
		local nextQuest = lastCompleted + 1

		local questName = "fs_crafting4_quest_0" .. nextQuest
		local questID = getPlayerQuestID(questName)

		QuestManager.activateQuest(pPlayer, questID)
	else
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_00)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_01)
	end

	VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, VILLAGE_PHASE4_ENGINEER)
end

function FsCrafting4:sendTooLateSui(pPlayer)
	if (readScreenPlayData(pPlayer, "VillageJediProgression", "FsCrafting4TooLateBox") == "1") then
		return
	end

	local sui = SuiMessageBox.new("FsCrafting4", "noCallback")

	sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_phase_change_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:crafting4_phase_over")
	sui.hideCancelButton()

	sui.sendTo(pPlayer)

	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsCrafting4TooLateBox", 1)
end

function FsCrafting4:removeCore(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pCore = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_crafting4_computer_core.iff", true)

	if (pCore ~= nil) then
		SceneObject(pCore):destroyObjectFromWorld()
		SceneObject(pCore):destroyObjectFromDatabase()
	end

	deleteScreenPlayData(pPlayer, "VillageJediProgression", "FsCrafting4TooLateBox")
end

function FsCrafting4:getActiveQuestNum(pPlayer)
	for i = 7, 1, -1 do
		local questName = "fs_crafting4_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasActiveQuest(pPlayer, questID) and not QuestManager.hasCompletedQuest(pPlayer, questID) then
			return i
		end
	end

	return -1
end

function FsCrafting4:getLastCompletedQuest(pPlayer)
	for i = 7, 1, -1 do
		local questName = "fs_crafting4_quest_0" .. i
		local questID = getPlayerQuestID(questName)

		if QuestManager.hasCompletedQuest(pPlayer, questID) then
			return i
		end
	end

	return -1
end

function FsCrafting4:notifyTrackingKitDestroyed(pItem)
	if (pItem == nil) then
		return 1
	end

	local ownerID = TangibleObject(pItem):getLuaStringData("ownerID")

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	local pInventory = CreatureObject(pOwner):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 1
	end

	local pTracker = getContainerObjectByTemplate(pInventory, "object/tangible/loot/collectible/collectible_rewards/fs_tracking_device.iff", true)

	if (pTracker ~= nil) then
		QuestManager.completeQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_02)
		QuestManager.activateQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_03)
		TangibleObject(pTracker):setLuaStringData("ownerID", ownerID)
		TangibleObject(pTracker):setLuaStringData("needsTrackingData", "true")
		createObserver(OBJECTREMOVEDFROMZONE, "FsCrafting4", "notifyTrackingDeviceDestroyed", pTracker, 1)
	else
		QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_02)
		QuestManager.uncompleteQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_01)

		if (VillageJediManagerTownship:getCurrentPhase() ~= 4) then
			CreatureObject(pOwner):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_kit_destroyed_over")
		else
			CreatureObject(pOwner):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_kit_destroyed")
		end
	end

	return 1
end

function FsCrafting4:notifyTrackingDeviceDestroyed(pItem)
	if (pItem == nil) then
		return 1
	end

	local ownerID = TangibleObject(pItem):getLuaStringData("ownerID")

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil) then
		return 1
	end

	if (QuestManager.hasCompletedQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_06)) then
		return 1
	end

	if (VillageJediManagerTownship:getCurrentPhase() ~= 4) then
		CreatureObject(pOwner):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_tracking_device_destroyed_over")
	else
		CreatureObject(pOwner):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_tracking_device_destroyed")
	end

	QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_06)
	QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_05)
	QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_04)
	QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_03)
	QuestManager.resetQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_02)
	QuestManager.uncompleteQuest(pOwner, QuestManager.quests.FS_CRAFTING4_QUEST_01)

	return 1
end

function FsCrafting4:obtainSatelliteData(pPlayer, pDroid)
	if (pPlayer == nil) then
		return
	end

	local sui = SuiMessageBox.new("FsCrafting4", "obtainDataCallback")

	if (pDroid == nil) then
		sui.setTargetNetworkId(0)
	else
		sui.setTargetNetworkId(SceneObject(pDroid):getObjectID())
	end

	sui.setProperty("", "Size", "500,250")

	sui.setTitle("@quest/force_sensitive/fs_crafting:tracking_data_title")
	sui.setPrompt("@quest/force_sensitive/fs_crafting:tracking_data_msg")

	sui.sendTo(pPlayer)
end

function FsCrafting4:noCallback(pPlayer, pSui, eventIndex, args)
end

function FsCrafting4:obtainDataCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03)) then
		return
	end

	if (CreatureObject(pPlayer):getCashCredits() < 1100) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_data_no_money")
		return
	end

	CreatureObject(pPlayer):subtractCashCredits(1100)
	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_data_purchase_msg_01")
	createEvent(getRandomNumber(1000, 4000), "FsCrafting4", "doObtainCallbackMessage2", pPlayer, "")
end

function FsCrafting4:doObtainCallbackMessage2(pPlayer)
	if (pPlayer == nil) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_data_purchase_msg_02")
	createEvent(getRandomNumber(1000, 2000), "FsCrafting4", "doObtainCallbackMessage3", pPlayer, "")
end

function FsCrafting4:doObtainCallbackMessage3(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pTracker = getContainerObjectByTemplate(pInventory, "object/tangible/loot/collectible/collectible_rewards/fs_tracking_device.iff", true)

	if (pTracker == nil) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_data_purchase_msg_03")
	TangibleObject(pTracker):setLuaStringData("needsTrackingData", "false")
	QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)
end

function FsCrafting4:getAlternatePlanet(pPlayer)
	local planetList = { "corellia", "dantooine", "dathomir", "endor", "lok", "naboo", "rori", "talus", "tatooine", "yavin4" }
	local curPlanet = SceneObject(pPlayer):getZoneName()
	local newPlanet = planetList[getRandomNumber(1, #planetList)]

	if (newPlanet == curPlanet) then
		newPlanet = FsCrafting4:getAlternatePlanet(pPlayer)
	end

	return newPlanet
end

function FsCrafting4:setupComputerCore(pCore, pPlayer)
	TangibleObject(pCore):setLuaStringData("ownerID", SceneObject(pPlayer):getObjectID())
	TangibleObject(pCore):setLuaStringData("puzzleGuess1", self.NOWIRE)
	TangibleObject(pCore):setLuaStringData("puzzleGuess2", self.NOWIRE)
	TangibleObject(pCore):setLuaStringData("puzzleGuess3", self.NOWIRE)
	TangibleObject(pCore):setLuaStringData("puzzleGuess4", self.NOWIRE)

	for i = 1, 4, 1 do
		TangibleObject(pCore):setLuaStringData("puzzleSolution" .. i, getRandomNumber(1,3))
	end

	TangibleObject(pCore):setLuaStringData("puzzleIntegrity", getRandomNumber(93, 99))
end

FsCrafting4TrackingDeviceMenuComponent = {}

function FsCrafting4TrackingDeviceMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local ownerID = TangibleObject(pSceneObject):getLuaStringData("ownerID")

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil or pOwner ~= pPlayer) then
		return
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@quest/force_sensitive/fs_crafting:tracking_device_menu_use")
end

function FsCrafting4TrackingDeviceMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return 0
	end

	local ownerID = TangibleObject(pSceneObject):getLuaStringData("ownerID")

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil or pOwner ~= pPlayer) then
		return 0
	end

	if (selectedID ~= 20) then
		return 0
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03) and not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_not_on_quest")
		return 0
	end

	local needsTrackingData = TangibleObject(pSceneObject):getLuaStringData("needsTrackingData")

	if (needsTrackingData == "true") then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:tracking_device_needs_data")
		return 0
	end

	local trackingPlanet = TangibleObject(pSceneObject):getLuaStringData("trackingPlanet")

	if (trackingPlanet == "") then
		trackingPlanet = FsCrafting4:getAlternatePlanet(pPlayer)
		TangibleObject(pSceneObject):setLuaStringData("trackingPlanet", trackingPlanet)

		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_crafting:tracking_device_wrong_planet")
		messageString:setTO(HelperFuncs:toTitleCase(trackingPlanet))
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	elseif (trackingPlanet ~= SceneObject(pPlayer):getZoneName()) then
		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/fs_crafting:tracking_device_wrong_planet")
		messageString:setTO(HelperFuncs:toTitleCase(trackingPlanet))
		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
	elseif (FsCrafting4Goto:hasTaskStarted(pPlayer) or FsCrafting4Theater:hasTaskStarted(pPlayer)) then
		FsCrafting4Goto:finish(pPlayer)
		FsCrafting4Theater:finish(pPlayer)

		FsCrafting4Goto:start(pPlayer)
	else
		FsCrafting4Goto:start(pPlayer)
	end

	return 0
end

FsCrafting4SatelliteMenuComponent = {}

function FsCrafting4SatelliteMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3, "@quest/force_sensitive/fs_crafting:crafting4_menu_retrieve_core")
end

function FsCrafting4SatelliteMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return 0
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)) then
		return 0
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:inventory_full")
		return 0
	end

	local pCore = getContainerObjectByTemplate(pInventory, "object/tangible/item/quest/force_sensitive/fs_crafting4_computer_core.iff", true)

	if (pCore == nil) then
		local pItem = giveItem(pInventory, "object/tangible/item/quest/force_sensitive/fs_crafting4_computer_core.iff", -1)

		if (pItem ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_menu_core_received")
			FsCrafting4Theater:finish(pPlayer)
			FsCrafting4:setupComputerCore(pItem, pPlayer)
			QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)
			QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)
		end
	end

	local pTracker = getContainerObjectByTemplate(pInventory, "object/tangible/loot/collectible/collectible_rewards/fs_tracking_device.iff", true)

	if (pTracker ~= nil) then
		TangibleObject(pTracker):setLuaStringData("needsTrackingData", "true")
	end

	return 0
end

FsCrafting4ComputerCoreMenuComponent = {}

function FsCrafting4ComputerCoreMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil or pPlayer == nil) then
		return
	end

	local ownerID = TangibleObject(pSceneObject):getLuaStringData("ownerID")

	local pOwner = getSceneObject(ownerID)

	if (pOwner == nil or pOwner ~= pPlayer) then
		return
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(68, 3, "@quest/force_sensitive/fs_crafting:crafting4_core_menu_configure")
	menuResponse:addRadialMenuItemToRadialID(68, 69, 3, self:getConnectionMenuName(pSceneObject, 1))
	menuResponse:addRadialMenuItemToRadialID(68, 70, 3, self:getConnectionMenuName(pSceneObject, 2))
	menuResponse:addRadialMenuItemToRadialID(68, 71, 3, self:getConnectionMenuName(pSceneObject, 3))
	menuResponse:addRadialMenuItemToRadialID(68, 72, 3, self:getConnectionMenuName(pSceneObject, 4))
	menuResponse:addRadialMenuItemToRadialID(68, 73, 3, "@quest/force_sensitive/fs_crafting:crafting4_core_menu_test")
	menuResponse:addRadialMenuItem(74, 3, "@quest/force_sensitive/fs_crafting:crafting4_core_menu_status")
end

function FsCrafting4ComputerCoreMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil) then
		return 0
	end

	if (CreatureObject(pPlayer):isDead() or CreatureObject(pPlayer):isIncapacitated()) then
		return 0
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pSceneObject):getParentID() ~= SceneObject(pInventory):getObjectID()) then
		return 0
	end

	if (not QuestManager.hasActiveQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05) or QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)) then
		return 0
	end

	if (selectedID == 68) then
		local sui = SuiMessageBox.new("FsCrafting4", "noCallback")

		sui.setProperty("", "Size", "500,250")
		sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_core_menu_configure")
		sui.setPrompt("@quest/force_sensitive/fs_crafting:crafting4_core_config_help")
		sui.hideCancelButton()

		sui.sendTo(pPlayer)
	elseif (selectedID == 69) then
		self:setConnection(pSceneObject, pPlayer, 1)
	elseif (selectedID == 70) then
		self:setConnection(pSceneObject, pPlayer, 2)
	elseif (selectedID == 71) then
		self:setConnection(pSceneObject, pPlayer, 3)
	elseif (selectedID == 72) then
		self:setConnection(pSceneObject, pPlayer, 4)
	elseif (selectedID == 73) then
		self:attemptConfigure(pSceneObject, pPlayer)
	elseif (selectedID == 74) then
		self:sendCurrentStatus(pSceneObject, pPlayer)
	end

	return 0
end

function FsCrafting4ComputerCoreMenuComponent:attemptConfigure(pCore, pPlayer)
	if (pCore == nil or pPlayer == nil) then
		return
	end

	local puzzleGuess1 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess1"))
	local puzzleGuess2 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess2"))
	local puzzleGuess3 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess3"))
	local puzzleGuess4 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess4"))
	local puzzleGuesses = { puzzleGuess1, puzzleGuess2, puzzleGuess3, puzzleGuess4 }

	local puzzleSolution1 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleSolution1"))
	local puzzleSolution2 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleSolution2"))
	local puzzleSolution3 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleSolution3"))
	local puzzleSolution4 = tonumber(TangibleObject(pCore):getLuaStringData("puzzleSolution4"))
	local puzzleSolutions = { puzzleSolution1, puzzleSolution2, puzzleSolution3, puzzleSolution4 }

	local puzzleResults = { false, false, false, false }
	local correctlyConnected = 0

	for i = 1, 4, 1 do
		if (puzzleGuesses[i] == puzzleSolutions[i]) then
			puzzleResults[i] = true
			correctlyConnected = correctlyConnected + 1
		end
	end

	if (correctlyConnected == 4) then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_06)

		if (VillageJediManagerTownship:getCurrentPhase() == 4) then
			local sui = SuiMessageBox.new("FsCrafting4", "noCallback")

			sui.setProperty("", "Size", "500,250")
			sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_core_menu_status")
			sui.setPrompt("@quest/force_sensitive/fs_crafting:crafting4_core_completed")
			sui.hideCancelButton()

			sui.sendTo(pPlayer)
		else
			FsCrafting4:sendTooLateSui(pPlayer)
		end
		TangibleObject(pCore):setLuaStringData("correctlyConfigured", "true")
	else
		local correctWiresUsed = 0
		local tempResults = puzzleResults

		for i = 1, 4, 1 do
			local alreadySolved = puzzleResults[i]

			if (not alreadySolved) then
				local curGuess = puzzleGuesses[i]

				local doBreak = false
				for j = 1, 4, 1 do
					if (not doBreak) then
						local alreadyUsed = tempResults[j]

						if (not alreadyUsed) then
							local correctWire = puzzleSolutions[j]

							if (curGuess == correctWire) then
								correctWiresUsed = correctWiresUsed + 1
								tempResults[j] = true
								doBreak = true
							end
						end
					end
				end
			end
		end

		TangibleObject(pCore):setLuaStringData("lastGuess1", puzzleGuess1)
		TangibleObject(pCore):setLuaStringData("lastGuess2", puzzleGuess2)
		TangibleObject(pCore):setLuaStringData("lastGuess3", puzzleGuess3)
		TangibleObject(pCore):setLuaStringData("lastGuess4", puzzleGuess4)
		TangibleObject(pCore):setLuaStringData("lastCorrectWiresConnected", correctlyConnected)
		TangibleObject(pCore):setLuaStringData("lastCorrectWiresUsed", correctWiresUsed)

		local integrity = tonumber(TangibleObject(pCore):getLuaStringData("puzzleIntegrity"))
		integrity = integrity - getRandomNumber(13,17)
		TangibleObject(pCore):setLuaStringData("puzzleIntegrity", integrity)

		if (integrity <= 0) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_core_ruined")
			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_04)
			QuestManager.resetQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_05)
			QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_03)
			SceneObject(pCore):destroyObjectFromWorld()
			SceneObject(pCore):destroyObjectFromDatabase()
		else
			local resultString = "@quest/force_sensitive/fs_crafting:crafting4_core_current_result"
			local litString = "@quest/force_sensitive/fs_crafting:crafting4_core_indicators_lit"
			local flickerString = "@quest/force_sensitive/fs_crafting:crafting4_core_flickering"
			local integrityString = "@quest/force_sensitive/fs_crafting:crafting4_core_integrity"

			local msgPrompt = resultString .. " \\#pcontrast1 " .. litString .. " \\#pcontrast2 " .. correctlyConnected
			msgPrompt = msgPrompt .. " \\#. \\#pcontrast1 " .. flickerString .. " \\#pcontrast2 " .. correctWiresUsed
			msgPrompt = msgPrompt .. " \\#. \\#pcontrast1 " .. integrityString .. " \\#pcontrast2 " .. integrity .. "% \\#. "

			local sui = SuiMessageBox.new("FsCrafting4", "noCallback")

			sui.setProperty("", "Size", "500,250")
			sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_core_menu_status")
			sui.setPrompt(msgPrompt)
			sui.hideCancelButton()

			sui.sendTo(pPlayer)
		end
	end
end

function FsCrafting4ComputerCoreMenuComponent:sendCurrentStatus(pCore, pPlayer)
	if (pCore == nil or pPlayer == nil) then
		return
	end

	local msgPrompt

	if (self:isConfigured(pCore)) then
		msgPrompt = "@quest/force_sensitive/fs_crafting:crafting4_core_completed_status"
	else
		local wire1String = self:getConnectionMenuName(pCore, 1)
		local wire2String = self:getConnectionMenuName(pCore, 2)
		local wire3String = self:getConnectionMenuName(pCore, 3)
		local wire4String = self:getConnectionMenuName(pCore, 4)

		local status01 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_01"
		local status02 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_02"
		local status03 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_03"
		local status04 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_04"
		local status05 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_05"

		msgPrompt = status01 .. " \\#pcontrast1 " .. status02 .. " \\#pcontrast2 " .. wire1String .. " \\#. \\#pcontrast1 " .. status03 .. " \\#pcontrast2 " .. wire2String
		msgPrompt = msgPrompt .. " \\#. \\#pcontrast1 " .. status04 .. " \\#pcontrast2 " .. wire3String .. " \\#. \\#pcontrast1 " .. status05 .. " \\#pcontrast2 " .. wire4String

		local lastGuess1 = tonumber(TangibleObject(pCore):getLuaStringData("lastGuess1"))
		local lastGuess2 = tonumber(TangibleObject(pCore):getLuaStringData("lastGuess2"))
		local lastGuess3 = tonumber(TangibleObject(pCore):getLuaStringData("lastGuess3"))
		local lastGuess4 = tonumber(TangibleObject(pCore):getLuaStringData("lastGuess4"))
		local lastCorrectConnected = tonumber(TangibleObject(pCore):getLuaStringData("lastCorrectWiresConnected"))
		local lastCorrectUsed = tonumber(TangibleObject(pCore):getLuaStringData("lastCorrectWiresUsed"))
		local integrity = tonumber(TangibleObject(pCore):getLuaStringData("puzzleIntegrity"))

		if (lastGuess1 ~= nil and lastGuess2 ~= nil and lastGuess3 ~= nil and lastGuess4 ~= nil) then
			local status06 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_06"
			local status07 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_07"
			local status08 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_08"
			local status09 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_09"
			local status10 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_10"
			local status11 = "@quest/force_sensitive/fs_crafting:crafting4_core_current_status_11"
			local resultString = "@quest/force_sensitive/fs_crafting:crafting4_core_current_result"
			local litString = "@quest/force_sensitive/fs_crafting:crafting4_core_indicators_lit"
			local flickerString = "@quest/force_sensitive/fs_crafting:crafting4_core_flickering"
			local integrityString = "@quest/force_sensitive/fs_crafting:crafting4_core_integrity"

			local last1String = self:getConnectionMenuName(pCore, 1, true)
			local last2String = self:getConnectionMenuName(pCore, 2, true)
			local last3String = self:getConnectionMenuName(pCore, 3, true)
			local last4String = self:getConnectionMenuName(pCore, 4, true)

			msgPrompt = msgPrompt .. " \\#. " .. status06 .. " \\#pcontrast1 " .. status07 .. " \\#pcontrast2 " .. last1String .. " \\#. \\#pcontrast1 " .. status08 .. " \\#pcontrast2 " .. last2String
			msgPrompt = msgPrompt .. " \\#. \\#pcontrast1 " .. status09 .. " \\#pcontrast2 " .. last3String .. " \\#. \\#pcontrast1 " .. status10 .. " \\#pcontrast2 " .. last4String
			msgPrompt = msgPrompt .. " \\#. " .. status11 .. " " .. resultString .. " \\#pcontrast1 " .. litString .. " \\#pcontrast2 " .. lastCorrectConnected
			msgPrompt = msgPrompt .. " \\#. \\#pcontrast1 " .. flickerString .. " \\#pcontrast2 " .. lastCorrectUsed .. " \\#. \\#pcontrast1 " .. integrityString .. " \\#pcontrast2 " .. integrity .. "% \\#. "
		else
			msgPrompt = msgPrompt .. " \\#. " .. "@quest/force_sensitive/fs_crafting:crafting4_core_current_no_testing"
		end
	end

	local sui = SuiMessageBox.new("FsCrafting4", "noCallback")

	sui.setProperty("", "Size", "500,250")
	sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_core_menu_status")
	sui.setPrompt(msgPrompt)
	sui.hideCancelButton()

	sui.sendTo(pPlayer)
end

function FsCrafting4ComputerCoreMenuComponent:isConfigured(pCore)
	return TangibleObject(pCore):getLuaStringData("correctlyConfigured") == "true"
end

function FsCrafting4ComputerCoreMenuComponent:setConnection(pCore, pPlayer, connectionNum)
	if (pCore == nil or pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local coreID = SceneObject(pCore):getObjectID()
	local pageId = readData(coreID .. ":pageID")

	if (pageId ~= 0) then
		PlayerObject(pGhost):removeSuiBox(pageId)
		deleteData(coreID .. ":pageID")
	end

	local sui = SuiListBox.new("FsCrafting4", "setConnectionCallback")

	sui.setTargetNetworkId(coreID)

	sui.setTitle("@quest/force_sensitive/fs_crafting:crafting4_core_msgbox_title")

	local connPrompt
	if (connectionNum == 1) then
		connPrompt = "@quest/force_sensitive/fs_crafting:crafting4_core_set_connection_one"
	elseif (connectionNum == 2) then
		connPrompt = "@quest/force_sensitive/fs_crafting:crafting4_core_set_connection_two"
	elseif (connectionNum == 3) then
		connPrompt = "@quest/force_sensitive/fs_crafting:crafting4_core_set_connection_three"
	elseif (connectionNum == 4) then
		connPrompt = "@quest/force_sensitive/fs_crafting:crafting4_core_set_connection_four"
	end

	sui.setPrompt(connPrompt .. " " .. self:getWireSetting(pCore, connectionNum))

	sui.add("No Wire", "")
	sui.add("Red Wire", "")
	sui.add("Blue Wire", "")
	sui.add("Yellow Wire", "")

	pageId = sui.sendTo(pPlayer)
	writeData(coreID .. ":pageID", pageId)
	writeData(coreID .. ":connectionNum", connectionNum)
end

function FsCrafting4:setConnectionCallback(pPlayer, pSui, eventIndex, args)
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		printLuaError("FsCrafting4:setConnectionCallback, pageData is nil.")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local coreID = suiPageData:getTargetNetworkId()
	local pCore = getSceneObject(coreID)

	if (pCore == nil) then
		return
	end

	deleteData(coreID .. ":pageID")
	local connectionNum = readData(coreID .. ":connectionNum")
	deleteData(coreID .. ":connectionNum")

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or tonumber(args) < 0) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:crafting4_core_no_selection_made")
		return
	end

	local chosenWire = tonumber(args)

	local wireString

	if (chosenWire == FsCrafting4.NOWIRE) then wireString = "@quest/force_sensitive/fs_crafting:crafting4_core_nothing"
	elseif (chosenWire == FsCrafting4.REDWIRE) then wireString = "@quest/force_sensitive/fs_crafting:crafting4_core_a_red_wire"
	elseif (chosenWire == FsCrafting4.BLUEWIRE) then wireString = "@quest/force_sensitive/fs_crafting:crafting4_core_a_blue_wire"
	elseif (chosenWire == FsCrafting4.YELLOWWIRE) then wireString = "@quest/force_sensitive/fs_crafting:crafting4_core_a_yellow_wire"
	else wireString = "@quest/force_sensitive/fs_crafting:crafting4_core_error" end

	local connectionString

	if (connectionNum == 1) then connectionString =  "@quest/force_sensitive/fs_crafting:crafting4_core_connection_one_set"
	elseif (connectionNum == 2) then connectionString =  "@quest/force_sensitive/fs_crafting:crafting4_core_connection_two_set"
	elseif (connectionNum == 3) then connectionString =  "@quest/force_sensitive/fs_crafting:crafting4_core_connection_three_set"
	elseif (connectionNum == 4) then connectionString =  "@quest/force_sensitive/fs_crafting:crafting4_core_connection_four_set"
	else connectionString = "@quest/force_sensitive/fs_crafting:crafting4_core_error" end

	TangibleObject(pCore):setLuaStringData("puzzleGuess" .. connectionNum, chosenWire)
	local messageString = LuaStringIdChatParameter(connectionString)
	messageString:setTO(wireString)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function FsCrafting4ComputerCoreMenuComponent:getWireSetting(pCore, connectionNum)
	local curGuess = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess" .. connectionNum))

	local wireString

	if (curGuess == FsCrafting4.NOWIRE) then return "@quest/force_sensitive/fs_crafting:crafting4_core_nothing"
	elseif (curGuess == FsCrafting4.REDWIRE) then return "@quest/force_sensitive/fs_crafting:crafting4_core_a_red_wire"
	elseif (curGuess == FsCrafting4.BLUEWIRE) then return "@quest/force_sensitive/fs_crafting:crafting4_core_a_blue_wire"
	elseif (curGuess == FsCrafting4.YELLOWWIRE) then return "@quest/force_sensitive/fs_crafting:crafting4_core_a_yellow_wire" end

	return "@quest/force_sensitive/fs_crafting:crafting4_core_error"
end

function FsCrafting4ComputerCoreMenuComponent:getConnectionMenuName(pCore, connectionNum, lastGuess)
	local menuName = "@quest/force_sensitive/fs_crafting:crafting4_core_error"

	local guessData = tonumber(TangibleObject(pCore):getLuaStringData("puzzleGuess" .. connectionNum))

	if (lastGuess) then
		guessData = tonumber(TangibleObject(pCore):getLuaStringData("lastGuess" .. connectionNum))
	end

	local stringNum

	if (connectionNum == 1) then stringNum = "one"
	elseif (connectionNum == 2) then stringNum = "two"
	elseif (connectionNum == 3) then stringNum = "three"
	elseif (connectionNum == 4) then stringNum = "four" end

	local wireString

	if (guessData == FsCrafting4.NOWIRE) then wireString = "nothing"
	elseif (guessData == FsCrafting4.REDWIRE) then wireString = "red"
	elseif (guessData == FsCrafting4.BLUEWIRE) then wireString = "blue"
	elseif (guessData == FsCrafting4.YELLOWWIRE) then wireString = "yellow" end

	if (stringNum == "" or wireString == "") then
		return menuName
	end

	return "@quest/force_sensitive/fs_crafting:crafting4_core_menu_" .. stringNum .. "_" .. wireString
end
