local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")
require("utils.helpers")
require("screenplays.screenplay")

-- The valid screenPlayState val's for branch unlock are as follows:
-- 0: Does NOT qualify for branch unlock.
-- 1: Qualifies for branch unlock, not unlocked. NOTE: This only applies to Hologrinder boxes.
-- 2: Branch Unlocked.

ExperienceConverter = ScreenPlay:new {
	xpConversion = {
		combat = {
			{ "bountyhunter", 5 },
			{ "combat_general", 3 },
			{ "combat_meleespecialize_onehand", 30 },
			{ "combat_meleespecialize_polearm", 30 },
			{ "combat_meleespecialize_twohand", 30 },
			{ "combat_meleespecialize_unarmed", 30 },
			{ "combat_rangedspecialize_carbine", 30 },
			{ "combat_rangedspecialize_heavy", 30 },
			{ "combat_rangedspecialize_pistol", 30 },
			{ "combat_rangedspecialize_rifle", 30 },
			{ "squadleader", 90 }
		},
		senses = {
			{ "bio_engineer_dna_harvesting", 3 },
			{ "camp", 5 },
			{ "creaturehandler", 9 },
			{ "dance", 10 },
			{ "entertainer_healing", 10 },
			{ "imagedesigner", 7 },
			{ "medical", 10 },
			{ "merchant", 4 },
			{ "music", 10 },
			{ "political", 3 },
			{ "resource_harvesting_inorganic", 10 },
			{ "scout", 8 },
			{ "slicing", 3 },
			{ "trapping", 25 },
		},
		reflex = {
			{ "bountyhunter", 5 },
			{ "combat_general", 3 },
			{ "combat_meleespecialize_onehand", 30 },
			{ "combat_meleespecialize_polearm", 30 },
			{ "combat_meleespecialize_twohand", 30 },
			{ "combat_meleespecialize_unarmed", 30 },
			{ "combat_rangedspecialize_carbine", 30 },
			{ "combat_rangedspecialize_heavy", 30 },
			{ "combat_rangedspecialize_pistol", 30 },
			{ "combat_rangedspecialize_rifle", 30 },
			{ "squadleader", 90 }
		},
		crafting = {
			{ "crafting_bio_engineer_creature", 4 },
			{ "crafting_clothing_armor", 5 },
			{ "crafting_clothing_general", 5 },
			{ "crafting_droid_general", 5 },
			{ "crafting_food_general", 5 },
			{ "crafting_general", 8 },
			{ "crafting_medicine_general", 5 },
			{ "crafting_spice", 5 },
			{ "crafting_structure_general", 35 },
			{ "crafting_weapons_general", 5 }
		}
	}
}

