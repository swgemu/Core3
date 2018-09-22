biogenicScientistGeneric02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init_talk",
	templateType = "Lua",
	luaClassHandler = "BiogenicScientistGeneric02ConvoHandler",
	screens = {}
}

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_25dab86a", -- Thank you. Many thanks indeed. But there are still more of those creatures. You must help us kill them.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_02:s_3cfc62f2","in_your_debt"}, -- It's OK. I'm can help.
		{"@conversation/biogenic_scientist_generic_02:s_f2a471b5","we_created_problem"}, -- Forget it. It's your problem. You deal with it.
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(init_talk);

init_helping = ConvoScreen:new {
	id = "init_helping",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_1efc7a3c", -- Thank you for helping us. When you're ready, you can unlock the security door to the cage area with the code 52577.
	stopConversation = "true",
	options = {
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(init_helping);

do_hope_so = ConvoScreen:new {
	id = "do_hope_so",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_fe7a5e25", -- I do hope so. Please hurry, I think there may still be some workers trapped in the main cage area with those monsters.
	stopConversation = "true",
	options = {
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(do_hope_so);

init_not_helping = ConvoScreen:new {
	id = "init_not_helping",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_4a7c5f71", -- I'm sorry that you've decided not to help us.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_02:s_ff058355","in_your_debt"}, -- I changed my mind. I will kill the creatures.
		{"@conversation/biogenic_scientist_generic_02:s_a31ce3f3","hope_youre_right"}, -- I'm sure you'll find some way to deal with it.
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(init_not_helping);

we_created_problem = ConvoScreen:new {
	id = "we_created_problem",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_c0da7db8", -- Yes, unfortunately we did create this problem. But now it has gotten out of control, and the lives of everyone in this complex are in the balance. Won't you please help us?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_02:s_138d31dc","in_your_debt"}, -- Alright. I'll do what I can to help.
		{"@conversation/biogenic_scientist_generic_02:s_8da0f5e3","were_all_dead"} -- Sorry. You're on your own.
	}
}

biogenicScientistGeneric02ConvoTemplate:addScreen(we_created_problem);

were_all_dead = ConvoScreen:new {
	id = "were_all_dead",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_7394ff2a", -- If that is the case, then we are all dead.
	stopConversation = "true",
	options = {
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(were_all_dead);

in_your_debt = ConvoScreen:new {
	id = "in_your_debt",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_ab3423ac", -- Oh, thank you. We are all in your debt. Many of the creatures have been locked inside the main cage area, but someone needs to go in there and finish them off. You can unlock the security door with the code 52577.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_02:s_8da0f5e3","good_luck"}, -- I will take care of the creatures. Good-bye.
		{"@conversation/biogenic_scientist_generic_02:s_787513b2","do_hope_so"}, -- Don't worry. I can handle it.
	}
}

biogenicScientistGeneric02ConvoTemplate:addScreen(in_your_debt);

hope_youre_right = ConvoScreen:new {
	id = "hope_youre_right",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_5f8b04be", -- I hope that you're right, but I doubt it.
	stopConversation = "true",
	options = {
	}
}
biogenicScientistGeneric02ConvoTemplate:addScreen(hope_youre_right);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/biogenic_scientist_generic_02:s_729e1a36", -- Good luck, my friend. Please hurry, I think there may still be some workers trapped in the main cage area with those monsters.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric02ConvoTemplate:addScreen(good_luck);

addConversationTemplate("biogenicScientistGeneric02ConvoTemplate", biogenicScientistGeneric02ConvoTemplate);
