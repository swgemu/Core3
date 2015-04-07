heroOfTatIntercomConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatIntercomConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_cf46030c", -- Hey! Is anyone out there? Who's that!
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_box:s_46ea9e29", "who_sent_you"}, -- I'm here to watch over you.
	}
}
heroOfTatIntercomConvoTemplate:addScreen(intro);

who_sent_you = ConvoScreen:new {
	id = "who_sent_you",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_83c7eb4e", -- Who sent you? That wife?! She's no good. She tricked us and is starving us in here! C'mon. Help us out of here. We can't do it alone. Our means of escape will cause too much of a ruckuss and she'll just catch us again! Go distract her and we'll do our thing.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_box:s_19cc687c", "blast_it"}, -- Stay quiet in there! I'll do no such thing.
		{"@conversation/quest_hero_of_tatooine_box:s_d22d9b89", "go_talk_to_her"}, -- Okay. I guess.
	}
}
heroOfTatIntercomConvoTemplate:addScreen(who_sent_you);

blast_it = ConvoScreen:new {
	id = "blast_it",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_e601f570", -- Blast it! We're going to be stuck in here! Don't tell her our plans! We'll be finished!
	stopConversation = "true",
	options = {}
}
heroOfTatIntercomConvoTemplate:addScreen(blast_it);

go_talk_to_her = ConvoScreen:new {
	id = "go_talk_to_her",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_68f8b129", -- Fantastic! We'll wait. Quick! Go talk to her..
	stopConversation = "true",
	options = {}
}
heroOfTatIntercomConvoTemplate:addScreen(go_talk_to_her);

intro_alreadytalked = ConvoScreen:new {
	id = "intro_alreadytalked",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_e606ff8b", -- Is that you again? What do you want?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_box:s_46d11795", "scram"}, -- Oh, nothing. I'll go back to my business.
	}
}
heroOfTatIntercomConvoTemplate:addScreen(intro_alreadytalked);

scram = ConvoScreen:new {
	id = "scram",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_8ce1bb85", -- Scram!
	stopConversation = "true",
	options = {}
}
heroOfTatIntercomConvoTemplate:addScreen(scram);

intro_noquest = ConvoScreen:new {
	id = "intro_noquest",
	leftDialog = "@conversation/quest_hero_of_tatooine_box:s_31845b51", -- ....
	stopConversation = "true",
	options = {}
}
heroOfTatIntercomConvoTemplate:addScreen(intro_noquest);

addConversationTemplate("heroOfTatIntercomConvoTemplate", heroOfTatIntercomConvoTemplate);