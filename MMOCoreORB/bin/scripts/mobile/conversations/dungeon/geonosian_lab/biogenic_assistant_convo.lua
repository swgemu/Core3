biogenicAssistantConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicAssistantConvoHandler",
	screens = {}
}

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_assistant:s_7dfa7256", -- Thank you for killing those creatures. They've escaped from their cages and they're out of control.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_ea2d9bb0","codes_for_reactor"}, -- What is it that you're doing here?
		{"@conversation/biogenic_assistant:s_82bc35bf","dont_know_much"}, -- Can you tell me anything about those monsters?
		{"@conversation/biogenic_assistant:s_89ca9e86","really_take_back_datapad"} -- The engineer told me to come get the codes from you.
	}
}

biogenicAssistantConvoTemplate:addScreen(init_talk);

really_take_back_datapad = ConvoScreen:new {
	id = "really_take_back_datapad",
	leftDialog = "@conversation/biogenic_assistant:s_b856cb2e", -- Really? Would you take them back to him? They are on this datapad. Thank you so much.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_33eb85b5","really_fantastic"}, -- Sure, I will take the codes to the engineer.
		{"@conversation/biogenic_assistant:s_eeaf9e0b","ok_i_understand"} -- Sorry, I don't have time right now.
	}
}

biogenicAssistantConvoTemplate:addScreen(really_take_back_datapad);

dont_know_much = ConvoScreen:new {
	id = "dont_know_much",
	leftDialog = "@conversation/biogenic_assistant:s_255de7f7", -- Not much. This is a genetic research facility, but I'm an engineering assistant. I don't know much about that stuff. But it would seem that when that earthquake hit, it somehow released the creatures from their cages.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_950188fd","have_codes_engineer_needs"} -- Assistant? I was told to get some codes from you?
	}
}

biogenicAssistantConvoTemplate:addScreen(dont_know_much);

i_have_these_codes = ConvoScreen:new {
	id = "i_have_these_codes",
	leftDialog = "@conversation/biogenic_assistant:s_be849f7b", -- I have these computer codes that I need to get to the engineer, but the creatures attacked me before I could get back to him. I wonder if you could bring the codes to him for me?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_33eb85b5","really_fantastic"}, -- Sure, I will take the codes to the engineer.
		{"@conversation/biogenic_assistant:s_eeaf9e0b","ok_i_understand"} -- Sorry, I don't have time right now.
	}
}

biogenicAssistantConvoTemplate:addScreen(i_have_these_codes);

have_codes_engineer_needs = ConvoScreen:new {
	id = "have_codes_engineer_needs",
	leftDialog = "@conversation/biogenic_assistant:s_d8a95d57", -- Yes, I have these computer codes that the head engineer needs, but I was attacked by these creatures. Here, the codes are on this datapad. Please take them to him.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_33eb85b5","really_fantastic"}, -- Sure, I will take the codes to the engineer.
		{"@conversation/biogenic_assistant:s_eeaf9e0b","ok_i_understand"} -- Sorry, I don't have time right now.
	}
}

biogenicAssistantConvoTemplate:addScreen(have_codes_engineer_needs);

really_fantastic = ConvoScreen:new {
	id = "really_fantastic",
	leftDialog = "@conversation/biogenic_assistant:s_c251c56d", -- Really? That would be fantastic! Here, the codes are on this datapad. You should be able to find him near the reactor. If the door to the engineering room is locked, the code 51892 will get you in. Thank you so much for your help.
	stopConversation = "true",
	options = {
	}
}

biogenicAssistantConvoTemplate:addScreen(really_fantastic);

ok_i_understand = ConvoScreen:new {
	id = "ok_i_understand",
	leftDialog = "@conversation/biogenic_assistant:s_aa495893", -- OK, I understand. If you get a chance, please come back.
	stopConversation = "true",
	options = {
	}
}

biogenicAssistantConvoTemplate:addScreen(ok_i_understand);

back_ask_favor = ConvoScreen:new {
	id = "back_ask_favor",
	leftDialog = "@conversation/biogenic_assistant:s_bf513acb", -- Oh, hey, you're back. I wonder if I could ask you for a favor?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_80dc0120","i_have_these_codes"}, -- What is the favor?
		{"@conversation/biogenic_assistant:s_eeaf9e0b","ok_i_understand"} -- Sorry, I don't have time right now.
	}
}

biogenicAssistantConvoTemplate:addScreen(back_ask_favor);

codes_for_reactor = ConvoScreen:new {
	id = "codes_for_reactor",
	leftDialog = "@conversation/biogenic_assistant:s_c3bd7233", -- I have the computer codes that the head engineer needs to get the reactor back online. I was on my way back to the engineering room, but I can't possibly make it there with all these creatures loose.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_114e560","really_take_them_back"}, -- Actually, he just told me to come get the codes.
		{"@conversation/biogenic_assistant:s_72510ac3","i_hope_so"} -- I'm sure you'll get there somehow. Good-bye.
	}
}

biogenicAssistantConvoTemplate:addScreen(codes_for_reactor);

i_hope_so = ConvoScreen:new {
	id = "i_hope_so",
	leftDialog = "@conversation/biogenic_assistant:s_bbbd5d0f", -- Yes, I hope so. Good-bye.
	stopConversation = "true",
	options = {
	}
}

biogenicAssistantConvoTemplate:addScreen(i_hope_so);

really_take_them_back = ConvoScreen:new {
	id = "really_take_them_back",
	leftDialog = "@conversation/biogenic_assistant:s_b856cb2e", -- Really? Would you take them back to him? They are on this datapad. Thank you so much.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_assistant:s_33eb85b5","really_fantastic"}, -- Sure, I will take the codes to the engineer.
		{"@conversation/biogenic_assistant:s_eeaf9e0b","ok_i_understand"} -- Sorry, I don't have time right now.
	}
}

biogenicAssistantConvoTemplate:addScreen(really_take_them_back);

thanks_for_delivering = ConvoScreen:new {
	id = "thanks_for_delivering",
	leftDialog = "@conversation/biogenic_assistant:s_25e7c7e7", -- Thank you for delivering the codes to the engineer. You've been a great help.
	stopConversation = "true",
	options = {
	}
}

biogenicAssistantConvoTemplate:addScreen(thanks_for_delivering);

please_deliver_codes = ConvoScreen:new {
	id = "please_deliver_codes",
	leftDialog = "@conversation/biogenic_assistant:s_b5c70166", -- Please take the codes to the engineer. If you need to get into the engineering area, use the code 51892. Thank you very much for your help.
	stopConversation = "true",
	options = {
	}
}

biogenicAssistantConvoTemplate:addScreen(please_deliver_codes);

addConversationTemplate("biogenicAssistantConvoTemplate", biogenicAssistantConvoTemplate);