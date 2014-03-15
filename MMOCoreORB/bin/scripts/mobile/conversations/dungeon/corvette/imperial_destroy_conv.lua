ImperialDestroyConversationTemplate = ConvoTemplate:new {
	initialScreen = "imperial_destroy_start",
	templateType = "Lua",
	luaClassHandler = "TicketGiverConversationHandler",
	screens = {}
}

imperial_destroy_start = ConvoScreen:new {
	id = "imperial_destroy_start",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_477d6952", --Just in time soldier! I have an urgent mission that requires your assistance.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_757e4a85", "imperial_destroy_1"}, -- Yes Sir, what are the details?
		{"@conversation/corvette_velso_imperial_destroy:s_823dca3f", "imperial_destroy_2"}, -- 	Sorry, too busy right now.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_start);


imperial_destroy_1 = ConvoScreen:new {
	id = "imperial_destroy_1",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_36c480be", -- A payload of weapons is being smuggled to a group of Rebels waiting to slaughter some outnumbered Imperial... er.. I mean to slaughter some innocent civilians. Yes. They're on a Corellian corvette, but it's marked as a medical transport so we don't want to attack it directly. I need you to find the destruction sequences for the corvette and blow it up from the inside. I have three leads on where the sequences could be located.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_1be45010", "imperial_destroy_3"}, -- Ok, let me type this down. What's the first lead?
		{"@conversation/corvette_velso_imperial_destroy:s_5aca4872", "imperial_destroy_4"}, -- 	Um... I think I'll come back later.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_1);


imperial_destroy_3 = ConvoScreen:new {
	id = "imperial_destroy_3",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_32084dfe", -- The city of Anchorhead is in southern Tatooine. Rebels are known to congregate in Anchorhead, so I feel there is a good chance the sequences we seek could be there. They might be in an abandoned building or in the back room of a cantina. I really have no idea. It is your job to uncover those sequences and return them to me.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_ed8d835e", "imperial_destroy_5"} -- What about the second possibility?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_3);


imperial_destroy_5 = ConvoScreen:new {
	id = "imperial_destroy_5",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_b68e2c66", -- The Rebels are rumored to have hidden among the Dantari on Dantooine. Specifically with a tribe called the Janta. We believe that when the Rebels evacuated the area, this ship was among those used. There may be information at the Janta Stronghold... retrieve it.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_b1606a2a", "imperial_destroy_6"} -- The third option?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_5);


imperial_destroy_6 = ConvoScreen:new {
	id = "imperial_destroy_6",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_e5e44e1d", -- The traitor Erran Sif is leading a small group of warriors on Talus. She betrayed the Empire in the past and is considered an enemy, so don't expect a friendly reception. I hear she's also no friend to the Rebel Alliance for whatever that's worth. Regardless, I believe she may have the codes for this corvette as she may have used it once herself. Infiltrate her base and report back with whatever you find.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_b99cf73b", "imperial_destroy_7"}, -- Okay, okay Sir. I'll do it.
		{"@conversation/corvette_velso_imperial_destroy:s_9495da35", "imperial_destroy_8"}, -- What were those locations again?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_6);


imperial_destroy_9 = ConvoScreen:new {
	id = "imperial_destroy_9",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_ce1a4a29", -- Speak soldier, what are you doing here?!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_9495da35", "imperial_destroy_8"}, -- What were those locations again?
		{"@conversation/corvette_velso_imperial_destroy:s_a1e2f8b6", "imperial_destroy_reset"}, -- I give up...sir. Please remove all progress I've made from your records.
		-- Other screens are inserted here, depending on what items they have in their inventory.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_9);

imperial_destroy_2 = ConvoScreen:new {
	id = "imperial_destroy_2",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_27825c70", -- What?! That wasn't a question! Fine, I can't let this mission be handled by someone like you anyway, get out of here!
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_2);

imperial_destroy_4 = ConvoScreen:new {
	id = "imperial_destroy_4",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_fc34951f", -- Later? You should take what you can get. Might not be a later.Guess that's when you'll be a good soldier too. Later. Or more likely never.
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_4);


imperial_destroy_7 = ConvoScreen:new {
	id = "imperial_destroy_7",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_160e282", -- Excellent, don't disappoint me soldier! Time is of the essence here. You can choose to return whenever you find something so that we can check the information as you find it. Or get them all at once, that's fine as well. Just make it quick. Dismissed!
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_7);


