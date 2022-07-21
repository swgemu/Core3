neutralTylaJinnConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "neutralTylaJinnConvoHandler",
	screens = {}
}

changed_faction_imperial = ConvoScreen:new {
	id = "changed_faction_imperial",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_374", -- Oh dear, you went and joined the military, didn't you?  You won't be able to help me now.  I was already almost arrested for pestering an Imperial officer.  I'll have to find someone else to help me.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(changed_faction_imperial);

changed_faction_rebel = ConvoScreen:new {
	id = "changed_faction_rebel",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_376", -- Much as I need help, I don't trust people in the Rebellion.  I keep hearing how you kill women and children.  Please leave me alone.

	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(changed_faction_rebel);

different_faction_rebel = ConvoScreen:new {
	id = "different_faction_rebel",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_380", -- I can't talk to you in case a member of the Imperial Security Bureau is watching.

	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(different_faction_rebel);

different_faction_imperial = ConvoScreen:new {
	id = "different_faction_imperial",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_378", -- Oh my, you are an Imperial, aren't you?  I guess you are too busy to help me.

	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(different_faction_imperial);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_382", -- Can you help me?  Please help me!  My friend's ship is missing and I haven't heard from him.  I'm really worried.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_384", "more_info"}, -- What can you tell me about it?
		{"@conversation/c_story1_1_neu_quest:s_388", "accept"}, -- I will help you find your friend.
		{"@conversation/c_story1_1_neu_quest:s_392", "reject"} -- I'd rather not.  I have a lot to do right now.
	}
}

neutralTylaJinnConvoTemplate:addScreen(start);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_386", -- He is a merchant and on one of this runs, he disappeared!  I can't imagine what happened!  He's a very good pilot. I don't think that Rori was one of his stops, but that's where his last coordinates say he was.  I'm very worried.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_396", "accept_job"}, -- I could always use a job.
		{"@conversation/c_story1_1_neu_quest:s_400", "reject_job"} -- No thank you.  You should go look for your own friend.
	}
}

neutralTylaJinnConvoTemplate:addScreen(more_info);

accept = ConvoScreen:new {
	id = "accept",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_390", -- Thank you!  I have the coordinates here.  Please bring me back any information you find. I'm so worried about him!
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(accept);

reject = ConvoScreen:new {
	id = "reject",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_394", -- You are very cruel not to help me find my friend.  I hope you get eaten by a sarlacc!
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(reject);

accept_job = ConvoScreen:new {
	id = "accept_job",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_398", -- This is quite a bit more than just a job.  My friend's life may be at stake!  His last coordinates were on Rori.  I'm really worried about him!  Let me transfer the coordinates to you.  If you can't actually find him, maybe you can find something of his that would give me a clue to where he may be.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(accept_job);

reject_job = ConvoScreen:new {
	id = "reject_job",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_402", -- I'm no kind of wilderness survivor!  You don't care about anything except yourself!  Go then and thanks for nothing!
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(reject_job);

welcome_back_no_info = ConvoScreen:new {
	id = "welcome_back_no_info",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_404", -- What did you find?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_430", "come_back_again"}, -- Nothing yet.
		{"@conversation/c_story1_1_neu_quest:s_434", "accept"} -- I lost the location. Can you give it to me again?
	}
}

neutralTylaJinnConvoTemplate:addScreen(welcome_back_no_info);

welcome_back_found_crash_site = ConvoScreen:new {
	id = "welcome_back_found_crash_site",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_404", -- What did you find?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_406", "crashed"}, -- The pilot's ship crashed.  I haven't found any trace of him though.
		{"@conversation/c_story1_1_neu_quest:s_434", "accept"} -- I lost the location. Can you give it to me again?
	}
}

neutralTylaJinnConvoTemplate:addScreen(welcome_back_found_crash_site);

welcome_back_found_spice = ConvoScreen:new {
	id = "welcome_back_found_spice",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_404", -- What did you find?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_410", "spice"} -- I found this datapad and this sample.  I think it's a spice.
	}
}

neutralTylaJinnConvoTemplate:addScreen(welcome_back_found_spice);

