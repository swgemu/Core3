local ObjectManager = require("managers.object.object_manager")

heraldScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	heraldList = {
		{ planet = "corellia", template = "herald_commoner", customName = "Excited Journalist", x = -5192.9, z = 21, y = -2545.55, angle = 46.5164, cell = 0, destX = 4651, destY = -5616, stringFile = "herald_corellia_imperial_strongold" },
		{ planet = "corellia", template = "herald_selonian_diplomat", x = 3256.5, z = 300, y = 5418.4, angle = -89, cell = 0, destX = -2482, destY = 2907, stringFile = "herald_corellia_afarathucave" },
		{ planet = "corellia", template = "herald_corellia_karin", x = -185, z = 28, y = -4460.71, angle = 0, cell = 0, destX = 1041, destY = 4193, stringFile = "herald_corellia_drall_patriot_hideout" },
		{ planet = "corellia", template = "herald_corellia_lock", x = -5418.26, z = 20.9986, y = -2792.36, angle = 59.9, cell = 0, destX = 1413, destY = -317, stringFile = "herald_corellia_lord_nyax_cult" },
		{ planet = "corellia", template = "herald_corsec_agent", x = -202.143, z = 28, y = -4504.32, angle = 203.539, cell = 0, destX = 5290, destY = 1493, stringFile = "herald_corellia_rogue_corsec" },
		--[[
		{ planet = "dantooine", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dantooine", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dantooine", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dantooine", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },

		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "dathomir", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },

		{ planet = "endor", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "endor", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "endor", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },

		{ planet = "lok", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
		{ planet = "lok", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },]]

		{ planet = "naboo", template = "herald_commoner", x = -13.9, z = 1.1, y = -9.9, angle = 71, cell = 1741472, destX = -6479, destY = -3243,  stringFile = "herald_naboo_imperial_weapon_research_facility" },
		{ planet = "naboo", template = "herald_commoner", x = 1998.4, z = 12, y = 2538.1, angle = -54, cell = 0, destX = 5860, destY = -4655,  stringFile = "herald_naboo_narglatch_cave" },
		{ planet = "naboo", template = "herald_commoner", x = 1573.2, z = 25, y = 2824.3, angle = -84, cell = 0, destX = 5741, destY = -1546,  stringFile = "herald_naboo_veermok_cave" },
		{ planet = "naboo", template = "herald_rsf_security_guard", x = -5032.08, z = 6, y = 4091.71, angle = 115, cell = 0, destX = -264, destY = 2823,  stringFile = "herald_naboo_gungan_warrior_stronghold" },
		{ planet = "naboo", template = "herald_patron", x = -5538, z = 6, y = 4365.1, angle = 103, cell = 0, destX = 2915, destY = 1151,  stringFile = "herald_naboo_mauler_encampment" },
	--[[
	{ planet = "rori", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "rori", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "rori", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "rori", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },

	{ planet = "talus", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "talus", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "talus", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "talus", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
]]
	{ planet = "tatooine", template = "herald_commoner", x = 1271.2, z = 7, y = 2972.48, angle = 288.274, cell = 0, destX = 57.5, destY = -88.6,  stringFile = "herald_tatooine_squill_cave" },
	{ planet = "tatooine", template = "herald_commoner", x = 145.91, z = 52, y = -5336.3, angle = 210, cell = 0, destX = -5370, destY = -4468,  stringFile = "herald_tatooine_tusken_village" },
	{ planet = "tatooine", template = "herald_commoner", x = -9.5, z = 0.408, y = 0.574, angle = 94, cell = 1213345, destX = 6551, destY = -1323,  stringFile = "herald_tatooine_beetle_cave" },
	{ planet = "tatooine", template = "herald_commoner", x = 3371.3, z = 5.0, y = -4520.8, angle = 118, cell = 0, destX = 5148, destY = 613,  stringFile = "herald_tatooine_hutt_hideout" },
	{ planet = "tatooine", template = "herald_lorne_prestar", x = 3376.1, z = 5, y = -4786, angle = 117, cell = 0, destX = -3976, destY = 6317,  stringFile = "herald_tatooine_fort_tusken" },
	{ planet = "tatooine", template = "herald_imperial_colonel", x = -1300, z = 12, y = -3507.2, angle = 100, cell = 0, destX = 0, destY = 0,  stringFile = "herald_tatooine_tusken_bunker" },
	{ planet = "tatooine", template = "herald_imperial_army_captain", x = -1307.46, z = 12, y = -3662.44, angle = 218.6, cell = 0, destX = -784, destY = -4451,  stringFile = "herald_tatooine_rebel_military_base" },
--[[
	{ planet = "yavin4", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "yavin4", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "yavin4", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "yavin4", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" },
	{ planet = "yavin4", template = "", x = 0, z = 0, y = 0, angle = 0, cell = 0, destX = 0, destY = 0,  stringFile = "" }, ]]
	}
}

registerScreenPlay("heraldScreenPlay", true)

function heraldScreenPlay:start()
	self:spawnMobiles()
end

function heraldScreenPlay:spawnMobiles()
	local mobiles = self.heraldList
	for i = 1, table.getn(mobiles), 1 do
		if isZoneEnabled(mobiles[i].planet) then
			local pSpawn = spawnMobile(mobiles[i].planet, mobiles[i].template, 1, mobiles[i].x, mobiles[i].z, mobiles[i].y, mobiles[i].angle, mobiles[i].cell)
			if (pSpawn ~= nil) then
				if (mobiles[i].customName ~= nil) then
					CreatureObject(pSpawn):setCustomObjectName(mobiles[i].customName)
				end
				writeData(SceneObject(pSpawn):getObjectID() .. ":heraldID", i)
			end
		end
	end
end

function heraldScreenPlay:createLoc(pPlayer, heraldNum)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local heraldData = self.heraldList[heraldNum]
		local stfFile = "@spawning/static_npc/" .. heraldData.stringFile
		local waypointID = playerObject:addWaypoint(heraldData.planet, stfFile .. ":waypoint_name_1", stfFile .. ":waypoint_description_1", heraldData.destX, heraldData.destY, WAYPOINT_COLOR_PURPLE, true, true, 0, 0)
		writeData(player:getObjectID() .. ":herald" .. heraldNum, waypointID)

		local pArea = spawnSceneObject(heraldData.planet, "object/active_area.iff", heraldData.destX, heraldData.z, heraldData.destY, 0, 0, 0, 0, 0)
		ObjectManager.withActiveArea(pArea, function(activeArea)
			activeArea:setRadius(10)
			createObserver(ENTEREDAREA, "heraldScreenPlay", "notifyEnteredHeraldArea", pArea)
			writeData(activeArea:getObjectID() .. ":ownerID", player:getObjectID())
			writeData(activeArea:getObjectID() .. ":heraldNum", heraldNum)
			writeData(player:getObjectID() .. ":heraldArea" .. heraldNum, activeArea:getObjectID())
		end)
	end)
end

function heraldScreenPlay:notifyEnteredHeraldArea(pActiveArea, pPlayer)
	return ObjectManager.withActiveArea(pActiveArea, function(activeArea)
		local ownerID = readData(activeArea:getObjectID() .. ":ownerID")
		local heraldNum = readData(activeArea:getObjectID() .. ":heraldNum")
		if (ownerID == CreatureObject(pPlayer):getObjectID()) then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/messages:go_message")
			self:cleanUp(pPlayer, heraldNum)
		end
	end)
end

function heraldScreenPlay:cleanUp(pPlayer, heraldNum)
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local waypointID = readData(player:getObjectID() .. ":herald" .. heraldNum)
		local areaID = readData(player:getObjectID() .. ":heraldArea" .. heraldNum)
		playerObject:removeWaypoint(waypointID, true)
		local pArea = getSceneObject(areaID)
		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end
		deleteData(SceneObject(pArea):getObjectID() .. ":ownerID")
		deleteData(SceneObject(pArea):getObjectID() .. ":heraldNum")
		writeData(player:getObjectID() .. ":heraldArea" .. heraldNum, 0)
		writeData(player:getObjectID() .. ":herald" .. heraldNum, 0)
	end)
