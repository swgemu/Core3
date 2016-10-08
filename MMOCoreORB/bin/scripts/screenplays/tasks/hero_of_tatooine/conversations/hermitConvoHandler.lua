local ObjectManager = require("managers.object.object_manager")

heroOfTatHermitConvoHandler = conv_handler:new {}

--[[
1 - Started squill quest
2 - Completed squill quest
4 - Completed Altruism
8 - Completed Intellect
16 - Completed Courage
32 - Completed Honor
64 - Completed Mark of Hero
]]

function heroOfTatHermitConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (HeroOfTatooineScreenPlay:isMissingMark(pPlayer)) then
		return convoTemplate:getScreen("you_have_returned_missing_marks")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(64, "hero_of_tatooine")) then
		return convoTemplate:getScreen("hero_returns")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine")) then
		return convoTemplate:getScreen("you_have_returned")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine")) then
		return convoTemplate:getScreen("return_intro")
	else
		return convoTemplate:getScreen("intro")
	end
end

function heroOfTatHermitConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "go_then") then
		CreatureObject(pPlayer):setScreenPlayState(1, "hero_of_tatooine")
	elseif (screenID == "you_have_returned_missing_marks") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "inv_full")
		else
			if (HeroOfTatooineScreenPlay:giveMissingMarks(pPlayer)) then
				clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "now_have_items")
			else
				clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_6441a2a6", "dont_have_room")
			end
		end
	elseif (screenID == "you_have_returned") then
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine") and CreatureObject(pPlayer):hasScreenPlayState(4, "hero_of_tatooine") and CreatureObject(pPlayer):hasScreenPlayState(8, "hero_of_tatooine")
			and CreatureObject(pPlayer):hasScreenPlayState(16, "hero_of_tatooine") and CreatureObject(pPlayer):hasScreenPlayState(32, "hero_of_tatooine")) then
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_cd2c070a", "you_bear_marks")
		end
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_503d468c", "which_mark")
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_da196589", "as_you_wish")
	elseif (screenID == "done_great_things") then

		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return
		end

		if (SceneObject(pInventory):isContainerFullRecursive()) then
			CreatureObject(pPlayer):setScreenPlayState(16, "hero_of_tatooine_missing_marks") -- 1 - Altruism, 2 - Intellect, 4 - Courage, 8 - Honor, 16 - Ring
			CreatureObject(pPlayer):sendSystemMessage("@quest/hero_of_tatooine/system_messages:hero_inv_full")
		else
			local pMark = giveItem(pInventory, "object/tangible/wearables/ring/ring_mark_hero.iff", -1)

			if (pMark == nil) then
				CreatureObject(pPlayer):setScreenPlayState(16, "hero_of_tatooine_missing_marks") -- 1 - Altruism, 2 - Intellect, 4 - Courage, 8 - Honor, 16 - Ring
				CreatureObject(pPlayer):sendSystemMessage("Error creating object. Please file a bug report.")
			end
		end

		PlayerObject(pGhost):awardBadge(11)
		CreatureObject(pPlayer):setScreenPlayState(64, "hero_of_tatooine")
		CreatureObject(pNpc):doAnimation("worship")
	elseif (screenID == "return_intro") then
		local pInventory =  CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSkull = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/hero_of_tatooine/squill_skull.iff", true)

			if (pSkull ~= nil) then
				clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_af540d0", "proven_worthy")
			end
		end
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_hermit:s_da196589", "as_you_wish")
	elseif (screenID == "proven_worthy") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pSkull = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/hero_of_tatooine/squill_skull.iff", true)

			if (pSkull == nil) then
				return 0
			end

			SceneObject(pSkull):destroyObjectFromWorld()
			SceneObject(pSkull):destroyObjectFromDatabase()
			CreatureObject(pPlayer):setScreenPlayState(2, "hero_of_tatooine")
			CreatureObject(pNpc):doAnimation("taken_aback")
		end
	elseif (screenID == "intro") then
		CreatureObject(pNpc):doAnimation("greet")
	end

	return pConvScreen
end