imperial_destroy_8 = ConvoScreen:new {
	id = "imperial_destroy_8",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_524ad772", -- Were you not listening soldier?! If I weren't desperate I would put you on kitchen duty for a month! Now which location do I have to repeat myself about?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_1be45010", "imperial_destroy_3"}, -- Ok, let me type this down. What's the first lead?
		{"@conversation/corvette_velso_imperial_destroy:s_ed8d835e", "imperial_destroy_5"}, -- What about the second possibility?
		{"@conversation/corvette_velso_imperial_destroy:s_b1606a2a", "imperial_destroy_6"} -- The third option?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_8);


imperial_destroy_neutral = ConvoScreen:new {
	id = "imperial_destroy_neutral",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_cc45dddf", -- I do not have time to chat, citizen. Please move along.
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_neutral);

imperial_destroy_reset = ConvoScreen:new {
	id = "imperial_destroy_reset",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_640dac0a", -- 	What?! You are a disgrace soldier! I will have your name sent to the inquisition for this! You will be relieved of all mission data and any documents you've gathered. You disgust me. Get out of my sight!
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_reset);

imperial_destroy_not_it_1 = ConvoScreen:new {
	id = "imperial_destroy_not_it_1",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_29a2b68d", -- Are you kidding me soldier? Can you even read? This is useless! But I'll keep it anyway, just in case...
	stopConversation = "true",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_e60ca0aa", "imperial_destroy_7"} -- Alright Sir, I'll get back to searching.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_not_it_1);

imperial_destroy_look = ConvoScreen:new {
	id = "imperial_destroy_look",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_65cd8f5e", -- Fine, let me have a look.
	stopConversation = "false",
	options = {
		-- Options added here.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_look);

imperial_destroy_not_it_2 = ConvoScreen:new {
	id = "imperial_destroy_not_it_2",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_988cb045", -- Who let you in to the Empire soldier?! This is rubbish! No, you can't have it back!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_e60ca0aa", "imperial_destroy_7"} -- Alright Sir, I'll get back to searching.
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_not_it_2);


imperial_destroy_found_it = ConvoScreen:new {
	id = "imperial_destroy_found_it",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_95397df3", -- It sure is soldier, good work! Now take this travel authorization to the Imperial pilot out by the shuttle, and he will arrange deep space transportation for you that will intercept that corvette. If you succeed in destroying that corvette and in escaping it, return to me for a reward.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_566ff600", "imperial_destroy_10"} -- Alright so I will be taken to the corvette to blow it up from the inside?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_found_it);

imperial_destroy_10 = ConvoScreen:new {
	id = "imperial_destroy_10",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_59e77066", -- I must find a way to impress my commanding officers. That'll be the quickest way to advance. Perhaps I can find a way to hamper Rebel efforts in this sector. That should be suitably impressive.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_d5fd52c1", "imperial_destroy_11"}, -- Alright so I will be taken to the corvette to blow it up from the inside?
		{"@conversation/corvette_velso_imperial_destroy:s_b99cf73b", "imperial_destroy_12"} -- Alright so I will be taken to the corvette to blow it up from the inside?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_10);

imperial_destroy_11 = ConvoScreen:new {
	id = "imperial_destroy_11",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_9e916cc9", -- Yes soldier, you are a lot brighter than you look! And after doing that and successfully escaping, return to me for a reward. Now hurry, hurry, hurry!
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_11);

imperial_destroy_12 = ConvoScreen:new {
	id = "imperial_destroy_12",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_d521e0c0", -- Tea?! Get out of here soldier, you're lucky I'm not incarcerating you! Wait... first give me 50, now!
	stopConversation = "true",
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_12);

imperial_destroy_13 = ConvoScreen:new {
	id = "imperial_destroy_13",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_105e0ec6", -- Why are you still here soldier?! Did you forget your weapon or are you just trying to upset me?!
	stopConversation = "false",	
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_af39813", "imperial_destroy_14"}, -- 	I'm sorry Sir, where do I take this ticket again?
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_13);


imperial_destroy_14 = ConvoScreen:new {
	id = "imperial_destroy_14",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_c159261e", -- You will be the death of me... take it to the pilot outside by the Lambda shuttle. If by some miracle you don't fail in this mission, return to me for a reward. Now go!
	stopConversation = "true",	
	options = {
	}
}

ImperialDestroyConversationTemplate:addScreen(imperial_destroy_14);

addConversationTemplate("ImperialDestroyConversationTemplate", ImperialDestroyConversationTemplate);
