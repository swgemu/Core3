local ObjectManager = require("managers.object.object_manager")

HelperDroidQuest = ScreenPlay:new {
	brawler = {"survival_knife", "wooden_staff", "heavy_axe"},
	marksman = {"cdef_pistol", "cdef_carbine", "cdef_rifle"},

	weaponTemplates = {
		brawler = {"object/weapon/melee/knife/knife_survival.iff", "object/weapon/melee/polearm/lance_staff_wood_s1.iff", "object/weapon/melee/axe/axe_heavy_duty.iff"},
		marksman = {"object/weapon/ranged/pistol/pistol_cdef.iff", "object/weapon/ranged/carbine/carbine_cdef.iff", "object/weapon/ranged/rifle/rifle_cdef.iff"},
	},

	scout = "object/tangible/scout/trap/trap_drowsy_dart.iff",

	stimpack = "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_a.iff",

	instrument = "object/tangible/instrument/slitherhorn.iff",

	coupons = {
		cloning = "object/tangible/item/new_player/new_player_cloning_coupon.iff",
		travel = "object/tangible/item/new_player/new_player_travel_coupon.iff",
		vehicle = "object/tangible/item/new_player/new_player_vehicle_coupon.iff",
	},

	fireworks = {
		"object/tangible/firework/firework_s10.iff",
		"object/tangible/firework/firework_s18.iff",
	},

	speciesStrings = {
		{"0", "human"},
		{"1", "rodian"},
		{"2", "trandoshan"},
		{"3", "moncal"},
		{"4", "wookiee"},
		{"5", "bothan"},
		{"6", "twilek"},
		{"7", "zabrak"},
		{"33", "ithorian"},
		{"49", "sullustan"},
	},

	SPECIES_MONCAL = 3,
	SPECIES_WOOKIEE = 4,
	SPECIES_SULLUSTAN = 49,
	SPECIES_ITHORIAN = 33,
}

registerScreenPlay("HelperDroidQuest", false)

-- ========= Sui Functions ==========

function HelperDroidQuest:startSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = SceneObject(pDroid):getObjectID()

	writeData(playerID .. ":HelperDroidID:", droidID)
	writeStringData(playerID .. ":HelperDroid:profession:", profession)

	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")
	local questsComplete = tonumber(getQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:"))

	if (questsComplete ~= nil) then
		self:professionQuestSui(pDroid, pPlayer, profession)
		return
	end

	local sui = SuiMessageBox.new("HelperDroidQuest", "startCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,500")
	sui.setForceCloseDistance(10)

	local prompt = "@new_player:" .. profession .. "_quest_00"

	sui.setCancelButtonText("@new_player:not_now_button")
	sui.setOkButtonText("@new_player:lets_start_button")

	sui.setPrompt(prompt)

	sui.sendTo(pPlayer)
end

function HelperDroidQuest:startCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:")
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	if (cancelPressed) then
		return
	end

	if (eventIndex == 0 and pDroid ~= nil) then
		if ((profession == "brawler" or profession == "marksman")) then
			createEvent(100, "HelperDroidQuest", "chooseWeapon", pPlayer, "")
			writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", 1)
			return
		end

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 0)
		self:professionQuestSui(pDroid, pPlayer, profession)
	end
end

