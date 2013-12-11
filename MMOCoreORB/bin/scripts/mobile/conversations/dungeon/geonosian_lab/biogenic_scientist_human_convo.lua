--If this convo has errors - Loc-nar this is the NPC that gives the Tenloss rifle schem and key code for geo lab room 1 86332
biogenic_scientist_human_ConversationTemplate = ConvoTemplate:new {
	initialScreen = "biogen_human_start",
	templateType = "Lua",    
	luaClassHandler = "biogenic_scientist_human_ConversationHandler",
	screens = {}
}

biogen_human_start = ConvoScreen:new {
	id = "biogen_human_start",
	leftDialog = "@conversation/biogenic_scientist_human:s_ba27cb12", -- Oh thank you so much s_976331da
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_dc4694a0","biogen_human_lab"}, -- it should be safe to leave now
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_start);

biogen_human_lab = ConvoScreen:new {
	id = "biogen_human_lab",
	leftDialog = "@conversation/biogenic_scientist_human:s_b076c975", -- since you're here
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_259e4732","biogen_human_minute"}, -- I'll make sure they are ok
		{"@conversation/biogenic_scientist_human:s_a2a14f83","biogen_human_alright"} -- We'll see if I get a chance (start second branch)
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_lab);

biogen_human_minute = ConvoScreen:new {
	id = "biogen_human_minute",
	leftDialog = "@conversation/biogenic_scientist_human:s_d080da0e", -- Thank you. Oh wait a minute. Before you go I have something for you...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_4136c2df","biogen_human_seem"} -- Thank you very much.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_minute);

biogen_human_seem = ConvoScreen:new {
	id = "biogen_human_seem",
	leftDialog = "@conversation/biogenic_scientist_human:s_b479c40b", -- Yes, you seem to have killed quite a few of those creatures.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_1c8bddbb","biogen_human_ohyes"}, -- What is it?
		{"@conversation/biogenic_scientist_human:s_7516dec7","biogen_human_longtime"} -- That's not necessary
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_seem);

biogen_human_longtime = ConvoScreen:new {
	id = "biogen_human_longtime",
	leftDialog = "@conversation/biogenic_scientist_human:s_a643bebd", -- No, I want you to have it. A long time ago...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_f891f03f","biogen_human_pleasure"}, -- Thank You so much. I appreciate it.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_longtime);

biogen_human_ohyes = ConvoScreen:new {
	id = "biogen_human_ohyes",
	leftDialog = "@conversation/biogenic_scientist_human:s_ce30b8e3", -- Oh, yes, here it is. A long time ago, we had plans to build weapons...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_f891f03f","biogen_human_pleasure"}, -- Thank You so much. I appreciate it.
		{"@conversation/biogenic_scientist_human:s_46b9a9b7","biogen_human_second"} -- On second thought, it's not necessary.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_ohyes);

biogen_human_second = ConvoScreen:new {
	id = "biogen_human_second",
	leftDialog = "@conversation/biogenic_scientist_human:s_4c5806c8", -- I hope so. If you can, please check on my collegues in the Gentics Lab One. (set state for convo complete without reward)
	stopConversation = "true",
	options = {
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_second);

-- start second branch

biogen_human_alright = ConvoScreen:new {
	id = "biogen_human_alright",
	leftDialog = "@conversation/biogenic_scientist_human:s_37a3f14d", -- Alright, but they may be in serious trouble. Thank you for your help.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_3c5b4784","biogen_human_heynow"} -- Hey Now. Don't I get something for saving your life?
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_alright);

biogen_human_heynow = ConvoScreen:new {
	id = "biogen_human_heynow",
	leftDialog = "@conversation/biogenic_scientist_human:s_7e89fa19", -- Oh, Well yes, I suppose I do have something here. Let me see if I can find it.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_1c8bddbb","biogen_human_herewego"} -- What is it?
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_heynow);

biogen_human_herewego = ConvoScreen:new {
	id = "biogen_human_herewego",
	leftDialog = "@conversation/biogenic_scientist_human:s_91b03aa5", -- No, You're right. Here we go. A long time ago...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_4136c2df","biogen_human_pleasure"}, -- Thank you very much
		{"@conversation/biogenic_scientist_human:s_c28dc6ef","biogen_human_insist"}  -- No thank you. That's not necessary.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_herewego);

biogen_human_insist = ConvoScreen:new {
	id = "biogen_human_insist",
	leftDialog = "@conversation/biogenic_scientist_human:s_e2c55073", -- No, no, I insist. A long time go, we...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_e79d7d15","biogen_human_problem"} -- Sure, it might come in handy.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_insist);

biogen_human_problem = ConvoScreen:new {
	id = "biogen_human_problem",
	leftDialog = "@conversation/biogenic_scientist_human:s_5044c295", -- No problem at all.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_259e4732","biogen_human_pleasure"} -- I'll make sure they are ok
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_problem);

biogen_human_pleasure = ConvoScreen:new {
	id = "biogen_human_pleasure",
	leftDialog = "@conversation/biogenic_scientist_human:s_976331da", -- It's my pleasure. Becareful, and good luck (set state for convo complete with reward)
	stopConversation = "true",
	options = {
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_pleasure);


-- returning player without reward.

biogen_human_returnno = ConvoScreen:new {
	id = "biogen_human_returnno",
	leftDialog = "@conversation/biogenic_scientist_human:s_2f286865", -- Oh hey, I'm glad you came back. I'm getting ready to get out of here..
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_e79d7d15","biogen_human_pleasure"} -- Sure, it might come in handy.
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_returnno);

-- returning player with reward

biogen_human_done = ConvoScreen:new {
	id = "biogen_human_done",
	leftDialog = "@conversation/biogenic_scientist_human:s_6fc909ee", -- You go a head. I'm just going to rest here for a moment.
	stopConversation = "true",
	options = {
	} 
}

biogenic_scientist_human_ConversationTemplate:addScreen(biogen_human_done);


addConversationTemplate("biogenic_scientist_human_ConversationTemplate", biogenic_scientist_human_ConversationTemplate);
