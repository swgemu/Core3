vardias_tyne_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "vardias_tyne_handler",
	screens = {}
}


npc_1_1 = ConvoScreen:new {
	id = "npc_1_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_1_1", --You look like you might know how to handle yourself. Maybe you can...
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_1_1", "npc_2_1"}, --Sure, I'll stop the bounty hunter for you
		{"@static_npc/tatooine/vardias_tyne:player_2_1", "npc_3_1"}, --Sorry but I don't involve myself with this type of thing
		{"@static_npc/tatooine/vardias_tyne:player_3_1", "npc_4_1"} --Did you really kill a sacred beast?
	}
}

vardias_tyne_convotemplate:addScreen(npc_1_1);

npc_2_1 = ConvoScreen:new {
	id = "npc_2_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_2_1", --Good, I thought I was dead for sure.  It's getting so you can't even protect your....
	stopConversation = "true",
	options = {
	}
}

vardias_tyne_convotemplate:addScreen(npc_2_1);

npc_3_1 = ConvoScreen:new {
	id = "npc_3_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_3_1", --I understand.  I wouldn't want to go up against a bounty hunter either.  You'd better clear out...
	stopConversation = "true",
	options = {
		
	}
}

vardias_tyne_convotemplate:addScreen(npc_3_1);

npc_4_1 = ConvoScreen:new {
	id = "npc_4_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_4_1", --All I did was shoot a rougue bantha that was destorying my vaporators.  Those blasted monks worship banthas...
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_1_1", "npc_2_1"}, --Sure, I'll stop the bounty hunter for you
		{"@static_npc/tatooine/vardias_tyne:player_2_1", "npc_3_1"} -- Sorry but I don't involve myself with this type of thing
	}
}

vardias_tyne_convotemplate:addScreen(npc_4_1);

npc_reward_1 = ConvoScreen:new{
	id = "npc_reward_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_reward_1", -- You stopped her?  You've saved my life!  Now I just need to figure out how to calm those monks down...
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_reward_1);

npc_work_1 = ConvoScreen:new{
	id = "npc_work_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_work_1",
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_sorry_1", "npc_backtowork_1"},
		{"@static_npc/tatooine/vardias_tyne:player_reset_1", "npc_reset_1"}
	}
}


vardias_tyne_convotemplate:addScreen(npc_work_1);

npc_reset_1 = ConvoScreen:new{
	id = "npc_reset_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_reset_1",
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_reset_1);

npc_backtowork_1 = ConvoScreen:new{
	id = "npc_backtowork_1",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_backtowork_1",
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_backtowork_1);

----------
--Quest 2 of 2
----------

npc_1_2 = ConvoScreen:new {
	id = "npc_1_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_1_2", -- I have a peace offering for the Dim-U monks.  I hope it will get them to leave me alone...
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_1_2", "npc_2_2"}, --Sure!
		{"@static_npc/tatooine/vardias_tyne:player_2_2", "npc_3_2"}, --No thanks.
		{"@static_npc/tatooine/vardias_tyne:player_3_2", "npc_4_2"} -- What is this peace offering?
	}
}

vardias_tyne_convotemplate:addScreen(npc_1_2);

npc_2_2 = ConvoScreen:new {
	id = "npc_2_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_2_2", --You have a good heart.  It's not everybody who will stop to help someone in trouble.
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_2_2);

npc_3_2 = ConvoScreen:new {
	id = "npc_3_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_3_2", --I guess a hotshot like you has better things to do.  Thanks anyway.
	stopConversation = "true",
	options = {
	}
}

vardias_tyne_convotemplate:addScreen(npc_3_2);

npc_4_2 = ConvoScreen:new {
	id = "npc_4_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_4_2", --I hired a talented artist to sculpt a bantha out of a piee of kiliad marble.  I need you to...
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_1_2", "npc_2_2"}, --Sure!
		{"@static_npc/tatooine/vardias_tyne:player_2_2", "npc_3_2"}, --No thanks.
	}
}

vardias_tyne_convotemplate:addScreen(npc_4_2);

npc_work_2 = ConvoScreen:new {
	id = "npc_work_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_work_2", --Did he accept my apoplogy?
	stopConversation = "fasle",
	options = {
		{"@static_npc/tatooine/vardias_tyne:player_sorry_2", "npc_backtowork_2"}, --I haven't made contact with him yet...
		{"@static_npc/tatooine/vardias_tyne:player_reset_2", "npc_reset_2"}, --This is too valuable.  I'm afraid it will be stolen...
	}
}

vardias_tyne_convotemplate:addScreen(npc_work_2);



npc_reward_2 = ConvoScreen:new {
	id = "npc_reward_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_reward_2", --You've come through for me again, and I won't forget it.
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_reward_2);

npc_backtowork_2 = ConvoScreen:new {
	id = "npc_backtowork_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_backtowork_2", --Okay, just let me know what his response is. I hope this...
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_backtowork_2);

npc_reset_2 = ConvoScreen:new {
	id = "npc_reset_2",
	leftDialog = "@static_npc/tatooine/vardias_tyne:npc_reset_2", --I guess a hotshot like you has better things to do.  Thanks anyway.
	stopConversation = "true",
	options = {}
}

vardias_tyne_convotemplate:addScreen(npc_reset_2);


addConversationTemplate("vardias_tyne_convotemplate", vardias_tyne_convotemplate);
