BiogenicHeraldConvoHandler = conv_handler:new {
	faction = 0
}

function BiogenicHeraldConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if self.faction ~= 0 and TangibleObject(pPlayer):getFaction() ~= self.faction then
		return convoTemplate:getScreen("no_faction")
	end

	return convoTemplate:getScreen("init")
end

biogenic_herald3_conv_handler = BiogenicHeraldConvoHandler:new {
	faction = FACTIONREBEL
}

biogenic_herald2_conv_handler = BiogenicHeraldConvoHandler:new {
	faction = FACTIONIMPERIAL
}
