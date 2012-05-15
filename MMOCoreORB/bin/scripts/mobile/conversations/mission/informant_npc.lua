function createInformantTemplate(lvl)
	informant_npc_convotemplate = ConvoTemplate:new {
		initialScreen = "convoscreenstart",
		templateType = "InformantNPC",
		screens = {}
	}
	
	informant_npc_convoscreenstart = ConvoScreen:new {
		id = "convoscreenstart",
		leftDialog = lvl, --Level of the informant.
		stopConversation = "true",
		options = { 
			{"level", lvl }
		}
	}
	informant_npc_convotemplate:addScreen(informant_npc_convoscreenstart);

	addConversationTemplate("informant_npc_lvl_" .. lvl, informant_npc_convotemplate);
end

createInformantTemplate("1")
createInformantTemplate("2")
createInformantTemplate("3")