heroOfTatRanchersWifeConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatRanchersWifeConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_82bd1b20", -- Who are you?! More of those thugs? I'll lock you up like I did the rest of your friends! Get out!!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_84ee73da", "guess_you_arent"}, -- Hold on! I'm not a thug or a pirate at all.
		{"@conversation/quest_hero_of_tatooine_wife:s_f6c25472", "leave_now"}, -- Eep! Okay, bye!
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro);

guess_you_arent = ConvoScreen:new {
	id = "guess_you_arent",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_aebcaa68", -- Really? Wait a second. I guess you don't look like a pirate or a thug. I'm sorry. I'm so riled up I can hardly think straight. Look, I could use your help with this. My husband has left to contact the authorities. I need to go calm down or I may do something drastic. Please, go down the stairs and keep an eye on those thugs for me. It would really help me out.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_c5a33502", "thanks_intercom"}, -- I'll go keep an eye on them.
		{"@conversation/quest_hero_of_tatooine_wife:s_e45adc31", "so_heartless"}, -- I'd rather not get into this mess.
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(guess_you_arent);

thanks_intercom = ConvoScreen:new {
	id = "thanks_intercom",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_83da2e04", -- Thank you so much! There's an intercom outside the room in which I've locked them up. They may try to coerce you into helping them. Just ignore them. I need to go relax for a minute...
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(thanks_intercom);

so_heartless = ConvoScreen:new {
	id = "so_heartless",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_18dbba11", -- Ugh! You're so heartless! Get out of my house! I don't need this right now!
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(so_heartless);

leave_now = ConvoScreen:new {
	id = "leave_now",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_f26b5d58", -- I'll call the authorities on you!! Leave now!
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(leave_now);

intro_hasquest = ConvoScreen:new {
	id = "intro_hasquest",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_7ee07d1c", -- I need to get myself calm. Please go downstairs and keep an eye out for escaping thugs.
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro_hasquest);

intro_noquest = ConvoScreen:new {
	id = "intro_noquest",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_b8584429", -- Being a rancer's wife is hard work. I barely get any time for myself with what all the work I have to do. Oh well. As you can see, having a successful rancher as a husband has its perks! Do you like how I decorated the place? Ack! Look at the time... I really need to get back to work. Nice meeting you!
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro_noquest);

intro_otherinprogress = ConvoScreen:new {
	id = "intro_otherinprogress",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_c74cdffb", -- I'm sorry. I'm having issues with pirates right now. Come back a little later. Maybe you can help me then. I really need to concentrate on the situation at hand...
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro_otherinprogress);

intro_distract = ConvoScreen:new {
	id = "intro_distract",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_3220d628", -- How are they? Are they behaving? Thank you for helping me. I completely appreciate this.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_f74cb815", "you_really_think_so"}, -- You know, you did a great job decorating this place.
		{"@conversation/quest_hero_of_tatooine_wife:s_ea1b59c", "cant_believe_this"}, -- They're planning to break out as we speak!
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro_distract);

you_really_think_so = ConvoScreen:new {
	id = "you_really_think_so",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_8ad6289", -- You really think so?! I'm so glad you noticed! I hope to win a house decorating contest this coming summer. I hope to get my home in the spotlight! Do you really think I'll win?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_abec95a3", "so_nice_ahh"}, -- I really think so!
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(you_really_think_so);

so_nice_ahh = ConvoScreen:new {
	id = "so_nice_ahh",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_2622df9f", -- You're so nice! I--AHHH!
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(so_nice_ahh);

cant_believe_this = ConvoScreen:new {
	id = "cant_believe_this",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_63f6701b", -- I can't believe this! I am awed by your honor. Thank you so much for helping us! Oh, here comes my husband now! They're going to take those nasty thugs away! Here, you really deserve this. I hope it will do you well.
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(cant_believe_this);

intro_leftprior = ConvoScreen:new {
	id = "intro_leftprior",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_43f5726a", -- It's you again! What do you want? Can't you see I'm busy?!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_37c0824f", "so_riled_up"}, -- Wait! I want to help you.
		{"@conversation/quest_hero_of_tatooine_wife:s_e83ad536", "go_away"}, -- I'm sorry to disturb you.
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(intro_leftprior);

go_away = ConvoScreen:new {
	id = "go_away",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_6422820b", -- Go away!
	stopConversation = "true",
	options = {}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(go_away);

so_riled_up = ConvoScreen:new {
	id = "so_riled_up",
	leftDialog = "@conversation/quest_hero_of_tatooine_wife:s_50587782", -- You do? I'm so riled up I can hardly think straight. My husband has left to contact the authorities. I need to go calm down or I may do something drastic. Please, go down the stairs and keep an eye on those thugs for me. It would really help me out. Will you help me?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_wife:s_210b4c5b", "thanks_intercom"}, -- Yes, I will!
		{"@conversation/quest_hero_of_tatooine_wife:s_1ecfff90", "so_heartless"}, -- No, I have other things to do.
	}
}
heroOfTatRanchersWifeConvoTemplate:addScreen(so_riled_up);

addConversationTemplate("heroOfTatRanchersWifeConvoTemplate", heroOfTatRanchersWifeConvoTemplate);