end

HeraldConvoHandler = Object:new {
	themePark = nil
}

function HeraldConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function HeraldConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if screenID == "init" then
		conversationScreen = self:handleScreenInit(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_1_1" then
		conversationScreen = self:handleScreenNpc1(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_2_1" then
		conversationScreen = self:handleScreenNpc2(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_3_1" then
		conversationScreen = self:handleScreenNpc3(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_4_1" then
		conversationScreen = self:handleScreenNpc4(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_work_1" then
		conversationScreen = self:handleScreenNpcWork(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_reset" then
		conversationScreen = self:handleScreenNpcReset(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	elseif screenID == "npc_backtowork_1" then
		conversationScreen = self:handleScreenNpcBackToWork(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	end
	return conversationScreen
end

function HeraldConvoHandler:handleScreenNpc1(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_1_1")
	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_1", "npc_2_1")
	clonedScreen:addOption(stfFile .. ":player_2_1", "npc_3_1")
	clonedScreen:addOption(stfFile .. ":player_3_1", "npc_4_1")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpc2(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local heraldData = self.themePark.heraldList[heraldNumber]
	local stfFile = "@spawning/static_npc/" .. heraldData.stringFile
	heraldScreenPlay:createLoc(pConversingPlayer, heraldNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_2_1")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpc3(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_3_1")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpc4(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_4_1")
	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_1_1", "npc_2_1")
	clonedScreen:addOption(stfFile .. ":player_2_1", "npc_3_1")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpcWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_work_1")

	clonedScreen:removeAllOptions()

	clonedScreen:addOption(stfFile .. ":player_sorry", "npc_backtowork_1")
	clonedScreen:addOption(stfFile .. ":player_reset", "npc_reset")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpcBackToWork(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	heraldScreenPlay:createLoc(pConversingPlayer, heraldNumber)
	heraldScreenPlay:cleanUp(pConversingPlayer, heraldNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_backtowork_1")

	return pConversationScreen
end

function HeraldConvoHandler:handleScreenNpcReset(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local heraldNumber = readData(SceneObject(pConversingNpc):getObjectID() .. ":heraldID")
	local stfFile = "@spawning/static_npc/" .. self.themePark.heraldList[heraldNumber].stringFile

	heraldScreenPlay:cleanUp(pConversingPlayer, heraldNumber)

	clonedScreen:setDialogTextStringId(stfFile .. ":npc_reset")

	return pConversationScreen
end


function HeraldConvoHandler:handleScreenInit(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local convoTemplate = LuaConversationTemplate(conversationTemplate)
	local nextScreenName
	local heraldNumber = readData(SceneObject(conversingNPC):getObjectID() .. ":heraldID")
	local activeHerald = readData(CreatureObject(conversingPlayer):getObjectID() .. ":herald" .. heraldNumber)
	if activeHerald ~= 0 then
		nextScreenName = "npc_work_1"
	else
		nextScreenName = "npc_1_1"
	end
	return self:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, convoTemplate:getScreen(nextScreenName))
end

function HeraldConvoHandler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
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

herald_conv_handler = HeraldConvoHandler:new {
	themePark = heraldScreenPlay
}