come_back_again = ConvoScreen:new {
	id = "come_back_again",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_432", -- I hope he's all right.  Please go out there soon.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(come_back_again);

crashed = ConvoScreen:new {
	id = "crashed",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_408", -- Crashed?  That's terrible!  Please go back there and search for some trace of him!
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(crashed);

spice = ConvoScreen:new {
	id = "spice",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_412", -- A spice?  What would he be doing with spice?  He doesn't touch the stuff.  Let me see this datapad, I have his personal code. Oh no!
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_414", "pilot"}, -- What does it say?
		{"@conversation/c_story1_1_neu_quest:s_418", "pilot_next"}, -- Maybe the spice will lead us to where he is.
		{"@conversation/c_story1_1_neu_quest:s_458", "skip_doctor"} -- I didn't sign on for this. I'm done.
	}
}

neutralTylaJinnConvoTemplate:addScreen(spice);

pilot = ConvoScreen:new {
	id = "pilot",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_416", -- He was attacked!  He doesn't say by who or what, but his ship was brought down.  There's no information here that helps me at all!  Just something about this sample and how it's important.  I don't care about that, I just want to find my friend!
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_418", "pilot_next"}, -- Maybe the spice will lead us to where he is.
	}
}

neutralTylaJinnConvoTemplate:addScreen(pilot);

pilot_next = ConvoScreen:new {
	id = "pilot_next",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_420", -- Do you think so?  My cousin is a doctor and could probably analyze that. Would you take it to him and see if he can help?

	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_422", "doctor"}, -- I would be happy to.
		{"@conversation/c_story1_1_neu_quest:s_426", "skip_doctor"} -- No, he's your cousin. You should go talk to him.
	}
}

neutralTylaJinnConvoTemplate:addScreen(pilot_next);

doctor = ConvoScreen:new {
	id = "doctor",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_424", -- Thank you again.  Here are the coordinates to his clinic.  I hope it helps.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(doctor);

skip_doctor = ConvoScreen:new {
	id = "skip_doctor",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_428", -- I can't, actually. We're not on good terms. If you change your mind about helping me, please come back.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(skip_doctor);

welcome_back_doctor = ConvoScreen:new {
	id = "welcome_back_doctor",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_438", -- Go talk to Doctor Vang.  There's not much else I can do to help you.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(welcome_back_doctor);

start_finish = ConvoScreen:new {
	id = "start_finish",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_440", -- I finally have information for you! Someone named Kaila contacted me and told me that she had information about my lost friend! He's lost in the wilderness.  You have to help me!  She won't give me the coordinates, but maybe she will give them to you.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_442", "no_info"}, -- Why wouldn't she give you the coordinates?
		{"@conversation/c_story1_1_neu_quest:s_446", "where_is_she"}, -- It's ok.  I'll help you.  Just tell me where I can find her.
		{"@conversation/c_story1_1_neu_quest:s_458", "no_part"} -- I didn't sign on for this. I'm done.
	}
}

neutralTylaJinnConvoTemplate:addScreen(start_finish);

no_info = ConvoScreen:new {
	id = "no_info",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_444", -- Hhmph, she says that I won't survive in the wilderness, and she's right there.  But she said that I'm foolish enough to go out there on my own.  She says that she doesn't want to get me killed!  I'd only do that if I couldn't find someone to help me!
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_446", "where_is_she"}, -- It's ok.  I'll help you.  Just tell me where I can find her.
		{"@conversation/c_story1_1_neu_quest:s_450", "no_part"} -- She's right.  You will get yourself killed.  You will probably get me killed in the process.
	}
}

neutralTylaJinnConvoTemplate:addScreen(no_info);

where_is_she = ConvoScreen:new {
	id = "where_is_she",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_448", -- Kaila's a regular at some dive in Narmle.  I'll give you a waypoint.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(where_is_she);

no_part = ConvoScreen:new {
	id = "no_part",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_452", -- You... you jerk!  You don't care about anyone or anything but yourself.  When you change your mind about helping me, maybe I'll talk to you.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(no_part);

welcome_back_no_datapad = ConvoScreen:new {
	id = "welcome_back_no_datapad",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_466", -- I don't know what is going on, exactly, but I'm going to try to have more inforamtion for you as soon as I can.  It's not looking good so far.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(welcome_back_no_datapad);

finished = ConvoScreen:new {
	id = "finished",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_466", -- I don't know what is going on, exactly, but I'm going to try to have more inforamtion for you as soon as I can.  It's not looking good so far.
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(finished);

addConversationTemplate("neutralTylaJinnConvoTemplate", neutralTylaJinnConvoTemplate);
