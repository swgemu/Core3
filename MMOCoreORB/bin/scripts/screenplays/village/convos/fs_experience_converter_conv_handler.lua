local ExperienceConverter = require("screenplays.village.convos.convohelpers.experience_converter")
local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

fs_experience_converter_conv_handler = Object:new {}

function fs_experience_converter_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local convosession = CreatureObject(pConversingPlayer):getConversationSession()

	local lastConversationScreen = nil

	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end

	local conversation = LuaConversationTemplate(pConversationTemplate)

	local nextConversationScreen

	if (lastConversationScreen ~= nil) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)

		--Get the linked screen for the selected option.
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)

		nextConversationScreen = conversation:getScreen(optionLink)

		if nextConversationScreen ~= nil then
			local nextLuaConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("init")
		end
	else
		nextConversationScreen = conversation:getScreen("init")
	end
	return nextConversationScreen
end

function fs_experience_converter_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if screenID == "init" then
		pConversationScreen = fs_experience_converter_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "cs_jsPlumb_1_7" then
		local nextUnlockableBranches = ExperienceConverter:getNextUnlockableBranches(pConversingPlayer)

		pConversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(pConversationScreen)

		if (nextUnlockableBranches ~= nil) then
			local insertionStringFormatted = nextUnlockableBranches[1]
			for i = 2, #nextUnlockableBranches, 1 do
				insertionStringFormatted = insertionStringFormatted .. " , " .. nextUnlockableBranches[i]
			end
			clonedConversation:setDialogTextTO(insertionStringFormatted)
		elseif (nextUnlockableBranches == nil) then
			clonedConversation:setCustomDialogText("I sense you are unable to learn any new skills at this time.")
		end
	elseif screenID == "cs_jsPlumb_1_17" then -- Unlocking new branches.
		fs_experience_converter_conv_handler:chooseBranchToUnlock(pConversingPlayer)
	elseif screenID == "cs_jsPlumb_1_11" then -- Transferring Experience of first type.
		fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pConversingPlayer, 0)
	elseif screenID == "cs_jsPlumb_1_126" then -- Transferring Experience of second type.
		fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pConversingPlayer, 1)
	elseif screenID == "cs_jsPlumb_1_139" then -- Transferring Experience of third type.
		fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pConversingPlayer, 2)
	elseif screenID == "cs_jsPlumb_1_152" then -- Transferring Experience of fourth type.
		fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pConversingPlayer, 3)
	end
	return pConversationScreen
end

function fs_experience_converter_conv_handler:chooseBranchToUnlock(pCreature)
	if (pCreature == nil) then
		return
	end

	local suiManager = LuaSuiManager()
	local options = ExperienceConverter:getNextUnlockableBranches(pCreature)

	if (options == nil) then
		CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/utils:no_available_branches")
		return
	end

	suiManager:sendListBox(pCreature, pCreature, "@quest/force_sensitive/utils:branch_select_title", "@quest/force_sensitive/utils:select_branch", 2, "@cancel", "", "@ok", "fs_experience_converter_conv_handler", "notifyBranchUnlocked", options)
end

function fs_experience_converter_conv_handler:notifyBranchUnlocked(pCreature, pSui, cancelPressed, arg0)
	if (pCreature == nil or cancelPressed) then
		return
	end
	local options = ExperienceConverter:getNextUnlockableBranches(pCreature)
	local tier4Selection = options[tonumber(arg0) + 1]
	local branchTier4 = ExperienceConverter:getHighestBoxForTrainer(tier4Selection)

	CreatureObject(pCreature):sendSystemMessageWithTO("@quest/force_sensitive/utils:branch_selected_unlock", tier4Selection)

	-- Set it as trained.
	CreatureObject(pCreature):setScreenPlayState(2, "VillageUnlockScreenPlay:" .. branchTier4)
end

function fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pCreature, experienceType)
	if (pCreature == nil) then
		return
	end

	local options = ExperienceConverter:getExperienceForConversion(pCreature, experienceType)

	local experienceTypeFS = nil
	if (experienceType == 0) then
		experienceTypeFS = "Force-sensitive Combat"
	elseif (experienceType == 1) then
		experienceTypeFS = "Force-sensitive Crafting"
	elseif (experienceType == 2) then
		experienceTypeFS = "Force-sensitive Senses"
	elseif (experienceType == 3) then
		experienceTypeFS = "Force-sensitive Reflex"
	end

	if (#options <= 0) then
		CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_for_conversion")
		return
	end

	-- Save the option.
	ExperienceConverter:setSuiTransferExperienceType(experienceType, CreatureObject(pCreature):getObjectID())

	if (experienceTypeFS ~= nil) then
		local suiManager = LuaSuiManager()
		suiManager:sendListBox(pCreature, pCreature, "@quest/force_sensitive/utils:xp_transfer_prompt", "Select the Experience you wish to convert to: " .. experienceTypeFS, 2, "@cancel", "", "@ok", "fs_experience_converter_conv_handler", "notifyTransfer", options)
	end
end

function fs_experience_converter_conv_handler:notifyTransfer(pCreature, pSui, cancelPressed, arg0)
	if (pCreature == nil or cancelPressed) then
		return
	end

	local objId = CreatureObject(pCreature):getObjectID()

	if (objId == nil) then
		return
	end

	local expTransferType = ExperienceConverter:getSuiTransferExperienceType(objId)

	local optionsName = ExperienceConverter:getExperienceForConversion(pCreature, expTransferType)

	local optionsNameFrom = optionsName[arg0 + 1]
	local optionsNameFromUnformatted = string.sub(optionsNameFrom, 8, string.len(optionsNameFrom))

	local experienceTypeFS = nil

	if (expTransferType == 0) then
		experienceTypeFS = "Force-sensitive Combat"
	elseif (expTransferType == 1) then
		experienceTypeFS = "Force-sensitive Crafting"
	elseif (expTransferType == 2) then
		experienceTypeFS = "Force-sensitive Senses"
	elseif (expTransferType == 3) then
		experienceTypeFS = "Force-sensitive Reflex"
	end

	if (experienceTypeFS ~= nil) then
		-- Save the choice...
		ExperienceConverter:setSuiTransferExperienceSelection(tostring(arg0 + 1), objId)

		-- NEED THE RATIO
		local ratio = ExperienceConverter:getExperienceRatio(optionsNameFromUnformatted, expTransferType)

		-- Add Options: 1 = string name, 2 = amount, 3 = ratio
		local optionsFrom = {}
		ObjectManager.withCreaturePlayerObject(pCreature, function(playerObject)
			optionsFrom = {optionsNameFrom, playerObject:getExperience(optionsNameFromUnformatted), ratio}
		end)
		local optionsTo = {experienceTypeFS, 0, 1}
		local suiManager = LuaSuiManager()
		suiManager:sendTransferBox(pCreature, pCreature, "@quest/force_sensitive/utils:xp_transfer_prompt", "How much of that Experience do you wish to convert to: " .. experienceTypeFS, "@ok", "fs_experience_converter_conv_handler", "transferExperiencePoints", optionsTo, optionsFrom)
	end
end

function fs_experience_converter_conv_handler:transferExperiencePoints(pCreature, pSui, cancelPressed, arg0, arg1)
	if (pCreature == nil or cancelPressed) then
		return
	end

	local objId = CreatureObject(pCreature):getObjectID()

	if (objId == nil) then
		return
	end

	local experienceTypeFS = nil
	local expTransferType = ExperienceConverter:getSuiTransferExperienceType(objId)

	if (expTransferType == 0) then
		experienceTypeFS = "@exp_n:fs_combat"
	elseif (expTransferType == 1) then
		experienceTypeFS = "@exp_n:fs_crafting"
	elseif (expTransferType == 2) then
		experienceTypeFS = "@exp_n:fs_senses"
	elseif (expTransferType == 3) then
		experienceTypeFS = "@exp_n:fs_reflex"
	end

	if (arg1 == "0") then
		CreatureObject(pCreature):sendSystemMessage("@quest/force_sensitive/utils:convert_allocate_more_xp")
		return
	end



	if (experienceTypeFS ~= nil) then
		ObjectManager.withCreatureAndPlayerObject(pCreature, function(creatureObject, playerObject)
			local optionsName = ExperienceConverter:getExperienceForConversion(pCreature, ExperienceConverter:getSuiTransferExperienceType(objId))
			local optionsChoice = tonumber(ExperienceConverter:getSuiTransferExperienceSelection(creatureObject:getObjectID()))
			local optionsNameFrom = tostring(optionsName[optionsChoice])
			local optionsNameFromUnformatted = string.sub(optionsNameFrom, 8, string.len(optionsNameFrom))
			ExperienceConverter:deleteSuiTransferExperienceSelection(objId)
			ExperienceConverter:deleteSuiTransferExperienceType(objId)
			local expFsUnformatted = string.sub(experienceTypeFS, 8, string.len(experienceTypeFS))
			local expFsCurrent = playerObject:getExperience(expFsUnformatted)
			local expNormal = playerObject:getExperience(optionsNameFromUnformatted)
			local ratio = ExperienceConverter:getExperienceRatio(optionsNameFromUnformatted, expTransferType)
			local xpToLose = (tonumber(arg1) * ratio) * -1

			-- If they are capped (or will be), don't let them transfer any more xp. The cap for any FS exp type seems to be 5100000.
			if (expFsCurrent >= playerObject:getExperienceCap(expFsUnformatted) or (expFsCurrent + tonumber(arg1) > playerObject:getExperienceCap(expFsUnformatted))) then
				creatureObject:sendSystemMessage("@quest/force_sensitive/utils:convert_at_fs_skill_cap")
				return
			elseif (expNormal + xpToLose < 0) then -- check for negative.
				creatureObject:sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_xp")
				return
			end

			local messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_lose")
			messageString:setTO(optionsNameFrom)
			local messageString2 = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_gain")
			messageString2:setTO(experienceTypeFS)
			messageString2:setDI(tonumber(arg1))
			messageString:setDI(xpToLose * -1)
			creatureObject:awardExperience(optionsNameFromUnformatted, xpToLose)
			creatureObject:awardExperience(expFsUnformatted, tonumber(arg1))

			creatureObject:sendSystemMessage(messageString:_getObject())
			creatureObject:sendSystemMessage(messageString2:_getObject())
		end)
	end
end

function fs_experience_converter_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreen = nil

	-- Paemos - "beckon" animation.
	CreatureObject(pConversingNpc):doAnimation("beckon")

	-- PUT IN FOR NOVA TESTING, PLEASE REMOVE BELOW!!!!!
	local branch = "force_sensitive_combat_prowess_ranged_accuracy_04"
	local questStatusTemp = CreatureObject(pConversingPlayer):getScreenPlayState("VillageUnlockScreenPlay:" .. branch)
	if (questStatusTemp == 0) then
		CreatureObject(pConversingPlayer):setScreenPlayState(1, "VillageUnlockScreenPlay:" .. branch)
	end
	-- PUT IN FOR NOVA TESTING, PLEASE REMOVE ABOVE!!!!

	-- See if they have a quest to unlock, or having XP to convert.
	if (ExperienceConverter.qualifiesForConversation(pConversingPlayer) == true) then
		nextScreen = "cs_jsPlumb_1_5"
	elseif ((ExperienceConverter.qualifiesForConversation(pConversingPlayer) == false) or nextScreen == nil) then
		nextScreen = "cs_jsPlumb_1_19"
	end

	return conversationTemplate:getScreen(nextScreen)
end
