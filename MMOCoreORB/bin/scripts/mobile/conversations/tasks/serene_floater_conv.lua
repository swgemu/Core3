serene_floater_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "serene_floater_handler",
	screens = {}
}

--You have the scroll
npc_smuggle_3 = ConvoScreen:new {
	id = "npc_smuggle_3",
	leftDialog = "@static_npc/tatooine/hedon_istee:npc_smuggle_3", --The scroll. You have begun your travel down the path of enlightenment, sensualist. We will watch from afar, but no longer through direct intervention.
	stopConversation = "true",
	options = {
	}
}

serene_floater_convotemplate:addScreen(npc_smuggle_3);

--You don't have the scroll
dontknowyou_3 = ConvoScreen:new {
	id = "dontknowyou_3",
	leftDialog = "@static_npc/tatooine/hedon_istee:dontknowyou_3", --Until that time has come, your life will be filled with false euphoria.
	stopConversation = "true",
	options = {
	}
}

serene_floater_convotemplate:addScreen(dontknowyou_3);

addConversationTemplate("serene_floater_convotemplate", serene_floater_convotemplate);