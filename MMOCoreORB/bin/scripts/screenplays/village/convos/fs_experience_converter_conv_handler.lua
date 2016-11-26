local ExperienceConverter = require("screenplays.village.convos.convohelpers.experience_converter")
local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

fs_experience_converter_conv_handler = conv_handler:new {}

function fs_experience_converter_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if screenID == "init" then
		pConvScreen = self:handleInit(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "cs_jsPlumb_1_7" then
		local nextUnlockableBranches = ExperienceConverter:getNextUnlockableBranches(pPlayer)

		pConvScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(pConvScreen)

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
		self:chooseBranchToUnlock(pPlayer)
	elseif screenID == "cs_jsPlumb_1_11" then -- Transferring Experience of first type.
		self:chooseExperienceTypeForRatio(pPlayer, 0)
	elseif screenID == "cs_jsPlumb_1_126" then -- Transferring Experience of second type.
		self:chooseExperienceTypeForRatio(pPlayer, 1)
	elseif screenID == "cs_jsPlumb_1_139" then -- Transferring Experience of third type.
		self:chooseExperienceTypeForRatio(pPlayer, 2)
	elseif screenID == "cs_jsPlumb_1_152" then -- Transferring Experience of fourth type.
		self:chooseExperienceTypeForRatio(pPlayer, 3)
	end
	return pConvScreen
end

function fs_experience_converter_conv_handler:chooseBranchToUnlock(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local suiManager = LuaSuiManager()
	local options = ExperienceConverter:getNextUnlockableBranches(pPlayer)

	if (options == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:no_available_branches")
		return
	end

	suiManager:sendListBox(pPlayer, pPlayer, "@quest/force_sensitive/utils:branch_select_title", "@quest/force_sensitive/utils:select_branch", 2, "@cancel", "", "@ok", "fs_experience_converter_conv_handler", "notifyBranchUnlocked", options)
end

function fs_experience_converter_conv_handler:notifyBranchUnlocked(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil or cancelPressed) then
		return
	end
	local options = ExperienceConverter:getNextUnlockableBranches(pPlayer)
	local tier4Selection = options[tonumber(arg0) + 1]
	local branchTier4 = ExperienceConverter:getHighestBoxForTrainer(tier4Selection)

	CreatureObject(pPlayer):sendSystemMessageWithTO("@quest/force_sensitive/utils:branch_selected_unlock", tier4Selection)

	-- Set it as trained.
	CreatureObject(pPlayer):setScreenPlayState(2, "VillageUnlockScreenPlay:" .. branchTier4)
end

function fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pPlayer, experienceType)
	if (pPlayer == nil) then
		return
	end

	local options = ExperienceConverter:getExperienceForConversion(pPlayer, experienceType)

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
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_for_conversion")
		return
	end

	-- Save the option.
	ExperienceConverter:setSuiTransferExperienceType(experienceType, CreatureObject(pPlayer):getObjectID())

	if (experienceTypeFS ~= nil) then
		local suiManager = LuaSuiManager()
		suiManager:sendListBox(pPlayer, pPlayer, "@quest/force_sensitive/utils:xp_transfer_prompt", "Select the Experience you wish to convert to: " .. experienceTypeFS, 2, "@cancel", "", "@ok", "fs_experience_converter_conv_handler", "notifyTransfer", options)
	end
end

function fs_experience_converter_conv_handler:notifyTransfer(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil or cancelPressed or arg0 == -1) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local objId = CreatureObject(pPlayer):getObjectID()

	if (objId == nil) then
		return
	end

	local expTransferType = ExperienceConverter:getSuiTransferExperienceType(objId)

	local optionsName = ExperienceConverter:getExperienceForConversion(pPlayer, expTransferType)

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
		local optionsFrom = {optionsNameFrom, PlayerObject(pGhost):getExperience(optionsNameFromUnformatted), ratio}
		local optionsTo = {experienceTypeFS, 0, 1}
		local suiManager = LuaSuiManager()
		suiManager:sendTransferBox(pPlayer, pPlayer, "@quest/force_sensitive/utils:xp_transfer_prompt", "How much of that Experience do you wish to convert to: " .. experienceTypeFS, "@ok", "fs_experience_converter_conv_handler", "transferExperiencePoints", optionsTo, optionsFrom)
	end
end

function fs_experience_converter_conv_handler:transferExperiencePoints(pPlayer, pSui, eventIndex, arg0, arg1)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil or cancelPressed) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local objId = CreatureObject(pPlayer):getObjectID()

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
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_allocate_more_xp")
		return
	end

	if (experienceTypeFS ~= nil) then
		local optionsName = ExperienceConverter:getExperienceForConversion(pPlayer, ExperienceConverter:getSuiTransferExperienceType(objId))
		local optionsChoice = tonumber(ExperienceConverter:getSuiTransferExperienceSelection(CreatureObject(pPlayer):getObjectID()))
		local optionsNameFrom = tostring(optionsName[optionsChoice])
		local optionsNameFromUnformatted = string.sub(optionsNameFrom, 8, string.len(optionsNameFrom))

		ExperienceConverter:deleteSuiTransferExperienceSelection(objId)
		ExperienceConverter:deleteSuiTransferExperienceType(objId)

		local expFsUnformatted = string.sub(experienceTypeFS, 8, string.len(experienceTypeFS))
		local expFsCurrent = PlayerObject(pGhost):getExperience(expFsUnformatted)
		local expNormal = PlayerObject(pGhost):getExperience(optionsNameFromUnformatted)
		local ratio = ExperienceConverter:getExperienceRatio(optionsNameFromUnformatted, expTransferType)
		local xpToLose = (tonumber(arg1) * ratio) * -1

		-- If they are capped (or will be), don't let them transfer any more xp. The cap for any FS exp type seems to be 5100000.
		if (expFsCurrent >= PlayerObject(pGhost):getExperienceCap(expFsUnformatted) or (expFsCurrent + tonumber(arg1) > PlayerObject(pGhost):getExperienceCap(expFsUnformatted))) then
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_at_fs_skill_cap")
			return
		elseif (expNormal + xpToLose < 0) then -- check for negative.
			CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_xp")
			return
		end

		local messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_lose")
		messageString:setTO(optionsNameFrom)
		local messageString2 = LuaStringIdChatParameter("@quest/force_sensitive/utils:xp_convert_gain")
		messageString2:setTO(experienceTypeFS)
		messageString2:setDI(tonumber(arg1))
		messageString:setDI(xpToLose * -1)
		CreatureObject(pPlayer):awardExperience(optionsNameFromUnformatted, xpToLose, false)
		CreatureObject(pPlayer):awardExperience(expFsUnformatted, tonumber(arg1), false)

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
		CreatureObject(pPlayer):sendSystemMessage(messageString2:_getObject())
	end
end

function fs_experience_converter_conv_handler:handleInit(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local conversationTemplate = LuaConversationTemplate(pConvTemplate)
	local nextScreen = nil

	-- Paemos - "beckon" animation.
	CreatureObject(pNpc):doAnimation("beckon")

	-- See if they have a quest to unlock, or having XP to convert.
	if (ExperienceConverter:qualifiesForConversation(pPlayer) == true) then
		nextScreen = "cs_jsPlumb_1_5"
	elseif ((ExperienceConverter:qualifiesForConversation(pPlayer) == false) or nextScreen == nil) then
		nextScreen = "cs_jsPlumb_1_19"
	end

	return conversationTemplate:getScreen(nextScreen)
end
