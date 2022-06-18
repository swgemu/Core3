rebelVeegaMadishConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "rebelVeegaMadishConvoHandler",
	screens = {}
}

changed_faction_imperial = ConvoScreen:new {
	id = "changed_faction_imperial",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_153", -- Don't bother trying to get information out of me, worm!  You betrayed your conscience at what price?  Is your cushy new position worth the damage you cause?  Never mind!  Get out of my sight!
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(changed_faction_imperial);

changed_faction_neutral = ConvoScreen:new {
	id = "changed_faction_neutral",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_155", -- I won't help you any more.  Someone who didn't weaken our position by quitting will be helping us locate the lost pilot.  If you still care enough to find the pilot, I'm sure other people are looking for him.

	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(changed_faction_neutral);

different_faction_neutral = ConvoScreen:new {
	id = "different_faction_neutral",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_157", -- You look eager enough, but I really need to speak with someone in the Alliance.

	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(different_faction_neutral);

different_faction_imperial = ConvoScreen:new {
	id = "different_faction_imperial",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_159", -- I beg your pardon.  Please leave me alone, you Imperial drone.

	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(different_faction_imperial);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_161", -- I need your help!  I have a situation that requires my attention and I cannot attend to it properly.  Would you be willing to help me out?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_163", "more_info"}, -- Perhaps, if I have more information.
		{"@conversation/c_story1_1_reb_quest:s_167", "accept"}, -- I will go investigate.
		{"@conversation/c_story1_1_reb_quest:s_171", "reject"} -- I'd rather not.  I have a lot to do right now.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(start);

more_info = ConvoScreen:new {
	id = "more_info",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_165", -- I have just gotten word that a pilot is missing. We have the coordinates of his last known location. It was on Rori. Would you be willing to run out there and see what happened?  He may be hurt or in danger.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_185", "accept_job"}, -- I could always use a job.
		{"@conversation/c_story1_1_reb_quest:s_189", "reject_job"} -- No thank you.  You should attend to your own duties.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(more_info);

accept = ConvoScreen:new {
	id = "accept",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_169", -- Very good.  Go to these coordinates on Rori and see if you can find anything out. Then report back to me. Oh, if he had cargo, maybe you could find out what happened to it.  That would probably help him out a lot.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(accept);

reject = ConvoScreen:new {
	id = "reject",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_183", -- Hopefully your decision didn't doom that poor pilot.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(reject);

accept_job = ConvoScreen:new {
	id = "accept_job",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_187", -- I will be happy to pay you for your time.  A ship has gone missing and the pilot has not been heard from.  We have his last coordinates. They are on Rori. We don't know if he's hurt or dead.  Go investigate and bring me back any information you find.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(accept_job);

reject_job = ConvoScreen:new {
	id = "reject_job",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_191", -- I guess you just aren't that helpful after all.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(reject_job);

welcome_back_no_info = ConvoScreen:new {
	id = "welcome_back_no_info",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_193", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_229", "come_back_again"}, -- I haven't found anything yet.
		{"@conversation/c_story1_1_reb_quest:s_237", "accept"} -- I need the location again.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_no_info);

welcome_back_found_crash_site = ConvoScreen:new {
	id = "welcome_back_found_crash_site",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_193", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_195", "crashed"}, -- The pilot's ship crashed.  I haven't found any trace of him though.
		{"@conversation/c_story1_1_reb_quest:s_237", "accept"} -- I need the location again.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_found_crash_site);

welcome_back_found_spice = ConvoScreen:new {
	id = "welcome_back_found_spice",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_193", -- Welcome back.  Did you find anything interesting?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_199", "spice"} -- Yes, I found this datapad and this sample.  I think it's a spice.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_found_spice);

come_back_again = ConvoScreen:new {
	id = "come_back_again",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_233", -- That's a shame.  Come back to me when you find something.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(come_back_again);

crashed = ConvoScreen:new {
	id = "crashed",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_233", -- Crashed?  That's terrible!  Please go back there and search for some trace of him.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(crashed);

spice = ConvoScreen:new {
	id = "spice",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_201", -- A spice?  Oh really?  Interesting.  Umm... I think you should get that analyzed. I know a doctor who will analyze that for you.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_203", "pilot"}, -- What about the pilot?
		{"@conversation/c_story1_1_reb_quest:s_216", "doctor"}, -- Well, if you look for the pilot, I'll follow up on the spice.
		{"@conversation/c_story1_1_reb_quest:s_221", "skip_doctor"} -- No, I did what you asked me to.  I'm leaving now.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(spice);

pilot = ConvoScreen:new {
	id = "pilot",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_205", -- Oh, I'll get this datapad sliced and follow up on that.  I think this spice is more important.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_207", "pilot_next"}, -- More important than a missing pilot?
		{"@conversation/c_story1_1_reb_quest:s_216", "doctor"}, -- Well, if you look for the pilot, I'll follow up on the spice.
		{"@conversation/c_story1_1_reb_quest:s_221", "skip_doctor"} -- No, I did what you asked me to.  I'm leaving now.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(pilot);

pilot_next = ConvoScreen:new {
	id = "pilot_next",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_209", -- Um, no, that's not what I mean.  I mean, I think you should follow up on that spice and let me worry about the pilot.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_211", "suspicious"}, -- This is getting suspicious, but I will do as you ask.
		{"@conversation/c_story1_1_reb_quest:s_216", "doctor"}, -- Well, if you look for the pilot, I'll follow up on the spice.
		{"@conversation/c_story1_1_reb_quest:s_221", "skip_doctor"} -- No, I did what you asked me to.  I'm leaving now.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(pilot_next);

suspicious = ConvoScreen:new {
	id = "suspicious",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_213", -- I'm sorry, I don't mean to put you on guard.  I just don't like knowing that there's some unknown spice out there when some child could get their hands on it.  Here's the doctor's clinic.  I'm sure he will be there.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_216", "doctor"}, -- Well, if you look for the pilot, I'll follow up on the spice.
		{"@conversation/c_story1_1_reb_quest:s_221", "skip_doctor"} -- No, I did what you asked me to.  I'm leaving now.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(suspicious);

doctor = ConvoScreen:new {
	id = "doctor",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_218", -- Of course I will!  Here are coordinates to my friend's medical practice.  He is there almost all the time.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(doctor);

skip_doctor = ConvoScreen:new {
	id = "skip_doctor",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_225", -- . . .
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(skip_doctor);

welcome_back_doctor = ConvoScreen:new {
	id = "welcome_back_doctor",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_245", -- Go talk to Doctor Vang.  There's not much else I can do to help you.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_doctor);

start_finish = ConvoScreen:new {
	id = "start_finish",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_249", -- I finally have information for you! Someone named Kaila contacted me and told me that she had information on the missing pilot.  Evidently he's lost in the wilderness.  She has the coordinates if you go over and talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_253", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_reb_quest:s_277", "where_is_she"}, -- I want to find out what's going on.  Where is she?
		{"@conversation/c_story1_1_reb_quest:s_285", "no_part"} -- No more of this for me.  I'm done.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(start_finish);

no_info = ConvoScreen:new {
	id = "no_info",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_257", -- Well, she didn't contact me directly and doesn't want to be seen talking to me.  I'm a wanted man, you understand.  One of those 'rebel terrorists' and all that rot.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_261", "where_is_she"}, -- As am I, my friend.  But I'm interested in finding out what this is about.  Where is she?
		{"@conversation/c_story1_1_reb_quest:s_269", "no_part"} -- You aren't the only one that the Empire is hunting.  I want no part of it.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(no_info);

kaila_waypoint = ConvoScreen:new {
	id = "kaila_waypoint",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_265", -- She's a regular at Narmle's Gambling Hall.  I'll give you a waypoint.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(kaila_waypoint);

no_part = ConvoScreen:new {
	id = "no_part",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_273", -- If you wish.  I won't condemn you, though others will.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(no_part);

welcome_back_no_datapad = ConvoScreen:new {
	id = "welcome_back_no_datapad",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_301", -- Can I talk to you later?  I'm tracking down a tough bit of information.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_no_datapad);

finish_act1 = ConvoScreen:new {
	id = "finish_act1",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_301", -- Can I talk to you later?  I'm tracking down a tough bit of information.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(finish_act1);

welcome_back_with_spice_imperial = ConvoScreen:new {
	id = "welcome_back_with_spice_imperial",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_293", -- Welcome to the right side of the battle lines.  I'm glad you are with us.  I understand that you found an odd spice sample.  I have some information about the missing pilot.  Someone named Kaila contacted me and told me that she had information on the missing pilot.  Evidently he's lost in the wilderness.  She has the coordinates if you go over and talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_253", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_reb_quest:s_277", "where_is_she"}, -- I want to find out what's going on.  Where is she?
		{"@conversation/c_story1_1_reb_quest:s_285", "no_part"} -- No more of this for me.  I'm done.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_with_spice_imperial);

welcome_back_with_spice_neutral = ConvoScreen:new {
	id = "welcome_back_with_spice_neutral",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_297", -- Welcome to the Alliance!  I hope you have been treated well so far.  Sources tell me that you found a spice sample and are looking for a missing pilot.  Someone named Kaila contacted me and told me that she had information on the missing pilot.  Evidently he's lost in the wilderness.  She has the coordinates if you go over and talk to her.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_253", "no_info"}, -- Didn't she give you the information when she contacted you?
		{"@conversation/c_story1_1_reb_quest:s_277", "where_is_she"}, -- I want to find out what's going on.  Where is she?
		{"@conversation/c_story1_1_reb_quest:s_285", "no_part"} -- No more of this for me.  I'm done.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(welcome_back_with_spice_neutral);

addConversationTemplate("rebelVeegaMadishConvoTemplate", rebelVeegaMadishConvoTemplate);
