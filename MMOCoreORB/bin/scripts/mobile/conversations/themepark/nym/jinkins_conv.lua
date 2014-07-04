jinkinsConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

----------
--Jinkins convos if quest completed
----------
good_work = ConvoScreen:new {
	id = "good_work",
	leftDialog = "@celebrity/jinkins:good_work", -- Securing that memory module proves that you have the makings of a true pirate. I'm sure you'll go far with the Lok Revenants. Now, is there something else I can do for you?
	stopConversation = "false",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(good_work);

talk_to_kole = ConvoScreen:new {
	id = "talk_to_kole",
	leftDialog = "@celebrity/jinkins:talk_to_kole", -- Kole is planning a new mission for you, based on the information I recovered from that memory module. You should talk to him to receive your next assignment.
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(talk_to_kole);

talk_to_nym = ConvoScreen:new {
	id = "talk_to_nym",
	leftDialog = "@celebrity/jinkins:talk_to_nym", -- You've already done my dirty work. But talk to Nym... I think he might need something from you.
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(talk_to_nym);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@celebrity/jinkins:good_bye", -- Alright, but I suggest you talk to Nym or Kole if you're still interested in our crew.
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(good_bye);

----------
--Jinkins convo if quest is in progress
----------
you_got_memory = ConvoScreen:new {
	id = "you_got_memory",
	leftDialog = "@celebrity/jinkins:you_got_memory", -- Did you retrieve it?  The memory module?
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:tell_me_again", "quest_info_again"}, -- Can you tell me again what you need?
		{"@celebrity/jinkins:yes", "hand_it_over"}, -- Yeah, I have it.
		{"@celebrity/jinkins:no", "get_back_to_work"}, -- Not yet.
	}
}
jinkinsConvoTemplate:addScreen(you_got_memory);

quest_info_again = ConvoScreen:new {
	id = "quest_info_again",
	leftDialog = "@celebrity/jinkins:quest_info_again", -- I need you - or someone more skilled - to retrieve a memory module from a droid that the Sulfur Lake Pirates have evidently captured. You may want to discuss the pirates' lair with one of their former members.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:sulfur_lake_pirates", "pirate_info"}, -- Who are the Sulfur Lake Pirates?
	}
}
jinkinsConvoTemplate:addScreen(quest_info_again);

get_back_to_work = ConvoScreen:new {
	id = "get_back_to_work",
	leftDialog = "@celebrity/jinkins:get_back_to_work", -- Really?  One of our operatives, a slicer who has infiltrated the Sulfur Pirate lair, is certain he saw you there. He also believes that you have already retrieved the module. But perhaps he was mistaken. Head to that cave and find the memory module for me.
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(get_back_to_work);

hand_it_over = ConvoScreen:new {
	id = "hand_it_over",
	leftDialog = "@celebrity/jinkins:hand_it_over", -- Excellent.  Now, if you'll just hand it to me...
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(hand_it_over);

----------
--This is the initial Jinkins convo
----------
first_time_hello = ConvoScreen:new {
	id = "first_time_hello",
	leftDialog = "@celebrity/jinkins:first_time_hello", -- Hmmm? You must be a new recruit. This crew changes faces faster than a Shi'odo spy. But I'm glad we have some fresh blood: The last "pirate" who wandered in here is still being digested by a kimogila somewhere past Rancid Ridge.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:who_are_you", "i_am_jinkins"}, -- Jinkins, eh?  What do you do?
		{"@celebrity/jinkins:tell_me_quest", "quest_info"}, -- Do you need me to do anything for you?
	}
}
jinkinsConvoTemplate:addScreen(first_time_hello);

i_am_jinkins = ConvoScreen:new {
	id = "i_am_jinkins",
	leftDialog = "@celebrity/jinkins:i_am_jinkins", -- I'm Jinkins, Nym's chief engineer. Nym asks for weapons, and I build them. I joined up with the Lok Revenants a few months before the Battle of Naboo, which makes me one of this crew's oldest members, along with Kole of course.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:who_is_kole", "kole_is_friend"}, -- Who is Kole?
		{"@celebrity/jinkins:who_is_nym", "nym_is_boss"}, -- Tell me about Nym.
		{"@celebrity/jinkins:tell_me_quest", "quest_info"}, -- Do you need me to do anything for you?
	}
}
jinkinsConvoTemplate:addScreen(i_am_jinkins);

kole_is_friend = ConvoScreen:new {
	id = "kole_is_friend",
	leftDialog = "@celebrity/jinkins:kole_is_friend", -- Kole is Nym's first mate. He's been with this crew longer than I have. In his younger days, he was a brilliant disguise artist and even worked for a few years as an assassin. Now, he mostly watches Nym's back.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:who_is_nym", "nym_is_boss"}, -- Tell me about Nym.
		{"@celebrity/jinkins:tell_me_quest", "quest_info"}, -- Do you need me to do anything for you?
	}
}
jinkinsConvoTemplate:addScreen(kole_is_friend);

