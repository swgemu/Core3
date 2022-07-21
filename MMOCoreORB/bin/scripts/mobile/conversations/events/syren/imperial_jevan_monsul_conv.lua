imperialJevanMonsulConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "imperialJevanMonsulConvoHandler",
	screens = {}
}

changed_faction_rebel = ConvoScreen:new {
	id = "changed_faction_rebel",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_219", -- I'm disappointed in you, traitor.  You turn your back on the Empire and then expect us to hand information over to you?  You are sadly mistaken.  Go talk to your own kind now.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(changed_faction_rebel);

changed_faction_neutral = ConvoScreen:new {
	id = "changed_faction_neutral",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_222", -- How is civilian life treating you?  Never mind, I don't want to know.  I also don't want to know why you are coming to me for classified information.  I have someone else handling this investigation now...military personnel.

	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(changed_faction_neutral);

different_faction_neutral = ConvoScreen:new {
	id = "different_faction_neutral",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_224", -- If I could use your help, I would, but my orders are for Imperial military only.

	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(different_faction_neutral);

different_faction_rebel = ConvoScreen:new {
	id = "different_faction_rebel",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_226", -- Go away, Rebel scum.

	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(different_faction_rebel);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_228", -- Greetings, soldier.  I have a situation that requires my attention and I cannot attend to it properly.  Would you be willing to help me out?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_230", "more_info"}, -- Perhaps, if I have more information.
		{"@conversation/c_story1_1_imp_quest:s_234", "accept"}, -- I will go investigate.
		{"@conversation/c_story1_1_imp_quest:s_238", "reject"} -- I'd rather not.  I have a lot to do right now.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(start);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_232", -- I have just gotten word that a pilot is missing. We have the coordinates of his last known location. It was on Rori. Would you be willing to run out there and see what happened?  He may be hurt or in danger.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_242", "accept_job"}, -- I will do anything I can to help the Empire.
		{"@conversation/c_story1_1_imp_quest:s_246", "reject_job"} -- No thank you.  You should attend to your own duties.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(more_info);

accept = ConvoScreen:new {
	id = "accept",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_236", -- Very good.  Go to these coordinates on Rori and see if you can find anything out. Then report back to me. Oh, if he had cargo, maybe you could find out what happened to it.  That would probably help him out a lot.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(accept);

reject = ConvoScreen:new {
	id = "reject",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_240", -- Hopefully your decision didn't doom that poor pilot.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(reject);

accept_job = ConvoScreen:new {
	id = "accept_job",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_244", -- Your loyalty encourages me.  I wish more people were like you.  Anyway, a pilot is missing and we don't know what happened. We have his last known coordinates on Rori. Investigate then bring me back any information you find, particularly information about his cargo. This is of great interest to the Empire.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(accept_job);

reject_job = ConvoScreen:new {
	id = "reject_job",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_248", -- I guess you just aren't that helpful after all.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(reject_job);

welcome_back_no_info = ConvoScreen:new {
	id = "welcome_back_no_info",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_250", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_276", "come_back_again"}, -- Not yet.
		{"@conversation/c_story1_1_imp_quest:s_280", "accept"} -- I lost the location. Can you give it to me again?
	}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_no_info);

welcome_back_found_crash_site = ConvoScreen:new {
	id = "welcome_back_found_crash_site",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_250", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_252", "crashed"}, -- The pilot's ship crashed.  I haven't found any trace of him though.
		{"@conversation/c_story1_1_imp_quest:s_280", "accept"} -- I lost the location. Can you give it to me again?
	}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_found_crash_site);

welcome_back_found_spice = ConvoScreen:new {
	id = "welcome_back_found_spice",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_250", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_256", "spice"} -- Yes, I found this datapad and this sample.  I think it's a spice.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_found_spice);

come_back_again = ConvoScreen:new {
	id = "come_back_again",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_278", -- Please get right on that.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(come_back_again);

crashed = ConvoScreen:new {
	id = "crashed",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_254", -- Crashed?  That's terrible!  Please go back there and search for some trace of him.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(crashed);

spice = ConvoScreen:new {
	id = "spice",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_258", -- A spice?  I have never seen anything like it.  Let's see what this datapad contains.  One moment for the decoder to do its job...there we go.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_260", "pilot"}, -- What does it say?
		{"@conversation/c_story1_1_imp_quest:s_304", "skip_doctor"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(spice);

pilot = ConvoScreen:new {
	id = "pilot",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_262", -- It looks like this sample was part of a larger shipment that the pilot was bringing somewhere.  The datapad is quite damaged. There's nothing about who shot the ship down, just that the ship was attacked.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_264", "pilot_next"}, -- So, now what do I do?
		{"@conversation/c_story1_1_imp_quest:s_304", "skip_doctor"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(pilot);

pilot_next = ConvoScreen:new {
	id = "pilot_next",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_266", -- I think that this spice sample is important somehow.  I have a loyal Imperial doctor that will analyze this sample if you take it to him.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_268", "doctor"}, -- I would be happy to.
		{"@conversation/c_story1_1_imp_quest:s_304", "skip_doctor"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(pilot_next);

doctor = ConvoScreen:new {
	id = "doctor",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_270", -- Good.  Here's the medical facility where he works.  You should find him inside.  I swear, I don't think he sleeps.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(doctor);

skip_doctor = ConvoScreen:new {
	id = "skip_doctor",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_306", -- If we do not find him, I'm holding you responsible.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(skip_doctor);

welcome_back_doctor = ConvoScreen:new {
	id = "welcome_back_doctor",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_284", -- Go talk to Doctor Vang.  There's not much else I can do to help you.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_doctor);

start_finish = ConvoScreen:new {
	id = "start_finish",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_286", -- Hello again, soldier.  It appears that my search bore fruit.  A lady named Kaila heard that I was looking for that lost pilot.  She said that she saw someone fitting his description in the wilderness.  Since you are already in the loop for this, I want you to go talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_288", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_imp_quest:s_300", "where_is_she"}, -- I don't need additional details.  I want to find out what's going on.
		{"@conversation/c_story1_1_imp_quest:s_304", "no_part"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(start_finish);

no_info = ConvoScreen:new {
	id = "no_info",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_290", -- No.  She is expecting a reward for valuable information.  The Empire will take care of that.  You will go talk to her, won't you?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_292", "where_is_she"}, -- Of course, sir.
		{"@conversation/c_story1_1_imp_quest:s_304", "no_part"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(no_info);

where_is_she = ConvoScreen:new {
	id = "where_is_she",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_302", -- Kaila apparently hangs out at some dive in Narmle.  Here's a waypoint.  It should be safe enough there.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(where_is_she);

no_part = ConvoScreen:new {
	id = "no_part",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_306", -- If we do not find him, I'm holding you responsible.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(no_part);

welcome_back_no_datapad = ConvoScreen:new {
	id = "welcome_back_no_datapad",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_301", -- Can I talk to you later?  I'm tracking down a tough bit of information.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_no_datapad);

finished = ConvoScreen:new {
	id = "finished",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_301", -- Can I talk to you later?  I'm tracking down a tough bit of information.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(finished);

welcome_back_with_spice_imperial = ConvoScreen:new {
	id = "welcome_back_with_spice_imperial",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_308", -- Welcome to the right side, soldier.  I'm glad to see that you support law and order.  Sources tell me that you found a spice sample and are looking for a missing pilot.  I have information for you.  A lady named Kaila saw the pilot out in the wilderness.  I want you to go talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_288", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_imp_quest:s_300", "where_is_she"}, -- I don't need additional details.  I want to find out what's going on.
		{"@conversation/c_story1_1_imp_quest:s_304", "no_part"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_with_spice_imperial);

welcome_back_with_spice_neutral = ConvoScreen:new {
	id = "welcome_back_with_spice_neutral",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_297", -- Welcome to the Alliance!  I hope you have been treated well so far.  Sources tell me that you found a spice sample and are looking for a missing pilot.  Someone named Kaila contacted me and told me that she had information on the missing pilot.  Evidently he's lost in the wilderness.  She has the coordinates if you go over and talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_288", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_imp_quest:s_300", "where_is_she"}, -- I don't need additional details.  I want to find out what's going on.
		{"@conversation/c_story1_1_imp_quest:s_304", "no_part"} -- No more of this for me.  I'm done.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(welcome_back_with_spice_neutral);

addConversationTemplate("imperialJevanMonsulConvoTemplate", imperialJevanMonsulConvoTemplate);
