heraldNaboo1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldnaboo:s_df58f20", -- You carry yourself well, my friend. Are you of nobility? No? Then, you must be an adventurer! I have information regarding certain points of interest here on Naboo. Do you wish to hear what I know?
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_3243aa0a", "sorry_to_disturb"}, -- No, I have to go!
		{"@conversation/heraldnaboo:s_7fc11314", "only_know"}, -- Yes, what do you know?
	}
}
heraldNaboo1ConvoTemplate:addScreen(init);

sorry_to_disturb = ConvoScreen:new {
	id = "sorry_to_disturb",
	leftDialog = "@conversation/heraldnaboo:s_68fd1f22", -- Oh! I'm so sorry to disturb you. Please, return when you have the time.
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(sorry_to_disturb);

only_know = ConvoScreen:new {
	id = "only_know",
	leftDialog = "@conversation/heraldnaboo:s_99e4afa", -- I only know what my employer requires me to know. Particularly, about the war between the Gungans and Imperials, the Mauler Camp, and the new Weapon Research Facility that the Empire has established.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_fd9053a8", "long_story"}, -- How did you come across this information?
		{"@conversation/heraldnaboo:s_d65aab98", "more_info"}, -- I'd like some more information.
	}
}
heraldNaboo1ConvoTemplate:addScreen(only_know);

long_story = ConvoScreen:new {
	id = "long_story",
	leftDialog = "@conversation/heraldnaboo:s_726bbe64", -- Well... That's a long story, my friend. I wouldn't even know where to begin. Surely, if I told you the reason, my employer would get rid of me. He's a ruthless man.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_385b2f92", "want_more_info"}, -- Okay, I guess I'll leave it alone, then.
		{"@conversation/heraldnaboo:s_bdc2cc97", "keep_voice_down"}, -- You've made me curious. Tell me.
	}
}
heraldNaboo1ConvoTemplate:addScreen(long_story);

want_more_info = ConvoScreen:new {
	id = "want_more_info",
	leftDialog = "@conversation/heraldnaboo:s_ec04baa6", -- Do you want more information about a particular area I've spoken about?
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_c213fa93", "wish_well"}, -- No, I'm out of here.
		{"@conversation/heraldnaboo:s_87b9da1d", "know_about"}, -- Yes, actually, I do.
	}
}
heraldNaboo1ConvoTemplate:addScreen(want_more_info);

wish_well = ConvoScreen:new {
	id = "wish_well",
	leftDialog = "@conversation/heraldnaboo:s_4b942e33", -- I wish you well, my friend. Have a wonderous day!
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(wish_well);

know_about = ConvoScreen:new {
	id = "know_about",
	leftDialog = "@conversation/heraldnaboo:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_7431a8fb", "loc1"}, -- The Imperial Weapons Research Facility.
		{"@conversation/heraldnaboo:s_b7659e9e", "loc2"}, -- Mauler Encampment
		{"@conversation/heraldnaboo:s_7ad7fe8f", "loc3"}, -- The Gungans and Imperials.
	}
}
heraldNaboo1ConvoTemplate:addScreen(know_about);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldnaboo:s_37c26930", -- An interesting place, that is. I have the general location of the establishment and can download it into your datapad. Just give me a moment--Ah! There we go. As I said, it won't be exact. You may have to do some searching.
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(loc1);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldnaboo:s_36d2fdef", -- They are a vile sort. Roric V`lia, Noble of the Naboo family, whom is my employer, doesn't like to deal with them much. But, I guess--uh. I wasn't suppose to tell you that. Um--here's the location.
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(loc2);

loc3 = ConvoScreen:new {
	id = "loc3",
	leftDialog = "@conversation/heraldnaboo:s_ba21d00c", -- It is such a tragedy. The Gungans are so peaceful, so cute and kind. Well, Jar Jar--I met him once. He's a bit annoying. Anyway! You can find the site of their most recent battle at the location I downloaded in your datapad. It's an exact location, a bit far away, however.
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(loc3);

keep_voice_down = ConvoScreen:new {
	id = "keep_voice_down",
	leftDialog = "@conversation/heraldnaboo:s_fa7e3331", -- Keep your voice down! I can only tell you this; there is something larger than us out there. An undescribable evil that makes even the most generous of nobility turn sour. Be careful, young one. Don't be pulled into their plans, their evil. I can't tell you anything else.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_83237923", "wise_of_you"}, -- I'll keep a lookout.
		{"@conversation/heraldnaboo:s_8858a3fe", "told_you"}, -- I want more information.
	}
}
heraldNaboo1ConvoTemplate:addScreen(keep_voice_down);

wise_of_you = ConvoScreen:new {
	id = "wise_of_you",
	leftDialog = "@conversation/heraldnaboo:s_2ca149bc", -- That is wise of you. Do you wish to hear about the information I can give you?
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_d241258b", "be_careful"}, -- No. Good bye.
		{"@conversation/heraldnaboo:s_ce76e0f", "know_about"}, -- Yes, what information do you have?
	}
}
heraldNaboo1ConvoTemplate:addScreen(wise_of_you);

be_careful = ConvoScreen:new {
	id = "be_careful",
	leftDialog = "@conversation/heraldnaboo:s_a96ea3c0", -- I wish you well. Please be careful. Heed my words!
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(be_careful);

told_you = ConvoScreen:new {
	id = "told_you",
	leftDialog = "@conversation/heraldnaboo:s_7c64e921", -- I told you! I can't tell you anything else. Please... do you wish to hear information about the places I've mentioned? You may be able to find out more there.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_9575185c", "keep_silent"}, -- No, I must go.
		{"@conversation/heraldnaboo:s_c029271f", "know_about"}, -- Yes, give me the information.
	}
}
heraldNaboo1ConvoTemplate:addScreen(told_you);

keep_silent = ConvoScreen:new {
	id = "keep_silent",
	leftDialog = "@conversation/heraldnaboo:s_7cd8dc9", -- I wish you well. Keep silent about what we talked about.
	stopConversation = "true",
	options = {}
}
heraldNaboo1ConvoTemplate:addScreen(keep_silent);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@conversation/heraldnaboo:s_84b85cd6", -- About what would you like more information?
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo:s_7431a8fb", "loc1"}, -- The Imperial Weapons Research Facility.
		{"@conversation/heraldnaboo:s_b7659e9e", "loc2"}, -- Mauler Encampment
		{"@conversation/heraldnaboo:s_7ad7fe8f", "loc3"}, -- The Gungans and Imperials.
	}
}
heraldNaboo1ConvoTemplate:addScreen(more_info);

addConversationTemplate("heraldNaboo1ConvoTemplate", heraldNaboo1ConvoTemplate);
