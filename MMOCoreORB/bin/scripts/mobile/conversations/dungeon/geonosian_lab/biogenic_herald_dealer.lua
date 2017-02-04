biogenicHeraldDealerConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "BiogenicHeraldDealerConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/biogenic_herald_dealer:s_ca3bfa0f", -- Eh... you don't look much like a miner, but then again we've been getting several strange folk comin' through this outpost of late. Several strange things goin' on 'round here too. Some funny times these days if you ask me.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_321d898b", "used_to_be_quiet"}, -- What do you mean by strange folk?
		{"@conversation/biogenic_herald_dealer:s_14b834bb", "struck_me"}, -- What kind of strange things have been going on?
		{"@conversation/biogenic_herald_dealer:s_490e56dd", "so_long"}, -- You don't say? Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(intro);

so_long = ConvoScreen:new {
	id = "so_long",
	leftDialog = "@conversation/biogenic_herald_dealer:s_188c477d", -- So long, stranger.
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(so_long);

used_to_be_quiet = ConvoScreen:new {
	id = "used_to_be_quiet",
	leftDialog = "@conversation/biogenic_herald_dealer:s_bbf0856c", -- Ever since all that debris came raining down we've had all sorts through here. Thugs, gangsters, adventurers, Imperials, and probably some from that rebellion, too. We used to be just a quiet mining outpost.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_b1be0157", "lots_of_questions"}, -- Do you not usually have that sort of people around here?
		{"@conversation/biogenic_herald_dealer:s_e13e9abc", "struck_me"}, -- Tell me about the strange things that have been going on.
		{"@conversation/biogenic_herald_dealer:s_d78255c2", "so_long"}, -- That's very interesting. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(used_to_be_quiet);

lots_of_questions = ConvoScreen:new {
	id = "lots_of_questions",
	leftDialog = "@conversation/biogenic_herald_dealer:s_3dc0cd9d", -- Being a mining outpost, we've always had a couple of seedy characters hanging around, but usually looking for work or somethin'. Now they're just all over the place. Asking lots of questions sometimes, too.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_aa4a4ec4", "several_people"}, -- Who has been asking questions?
		{"@conversation/biogenic_herald_dealer:s_f51b07ff", "sometimes_they_ask"}, -- What kind of questions?
		{"@conversation/biogenic_herald_dealer:s_1f5ef4a0", "dunno_probably"}, -- Am I a seedy character?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(lots_of_questions);

several_people = ConvoScreen:new {
	id = "several_people",
	leftDialog = "@conversation/biogenic_herald_dealer:s_ac44ebc8", -- Several people. Some folk coming in from Tatooine on the shuttle. Some Imperial types. I know they're Imperial because they wear those flashy uniforms.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_7828a8aa", "sometimes_they_ask"}, -- What kind of questions are they asking?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(several_people);

sometimes_they_ask = ConvoScreen:new {
	id = "sometimes_they_ask",
	leftDialog = "@conversation/biogenic_herald_dealer:s_827f01ce", -- Sometimes they ask about all that debris. Sometimes they ask questions about mining. I do remember some of those Imperials asking us if we'd seen anything unusual.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_c0036582", "told_em_no"}, -- What did you tell them?
		{"@conversation/biogenic_herald_dealer:s_674fdb0a", "at_the_time"}, -- Had you seen anything unusual?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(sometimes_they_ask);

told_em_no = ConvoScreen:new {
	id = "told_em_no",
	leftDialog = "@conversation/biogenic_herald_dealer:s_12f0f46", -- I told 'em no. Hardly anythin' unusual ever happened around here. But if I had seen then what I've seen now, I would have changed my answer.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_6ecc5ef7", "had_an_earthquake"}, -- What was it that you saw?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(told_em_no);

had_an_earthquake = ConvoScreen:new {
	id = "had_an_earthquake",
	leftDialog = "@conversation/biogenic_herald_dealer:s_5b67bd", -- Well, not long ago we had an earthquake or somthin' nearby. Some thought it was an explosion, but either way, stuff like that is important to a miner. So I went over to check it out... see if there was any damage to any equipment...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_8d32acbf", "darn_right"}, -- Did you find anything?
		{"@conversation/biogenic_herald_dealer:s_53fdb2c3", "oh_well"}, -- Sorry, this story is boring. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(had_an_earthquake);

darn_right = ConvoScreen:new {
	id = "darn_right",
	leftDialog = "@conversation/biogenic_herald_dealer:s_86db3ca8", -- Darn right I did. Turns out the quake was centered near a small mountain. We never did start any mining there as there was nothin' worth digging up. But I checked out the mountain anyway. And that's when the weird thing happened...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_e00ac98e", "saw_a_cave"}, -- What happened?
		{"@conversation/biogenic_herald_dealer:s_53fdb2c3", "oh_well"}, -- Sorry, this story is boring. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(darn_right);

oh_well = ConvoScreen:new {
	id = "oh_well",
	leftDialog = "@conversation/biogenic_herald_dealer:s_2608508b", -- Oh... well, sorry. Good-bye.
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(oh_well);

saw_a_cave = ConvoScreen:new {
	id = "saw_a_cave",
	leftDialog = "@conversation/biogenic_herald_dealer:s_83b0842f", -- Well, I saw a cave in the mountain. But not a natural cave, someone put that cave there on purpose. The weird thing, though, is that I didn't see the cave there when I looked the first time. Then when I turned away and looked back, it was gone again.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_894992c6", "been_there"}, -- I think that I've been to this place that you're talking about.
		{"@conversation/biogenic_herald_dealer:s_72308e43", "came_straight_back"}, -- Wow. What did you do?
		{"@conversation/biogenic_herald_dealer:s_9c48be16", "dont_believe"}, -- You're obviously crazy.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(saw_a_cave);

been_there = ConvoScreen:new {
	id = "been_there",
	leftDialog = "@conversation/biogenic_herald_dealer:s_46aee9", -- You've been there? Did you find that mountain? Did you see the cave? I'm not crazy am I?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_520ae1e7", "knew_it"}, -- You're right, there was a cave there.
		{"@conversation/biogenic_herald_dealer:s_93f3969d", "not_crazy"}, -- I'm sorry, I didn't see anything.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(been_there);

came_straight_back = ConvoScreen:new {
	id = "came_straight_back",
	leftDialog = "@conversation/biogenic_herald_dealer:s_1945c2e", -- Came straight back here obviously. I know better than to stick my head into odd caves that may or may not exist. Trouble is... no one here believes me. They all think it was just my eyes playin' tricks.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_894992c6", "been_there"}, -- I think that I've been to this place that you're talking about.
		{"@conversation/biogenic_herald_dealer:s_113ae28f", "here_is_loc"}, -- I'd like to go take a look at this mountain.
		{"@conversation/biogenic_herald_dealer:s_1fc825af", "dont_believe"}, -- Those people are right. You're nuts.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(came_straight_back);

here_is_loc = ConvoScreen:new {
	id = "here_is_loc",
	leftDialog = "@conversation/biogenic_herald_dealer:s_b9c59c4a", -- Sure, here is the location of the mountain. You go check it out yourself, then everyone will know that I'm not seein' things. If do find it, bring back any relics or junk you might come across. I'll buy it from you for proof!
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(here_is_loc);

dont_believe = ConvoScreen:new {
	id = "dont_believe",
	leftDialog = "@conversation/biogenic_herald_dealer:s_ec4e1fe", -- Well if you don't believe me, why don't you go check it out yourself. Here, I'll give you the location of the cave. Go see it with your own eyes. If do find it, bring back any relics or junk you might come across. I'll buy it from you for proof!
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(dont_believe);

at_the_time = ConvoScreen:new {
	id = "at_the_time",
	leftDialog = "@conversation/biogenic_herald_dealer:s_a70cda4", -- At the time, no I hadn't. Hardly anythin' unusual ever happened around here. But if I had seen then what I had seen now, I would definately had told 'em.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_6ecc5ef7", "had_an_earthquake"}, -- What was it that you saw?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(at_the_time);

dunno_probably = ConvoScreen:new {
	id = "dunno_probably",
	leftDialog = "@conversation/biogenic_herald_dealer:s_e998f1ae", -- I dunno. Probably.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_aa4a4ec4", "several_people"}, -- Who has been asking questions?
		{"@conversation/biogenic_herald_dealer:s_85f5abed", "sometimes_they_ask"}, -- What kind of questions have people been asking?
		{"@conversation/biogenic_herald_dealer:s_e4e38e80", "so_long"}, -- Sorry, I've got to go. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(dunno_probably);

struck_me = ConvoScreen:new {
	id = "struck_me",
	leftDialog = "@conversation/biogenic_herald_dealer:s_2688b2a3", -- Well, I'll tell you something that struck me as curious. No one else around here really believes me though. They think I'm crazy...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_61f5ac3", "had_an_earthquake"}, -- OK, tell me please.
		{"@conversation/biogenic_herald_dealer:s_253d6dd2", "used_to_be_quiet"}, -- Why don't you tell me about those strange folk?
		{"@conversation/biogenic_herald_dealer:s_4399b8ac", "good_bye"}, -- Frankly, I don't think much better of you. Good-bye.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(struck_me);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@conversation/biogenic_herald_dealer:s_5c031163", -- Well I don't think much of you, either. Good-bye.
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(good_bye);

intro_back = ConvoScreen:new {
	id = "intro_back",
	leftDialog = "@conversation/biogenic_herald_dealer:s_ec7227cf", -- Did you find that mountain? Did you see the cave? I'm not crazy am I?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_dealer:s_520ae1e7", "knew_it"}, -- You're right, there was a cave there.
		{"@conversation/biogenic_herald_dealer:s_93f3969d", "not_crazy"}, -- I'm sorry, I didn't see anything.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(intro_back);

not_crazy = ConvoScreen:new {
	id = "not_crazy",
	leftDialog = "@conversation/biogenic_herald_dealer:s_f2d5ae08", -- No! It can't be. I know that I'm not crazy!
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(not_crazy);

knew_it = ConvoScreen:new {
	id = "knew_it",
	leftDialog = "@conversation/biogenic_herald_dealer:s_8a046130", -- I knew it! Wait 'til I tell everyone. Now they'll know I'm not crazy! Did you find any relics that I might be able to buy from you?
	stopConversation = "false",
	options = {
		--{"@conversation/biogenic_herald_dealer:s_52beeae8", "what_you_have"}, -- Yes, I have a few things you might be interested in.
		--{"@conversation/biogenic_herald_dealer:s_2b7c5c5a", "thanks_for_checking"}, -- No, I don't have anything, sorry.
	}
}
biogenicHeraldDealerConvoTemplate:addScreen(knew_it);

what_you_have = ConvoScreen:new {
	id = "what_you_have",
	leftDialog = "@conversation/biogenic_herald_dealer:s_551304d2", -- Alright, let's see what you have.
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(what_you_have);

thanks_for_checking = ConvoScreen:new {
	id = "thanks_for_checking",
	leftDialog = "@conversation/biogenic_herald_dealer:s_ce4b0ac8", -- Well, that's OK. At least I have your word to back me up. Thanks for checking it out for me.
	stopConversation = "true",
	options = {}
}
biogenicHeraldDealerConvoTemplate:addScreen(thanks_for_checking);

addConversationTemplate("biogenicHeraldDealerConvoTemplate", biogenicHeraldDealerConvoTemplate);
