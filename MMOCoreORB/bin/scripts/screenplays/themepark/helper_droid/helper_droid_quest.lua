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
		{0, "human"},
		{1, "rodian"},
		{2, "trandoshan"},
		{3, "moncal"},
		{4, "wookie"},
		{5, "bothan"},
		{6, "twilek"},
		{7, "zabrak"},
		{33, "ithorian"},
		{49, "sullustan"},
	},
}

registerScreenPlay("HelperDroidQuest", false)

-- ========= Sui Functions ==========

function HelperDroidQuest:professionQuestSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = SceneObject(pDroid):getObjectID()

	writeData(playerID .. ":HelperDroidID:", droidID)
	writeStringData(playerID .. ":HelperDroid:profession:", profession)

	-- QUEST RESET
	--setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 0)
	--writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", 0)

	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")
	local questsComplete = tonumber(getQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:"))

	if (questsComplete == nil) then
		questsComplete = 0
	elseif (questsComplete == 6 or (questsComplete == 5 and (profession == "marksman" or profession == "artisan"))) then
		self:finalQuestSui(pDroid, pPlayer, profession)
		return
	end

	if (questStatus < questsComplete) then
		questStatus = questsComplete
		writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", questsComplete)
	end

	print("professionQuestSui - quest status = " .. questStatus ..  " quests complete = " .. questsComplete)

	if ((profession == "brawler" or profession == "marksman") and questStatus == 1 and questsComplete == 0) then
		createEvent(100, "HelperDroidQuest", "chooseWeapon", pPlayer, "")
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
	if (questStatus > 0 and profession ~= "artisan") then
		questStatus = questStatus + 1
	end

	local prompt = "@new_player:" .. profession .. "_quest_0" .. tostring(questStatus)

	if (questsComplete >= 1) then
		sui.setCancelButtonText("@new_player:not_now_button")
		sui.setOkButtonText("@new_player:give_quest_button")
	else
		sui.setCancelButtonText("@new_player:not_now_button")
		sui.setOkButtonText("@new_player:lets_start_button")
	end

	if (profession == "entertainer" and questStatus == 3) then
		local species = CreatureObject(pPlayer):getSpecies()
		local speciesStrings = self.speciesStrings
		local string = ""

		for i = 0, #speciesString, 1 do
			local stringNum = speciesString[i][1]

			if (stringNum == species) then
				string = speciesString[i][2]
				break
			end
		end

		prompt = prompt .. "_" .. string

		-- 3 = moncal, 4 = wookie, 49 = sullustan, 33 = ithorian
		if (species == 4 or species == 3 or species == 40 or species == 33) then
			-- These 4 species have to skip quest 3 for entertainer
			sui.setOkButtonTest("@new_player:continue_button")
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
		return
	end

	print("professionCallback - event index = " .. eventIndex .. " quest status = " .. questStatus .. " profession = " .. profession)

	-- OK response
	if (eventIndex == 0) then
		if (questStatus == 0) then
			writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", 1)

			if (profession == "scout" or profession == "artisan") then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 1)
			end

			self:professionQuestSui(pDroid, pPlayer, profession)
			return
		else
			-- Player has accepted to start quest. Set their status, completed will be set when task is finished
			writeData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:", questStatus + 1)

			if (questStatus == 3 and profession == "entertainer") then
				local species = CreatureObject(pPlayer):getSpecies()

				if (species == 4 or species == 3 or species == 40 or species == 33) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

					self:professionQuestSui(pDroid, pPlayer, profession)
					return
				end
			end

			self:giveQuest(pPlayer, profession)
		end
	end
end

