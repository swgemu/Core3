local ObjectManager = require("managers.object.object_manager")
includeFile("events/eventPerkData.lua")

eventPromoterScreenplay = ScreenPlay:new {
	numberOfActs = 1,

	promoterLocs = {
		{ planet = "naboo", x = -6.5, z = 1.6, y = -16.2, angle = 0, cell = 1393868 }, -- Keren
		{ planet = "naboo", x = -6.5, z = 1.6, y = -16.1, angle = 0, cell = 1717473 }, -- Moenia
		{ planet = "naboo", x = -23.6, z = 1.6, y = -16.8, angle = 0, cell = 1677400 }, -- Theed 1
		{ planet = "naboo", x = -23.6, z = 1.6, y = -16.8, angle = 0, cell = 1697383 }, -- Theed 2
		{ planet = "naboo", x = -6.5, z = 1.6, y = -16.2, angle = 0, cell = 1419017 }, -- Deeja Peak
		{ planet = "naboo", x = -23.6, z = 1.6, y = -16.8, angle = 0, cell = 1741483 }, -- Kaadarra
		{ planet = "naboo", x = -23.6, z = 1.6, y = -16.8, angle = 0, cell = 1865369 }, -- Lake Retreat
		{ planet = "tatooine", x = -5.5, z = 1.6, y = -7.2, angle = -146, cell = 1233979 }, -- Mos Entha
		{ planet = "tatooine", x = -24, z = 1.6, y = -4, angle = 175, cell = 1261023 }, -- Mos Espa
		{ planet = "tatooine", x = -24, z = 1.6, y = -4, angle = 175, cell = 1223855 }, -- Bestine
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 1855554 }, -- Coronet
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 1935532 }, -- Tyrena 1
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 1935828 }, -- Tyrena 2
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 2365813 }, -- Bela Vistal
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 2775419 }, -- Vreni Island
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 3005676 }, -- Kor Vella
		{ planet = "corellia", x = -24, z = 1.6, y = -4, angle = 175, cell = 3075372 } -- Doaba Guerful
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
	for i = 1, #mobiles, 1 do
		if isZoneEnabled(mobiles[i].planet) then
			spawnMobile(mobiles[i].planet, "event_promoter", 1, mobiles[i].x, mobiles[i].z, mobiles[i].y, mobiles[i].angle, mobiles[i].cell)
		end
	end
end

function eventPromoterScreenplay:sendSaleSui(pNpc, pPlayer, screenID)
	if (pPlayer == nil or pNpc == nil) then
		return
	end

	writeStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase", screenID)
	local suiManager = LuaSuiManager()
	local perkData = self:getPerkTable(screenID)

	local options = { }
	for i = 1, #perkData, 1 do
		local perk = {getStringId(perkData[i].displayName) .. " (Cost: " .. perkData[i].cost .. ")", 0}
		table.insert(options, perk)
	end

	suiManager:sendListBox(pNpc, pPlayer, "@event_perk:pro_show_list_title", "@event_perk:pro_show_list_desc", 2, "@cancel", "", "@ok", "eventPromoterScreenplay", "handleSuiPurchase", 32, options)
end

function eventPromoterScreenplay:getPerkTable(category)
	if category == "sale_decorations" then
		return eventPerkDecorationDeeds
	elseif category == "sale_imperial_decorations" then
		return eventPerkImperialDecorationDeeds
	elseif category == "sale_rebel_decorations" then
		return eventPerkRebelDecorationDeeds
	elseif category == "sale_venues" then
		return eventPerkVenueDeeds
	elseif category == "sale_imperial_venues" then
		return eventPerkImperialVenueDeeds
	elseif category == "sale_rebel_venues" then
		return eventPerkRebelVenueDeeds
	elseif category == "sale_games_supplies" then
		return eventPerkGamesSuppliesDeeds
	elseif category == "sale_personnel" then
		return eventPerkPersonnelDeeds
	elseif category == "sale_imperial_personnel" then
		return eventPerkImperialPersonnelDeeds
	elseif category == "sale_rebel_personnel" then
		return eventPerkRebelPersonnelDeeds
	end
end

function eventPromoterScreenplay:handleSuiPurchase(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil) then
		return
	end

	if (cancelPressed) then
		deleteStringData(CreatureObject(pPlayer):getObjectID() .. ":event_promoter_purchase")
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local purchaseCategory = readStringData(playerID .. ":event_promoter_purchase")
	local purchaseIndex = arg0 + 1
	local perkData = self:getPerkTable(purchaseCategory)

	local deedData = perkData[purchaseIndex]
	deleteStringData(playerID .. ":event_promoter_purchase")
	self:giveItem(pPlayer, deedData)
end

function eventPromoterScreenplay:giveItem(pPlayer, deedData)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	if (CreatureObject(pPlayer):getCashCredits() < deedData.cost) then
		CreatureObject(pPlayer):sendSystemMessage("@dispenser:insufficient_funds")
		return
	elseif (SceneObject(pInventory):isContainerFullRecursive()) then
		CreatureObject(pPlayer):sendSystemMessage("@event_perk:promoter_full_inv")
		return
	elseif (not PlayerObject(pGhost):isPrivileged()) then
		if (PlayerObject(pGhost):hasEventPerk("shuttle_beacon")) then
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:only_one_shuttle_beacon")
			return
		elseif (PlayerObject(pGhost):getEventPerkCount() >= 5) then
			CreatureObject(pPlayer):sendSystemMessage("@event_perk:pro_too_many_perks")
			return
		end
	end

	CreatureObject(pPlayer):subtractCashCredits(deedData.cost)

	local templatePath
	if string.find(deedData.template, ".iff") then
		templatePath = deedData.template
	else
		templatePath = "object/tangible/deed/event_perk/" .. deedData.template .. ".iff"
	end

	local pItem = giveItem(pInventory, templatePath, -1)

	if (pItem ~= nil) then
		PlayerObject(pGhost):addEventPerk(pItem)
	end
end


eventPromoterConvoHandler = conv_handler:new {}

function eventPromoterConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (string.find(screenID, "sale") ~= nil) then
		eventPromoterScreenplay:sendSaleSui(pNpc, pPlayer, screenID)
	end

	return pConvScreen
end