function HelperDroidQuest:professionQuestSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = SceneObject(pDroid):getObjectID()

	writeData(playerID .. ":HelperDroidID:", droidID)
	writeStringData(playerID .. ":HelperDroid:profession:", profession)

	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")
	local questsComplete = tonumber(getQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:"))

	if (questsComplete == nil) then
		self:startSui(pDroid, pPlayer, profession)
	end

	if (questsComplete == 6 or (questsComplete == 5 and (profession == "marksman" or profession == "artisan"))) then
		self:finalQuestSui(pDroid, pPlayer, profession)
		return
	end

	if (questStatus < questsComplete) then
		questStatus = questsComplete
		writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", questsComplete)
	end

	if (questStatus == 0 and (profession == "brawler" or profession == "marksman")) then
		createEvent(100, "HelperDroidQuest", "chooseWeapon", pPlayer, "")
		writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", 1)
		return
	end

	if (questStatus > questsComplete) then
		self:onQuestSui(pDroid, pPlayer, profession)
		return
	end

	local sui = SuiMessageBox.new("HelperDroidQuest", "professionCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,500")
	sui.setForceCloseDistance(10)

	-- Prompt the next quest
	questStatus = questStatus + 1

	local prompt = "@new_player:" .. profession .. "_quest_0" .. tostring(questStatus)

	sui.setCancelButtonText("@new_player:not_now_button")
	sui.setOkButtonText("@new_player:give_quest_button")

	if (profession == "medic" and questStatus == 1) then
		sui.setOkButtonText("@new_player:okay_button")
		sui.hideCancelButton()
	end

	if (profession == "entertainer" and questStatus == 3) then
		local species = CreatureObject(pPlayer):getSpecies()
		local speciesStr = self.speciesStrings
		local string = ""

		for i = 1, #speciesStr, 1 do
			local stringNum = speciesStr[i][1]

			if (stringNum == tostring(species)) then
				string = speciesStr[i][2]
				break
			end
		end

		prompt = prompt .. "_" .. string

		if (species == self.SPECIES_MONCAL or species == self.SPECIES_WOOKIEE or species == self.SPECIES_SULLUSTAN or species == self.SPECIES_ITHORIAN) then
			-- These 4 species have to skip quest 3 for entertainer
			sui.setOkButtonText("@new_player:continue_button")
			sui.hideCancelButton()
		end
	end

	sui.setPrompt(prompt)

	sui.sendTo(pPlayer)
end

function HelperDroidQuest:professionCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:")
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (cancelPressed) then
		if (pDroid ~= nil) then
			spatialChat(pDroid, "@new_player:delayed_accepting_quest")
		end
		return
	end

	-- OK response
	if (eventIndex == 0) then
		-- Player has accepted to start quest. Set their status, completed will be set when task is finished
		writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", questStatus + 1)

		if (questStatus == 0 and (profession == "scout" or profession == "medic")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 1)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return
		end

		if (questStatus == 2 and profession == "entertainer") then
			local species = CreatureObject(pPlayer):getSpecies()

			if (species == self.SPECIES_MONCAL or species == self.SPECIES_WOOKIEE or species == self.SPECIES_SULLUSTAN or species == self.SPECIES_ITHORIAN) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

				self:professionQuestSui(pDroid, pPlayer, profession)
				return
			end
		end

		self:giveQuest(pPlayer, profession)
	end
end

function HelperDroidQuest:onQuestSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	local sui = SuiMessageBox.new("HelperDroidQuest", "onQuestCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,500")
	sui.setForceCloseDistance(10)

	sui.setCancelButtonText("@new_player:no_help_needed_button")
	sui.setOkButtonText("@new_player:help_please_button")

	local prompt = "@new_player:" .. profession .. "_quest_0" .. questStatus

	if ((questStatus == 6 and profession == "brawler") or (questStatus == 5 and profession == "marksman")) then
		local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:")

		prompt = "@new_player:" .. profession .. "_quest_0" .. tostring(questStatus)
		local message2 = "@new_player:" .. profession .. "_quest_0" .. tostring(questStatus) .. "_b"

		prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(killCount) .. " @new_player:counter_not_update \\#. "
	elseif (questStatus == 6 and profession == "scout") then
		local totalHide = readData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")

		prompt = "@new_player:" .. profession .. "_quest_06"
		local message2 = "@new_player:" .. profession .. "_quest_06_b"

		prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(totalHide) .. " @new_player:counter_not_update \\#. "
	elseif (questStatus == 5 and profession == "artisan") then
		local craftCount = readData(playerID .. ":" .. profession .. ":HelperDroid:riflesCrafted:")

		prompt = "@new_player:" .. profession .. "_quest_05"
		local message2 = "@new_player:" .. profession .. "_quest_05_b"

		prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(craftCount) .. " @new_player:counter_not_update \\#. "
	elseif (profession == "medic") then
		if (questStatus == 3) then
			prompt = "@new_player:medic_diagnose"
			sui.setOkButtonText("@new_player:general_medic_button")
		elseif (questStatus == 6) then
			local tendedTable = readStringVectorSharedMemory(playerID .. ":" .. profession .. ":HelperDroid:tendedPatients:")

			prompt = "@new_player:medic_quest_06"
			local message2 = "@new_player:" .. profession .. "_quest_06_b"

			prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(#tendedTable) .. " @new_player:counter_not_update \\#. "
		end
	elseif (profession == "entertainer") then
		if (questStatus == 3) then
			prompt = "@new_player:entertainer_image_design"
			sui.setOkButtonText("@new_player:general_entertainer_button")
		elseif (questStatus == 6) then
			local totalPatrons = readData(playerID .. ":" .. profession .. ":HelperDroid:totalPatrons:")

			prompt = "@new_player:entertainer_quest_06"
			local message2 = ("@new_player:entertainer_quest_06_b")

			prompt = prompt .. "     \\#pcontrast1 " .. message2 .. " " .. tostring(totalPatrons) .. " @new_player:counter_not_update \\#. "
		end
	end

	sui.setPrompt(prompt)
	sui.sendTo(pPlayer)
end

function HelperDroidQuest:onQuestCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPress) then
		return
	end

	local args = {...}
	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:")
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (eventIndex == 0) then
		if (profession == "brawler" or profession == "marksman") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("Combat.Targeting")

		elseif (profession == "scout") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingScout")

		elseif (profession == "artisan") then
			if (questStatus == 1 or questStatus == 2 or questStatus == 3) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingArtisan.Resources")
			elseif (questStatus == 4) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingArtisan.Crafting")
			elseif (questStatus == 5) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("Crafting.FindingResources")
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("Crafting")
			end

		elseif (profession == "medic") then
			if (questStatus == 2) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Exploring.FindHospital")
			elseif (questStatus == 3 or questStatus == 4) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingMedic")
			elseif (questStatus == 5) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingMedic.DraftSchematics")
			elseif (questStatus == 6) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingMedic.Damage")
			end

		elseif (profession == "entertainer") then
			if (questStatus == 1 or questStatus == 2) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer.Instruments")
			elseif (questStatus == 3) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer.Instruments")
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer")
			elseif (questStatus == 4) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer.Instruments")
			elseif (questStatus == 5) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Exploring.FindCantina")
			elseif (questStatus == 6) then
				CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer")
			end
		end
	end
end

function HelperDroidQuest:finalQuestSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	HelperDroid:playDroidSound(pPlayer)

	local sui = SuiMessageBox.new("HelperDroidQuest", "noCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,200")
	sui.setProperty("btnCancel", "Visible", "false")
	sui.setForceCloseDistance(10)

	local finalmessage = ""

	if (profession == "brawler") then
		finalmessage = "@new_player:brawler_quest_complete"
	elseif (profession == "marksman") then
		finalmessage = "@new_player:marksman_quest_complete"
	elseif (profession == "scout") then
		finalmessage = "@new_player:scout_quest_complete"
	elseif (profession == "artisan") then
		finalmessage = "@new_player:artisan_quest_complete"
	elseif (profession == "medic") then
		finalmessage = "@new_player:medic_quest_complete"
	elseif (profession == "entertainer") then
		finalmessage = "@new_player:entertainer_quest_complete"
	end

	sui.setPrompt(finalmessage)

	sui.sendTo(pPlayer)

	deleteData(playerID .. ":HelperDroidID:")
	deleteStringData(playerID .. ":HelperDroid:profession:")
end

function HelperDroidQuest:noCallback(pPlayer, pSui, eventIndex, ...)
end

-- ========= END Sui Functions ==========

-- ========= Quest Task Handler ==========

function HelperDroidQuest:giveQuest(pPlayer, profession)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "brawler") then
		if (questStatus == 2 or questStatus == 6) then
			createObserver(KILLEDCREATURE, "HelperDroidQuest", "notifyKilledCreature", pPlayer)
			return
		elseif (questStatus == 3 or questStatus == 4 or questStatus == 5) then
			createObserver(ABILITYUSED, "HelperDroidQuest", "notifyAbilityUsed", pPlayer)
			return
		end
	elseif (profession == "marksman") then
		if (questStatus == 2 or questStatus == 5) then
			createObserver(KILLEDCREATURE, "HelperDroidQuest", "notifyKilledCreature", pPlayer)
			return
		elseif (questStatus == 3 or questStatus == 4) then
			createObserver(ABILITYUSED, "HelperDroidQuest", "notifyAbilityUsed", pPlayer)
			return
		end
	elseif (profession == "scout") then
		if (questStatus == 2 or questStatus == 3 or questStatus == 6) then
			createObserver(HARVESTEDCREATURE, "HelperDroidQuest", "notifyCreatureHarvested", pPlayer)
			return
		elseif (questStatus == 4) then
			createObserver(PROTOTYPECREATED, "HelperDroidQuest", "notifyObjectCrafted", pPlayer)
			return
		elseif (questStatus == 5) then
			createObserver(DEPLOYEDCAMP, "HelperDroidQuest", "notifyCampDeployed", pPlayer)
			return
		end
	elseif (profession == "artisan") then
		if (questStatus == 1) then
			createObserver(SURVEY, "HelperDroidQuest", "notifySurvey", pPlayer, 1)
		elseif (questStatus == 2 or questStatus == 3) then
			createObserver(SAMPLETAKEN, "HelperDroidQuest", "notifySampleTaken", pPlayer, 1)
			return
		elseif (questStatus == 4 or questStatus == 5) then
			createObserver(PROTOTYPECREATED, "HelperDroidQuest", "notifyObjectCrafted", pPlayer)
			return
		end

	elseif (profession == "medic") then
		if (questStatus == 2) then
			createObserver(PARENTCHANGED, "HelperDroidQuest", "notifyParentChanged", pPlayer, 1)
			return
		elseif (questStatus == 3 or questStatus == 4 or questStatus == 6) then
			createObserver(ABILITYUSED, "HelperDroidQuest", "notifyAbilityUsed", pPlayer)
			return
		elseif (questStatus == 5) then
			createObserver(PROTOTYPECREATED, "HelperDroidQuest", "notifyObjectCrafted", pPlayer)
			return
		end

	elseif (profession == "entertainer") then
		if (questStatus == 1 or questStatus == 2) then
			createObserver(STARTENTERTAIN, "HelperDroidQuest", "notifyEntertaining", pPlayer, 1)
			return
		elseif (questStatus == 3) then
			createObserver(IMAGEDESIGNHAIR, "HelperDroidQuest", "notifyImageDesign", pPlayer, 1)
			return
		elseif (questStatus == 4) then
			createObserver(FLOURISH, "HelperDroidQuest", "notifyFlourishing", pPlayer, 1)
			return
		elseif (questStatus == 5) then
			createObserver(PARENTCHANGED, "HelperDroidQuest", "notifyParentChanged", pPlayer, 1)
			return
		elseif (questStatus == 6) then
			createObserver(WASLISTENEDTO, "HelperDroidQuest", "notifyNewPatron", pPlayer, 1)
			createObserver(WASWATCHED, "HelperDroidQuest", "notifyNewPatron", pPlayer, 1)
			return
		end

	end
