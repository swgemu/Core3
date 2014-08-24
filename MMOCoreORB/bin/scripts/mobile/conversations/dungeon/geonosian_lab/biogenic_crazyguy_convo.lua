biogenicCrazyGuyConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicCrazyGuyConvoHandler",
	screens = {}
}

cs_jsPlumb_1_15 = ConvoScreen:new {
	id = "cs_jsPlumb_1_15",
	leftDialog = "@conversation/biogenic_crazyguy:s_eb2f9960", -- HELP! HELP! Are you here?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_5d16248c", "cs_jsPlumb_1_216"}, -- Yes, I'm here. Now what is going on?
		{"@conversation/biogenic_crazyguy:s_e34d6272", "cs_jsPlumb_1_21"}, -- Is who here? Start making sense!
		{"@conversation/biogenic_crazyguy:s_564ba87", "cs_jsPlumb_1_688"}, -- I swear, if you don't tell me what's going on...
		{"@conversation/biogenic_crazyguy:s_e5f4a149", "cs_jsPlumb_1_154"} -- Please don't hurt me. I was just leaving.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_15);

cs_jsPlumb_1_19 = ConvoScreen:new {
	id = "cs_jsPlumb_1_19",
	leftDialog = "@conversation/biogenic_crazyguy:s_d166b780", -- Go? No, I want you to leave... in there!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_e1fbb5ed", "cs_jsPlumb_1_127"}, -- In where? Into that opening back there?
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "cs_jsPlumb_1_1043"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_19);

cs_jsPlumb_1_21 = ConvoScreen:new {
	id = "cs_jsPlumb_1_21",
	leftDialog = "@conversation/biogenic_crazyguy:s_1c4a552c", -- No, who is not here. That is... the problem. I think? Are you ...who?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_7d4e91e1", "cs_jsPlumb_1_410"}, -- Yes, I am. I think.
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "cs_jsPlumb_1_1043"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_21);

cs_jsPlumb_1_37 = ConvoScreen:new {
	id = "cs_jsPlumb_1_37",
	leftDialog = "@conversation/biogenic_crazyguy:s_51edfa93", -- Then maybe you aren't... who you are. So long then.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_37);

cs_jsPlumb_1_114 = ConvoScreen:new {
	id = "cs_jsPlumb_1_114",
	leftDialog = "@conversation/biogenic_crazyguy:s_80c190c3", -- *gurk* Why... you're here? Did they send you? I see that you're here.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_f6dd63d", "cs_jsPlumb_1_15"}, -- Did who send me? What's going on here?
		{"@conversation/biogenic_crazyguy:s_e7953fb5", "cs_jsPlumb_1_210"}, -- What is the matter with you?
		{"@conversation/biogenic_crazyguy:s_daa5a74d", "cs_jsPlumb_1_498"} -- Ok, you seem distracted. I'll leave you alone.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_114);

cs_jsPlumb_1_137 = ConvoScreen:new {
	id = "cs_jsPlumb_1_137",
	leftDialog = "@conversation/biogenic_crazyguy:s_4e52ced2", -- Hey, I remember you... but I've never seen you before.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_9499432", "cs_jsPlumb_1_548"}, -- Still crazy as ever I see.
		{"@conversation/biogenic_crazyguy:s_a64c5d9e", "cs_jsPlumb_1_37"}, -- Of course you have, I was here just a bit ago.
		{"@conversation/biogenic_crazyguy:s_70a572af", "cs_jsPlumb_1_927"} -- I don't have time for this. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_137);

cs_jsPlumb_1_160 = ConvoScreen:new {
	id = "cs_jsPlumb_1_160",
	leftDialog = "@conversation/biogenic_crazyguy:s_68d073fe", -- Keep what in mind? Was it something important? Oh well.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_564ba87", "cs_jsPlumb_1_688"}, -- I swear, if you don't tell me what's going on...
		{"@conversation/biogenic_crazyguy:s_3157939", "cs_jsPlumb_1_33"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_160);

cs_jsPlumb_1_210 = ConvoScreen:new {
	id = "cs_jsPlumb_1_210",
	leftDialog = "@conversation/biogenic_crazyguy:s_74fbbad2", -- Look around... do you see it? That's, uh... what is?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_9c653067", "cs_jsPlumb_1_224"}, -- See what? I don't...
		{"@conversation/biogenic_crazyguy:s_564ba87", "cs_jsPlumb_1_688"} -- I swear, if you don't tell me what's going on...
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_210);

cs_jsPlumb_1_216 = ConvoScreen:new {
	id = "cs_jsPlumb_1_216",
	leftDialog = "@conversation/biogenic_crazyguy:s_14b63e24", -- Yes! I see you are... the truth. When you leave... we all can go. But I must tell you...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_1c8bddbb", "cs_jsPlumb_1_220"}, -- What is it?
		{"@conversation/biogenic_crazyguy:s_f0a82cfa", "cs_jsPlumb_1_1030"}, -- I think you've told me enough already.
		{"@conversation/biogenic_crazyguy:s_70a572af", "cs_jsPlumb_1_927"} -- I don't have time for this. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_216);

cs_jsPlumb_1_220 = ConvoScreen:new {
	id = "cs_jsPlumb_1_220",
	leftDialog = "@conversation/biogenic_crazyguy:s_5d995d79", -- Life is not all about... rhyming. And soon it will be over.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_fd7a670e", "cs_jsPlumb_1_160"}, -- Right... I'll try to, um... keep that in mind.
		{"@conversation/biogenic_crazyguy:s_20413fbf", "cs_jsPlumb_1_561"} -- I'm sorry, I guess I just don't get it. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_220);

cs_jsPlumb_1_224 = ConvoScreen:new {
	id = "cs_jsPlumb_1_224",
	leftDialog = "@conversation/biogenic_crazyguy:s_3e250a", -- No... no one. No one does. No one anymore.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_224);

cs_jsPlumb_1_410 = ConvoScreen:new {
	id = "cs_jsPlumb_1_410",
	leftDialog = "@conversation/biogenic_crazyguy:s_524005c4", -- Yes! Yes you are! I see you... now you must go!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_64bc92a0", "cs_jsPlumb_1_463"}, -- Go where? Tell me what's happening!
		{"@conversation/biogenic_crazyguy:s_cc90aebb", "cs_jsPlumb_1_195"} -- Good idea. I can't take any more of this.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_410);

cs_jsPlumb_1_463 = ConvoScreen:new {
	id = "cs_jsPlumb_1_463",
	leftDialog = "@conversation/biogenic_crazyguy:s_b18aca61", -- What isn't happening? You, that's what... why? Go now.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_be321a24", "cs_jsPlumb_1_548"}, -- Ok, ok. I'm going.
		{"@conversation/biogenic_crazyguy:s_a9f69fb7", "cs_jsPlumb_1_127"}, -- Go? You want me to leave?
		{"@conversation/biogenic_crazyguy:s_3157939", "cs_jsPlumb_1_33"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_463);

cs_jsPlumb_1_127 = ConvoScreen:new {
	id = "cs_jsPlumb_1_127",
	leftDialog = "@conversation/biogenic_crazyguy:s_7d4f8520", -- Yes, yes. Keep going. That way. No, wait. That way.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_be321a24", "cs_jsPlumb_1_758"}, -- Ok, ok. I'm going.
		{"@conversation/biogenic_crazyguy:s_3157939", "cs_jsPlumb_1_33"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_127);

cs_jsPlumb_1_548 = ConvoScreen:new {
	id = "cs_jsPlumb_1_548",
	leftDialog = "@conversation/biogenic_crazyguy:s_3a0e3163", -- How many? 32281... monsters... 32281... monsters.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_548);

cs_jsPlumb_1_688 = ConvoScreen:new {
	id = "cs_jsPlumb_1_688",
	leftDialog = "@conversation/biogenic_crazyguy:s_469eaf3a", -- No, not going on... going in, and when you've done that... we all go out.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_d87072f3", "cs_jsPlumb_1_19"}, -- Go in? Go out? What are you talking about?
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "cs_jsPlumb_1_1043"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_688);

cs_jsPlumb_1_758 = ConvoScreen:new {
	id = "cs_jsPlumb_1_758",
	leftDialog = "@conversation/biogenic_crazyguy:s_91c86ae2", -- For the monsters... 32281 is it. You see, 32281... monsters. There are 32281 monsters.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_758);

cs_jsPlumb_1_1030 = ConvoScreen:new {
	id = "cs_jsPlumb_1_1030",
	leftDialog = "@conversation/biogenic_crazyguy:s_51edfa93", -- Then maybe you aren't... who you are. So long then.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(cs_jsPlumb_1_1030);

addConversationTemplate("biogenicCrazyGuyConvoTemplate", biogenicCrazyGuyConvoTemplate);