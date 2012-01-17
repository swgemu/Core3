informant_npc_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreenstart",
	templateType = "InformantNPC",
	screens = {}
}

informant_npc_convoscreenstart = ConvoScreen:new {
	id = "convoscreenstart",
	leftDialog = "1", --Level of the informant.
	stopConversation = "true",
	options = { 
		{"level", "1" }
	}
}
informant_npc_convotemplate:addScreen(informant_npc_convoscreenstart);

addConversationTemplate("informant_npc", informant_npc_convotemplate);