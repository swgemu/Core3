commanderDkrnConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchCommanderDkrnConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_imperial_herald:s_527f9e64", -- Ah, a fellow member of the glorious Empire! You came just in time. We need one of our trusted soldiers to fetch something for us. It is a chance, not only to fulfill a difficult mission and receive praise from the Empire, but to gather information regarding the Death Watch and their point of operations. Are you interested?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_e62fc90c", "excellent_find_hideout"}, -- Yes, sir! Right away!
		{"@conversation/death_watch_imperial_herald:s_ecc5dd3c", "group_of_killers"}, -- Wait. Who are these Death Watch operatives?
		{"@conversation/death_watch_imperial_herald:s_8107be6d", "you_are_dismissed"}, -- No, it sounds dangerous.
	}
}
commanderDkrnConvoTemplate:addScreen(intro);

quest_already_completed = ConvoScreen:new {
	id = "quest_already_completed",
	leftDialog = "@conversation/death_watch_imperial_herald:s_68732e54", -- Soldier. How may I help you? You are well viewed in the eyes of the Empire for your help earlier.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_5bc39fc9", "death_watch_location"}, -- I need to find the hideout again.
	}
}
commanderDkrnConvoTemplate:addScreen(quest_already_completed);

death_watch_location = ConvoScreen:new {
	id = "death_watch_location",
	leftDialog = "@conversation/death_watch_imperial_herald:s_16f71658", -- The Death Watch hideout can be found on Endor in the northwestern part of the planet. Be cautious and bring your friends with you. I hear they do not take prisoners and enjoying killing intruders.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(death_watch_location);

group_of_killers = ConvoScreen:new {
	id = "group_of_killers",
	leftDialog = "@conversation/death_watch_imperial_herald:s_1b104a9f", -- A well-trained group of killers and thieves. If I were you, I'd be careful. It would be smart to bring along a few of your friends, but it's up to you.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_6decea2a", "excellent_find_hideout"}, -- Okay. I will help.
		{"@conversation/death_watch_imperial_herald:s_6405e2a0", "we_will_wait"}, -- Sounds too dangerous for me.
	}
}
commanderDkrnConvoTemplate:addScreen(group_of_killers);

excellent_find_hideout = ConvoScreen:new {
	id = "excellent_find_hideout",
	leftDialog = "@conversation/death_watch_imperial_herald:s_126d6e08", -- Excellent, soldier! You'll need to find the Death Watch hideout on Endor. It can be located in the northwestern part of the planet. We need for you to find their leader and bring a sample of his blood back to us. You will be well rewarded.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_b6b25f13", "good_now_go"}, -- Yes, sir!
		{"@conversation/death_watch_imperial_herald:s_43908466", "shouldnt_ask_questions"}, -- Uh. Why do you want blood?
		{"@conversation/death_watch_imperial_herald:s_6405e2a0", "we_will_wait"}, -- Sounds too dangerous for me.
	}
}
commanderDkrnConvoTemplate:addScreen(excellent_find_hideout);

shouldnt_ask_questions = ConvoScreen:new {
	id = "shouldnt_ask_questions",
	leftDialog = "@conversation/death_watch_imperial_herald:s_622c3f31", -- A soldier shouldn't ask his commanding officer questions! But if you must know... The Empire seems to think that leader of the Death Watch would make a good candidate for a Prime Clone for a new batch of stormtroopers. However, we'll need for you to kill this so-called leader. There's no sense in keeping him around. We've learned our lesson from the past. Well. Will you accept your mission?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_210b4c5b", "good_now_go"}, -- Yes, I will!
		{"@conversation/death_watch_imperial_herald:s_f61ed984", "you_are_disgrace"}, -- No, that's just... wrong!
		{"@conversation/death_watch_imperial_herald:s_6405e2a0", "we_will_wait"}, -- Sounds too dangerous for me.
	}
}
commanderDkrnConvoTemplate:addScreen(shouldnt_ask_questions);

you_are_disgrace = ConvoScreen:new {
	id = "you_are_disgrace",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2979d13", -- Morals?! Get out of here! You are a disgrace to the Empire.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(you_are_disgrace);


good_now_go = ConvoScreen:new {
	id = "good_now_go",
	leftDialog = "@conversation/death_watch_imperial_herald:s_e478107c", -- Good! Now go to the Death Watch hideout and slay this so-called leader. Don't forget to bring back a sample of his blood for us. We'll need it for future... experimentations.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(good_now_go);

we_will_wait = ConvoScreen:new {
	id = "we_will_wait",
	leftDialog = "@conversation/death_watch_imperial_herald:s_71f459c7", -- I see. Well, then. We will wait for another promising subject to accept the mission. You are dismissed.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(we_will_wait);

you_are_dismissed = ConvoScreen:new {
	id = "you_are_dismissed",
	leftDialog = "@conversation/death_watch_imperial_herald:s_406804c7", -- You are dismissed.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(you_are_dismissed);

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	leftDialog = "@conversation/death_watch_imperial_herald:s_d441c51a", -- I do not acknowledge those that do not belong to the Empire. Be gone.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(wrong_faction);

busy_cant_talk = ConvoScreen:new {
	id = "busy_cant_talk",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2e8ff1b4", -- I am incredibly busy right now. The Empire demands that I concentrate fully on my assignment. Come back a little later and talk with me. I may have a task for you to do.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(busy_cant_talk);

return_intro = ConvoScreen:new {
	id = "return_intro",
	leftDialog = "@conversation/death_watch_imperial_herald:s_1a897bb0", -- You have returned! Did you complete your mission?
	stopConversation = "false",
	options = {
		-- Handled by convo handler
		--{"@conversation/death_watch_imperial_herald:s_4f1e472e", "excellent_reward"}, -- I have your blood sample right here.
		--{"@conversation/death_watch_imperial_herald:s_dc839e59", "very_well_be_quick"}, -- No, I'm still looking into it.
		--{"@conversation/death_watch_imperial_herald:s_55aa1278", "more_info"}, -- I need more information regarding my mission.
		--{"@conversation/death_watch_imperial_herald:s_f70821a3", "sorry_to_hear"}, -- I quit!
	}
}
commanderDkrnConvoTemplate:addScreen(return_intro);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@conversation/death_watch_imperial_herald:s_4e028860", -- The Death Watch Hideout is located on Endor and can be found in the northwestern part of the planet. You'll need to find the leader and destroy him. Be sure to bring back a blood sample. That is all.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(more_info);

excellent_reward = ConvoScreen:new {
	id = "excellent_reward",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2c258e47", -- Excellent! You have done great work for the Empire. I can only give you very little. You have my gratitude.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(excellent_reward);

very_well_be_quick = ConvoScreen:new {
	id = "very_well_be_quick",
	leftDialog = "@conversation/death_watch_imperial_herald:s_382404f", -- Very well. Be quick about it and return to us with good news!
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(very_well_be_quick);

sorry_to_hear = ConvoScreen:new {
	id = "sorry_to_hear",
	leftDialog = "@conversation/death_watch_imperial_herald:s_79b531ae", -- I am sorry to hear this. We were so close to our goal. Very well, then. You are dismissed.
	stopConversation = "true",
	options = {
	}
}
commanderDkrnConvoTemplate:addScreen(sorry_to_hear);

addConversationTemplate("commanderDkrnConvoTemplate", commanderDkrnConvoTemplate);
