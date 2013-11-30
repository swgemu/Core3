local ObjectManager = require("managers.object.object_manager")
RaceTrackConvoManager = Object:new {}

function RaceTrackConvoManager:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
	return ObjectManager.withCreatureObject(conversingPlayer, function(creatureObject)
		printf(self.trackName)
		local convosession = creatureObject:getConversationSession()
		local lastConversationScreen = nil
		local conversation = LuaConversationTemplate(conversationTemplate)
		local nextConversationScreen
		if ( conversation ~= nil ) then
			-- checking to see if we have a next screen
			if ( convosession ~= nil ) then
				 local session = LuaConversationSession(convosession)
				 if ( session ~= nil ) then
				 	lastConversationScreen = session:getLastConversationScreen()
				 else
				 	print("session was not good in getNextScreen")
				 end
			end
			if ( lastConversationScreen == nil ) then
			 	nextConversationScreen = conversation:getInitialScreen()
			else
				local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
				local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
				nextConversationScreen = conversation:getScreen(optionLink)
			end
		end
		return nextConversationScreen
	end)
end

function RaceTrackConvoManager:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	if ( screenID == "cs_jsPlumb_1_116" ) then
		self:startRacing(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_181" ) then -- Personal Best
		self:displayPersonalBestTime(conversingPlayer)
	elseif ( screenID == "cs_jsPlumb_1_207" ) then -- Track Best
		self:displayTrackBestTime(conversingPlayer)
	end
	return conversationScreen
end

return RaceTrackConvoManager