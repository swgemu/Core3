local ObjectManager = require("managers.object.object_manager")
includeFile("events/eventPerkData.lua")

eventPromoterScreenplay = ScreenPlay:new {
	numberOfActs = 1,

	promoterLocs = {
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1393862 }, -- Keren
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1717467 }, -- Moenia
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1677392 }, -- Theed 1
		{ planet = "naboo", x = -5.4, z = 1.0, y = 23.4, angle = 123, cell = 1697375 }, -- Theed 2
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1419011 }, -- Deeja Peak
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1741475 }, -- Kaadarra
		{ planet = "naboo", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1865361 }, -- Lake Retreat
		{ planet = "tatooine", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1233973 }, -- Mos Entha
		{ planet = "tatooine", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1261015 }, -- Mos Espa
		{ planet = "tatooine", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1223847 }, -- Bestine
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1855546 }, -- Coronet
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1935524 }, -- Tyrena 1
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 1935820 }, -- Tyrena 2
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 2365805 }, -- Bela Vistal
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 2775411 }, -- Vreni Island
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 3005668 }, -- Kor Vella
		{ planet = "corellia", x = -0.1, z = 1.0, y = 20.8, angle = 0, cell = 3075364 } -- Doaba Guerful
	}
}

registerScreenPlay("eventPromoterScreenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function eventPromoterScreenplay:start()
	self:spawnMobiles()
end

function eventPromoterScreenplay:spawnMobiles()
	local mobiles = self.promoterLocs
	for i = 1, table.getn(mobiles), 1 do
		if isZoneEnabled(mobiles[i].planet) then
			spawnMobile(mobiles[i].planet, "event_promoter", 1, mobiles[i].x, mobiles[i].z, mobiles[i].y, mobiles[i].angle, mobiles[i].cell)
		end
	end
end

function eventPromoterScreenplay:sendSaleSui(pNpc, pPlayer, screenID)
	writeStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase", screenID)
	local suiManager = LuaSuiManager()
	local title, desc
	local perkData = { }

	if screenID == "sale_decorations" then
		title = "@conversation/event_promoter:s_14"
		desc = "@conversation/event_promoter:s_12"
		perkData = eventPerkDecorationDeeds
	elseif screenID == "sale_venues" then
		title = "@conversation/event_promoter:s_30"
		desc = "@conversation/event_promoter:s_28"
		perkData = eventPerkVenueDeeds
	elseif screenID == "sale_games_supplies" then
		title = "@conversation/event_promoter:s_76"
		desc = "@conversation/event_promoter:s_44"
		perkData = eventPerkGamesSuppliesDeeds
	elseif screenID == "sale_personnel" then
		title = "@conversation/event_promoter:s_100"
		desc = "@conversation/event_promoter:s_82"
		perkData = eventPerkPersonnelDeeds
	end

	local options = { }
	for i = 1, table.getn(perkData), 1 do
		table.insert(options, getStringId(perkData[i].displayName) .. " (Cost: " .. perkData[i].cost .. ")")
	end

	suiManager:sendListBox(pNpc, pPlayer, title, desc, 2, "@cancel", "", "@ok", "eventPromoterScreenplay", "handleSuiPurchase", options)
end

function eventPromoterScreenplay:handleSuiPurchase(pPlayer, pSui, cancelPressed, arg0)
	if (cancelPressed) then
		deleteStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase")
		return
	end
	local purchaseCategory = readStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase")
	local purchaseIndex = arg0 + 1
	local perkData

	if purchaseCategory == "sale_decorations" then
		perkData = eventPerkDecorationDeeds
	elseif purchaseCategory == "sale_venues" then
		perkData = eventPerkVenueDeeds
	elseif purchaseCategory == "sale_games_supplies" then
		perkData = eventPerkGamesSuppliesDeeds
	elseif purchaseCategory == "sale_personnel" then
		perkData = eventPerkPersonnelDeeds
	end

	local deedData = perkData[purchaseIndex]
	deleteStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase")
	self:giveItem(pPlayer, deedData)
end

function eventPromoterScreenplay:giveItem(pPlayer, deedData)
	ObjectManager.withCreatureObject(pPlayer, function(player)
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
		local slotsRemaining = SceneObject(pInventory):getContainerVolumeLimit() - SceneObject(pInventory):getContainerObjectsSize()

		if (player:getCashCredits() < deedData.cost) then
			player:sendSystemMessage("@dispenser:insufficient_funds")
			return
		end
		
		if (slotsRemaining == 0) then
			player:sendSystemMessage("@event_perk:promoter_full_inv")
			return
		end

		player:subtractCashCredits(deedData.cost)

		local templatePath = "object/tangible/deed/event_perk/" .. deedData.template .. ".iff"
		local pItem = giveItem(pInventory, templatePath, -1)
	end)
end


eventPromoterConvoHandler = Object:new {}

function eventPromoterConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("welcome")
end

function eventPromoterConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local screen = LuaConversationScreen(conversationScreen)
		local screenID = screen:getScreenID()
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		if (string.find(screenID, "sale") ~= nil) then
			eventPromoterScreenplay:sendSaleSui(conversingNPC, conversingPlayer, screenID)
		end
		return conversationScreen
	end)
end

function eventPromoterConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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