end

-- ========= END Quest Task Handler ==========

-- ========= New Player Item Choice and Creation ==========

function HelperDroidQuest:giveProfessionItem(pPlayer, profession)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		if (pDroid ~= nil) then
			spatialChat(pDroid, "@new_player:inventory_full")
		end
		return
	end

	if (profession == "artisan") then
		local pCraftingTool = giveItem(pInventory, "object/tangible/crafting/station/generic_tool.iff", -1)

		if (pCraftingTool ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@new_player:given_crafting_tool")
		end

		local pSurveryDevice = giveItem(pInventory, "object/tangible/survey_tool/survey_tool_mineral.iff", -1)

		if (pSurveryDevice ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@new_player:given_survey_device")
		end
	elseif (profession == "scout") then
		local pCraftingTool = giveItem(pInventory, "object/tangible/crafting/station/generic_tool.iff", -1)

		if (pCraftingTool ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@new_player:given_crafting_tool")
		end
	elseif (profession == "medic") then
		local pCraftingTool = giveItem(pInventory, "object/tangible/crafting/station/generic_tool.iff", -1)

		if (pCraftingTool ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@new_player:given_crafting_tool")
		end
	elseif (profession == "entertainer") then
		local pInstrument = giveItem(pInventory, "object/tangible/instrument/slitherhorn.iff", -1)

		if (pInstrument ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@new_player:given_slitherhorn")
		end
	end
end

function HelperDroidQuest:chooseWeapon(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)
	local profession = readStringData(playerID .. ":HelperDroid:profession:")

	if (pDroid == nil) then
		return
	end

	local sui = SuiMessageBox.new("HelperDroidQuest", "weaponCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,200")

	local prompt = "@new_player:" .. profession .. "_quest_weapon_choice"

	sui.setPrompt(prompt)
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	local items = {}

	if (profession == "brawler") then
		items = self.brawler
	elseif (profession == "marksman") then
		items = self.marksman
	end

	for i = 1, #items, 1 do
		local buttonText = "@new_player:" .. items[i] .. "_button"

		if (i == 1) then
			sui.setCancelButtonText(buttonText)
		elseif (i == 2) then
			sui.setOtherButtonText(buttonText)
		elseif (i == 3) then
			sui.setOkButtonText(buttonText)
		end
	end

	sui.sendTo(pPlayer)
end

function HelperDroidQuest:weaponCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local revertPressed = args[1]

	local playerID = SceneObject(pPlayer):getObjectID()

	if (cancelPressed) then
		self:givePlayerWeapon(pPlayer, 1)
	elseif (revertPressed ~= nil) then
		self:givePlayerWeapon(pPlayer, 2)
	elseif (eventIndex == 0) then
		self:givePlayerWeapon(pPlayer, 3)
	end
end

function HelperDroidQuest:givePlayerWeapon(pPlayer, weapon)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:")
	local templates = self.weaponTemplates[profession]

	local weaponTemp = templates[weapon]

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	if pInventory == nil then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		if (pDroid ~= nil) then
			spatialChat(pDroid, "@new_player:inventory_full")
		end
		return
	end

	local pWeapon = giveItem(pInventory, weaponTemp, -1)

	if (pWeapon ~= nil) then
		local profession = readStringData(playerID .. ":HelperDroid:profession:")

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 1)

		local message = "You received a " .. SceneObject(pWeapon):getDisplayedName()
		CreatureObject(pPlayer):sendSystemMessage(message)

		createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
	end
end

function HelperDroidQuest:grantMedicResources(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isCreatureObject()) then
		return
	end

	givePlayerResource(pPlayer, "organic", 8)
	givePlayerResource(pPlayer, "inorganic", 8)
end

-- ========= END New Player Item Choice and Creation ==========

-- ========= Observer Handlers ==========

function HelperDroidQuest:notifyKilledCreature(pPlayer, pVictim)
	if (pPlayer == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local weaponType = CreatureObject(pPlayer):getWeaponType()
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "brawler") then
		-- Make sure they are using brawler weapon: unarmed = 16 one handed = 32 two handed = 64
		if (weaponType == 16 or weaponType == 32 or weaponType == 64 or weaponType == 128) then
			if (questStatus == 2) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

				createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
				return 1
			elseif (questStatus == 6) then
				local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:") + 1
				writeData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:", killCount)

				if (killCount >= 10 and pDroid ~= nil) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end
				return 0
			end
		end
	elseif (profession == "marksman") then
		-- Make sure they are using marksman weapon: pistol = 256 carbine = 512 rifle = 1024
		if (weaponType == 256 or weaponType == 512 or weaponType == 1024) then
			if (questStatus == 2) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

				createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
				return 1
			elseif (questStatus == 5) then
				local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:") + 1
				writeData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:", killCount)

				if (killCount >= 10 and pDroid ~= nil) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)
					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)

					deleteData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:")
					return 1
				end
				return 0
			end
		end
	end

	return 0
end

function HelperDroidQuest:notifyAbilityUsed(pPlayer, pTarget, abilityHash)
	if (pPlayer == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "brawler") then
		if (questStatus == 3 and abilityHash == getHashCode("berserk1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (questStatus == 4 and (abilityHash == getHashCode("melee1hlunge1") or abilityHash == getHashCode("melee2hlunge1") or abilityHash == getHashCode("unarmedlunge1") or abilityHash == getHashCode("polearmlunge1"))) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

				createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
				return 1
		elseif (questStatus == 5 and abilityHash == getHashCode("centerofbeing")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		end
	elseif  (profession == "marksman") then
		if (questStatus == 3 and abilityHash == getHashCode("pointblanksingle1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (questStatus == 4 and abilityHash == getHashCode("overchargeshot1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		end
	elseif  (profession == "medic") then
		if (questStatus == 3 and abilityHash == getHashCode("diagnose") and pTarget ~= nil and pTarget ~= pPlayer) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (abilityHash == getHashCode("tendwound") and pTarget ~= nil and pTarget ~= pPlayer) then
			if (questStatus == 4) then
				local pCell = SceneObject(pPlayer):getParent()

				if (pCell == nil) then
					return 0
				end

				local pBuilding = SceneObject(pCell):getParent()

				if (pBuilding == nil or not SceneObject(pBuilding):isBuildingObject()) then
					return 0
				end

				if (string.find(SceneObject(pBuilding):getTemplateObjectPath(), "hospital")) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end
			elseif (questStatus == 6) then
				local tendedPatients = readStringVectorSharedMemory(playerID .. ":" .. profession .. ":HelperDroid:tendedPatients:")
				local targetID = SceneObject(pTarget):getObjectID()

				for i = 1, #tendedPatients, 1 do
					local patientID = tonumber(tendedPatients[i])

					if (targetID == patientID) then
						return 0
					end
				end

				if (#tendedPatients + 1 < 5) then
					tendedPatients[#tendedPatients + 1] = tostring(targetID)

					writeStringVectorSharedMemory(playerID .. ":" .. profession .. ":HelperDroid:tendedPatients:", tendedPatients)
					return 0
				else
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					deleteStringVectorSharedMemory(playerID .. ":" .. profession .. ":HelperDroid:tendedPatients:")
					return 1
				end
			end
		end
	end

	return 0
end

function HelperDroidQuest:notifyCreatureHarvested(pPlayer, pResourceSpawn, totalResources)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "scout" and totalResources > 0) then
		if (questStatus == 2) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (questStatus == 3) then
			local totalBone = readData(playerID .. ":" .. profession .. ":HelperDroid:boneHarvested:")
			local totalHide = readData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")
			local boneType = "bone"
			local hideType = "hide"

			local pSpawn = LuaResourceSpawn(pResourceSpawn)

			if (pSpawn ~= nil) then
				if (pSpawn:isType(boneType)) then
					totalBone = totalBone + totalResources
					writeData(playerID .. ":" .. profession .. ":HelperDroid:boneHarvested:", totalBone)
				end

				if (pSpawn:isType(hideType)) then
					totalHide = totalHide + totalResources
					writeData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:", totalHide)
				end

				if (totalBone >= 3 and totalHide >= 3) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:boneHarvested:")
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end
			end
		elseif (questStatus == 6) then
			local totalHide = readData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")
			local hideType = "hide"

			local pSpawn = LuaResourceSpawn(pResourceSpawn)

			if (pSpawn ~= nil) then
				if (pSpawn:isType(hideType)) then
					totalHide = totalHide + totalResources
					writeData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:", totalHide)
				end

				if (totalHide >= 90) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end
			end
		end
	end

	return 0
end

function HelperDroidQuest:notifyObjectCrafted(pPlayer, pItem, practice)
	if (pPlayer == nil or pItem == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "scout" and questStatus == 4) then
		if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/tangible/scout/trap/trap_drowsy_dart") and not practice) then
			return 0
		end

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

		createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1
	elseif (profession == "medic" and questStatus == 5) then
		if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/tangible/medicine/crafted/crafted_stimpack") and not practice) then
			return 0
		end

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

		createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1
	elseif (profession == "artisan") then
		if (questStatus == 4) then
			if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/tangible/survey_tool/survey_tool_liquid") and not practice) then
				return 0
			end

			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

			createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (questStatus == 5) then
			if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/weapon/ranged/rifle/rifle_cdef")) then
				return 0
			end

			local totalRifles = readData(playerID .. ":" .. profession .. ":HelperDroid:riflesCrafted:") + 1

			if (totalRifles > 4) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)
				deleteData(playerID .. ":" .. profession .. ":HelperDroid:riflesCrafted:")

				createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
				return 1
			end

			writeData(playerID .. ":" .. profession .. ":HelperDroid:riflesCrafted:", totalRifles)
		end
	end

	return 0
end

function HelperDroidQuest:notifyCampDeployed(pPlayer, pCampArea)
	if (pPlayer == nil or pCampArea == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "scout" and questStatus == 5) then
		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

		createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1
	end

	return 0
end

function HelperDroidQuest:notifySurvey(pPlayer, pResourceSpawn, density)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")
	local pSpawn = LuaResourceSpawn(pResourceSpawn)

	if (pSpawn ~= nil) then
		if (not pSpawn:isType("mineral")) then
			return 0
		end

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 1)

		createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1

	end
end

function HelperDroidQuest:notifySampleTaken(pPlayer, pResourceSpawn, unitsSampled)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "artisan" and  unitsSampled > 0) then
		local pSpawn = LuaResourceSpawn(pResourceSpawn)

		if (pSpawn ~= nil) then
			local mineralType = "mineral"
			local metalType = "metal"

			if (questStatus == 2 and pSpawn:isType(mineralType)) then
				local totalMineral = readData(playerID .. ":" .. profession .. ":HelperDroid:mineralSampled:")
				totalMineral = totalMineral + unitsSampled

				if (totalMineral > 7) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:mineralSampled:")

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end

				writeData(playerID .. ":" .. profession .. ":HelperDroid:mineralSampled:", totalMineral)
			elseif (questStatus == 3 and pSpawn:isType(metalType)) then
				local totalMetal = readData(playerID .. ":" .. profession .. ":HelperDroid:metalSampled:")
				totalMetal = totalMetal + unitsSampled

				if (totalMetal > 18) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:metalSampled:")

					createEvent(1000, "HelperDroidQuest", "giveReward", pPlayer, profession)
					return 1
				end

				writeData(playerID .. ":" .. profession .. ":HelperDroid:metalSampled:", totalMetal)
			end
		end
	end

	return 0
end

function HelperDroidQuest:notifyEntertaining(pPlayer, pPlayer2)
	if (pPlayer == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "entertainer") then
		if (questStatus == 1 and CreatureObject(pPlayer):isDancing()) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 1)

			createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		elseif (questStatus == 2 and CreatureObject(pPlayer):isPlayingMusic()) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

			createEvent(4000, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		end
	end

	return 0
end

function HelperDroidQuest:notifyFlourishing(pPlayer, flourishID)
	if (pPlayer == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "entertainer" and questStatus == 4) then
		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

		createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1
	end

	return 0
end

function HelperDroidQuest:notifyParentChanged(pPlayer, pParent)
	if (pPlayer == nil or pParent == nil) then
		return 0
	end

	local pBuilding = SceneObject(pParent):getParent()

	if (pBuilding == nil or not SceneObject(pBuilding):isBuildingObject()) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "entertainer" and questStatus == 5) then
		if (string.find(SceneObject(pBuilding):getTemplateObjectPath(), "cantina") or string.find(SceneObject(pBuilding):getTemplateObjectPath(), "theater")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

			createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		end
	elseif (profession == "medic" and questStatus == 2) then
		if (string.find(SceneObject(pBuilding):getTemplateObjectPath(), "hospital")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

			createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
			return 1
		end
	end

	return 0
end

function HelperDroidQuest:notifyNewPatron(pPlayer, pPatron)
	if (pPlayer == nil or pPatron == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "entertainer" and questStatus == 6) then
		local totalPatrons = readData(playerID .. ":" .. profession .. ":HelperDroid:totalPatrons:") + 1

		if (totalPatrons >= 7) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)

			createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
			deleteData(playerID .. ":" .. profession .. ":HelperDroid:totalPatrons:")
			return 1
		end

		writeData(playerID .. ":" .. profession .. ":HelperDroid:totalPatrons:", totalPatrons)
	end

	return 0
end

function HelperDroidQuest:notifyImageDesign(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	if (profession == "entertainer" and questStatus == 3) then
		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

		createEvent(100, "HelperDroidQuest", "giveReward", pPlayer, profession)
		return 1
	end
	return 0
end

-- ========= END Observer Handlers ==========

-- ========= Reward Generation, Experience and Credits ==========

function HelperDroidQuest:giveReward(pPlayer, profession)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	if (pDroid == nil) then
		return
	end

	local questsComplete = tonumber(getQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:"))
	local randomMessage = getRandomNumber(5)
	local message = "@new_player:task_complete_no_reward_0" .. tostring(randomMessage)
	local ttString = ""
	local DI = 0

	local credits = 100
	local experience = 50
	local xpType = "combat_general"

	if (profession == "brawler" or profession == "marksman") then
		local weaponType = CreatureObject(pPlayer):getWeaponType()

		if (weaponType == 16) then
			xpType = "combat_meleespecialize_unarmed"
		elseif (weaponType == 32) then
			xpType = "combat_meleespecialize_onehand"
		elseif (weaponType == 64) then
			xpType = "combat_meleespecialize_twohand"
		elseif (weaponType == 128) then
			xpType = "combat_meleespecialize_polearm"
		elseif (weaponType == 256) then
			xpType = "combat_rangedspecialize_pistol"
		elseif (weaponType == 512) then
			xpType = "combat_rangedspecialize_carbine"
		elseif (weaponType == 1024) then
			xpType = "combat_rangedspecialize_rifle"
		end
	elseif (profession == "scout") then
		xpType = "scout"
	elseif (profession == "artisan") then
		xpType = "crafting_general"
	elseif (profession == "medic") then
		xpType = "medical"
	elseif (profession == "entertainer") then
		xpType = "entertainer_healing"
	end

	--[[ Total Quests:
		- Brawler: 6
		- Marksman: 5
		- Scout: 6
		- Entertainer: 6
		- Artisan: 5
		- Medic: 6
	]]

	if (questsComplete == 1) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		self:grantFireWorksReward(pDroid, pPlayer)

		DI = credits
		message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		ttString = "1st"
	elseif (questsComplete == 2) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		ttString = "2nd"
	elseif (questsComplete == 3) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if ((profession == "marksman" or profession == "artisan") and not self:checkHasReward(pPlayer, "cloning")) then
			self:grantCouponReward(pDroid, pPlayer, "cloning")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		elseif (profession == "medic") then
			self:grantMedicResources(pPlayer)
		end

		ttString = "3rd"
	elseif (questsComplete == 4) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if ((profession == "marksman" or profession == "artisan") and not self:checkHasReward(pPlayer, "travel")) then
			self:grantCouponReward(pDroid, pPlayer, "travel")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		elseif (not self:checkHasReward(pPlayer, "cloning")) then
			self:grantCouponReward(pDroid, pPlayer, "cloning")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		ttString = "4th"
	elseif (questsComplete == 5) then
		if (profession == "marksman" or profession == "artisan") then
			experience = 200
			credits = 2000

			if (not self:checkHasReward(pPlayer, "vehicle")) then
				self:grantCouponReward(pDroid, pPlayer, "vehicle")
				DI = credits
				message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
			end
		elseif (not self:checkHasReward(pPlayer, "travel")) then
			self:grantCouponReward(pDroid, pPlayer, "travel")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		ttString = "5th"
	elseif (questsComplete == 6) then
		experience = 200
		credits = 2000

		if (not self:checkHasReward(pPlayer, "vehicle")) then
			self:grantCouponReward(pDroid, pPlayer, "vehicle")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		ttString = "6th"
	end

	local rewardString = LuaStringIdChatParameter(message)

	if (DI ~= 0) then
		rewardString:setDI(DI)
	end

	rewardString:setTT(ttString)
	rewardString:setTU(SceneObject(pDroid):getCustomObjectName())
	CreatureObject(pPlayer):sendSystemMessage(rewardString:_getObject())

	if ((profession == "marksman" or profession == "artisan") and questsComplete == 5) then
		self:finalQuestSui(pDroid, pPlayer, profession)
	elseif (questsComplete < 6) then
		self:professionQuestSui(pDroid, pPlayer, profession)
	else
		self:finalQuestSui(pDroid, pPlayer, profession)
	end
end

function HelperDroidQuest:grantFireWorksReward(pDroid, pPlayer)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		spatialChat(pDroid, "@new_player:inventory_full")
		return
	end

	local fireworkTemp = self.fireworks[getRandomNumber(2)]

	local firework = giveItem(pInventory, fireworkTemp, -1)

	if (firework ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@new_player:completed_first_task")
		CreatureObject(pPlayer):sendSystemMessage("@new_player:given_fireworks")
	end
end

function HelperDroidQuest:grantCouponReward(pDroid, pPlayer, couponString)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	local couponTemp = self.coupons[couponString]

	if pInventory == nil then
		return
	end

	if (SceneObject(pInventory):isContainerFullRecursive()) then
		spatialChat(pDroid, "@new_player:inventory_full")
		return
	end

	local couponItem = giveItem(pInventory, couponTemp, -1)

	if (couponItem ~= nil) then
		local message = "@new_player:"
		local message2 = "@new_player:"

		if (couponString == "cloning") then
			message = message .. "given_cloning_coupon"
			message2 = message2 .. "completed_second_task"
		elseif (couponString == "travel") then
			message = message .. "given_travel_coupon"
			message2 = message2 .. "completed_third_task"
		elseif (couponString == "vehicle") then
			message = message .. "given_vehicle_coupon"
			message2 = message2 .. "completed_first_profession"
		end

		CreatureObject(pPlayer):sendSystemMessage(message2)
		CreatureObject(pPlayer):sendSystemMessage(message)
	end
end

function HelperDroidQuest:checkHasReward(pPlayer, reward)
	if (pPlayer == nil) then
		return false
	end

	local template = self.coupons[reward]
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil then
		return false
	end

	local pObject = getContainerObjectByTemplate(pInventory, template, true)

	if (pObject ~= nil) then
		return true
	end

	return false
end

-- ========= END Reward Generation, Experience and Credits ==========