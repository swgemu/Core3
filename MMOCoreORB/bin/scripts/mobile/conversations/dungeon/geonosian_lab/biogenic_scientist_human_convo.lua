biogenicScientistHumanConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicScientistHumanConvoHandler",
	screens = {}
}

thanks_so_much = ConvoScreen:new {
	id = "thanks_so_much",
	leftDialog = "@conversation/biogenic_scientist_human:s_ba27cb12", -- Oh, thank you so much! Thank you for saving my life. I just want to get out of here. I want to get away.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_dc4694a0", "killed_quite_a_few"}, -- It should be safe for you to leave now.
		{"@conversation/biogenic_scientist_human:s_3c5b4784", "well_yes"}, -- Hey now. Don't I get something for saving your life?
		{"@conversation/biogenic_scientist_human:s_976331da", "thank_you_wait"} -- It's my pleasure. Be careful, and good luck.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(thanks_so_much);

killed_quite_a_few = ConvoScreen:new {
	id = "killed_quite_a_few",
	leftDialog = "@conversation/biogenic_scientist_human:s_b479c40b", -- Yes, you seem to have killed quite a few of those creatures. I'll try to make my way out. Before I go, though, I may have something you might could use...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_1c8bddbb", "here_it_is"}, -- What is it?
		{"@conversation/biogenic_scientist_human:s_c28dc6ef", "no_i_insist"} -- No, thank you. That's not necessary.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(killed_quite_a_few);

no_i_insist = ConvoScreen:new {
	id = "no_i_insist",
	leftDialog = "@conversation/biogenic_scientist_human:s_e2c55073", -- No, no, I insist. A long time ago, we had plans to build weapons in case our experiments ever got out of control. We never got around to building them, and I guess now it's too late. Someone like yourself should be able to make use of this.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_e79d7d15", "i_hope_so"} -- Sure, it might come in handy.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(no_i_insist);

well_yes = ConvoScreen:new {
	id = "well_yes",
	leftDialog = "@conversation/biogenic_scientist_human:s_7e89fa19", -- Oh, well yes, I suppose I do have something here. Let me see if I can find it.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_1c8bddbb", "here_it_is"}, -- What is it?
		{"@conversation/biogenic_scientist_human:s_46b9a9b7", "no_youre_right"} -- On second thought, it's not necessary.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(well_yes);

here_it_is = ConvoScreen:new {
	id = "here_it_is",
	leftDialog = "@conversation/biogenic_scientist_human:s_ce30b8e3", -- Oh, yes, here it is. A long time ago, we had plans to build weapons in case our experiments ever got out of control. We never got around to building them, and I guess now it's too late. Someone like yourself should be able to make use of this.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_e79d7d15", "i_hope_so"} -- Sure, it might come in handy.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(here_it_is);

no_youre_right = ConvoScreen:new {
	id = "no_youre_right",
	leftDialog = "@conversation/biogenic_scientist_human:s_91b03aa5", -- No, you're right. Here we go. A long time ago, we had plans to build weapons in case our experiments ever got out of control. We never got around to building them, and I guess now it's too late. Someone like yourself should be able to make use of this.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_e79d7d15", "i_hope_so"} -- Sure, it might come in handy.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(no_youre_right);

since_youre_here = ConvoScreen:new {
	id = "since_youre_here",
	leftDialog = "@conversation/biogenic_scientist_human:s_b076c975", -- Since you're here, could you please check on my colleagues in Genetics Lab One. If they were still in there when the doors locked down they might be in trouble. You can unlock the door with the code 86332 if necessary.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_259e4732", "thanks_appreciate"}, -- I'll make sure they're OK.
		{"@conversation/biogenic_scientist_human:s_a2a14f83", "alright_may_be_trouble"} -- We'll see if I get a chance.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(since_youre_here);

glad_youre_back = ConvoScreen:new {
	id = "glad_youre_back",
	leftDialog = "@conversation/biogenic_scientist_human:s_2f286865", -- Oh hey, I'm glad you came back. I'm getting ready to get out of here, but before I go, I have something that I wanted to give you...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_1c8bddbb", "here_it_is"}, -- What is it?
		{"@conversation/biogenic_scientist_human:s_c28dc6ef", "no_i_insist"} -- No, thank you. That's not necessary.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(glad_youre_back);

thank_you_wait = ConvoScreen:new {
	id = "thank_you_wait",
	leftDialog = "@conversation/biogenic_scientist_human:s_d080da0e", -- Thank you. Oh, wait a minute. Before you go I have something maybe that you can use. Just a moment and let me find it...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_7516dec7", "no_i_want_you_to"}, -- That's not necessary. You don't need to give me anything.
		{"@conversation/biogenic_scientist_human:s_1c8bddbb", "here_it_is"} -- What is it?
	}
}

biogenicScientistHumanConvoTemplate:addScreen(thank_you_wait);

thanks_appreciate = ConvoScreen:new {
	id = "thanks_appreciate",
	leftDialog = "@conversation/biogenic_scientist_human:s_f891f03f", -- Thank you so much. I appreciate it.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistHumanConvoTemplate:addScreen(thanks_appreciate);

i_hope_so = ConvoScreen:new {
	id = "i_hope_so",
	leftDialog = "@conversation/biogenic_scientist_human:s_4c5806c8", -- I hope so.  If you can, please check on my collegues in Genetics Lab One. If they were still in there when the doors locked down they might be in trouble. You can unlock the door with the code 86332 if necessary.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_259e4732", "thanks_appreciate"}, -- I'll make sure they're OK.
		{"@conversation/biogenic_scientist_human:s_a2a14f83", "alright_may_be_trouble"} -- We'll see if I get a chance.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(i_hope_so);

alright_may_be_trouble = ConvoScreen:new {
	id = "alright_may_be_trouble",
	leftDialog = "@conversation/biogenic_scientist_human:s_37a3f14d", -- Alright, but they may be in serious trouble. Thank you anyway for all your help.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistHumanConvoTemplate:addScreen(alright_may_be_trouble);

go_on_ahead = ConvoScreen:new {
	id = "go_on_ahead",
	leftDialog = "@conversation/biogenic_scientist_human:s_6fc909ee", -- You go on ahead. I'm just going to rest here for a moment. Don't forget, if you need to get into Genetics Lab One, you can use the code 86332.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistHumanConvoTemplate:addScreen(go_on_ahead);

no_i_want_you_to = ConvoScreen:new {
	id = "no_i_want_you_to",
	leftDialog = "@conversation/biogenic_scientist_human:s_a643bebd", -- No, I want you to have it. A long time ago, we had plans to build weapons in case our experiments ever got out of control. We never got around to building them, and I guess now it's too late. Someone like yourself should be able to make use of this.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_human:s_4136c2df", "since_youre_here"} -- Thank you very much.
	}
}

biogenicScientistHumanConvoTemplate:addScreen(no_i_want_you_to);

addConversationTemplate("biogenicScientistHumanConvoTemplate", biogenicScientistHumanConvoTemplate);