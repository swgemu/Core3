dolac_legasi_escaped_prisoner_convotemplate = ConvoTemplate:new {
	initialScreen = "otherescort_1",
	templateType = "Normal",
	luaClassHandler = "",
	screens = {}
}

----------
--These are the messages displayed by the prisoner
----------
otherescort_1 = ConvoScreen:new {
	id = "otherescort_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:otherescort_1", --Run! The wraiths are after you!
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_more_1_1", "npc_more_1_1"} --How did you get out of your cell?
	}
}

dolac_legasi_escaped_prisoner_convotemplate:addScreen(otherescort_1);

npc_more_1_1 = ConvoScreen:new {
	id = "npc_more_1_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_more_1_1", --The wraiths willed it to be so. Nothing can contend against them. Soon they will spread to other planets.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_more_2_1", "npc_more_2_1"} --What are these wraiths?
	}
}

dolac_legasi_escaped_prisoner_convotemplate:addScreen(npc_more_1_1);

npc_more_2_1 = ConvoScreen:new {
	id = "npc_more_2_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_more_2_1", --The ghosts of the past. The shadows that move and speak in your mind. Can't you hear them? Can't you see them?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_more_3_1", "npc_more_3_1"} --Where do these wraiths come from?
	}
}

dolac_legasi_escaped_prisoner_convotemplate:addScreen(npc_more_2_1);

npc_more_3_1 = ConvoScreen:new {
	id = "npc_more_3_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_more_3_1", --The place of shadows! That is where they come from. And the shadow stone is where they get their power. They will come for all of us! There is no escape!
	stopConversation = "false",
	options = {
	}
}

dolac_legasi_escaped_prisoner_convotemplate:addScreen(npc_more_3_1);

addConversationTemplate("dolac_legasi_escaped_prisoner_convotemplate", dolac_legasi_escaped_prisoner_convotemplate);