nym_is_boss = ConvoScreen:new {
	id = "nym_is_boss",
	leftDialog = "@celebrity/jinkins:nym_is_boss", -- You must be joking... Nym is the most feared pirate in the Maramere system. He routed the Trade Federation from Lok and its neighboring planets right around the start of the Clone Wars, and he's maintained complete control over the spacelanes in this region ever since.  There's nobody with more power on Lok. And except for Jabba the Hutt, he's probably the most powerful alien in the Outer Rim. The Imperials on this planet couldn't even lift Nym's shadow... And he has no love for the Empire, if you catch my meaning...
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:who_is_kole", "kole_is_friend"}, -- Who is Kole?
		{"@celebrity/jinkins:tell_me_quest", "quest_info"}, -- Do you need me to do anything for you?
	}
}
jinkinsConvoTemplate:addScreen(nym_is_boss);

quest_info = ConvoScreen:new {
	id = "quest_info",
	leftDialog = "@celebrity/jinkins:quest_info", -- Actually, there is something I'd like you to look into, if you can.  I recently intercepted a distress call from a starship that crashed-landed on Lok. Ships nose-dive into the planet all the time, but this one took off from an Imperial mining installation on Lok and never made it into the atmosphere. I think it slammed down near the hideout of the Sulfur Lake Pirates. I'm very interested in this vessel...
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:distress_call", "crashed_ship"}, -- You intercepted a distress call?
	}
}
jinkinsConvoTemplate:addScreen(quest_info);

crashed_ship = ConvoScreen:new {
	id = "crashed_ship",
	leftDialog = "@celebrity/jinkins:crashed_ship", -- Yes. As part of my duties, I monitor comlink and transceiver activity around the system. We don't want a Star Destroyer sneaking up on us, do we? Anyway, this particular starship interests me because it was carrying Imperial cargo. A droid, in fact, that was once owned by General Otto at an Imperial base here on Lok.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:droid_memory", "imperial_info"}, -- What's so special about this droid?
	}
}
jinkinsConvoTemplate:addScreen(crashed_ship);

imperial_info = ConvoScreen:new {
	id = "imperial_info",
	leftDialog = "@celebrity/jinkins:imperial_info", -- Probably nothing. But, as an Imperial droid, it might be carrying some very interesting data.  Shipping schedules, guard rosters, prisoner transfer information, schematics for some terrifying super weapon... Anything the droid knows could be sold on the black market or traded back to Otto for a favor down the road. It might also tell us something about that Imperial mining facility, which we haven't been able to infiltrate. You'd be rewarded well if you could secure that droid's memory module.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:ill_get_memory", "heres_droid_memory"}, -- I'll recover the module. Where can I find this droid?
	}
}
jinkinsConvoTemplate:addScreen(imperial_info);

heres_droid_memory = ConvoScreen:new {
	id = "heres_droid_memory",
	leftDialog = "@celebrity/jinkins:heres_droid_memory", -- Excellent.  I'll provide you with a waypoint to the Sulfur Lake.  Our scouts learned that the Sulfur Lake Pirates have already taken the cargo - including the droid - from the crashed starship, so don't waste your time looking through the wreckage. Just head to the pirates' lair, locate the droid, and grab the memory module. Oh, and watch out for the pirates' "bridge troll." I'm not sure what that is, but it sounds dangerous...
	stopConversation = "true",
	options = {
		{"@celebrity/jinkins:sulfur_lake_pirates", "pirate_info"}, -- Who are the Sulfur Lake Pirates?
	}
}
jinkinsConvoTemplate:addScreen(heres_droid_memory);

pirate_info = ConvoScreen:new {
	id = "pirate_info",
	leftDialog = "@celebrity/jinkins:pirate_info", -- Probably the most bloodthirsty, least-intelligent pirates on Lok. Like all the other pirate bands, they are constantly trying to dethrone Nym as Lok's reigning pirate king. They hate Nym for taking control of all the nearby hyperspace routes and claim that he's working with the Imperials. The gravel maggots have been looking for an excuse to go to war with us for years... There's a hermit living near Nym's stronghold who once worked for the Sulfur Pirates. He might be able to tell you more.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:whos_the_guy", "deals_with_pirates"}, -- Who is this hermit?
	}
}
jinkinsConvoTemplate:addScreen(pirate_info);

deals_with_pirates = ConvoScreen:new {
	id = "deals_with_pirates",
	leftDialog = "@celebrity/jinkins:deals_with_pirates", -- I don't know much about him. We think he was some sort of droid designer for the Old Republic, but fled to Lok when the Empire took power. A few years ago, Nym used him to fence good on Coruscant. But before that, he was performing droid upgrades for the Sulfur Lake Pirates. He can probably tell you about their base.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:ill_see_the_guy", "heres_the_guy"}, -- Okay, I'll go talk to him.
	}
}
jinkinsConvoTemplate:addScreen(deals_with_pirates);

heres_the_guy = ConvoScreen:new {
	id = "heres_the_guy",
	leftDialog = "@celebrity/jinkins:heres_the_guy", -- Good. I'll mark his last known location in your datapad.  Be sure to ask him about the pirates, see what he knows.
	stopConversation = "false",
	options = {
		{"@celebrity/jinkins:anything_else", "you_know_all"}, -- Is there anything else you can tell me?
	}
}
jinkinsConvoTemplate:addScreen(heres_the_guy);

you_know_all = ConvoScreen:new {
	id = "you_know_all",
	leftDialog = "@celebrity/jinkins:you_know_all", -- Not really. You know everything I know.
	stopConversation = "true",
	options = {
	}
}
jinkinsConvoTemplate:addScreen(you_know_all);

addConversationTemplate("jinkinsConvoTemplate", jinkinsConvoTemplate);
