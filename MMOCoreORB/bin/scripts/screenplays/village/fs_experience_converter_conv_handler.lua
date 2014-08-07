local ExperienceConverter = require("screenplays.village.experience_converter")
local Logger = require("utils.logger")
require("utils.helpers")
local ObjectManager = require("managers.object.object_manager")

fs_experience_converter_conv_handler = Object:new {}

function fs_experience_converter_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
	local creature = LuaCreatureObject(pConversingPlayer)
	local convosession = creature:getConversationSession()

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
			for i = 2, table.getn(nextUnlockableBranches), 1 do
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
	local suiManager = LuaSuiManager()
	local options = ExperienceConverter:getNextUnlockableBranches(pCreature)
	local playerObject = LuaPlayerObject(pCreature)

	if (options == nil) then
		local player = LuaCreatureObject(pCreature)
		player:sendSystemMessage("@quest/force_sensitive/utils:no_available_branches")
		return
	end

	suiManager:sendListBox(pCreature, pCreature, "@quest/force_sensitive/utils:branch_select_title", "@quest/force_sensitive/utils:select_branch", 2, "@cancel", "", "@ok", "fs_experience_converter_conv_handler", "notifyBranchUnlocked", options)
end

function fs_experience_converter_conv_handler:notifyBranchUnlocked(pCreature, pSui, cancelPressed, arg0)
	if (not cancelPressed) then
		local arguement = arg0 + 1
		local options = ExperienceConverter:getNextUnlockableBranches(pCreature)
		local tier4Selection = options[arguement]
		local branchTier4 = ExperienceConverter:getHighestBoxForTrainer(tier4Selection)


		ObjectManager.withCreatureObject(pCreature, function(creatureObject)
			ObjectManager.withPlayerObject(creatureObject:getPlayerObject(), function(playerObject)
				playerObject:setForceSensitiveUnlockedBranches(branchTier4)
			end)
			creatureObject:sendSystemMessageWithTO("@quest/force_sensitive/utils:branch_selected_unlock", tier4Selection)
		end)

		-- Remove the screenplay state for the tree they just trained...
		ExperienceConverter:removeScreenPlayState(pCreature, tier4Selection)
	end
end

function fs_experience_converter_conv_handler:chooseExperienceTypeForRatio(pCreature, pExperienceType)
	local suiManager = LuaSuiManager()
	local options = ExperienceConverter:getExperienceForConversion(pCreature, pExperienceType)

	if (table.getn(options) <= 0) then
		local player = LuaCreatureObject(pCreature)
		player:sendSystemMessage("@quest/force_sensitive/utils:convert_not_enough_for_conversion")
		return
	end
	suiManager:sendListBox(pCreature, pCreature, "@sui:swg", "@ui:experience_name", 2, "@ok", "", "@cancel", "fs_experience_converter_conv_handler", "notifyTransfer", options)
end

function fs_experience_converter_conv_handler:notifyTransfer(pCreature, pSui, cancelPressed, arg0)
	if (not cancelPressed) then
		local amount = ExperienceConverter:getExperienceAmount(pCreature, arg0)
		--local suiManager = LuaSuiManager()
		--suiManager:sendTransferBox(pCreature, pCreature, "@sui:swg", message, "@ok", "ExperienceConverter", "transferExperiencePoints")
		local player = LuaCreatureObject(pCreature)
		player:sendSystemMessage("You want to transfer " .. amount .. " of experience, but we're still working on that.")
	end
end

function fs_experience_converter_conv_handler.handleInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreen = nil

	local playerCreature = LuaCreatureObject(pConversingPlayer)

	-- See if they have a quest to unlock, or having XP to convert.
	if (ExperienceConverter.qualifiesForConversation(pConversingPlayer) == true) then
		nextScreen = "cs_jsPlumb_1_5"
	elseif ((ExperienceConverter.qualifiesForConversation(pConversingPlayer) == false) or nextScreen == nil) then
		nextScreen = "cs_jsPlumb_1_19"
	end

	return conversationTemplate:getScreen(nextScreen)
end