function ExperienceConverter:getBranchLearnList(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local branchList = "\nNothing"
	local hasBranch = false
	for i = 1, #VillageJediManagerCommon.forceSensitiveBranches, 1 do
		local branchName = VillageJediManagerCommon.forceSensitiveBranches[i]

		if (VillageJediManagerCommon.hasUnlockedBranch(pPlayer, branchName)) then
			local localizedBranch = getStringId("@quest/force_sensitive/utils:" .. branchName)
			if (hasBranch) then
				branchList = branchList .. "\n" .. localizedBranch
			else
				hasBranch = true
				branchList = "\n" .. localizedBranch
			end
		end
	end

	return branchList
end

function ExperienceConverter:sendConversionSUI(pPlayer, pNpc, experienceType)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):closeSuiWindowType(SuiWindowType.FS_EXP_CONVERT)

	local conversionList = self.xpConversion[experienceType]

	if (conversionList == nil) then
		printLuaError("ExperienceConverter:sendConversionSUI, could not grab xp conversion table for type " .. experienceType)
		return
	end

	local xpList = { }

	for i = 1, #conversionList, 1 do
		local xpAmount = PlayerObject(pGhost):getExperience(conversionList[i][1])

		if (xpAmount >= conversionList[i][2]) then
			table.insert(xpList, conversionList[i][1])
		end
	end

	if (#xpList <= 0) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_for_conversion")
		return
	end

	local sui = SuiListBox.new("ExperienceConverter", "convertXpTypeCallback")

	sui.setTargetNetworkId(SceneObject(pNpc):getObjectID())
	sui.setTitle("@quest/force_sensitive/utils:xp_transfer_prompt")
	sui.setPrompt("Select the experience you wish to convert to " .. getStringId("@exp_n:fs_" .. experienceType) .. ".")

	for i = 1, #xpList, 1 do
		sui.add(getStringId("@exp_n:" .. xpList[i]), xpList[i])
	end
	sui.setWindowType(SuiWindowType.FS_EXP_CONVERT)
	sui.sendTo(pPlayer)

	writeStringSharedMemory(SceneObject(pPlayer):getObjectID() .. ":paemosConversionType", experienceType)
end

function ExperienceConverter:convertXpTypeCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)
	local xpType = readStringSharedMemory(playerID .. ":paemosConversionType")

	if (xpType == "") then
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	PlayerObject(pGhost):closeSuiWindowType(SuiWindowType.FS_EXP_CONVERT)

	local chosenXp = suiPageData:getStoredData(tostring(args))
	local xpAmount = PlayerObject(pGhost):getExperience(chosenXp)
	local conversionList = self.xpConversion[xpType]

	local ratio = 0

	for i = 1, #conversionList, 1 do
		if (conversionList[i][1] == chosenXp) then
			ratio = conversionList[i][2]
		end
	end

	if (xpAmount < ratio) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_xp")
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	if (ratio == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_illegal_type")
		deleteStringSharedMemory(playerID .. ":paemosConversionType")
		return
	end

	writeStringSharedMemory(playerID .. ":paemosChosenXp", chosenXp)
	local npcID = suiPageData:getTargetNetworkId()

	local sui = SuiTransferBox.new("ExperienceConverter", "convertXpTransferCallback")

	sui.setTargetNetworkId(npcID)
	sui.setTitle("@quest/force_sensitive/utils:xp_transfer_prompt")
	sui.setPrompt("How much " .. getStringId("@exp_n:" .. chosenXp) .. " experience do you wish to convert?\n(1 for " .. ratio .. " conversion ratio)")
	sui.setTransferFromText("Experience")
	sui.setTransferFromValue(xpAmount)
	sui.setTransferFromInputValue(xpAmount)
	sui.setTransferToText("To Convert")
	sui.setTransferToValue(0)
	sui.setTransferToInputValue(0)
	sui.setConversionFromRatio(1)
	sui.setConversionToRatio(1)
	sui.setWindowType(SuiWindowType.FS_EXP_CONVERT)

	sui.sendTo(pPlayer)
end

function ExperienceConverter:convertXpTransferCallback(pPlayer, pSui, eventIndex, transferInputFromValue, transferInputToValue)
	local playerID = SceneObject(pPlayer):getObjectID()
	local conversionType = readStringSharedMemory(playerID .. ":paemosConversionType")
	local chosenXp = readStringSharedMemory(playerID .. ":paemosChosenXp")
	deleteStringSharedMemory(playerID .. ":paemosConversionType")
	deleteStringSharedMemory(playerID .. ":paemosChosenXp")

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local xpToConvert = tonumber(transferInputToValue)

	if xpToConvert <= 0 then
		return
	end

	local conversionList = self.xpConversion[conversionType]
	local ratio = 0

	for i = 1, #conversionList, 1 do
		if (conversionList[i][1] == chosenXp) then
			ratio = conversionList[i][2]
		end
	end

	if (ratio == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_illegal_type")
		return
	end

	local xpAmount = PlayerObject(pGhost):getExperience(chosenXp)

	if (xpAmount < xpToConvert) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_xp")
		return
	end

	local convertedXp = math.floor(xpToConvert / ratio)
	local modValue = xpToConvert % ratio

	if modValue > 0 then
		xpToConvert = xpToConvert - modValue
	end

	local fsXpAmount = PlayerObject(pGhost):getExperience("fs_" .. conversionType)
	local fsXpCap = PlayerObject(pGhost):getExperienceCap("fs_" .. conversionType)

	if (fsXpCap > 0) then
		if (fsXpCap <= fsXpAmount) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_at_fs_skill_cap")
			return
		end

		if (fsXpAmount + convertedXp > fsXpCap) then
			convertedXp = fsXpCap - fsXpAmount;
			xpToConvert = convertedXp * ratio;
		end
	else
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_no_skill")
		return
	end

	if (convertedXp < 1) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_allocate_more_xp")
		return
	end

	CreatureObject(pPlayer):awardExperience(chosenXp, xpToConvert * -1, false)

	local messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_lose")
	messageString:setTO(getStringId("@exp_n:" .. chosenXp))
	messageString:setDI(xpToConvert)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	CreatureObject(pPlayer):awardExperience("fs_" .. conversionType, convertedXp, false)

	messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_gain")
	messageString:setTO(getStringId("@exp_n:fs_" .. conversionType))
	messageString:setDI(convertedXp)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

return ExperienceConverter
