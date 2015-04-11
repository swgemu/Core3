local ObjectManager = require("managers.object.object_manager")

risArmorQuest = ScreenPlay:new {
	numberOfActs = 1,

	questSchematics = {
		quest1 = { template = "object/draft_schematic/armor/armor_segment_ris.iff", displayName = "@craft_clothing_ingredients_n:armor_segment_ris" },
		quest3 = { template = "object/draft_schematic/armor/component/armor_layer_ris.iff", displayName = "@craft_clothing_ingredients_n:armor_layer_ris" },
		quest5 = { template = "object/draft_schematic/clothing/clothing_armor_ris_boots.iff", displayName = "@wearables_name:armor_ris_boots" }
	},


	questItems = {
		quest2 = { template = "object/tangible/component/armor/armor_segment_ris.iff", displayName = "@craft_clothing_ingredients_n:armor_segment_ris" },
		quest4 = { template = "object/tangible/component/armor/armor_layer_ris.iff", displayName = "@craft_clothing_ingredients_n:armor_layer_ris" },
		quest6 = { template = "object/tangible/wearables/armor/ris/armor_ris_boots.iff", displayName = "@wearables_name:armor_ris_boots" }
	},


	finalRewardSchematics = {
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_bicep_l.iff", displayName = "@wearables_name:armor_ris_bicep_l" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_bicep_r.iff", displayName = "@wearables_name:armor_ris_bicep_r" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_bracer_l.iff", displayName = "@wearables_name:armor_ris_bracer_l" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_bracer_r.iff", displayName = "@wearables_name:armor_ris_bracer_r" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_chest_plate.iff", displayName = "@wearables_name:armor_ris_chest_plate" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_gloves.iff", displayName = "@wearables_name:armor_ris_gloves" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_helmet.iff", displayName = "@wearables_name:armor_ris_helmet" },
		{ template = "object/draft_schematic/clothing/clothing_armor_ris_leggings.iff", displayName = "@wearables_name:armor_ris_leggings" }
	}

}

registerScreenPlay("risArmorQuest", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function risArmorQuest:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
	end
end

function risArmorQuest:spawnMobiles()
	spawnMobile("dantooine", "mol_nimai", 1, -6805, 126, 6022, 179, 0)
end


risArmorQuestConvoHandler = Object:new {}

function risArmorQuestConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	-- 1 = quest 1, 2 = quest 2, 4 = quest 3, 8 = quest 4, 16 = quest 5, 32 = quest 6, 64 = completed
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)

		if (not player:hasSkill("crafting_armorsmith_master")) then
			return convoTemplate:getScreen("not_master_armorsmith")
		elseif (player:hasScreenPlayState(64, "ris_armor_quest")) then -- All quests completed
			return convoTemplate:getScreen("completed_all_quests")
		elseif (player:hasScreenPlayState(32, "ris_armor_quest")) then -- On quest 6
			return convoTemplate:getScreen("quest_6_query")
		elseif (player:hasScreenPlayState(16, "ris_armor_quest")) then
			return convoTemplate:getScreen("quest_5_start")
		elseif (player:hasScreenPlayState(8, "ris_armor_quest")) then
			return convoTemplate:getScreen("quest_4_query")
		elseif (player:hasScreenPlayState(4, "ris_armor_quest")) then
			return convoTemplate:getScreen("quest_3_start")
		elseif (player:hasScreenPlayState(2, "ris_armor_quest")) then
			return convoTemplate:getScreen("quest_2_query")
		elseif (player:hasScreenPlayState(1, "ris_armor_quest")) then
			return convoTemplate:getScreen("quest_1_description")
		else
			return convoTemplate:getScreen("quest_1_start")
		end
	end)
end

function risArmorQuestConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local screen = LuaConversationScreen(conversationScreen)
		local screenID = screen:getScreenID()
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		if (screenID == "quest_1_start") then
			clonedConversation:setDialogTextDI("50000")
			if (player:getCashCredits() < 50000) then
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_1_start", "not_enough_money")
			else
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_1_start", "quest_1_start_yes")
			end
			clonedConversation:addOption("@quest_armorsmith:no_to_quest_1_start", "quest_1_start_no")
		elseif (screenID == "quest_1_start_yes") then
			player:subtractCashCredits(50000)
			player:setScreenPlayState(1, "ris_armor_quest")
		elseif (screenID == "quest_1_description") then
			self:teachSchematic(conversingPlayer, risArmorQuest.questSchematics.quest1)
			player:setScreenPlayState(2, "ris_armor_quest")
		elseif (screenID == "quest_2_query") then
			clonedConversation:setDialogTextTO(risArmorQuest.questItems.quest2.displayName)
			if (self:hasQuestItem(conversingPlayer, risArmorQuest.questItems.quest2.template)) then
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_2_query", "quest_2_complete")
			else
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_2_query", "illegal_response")
			end
			clonedConversation:addOption("@quest_armorsmith:no_to_quest_2_query", "quest_2_incomplete")
		elseif (screenID == "quest_2_complete") then
			player:setScreenPlayState(4, "ris_armor_quest")
			self:removeQuestItem(conversingPlayer, risArmorQuest.questItems.quest2.template)
		elseif (screenID == "quest_3_start") then
			self:teachSchematic(conversingPlayer, risArmorQuest.questSchematics.quest3)
			player:setScreenPlayState(8, "ris_armor_quest")
		elseif (screenID == "quest_4_query") then
			clonedConversation:setDialogTextTO(risArmorQuest.questItems.quest4.displayName)
			if (self:hasQuestItem(conversingPlayer, risArmorQuest.questItems.quest4.template)) then
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_4_query", "quest_4_complete")
			else
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_4_query", "illegal_response")
			end
			clonedConversation:addOption("@quest_armorsmith:no_to_quest_4_query", "quest_4_incomplete")
		elseif (screenID == "quest_4_complete") then
			player:setScreenPlayState(16, "ris_armor_quest")
			self:removeQuestItem(conversingPlayer, risArmorQuest.questItems.quest4.template)
		elseif (screenID == "quest_5_start") then
			self:teachSchematic(conversingPlayer, risArmorQuest.questSchematics.quest5)
			player:setScreenPlayState(32, "ris_armor_quest")
		elseif (screenID == "quest_6_query") then
			clonedConversation:setDialogTextTO(risArmorQuest.questItems.quest6.displayName)
			if (self:hasQuestItem(conversingPlayer, risArmorQuest.questItems.quest6.template)) then
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_6_query", "quest_6_complete")
			else
				clonedConversation:addOption("@quest_armorsmith:yes_to_quest_6_query", "illegal_response")
			end
			clonedConversation:addOption("@quest_armorsmith:no_to_quest_6_query", "quest_6_incomplete")
		elseif (screenID == "quest_6_complete") then
			player:setScreenPlayState(64, "ris_armor_quest")
			self:removeQuestItem(conversingPlayer, risArmorQuest.questItems.quest6.template)
			self:rewardSchematics(conversingPlayer)
		end
		return conversationScreen
	end)
end

function risArmorQuestConvoHandler:teachSchematic(pPlayer, templateTable)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		playerObject:addRewardedSchematic(templateTable.template, 2, -1, true)
		local messageString = LuaStringIdChatParameter("@loot_schematic:skill_granted")
		messageString:setTO(getStringId(templateTable.displayName))
		player:sendSystemMessage(messageString:_getObject())
	end)
end

function risArmorQuestConvoHandler:rewardSchematics(pPlayer)
	for i = 1, table.getn(risArmorQuest.finalRewardSchematics), 1 do
		self:teachSchematic(pPlayer, risArmorQuest.finalRewardSchematics[i])
	end
end

function risArmorQuestConvoHandler:hasQuestItem(pPlayer, template)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	return pInventory ~= nil and getContainerObjectByTemplate(pInventory, template, true) ~= nil
end

function risArmorQuestConvoHandler:removeQuestItem(pPlayer, template)
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	local pItem = getContainerObjectByTemplate(pInventory, template, true)
	ObjectManager.withSceneObject(pItem, function(item)
		item:destroyObjectFromWorld()
		item:destroyObjectFromDatabase()
	end)
end

function risArmorQuestConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