function HelperDroidQuest:onQuestSui(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	print("onQuestSui - questStatus = " .. questStatus)

	local sui = SuiMessageBox.new("HelperDroidQuest", "onQuestCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,500")
	sui.setForceCloseDistance(10)

	sui.setCancelButtonText("@new_player:no_help_needed_button")
	sui.setOkButtonText("@new_player:help_please_button")

	local prompt = "@new_player:" .. profession .. "_quest_0" .. questStatus

	-- Kill Count Quest Help prompt
	if (questStatus == 6 and profession == "brawler") then
		local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:")

		prompt = "@new_player:" .. profession .. "_quest_06";
		local message2 = "@new_player:" .. profession .. "_quest_06_b";

		prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(killCount) .. " @new_player:counter_not_update \\#. ";
	elseif (questStatus == 5 and profession == "marksman") then
		local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:")

		prompt = "@new_player:" .. profession .. "_quest_05";
		local message2 = "@new_player:" .. profession .. "_quest_05_b";

		prompt = prompt .. "      \\#pcontrast1 " .. message2 .. " " .. tostring(killCount) .. " @new_player:counter_not_update \\#. ";
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

	if (eventIndex == 0) then
		if (profession == "brawler" or profession == "marksman") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("Combat.Targeting")
		elseif (profession == "scout") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingScout")
		elseif (profession == "artisan") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingArtisan")
		elseif (profession == "medic") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingMedic")
		elseif (profession == "entertainer") then
			CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG.WhereDoIBegin.Professions.PlayingEntertainer")
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

	print("giveQuest - profession = " .. profession .. " questStatus = " .. questStatus)

	-- Quests here will start with a status of 3 and end at final of 6
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
		if (questStatus == 2 or questStatus == 3 or questStats == 4) then
			createObserver(SAMPLE, "HelperDroidQuest", "notifySampleTaken", pPlayer, 1)
			return
		end


	elseif (profession == "medic") then


	elseif (profession == "entertainer") then

	end
end

-- ========= END Quest Task Handler ==========

-- ========= New Player Item Choice and Creation ==========

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

	deleteData(playerID .. ":HelperDroidID:")

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

		if (pDroid ~= nil) then
			self:professionQuestSui(pDroid, pPlayer, profession)
		end
	end
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

	print("notifyKilledCreature - profession = " .. profession .. " quest status = " .. questStatus .. " weapon type = " .. weaponType)

	if (profession == "brawler") then
		-- Make sure they are using brawler weapon: unarmed = 16 one handed = 32 two handed = 64
		if (weaponType == 16 or weaponType == 32 or weaponType == 64 or weaponType == 128) then
			if (questStatus == 2) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

				if (pDroid ~= nil) then
					self:giveReward(pDroid, pPlayer, profession)
				end
				return 1
			elseif (questStatus == 6) then
				local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:") + 1
				writeData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:", killCount)

				if (killCount >= 10 and pDroid ~= nil) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)
					self:giveReward(pDroid, pPlayer, profession)
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

				if (pDroid ~= nil) then
					self:giveReward(pDroid, pPlayer, profession)
				end
				return 1
			elseif (questStatus == 5) then
				local killCount = readData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:") + 1
				writeData(playerID .. ":" .. profession .. ":HelperDroid:questKillCount:", killCount)

				if (killCount >= 10 and pDroid ~= nil) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)
					self:giveReward(pDroid, pPlayer, profession)

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

	print("notifyAbilityUsed - profession = " .. profession .. " quest status = " .. questStatus .." abilityHash = " .. abilityHash)

	if (profession == "brawler") then
		if (questStatus == 3 and abilityHash == getHashCode("berserk1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

			if (pDroid ~= nil) then
				self:giveReward(pDroid, pPlayer, profession)
			end
			return 1
		elseif (questStatus == 4 and (abilityHash == getHashCode("melee1hlunge1") or abilityHash == getHashCode("melee2hlunge1") or abilityHash == getHashCode("unarmedlunge1") or abilityHash == getHashCode("polearmlunge1"))) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

				if (pDroid ~= nil) then
					self:giveReward(pDroid, pPlayer, profession)
				end
				return 1
		elseif (questStatus == 5 and abilityHash == getHashCode("centerofbeing")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

			if (pDroid ~= nil) then
				self:giveReward(pDroid, pPlayer, profession)
			end
			return 1
		end
	elseif  (profession == "marksman") then
		if (questStatus == 3 and abilityHash == getHashCode("pointblanksingle1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)

			if (pDroid ~= nil) then
				self:giveReward(pDroid, pPlayer, profession)
			end
			return 1
		elseif (questStatus == 4 and abilityHash == getHashCode("overchargeshot1")) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

			if (pDroid ~= nil) then
				self:giveReward(pDroid, pPlayer, profession)
			end
			return 1
		end
	end

	return 0
end

function HelperDroidQuest:notifyCreatureHarvested(pPlayer, pResourceSpawn, totalResources)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	print("notifyCreatureHarvested - profession = " .. profession .. " quest status = " .. questStatus .." total resources = " .. totalResources)

	if (profession == "scout" and totalResources > 0) then
		if (questStatus == 2) then
			setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

			if (pDroid ~= nil) then
				self:giveReward(pDroid, pPlayer, profession)
			end
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

					if (pDroid ~= nil) then
						self:giveReward(pDroid, pPlayer, profession)
					end
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

				print(" total hide == " .. totalHide)

				if (totalHide >= 90) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 6)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:hideHarvested:")

					if (pDroid ~= nil) then
						self:giveReward(pDroid, pPlayer, profession)
					end
					return 1
				end
			end
		end
	end

	return 0
end

function HelperDroidQuest:notifyObjectCrafted(pPlayer, pItem)
	if (pPlayer == nil or pItem == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	print("notifyObjectCrafted - profession = " .. profession .. " quest status = " .. questStatus)

	if (profession == "scout" and questStatus == 4) then
		if (not string.find(SceneObject(pItem):getTemplateObjectPath(), "object/tangible/scout/trap/trap_drowsy_dart")) then
			return 0
		end

		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)

		if (pDroid ~= nil) then
			self:giveReward(pDroid, pPlayer, profession)
		end
		return 1
	end

	return 0
end

function HelperDroidQuest:notifyCampDeployed(pPlayer, pCampArea)
	if (pPlayer == nil or pCampArea == nil) then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	print("notifyCampDeployed - profession = " .. profession .. " quest status = " .. questStatus)

	if (profession == "scout" and questStatus == 5) then
		setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 5)

		if (pDroid ~= nil) then
			self:giveReward(pDroid, pPlayer, profession)
		end
		return 1
	end

	return 0
end

function HelperDroidQuest:notifySampleTaken(pPlayer, pResourceSpawn, totalResources)
	if (pPlayer == nil or pResourceSpawn == nil) then
		return 1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)

	local profession = readStringData(playerID .. ":HelperDroid:profession:", profession)
	local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

	print("notifyCreatureHarvested - profession = " .. profession .. " quest status = " .. questStatus .." total resources = " .. totalResources)

	if (profession == "artisan" and totalResources > 0) then
		local mineralType = "mineral"
		local metalType = "metal"
		local pSpawn = LuaResourceSpawn(pResourceSpawn)

		if (pSpawn ~= nil) then
			if (not pSpawn:isType(mineralType)) then
				return 0
			end

			if (questStatus == 2) then
				setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 2)

				if (pDroid ~= nil) then
					self:giveReward(pDroid, pPlayer, profession)
				end
				return 1
			elseif (questStatus == 3) then
				local totalMineral = readData(playerID .. ":" .. profession .. ":HelperDroid:mineralSampled:")
				totalMineral = totalMineral + totalResources

				if (totalMineral >= 8) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 3)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:mineralSampled:")

					if (pDroid ~= nil) then
						self:giveReward(pDroid, pPlayer, profession)
					end
					return 1
				end
			elseif (questStatus == 4 and pSpawn:isType(metalType)) then
				local totalMetal = readData(playerID .. ":" .. profession .. ":HelperDroid:metalSampled:")
				totalMetal = totalMetal + totalResources

				if (totalMetal >= 19) then
					setQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:", 4)
					deleteData(playerID .. ":" .. profession .. ":HelperDroid:metalSampled:")

					if (pDroid ~= nil) then
						self:giveReward(pDroid, pPlayer, profession)
					end
					return 1
				end
			end
		end
	end

	return 0
