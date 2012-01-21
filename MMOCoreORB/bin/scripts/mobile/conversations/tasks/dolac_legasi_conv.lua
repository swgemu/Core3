dolac_legasi_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "dolac_legasi_handler",
	screens = {}
}

--These are played if you are a Rebel
dontknowyou_1 = ConvoScreen:new {
	id = "dontknowyou_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:dontknowyou_1",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(dontknowyou_1);

dontknowyou_3 = ConvoScreen:new {
	id = "dontknowyou_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:dontknowyou_3",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(dontknowyou_3);

--This is displayed if you have not completed the Mozo Bondog quest line.
notyet = ConvoScreen:new {
	id = "notyet",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:notyet",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(notyet);

--Quest 1 of 3
npc_1_1 = ConvoScreen:new {
	id = "npc_1_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_1_1", --Has the fool Mozo sent you to solve the mystery of the disappearing inmates? I doubt you can, stranger. Odd, isn't it, that I call you stranger when I must seem just as strange to you? Stranger, perhaps. But in this place, most things seem strange. About those disappearing inmates... Interested?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_1", "npc_2_1"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_1", "npc_3_1"} --No.
	}
}

dolac_legasi_convotemplate:addScreen(npc_1_1);

npc_2_1 = ConvoScreen:new {
	id = "npc_2_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_2_1", --As it turns out, one of them has reappeared. Finding him will undoubtably shed some light on where the others have gone. But you must hurry. Dathomir is not exactly the sort of place one wishes to wander about. There are many horrors, both seen and unseen, that can claim a being's life... or soul.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_1", "npc_4_1"} --Tell me more about the disappearances.
	}
}

dolac_legasi_convotemplate:addScreen(npc_2_1);

npc_3_1 = ConvoScreen:new {
	id = "npc_3_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_3_1", --I didn't think you'd be the one to solve this riddle. I'm not sure what made you think you could. Was it the fact that the Force is strong in you? Oh dear, I've said too much.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_3_1);

npc_4_1 = ConvoScreen:new {
	id = "npc_4_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_4_1", --As I said, Dathomir is full of strange occurrences. In most cases, the prison cells were still sealed and there was no evidence of a breakout. What do you think this would imply?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_1", "npc_5_1"} --The inmates had help on the inside.
	}
}

dolac_legasi_convotemplate:addScreen(npc_4_1);

npc_5_1 = ConvoScreen:new {
	id = "npc_5_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_5_1", --That is a good conclusion, yet the recording devices show no evidence of any foul play. And there's the issue of the wraiths.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_1", "npc_6_1"}, --What are the wraiths?
	}
}

dolac_legasi_convotemplate:addScreen(npc_5_1);

npc_6_1 = ConvoScreen:new {
	id = "npc_6_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_6_1", --The specters of those who have died on Dathomir. And those must surely number in the thousands. Could the wraiths have helped these inmates escape? Locate the lost inmate and you might have your answer. Do you wish to do it?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_1", ""}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_1", "npc_3_1"} --No.
	}
}

dolac_legasi_convotemplate:addScreen(npc_6_1);

--Failure Messages
npc_failure_1 = ConvoScreen:new {
	id = "npc_failure_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_1", --What hope did you have against such an ancient evil? You are nothing compared to its power.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_1);

npc_failure_2 = ConvoScreen:new {
	id = "npc_failure_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_2", --No shard, no secrets revealed. Such a waste.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_2);

npc_failure_3 = ConvoScreen:new {
	id = "npc_failure_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_3", --The darkness will spread from Dathomir to other planets. Perhaps the Emperor will have to become involved.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_3);


addConversationTemplate("rebel_recruiter_convotemplate", rebel_recruiter_convotemplate);
