require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

RecordKeeper =ScreenPlay:new {
	quests = { "dummy"},
	keeperName = "dummy",
	faction = 0
}
function RecordKeeper:start()
	-- no op
end
function RecordKeeper:wipeQuests(pObject)
	ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject, playerObject)
		for k,v in pairs(self.quests) do
			-- we wipe out all screen play data for this theme park/quest
			clearScreenPlayData(pObject,k)
		end
		writeScreenPlayData(pObject, self.keeperName, "completed", 1)
	end)
end

function RecordKeeper:resetQuests(pObject)
	for k,v in pairs(self.quests) do
		park = _G[v]
		park:resetCurrentMission(pObject)
	end
	ObjectManager.withCreatureAndPlayerObject(pObject, function(creatureObject, playerObject)
		writeScreenPlayData(pObject, self.keeperName, "completed", 1)
	end)
end
function RecordKeeper:needsFaction()
	if faction == 0 then
		return false
	else
		return true
	end
end

function RecordKeeper:hasFaction(faction, pCreature)
	if pCreature == nil then
		return false
	end

	local creature = CreatureObject(pCreature)

	if creature:getFaction() == faction then
		return true
	else
		return false
	end
end

record_keeper_conv_handler = Object:new {
	keeper = nil
}

function record_keeper_conv_handler:setThemePark(keeperNew)
	self.keeper = keeperNew
end

function record_keeper_conv_handler:getNextConversationScreen(pConversationTemplate, pConversingPlayer, selectedOption)
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
			nextConversationScreen = LuaConversationScreen(nextConversationScreen)
		else
			nextConversationScreen = conversation:getScreen("start")
		end
	else
		nextConversationScreen = conversation:getScreen("start")
	end
	return nextConversationScreen
end
function record_keeper_conv_handler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if screenID == "start" then
		--pConversationScreen = self:handleScreenInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "not_faction" then
		--pConversationScreen = self:handleScreenNoFaction(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "completed" then
		--pConversationScreen = self:handleScreenCompleted(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "not_started" then
		--pConversationScreen = self:handleScreenNotStarted(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	end
	return pConversationScreen
end
-- TODO add case handlers for states of the record keeper
function record_keeper_conv_handler:handleScreenInit(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pConversingPlayer):getObjectID() .. ":activeScreenPlay")
end
function record_keeper_conv_handler:handleScreenNoFaction(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pConversingPlayer):getObjectID() .. ":activeScreenPlay")
end
function record_keeper_conv_handler:handleScreenCompleted(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pConversingPlayer):getObjectID() .. ":activeScreenPlay")
end
function record_keeper_conv_handler:handleScreenNotStarted(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	local nextScreenName
	local activeScreenPlay = readStringData(CreatureObject(pConversingPlayer):getObjectID() .. ":activeScreenPlay")
end