end

-- ========= END Observer Handlers ==========

-- ========= Reward Generation, Experience and Credits ==========

function HelperDroidQuest:giveReward(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questsComplete = tonumber(getQuestStatus(playerID .. ":" .. profession .. ":HelperDroid:completeQuests:"))

	print("giveReward - info - questsComplete = " .. questsComplete .. " profession = " .. profession)

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
		xpType = "medic"
	elseif (profession == "entertainer") then
		--xpType = ?
	end

	-- All professions have 6 quests except for artisan and marksman, which have 5

	if (questsComplete == 2) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		self:grantFireWorksReward(pDroid, pPlayer)

		ttString = "1st"
		DI = credits
		message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
	elseif (questsComplete == 3) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if ((profession == "marksman" or profession == "artisan") and not self:checkHasReward(pPlayer, "cloning")) then
			self:grantCouponReward(pDroid, pPlayer, "cloning")
		end

		DI = credits
		message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		ttString = "2nd"
	elseif (questsComplete == 4) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if ((profession == "marksman" or profession == "artisan") and not self:checkHasReward(pPlayer, "travel")) then
			self:grantCouponReward(pDroid, pPlayer, "travel")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		if (not self:checkHasReward(pPlayer, "cloning")) then
			self:grantCouponReward(pDroid, pPlayer, "cloning")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		ttString = "3rd"
	elseif (questsComplete == 5) then
		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if (profession == "marksman" or profession == "artisan") then
			experience = 200
			credits = 2000
			ttString = "4th"

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

		ttString = "4th"
	elseif (questsComplete == 6) then
		experience = 200
		credits = 2000

		CreatureObject(pPlayer):awardExperience(xpType, experience, true)
		CreatureObject(pPlayer):addCashCredits(credits, true)

		if (not self:checkHasReward(pPlayer, "vehicle")) then
			self:grantCouponReward(pDroid, pPlayer, "vehicle")
			DI = credits
			message = "@new_player:task_complete_reward_0" .. tostring(randomMessage)
		end

		ttString = "5th"
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
		--('string/en/new_player.stf', 157, 'completed_first_task', 'Congratulations on completing your first ever task! If you wish to celebrate, you can use these fireworks.'),
		CreatureObject(pPlayer):sendSystemMessage("@new_player:completed_first_task")

		--('string/en/new_player.stf', 143, 'given_fireworks', 'A firework device has been placed in your inventory.'),
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