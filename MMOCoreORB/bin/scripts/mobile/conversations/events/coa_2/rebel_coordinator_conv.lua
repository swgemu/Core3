rebelCoordinatorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebelCoordinatorConvoHandler",
	screens = {}
}

act1_not_complete = ConvoScreen:new {
	id = "act1_not_complete",
	leftDialog = "@recruiting/rebel_recruit:rr13", -- Hello friend. What can I do for you?
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(act1_not_complete);

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:coordinator_imperial_response", -- You seem to be more interested in helping the Empire. Why don't you come back when you've come to your senses.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(begin_wrong_faction);

m1_begin = ConvoScreen:new {
	id = "m1_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin", -- I hope you're here to help. We're stretched thin looking for Skimmer.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_info1", "m1_begin_info1"}, -- What's going on?
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_yes", "m1_begin_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_no", "m1_begin_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m1_begin);

m1_begin_info1 = ConvoScreen:new {
	id = "m1_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_info1_response", -- We're trying to locate one of our operatives code named Skimmer and we have a lot of tips to follow up. It has to do with this Dead Eye project we've been hearing about.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_yes", "m1_begin_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_no", "m1_begin_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m1_begin_info1);

m1_begin_yes = ConvoScreen:new {
	id = "m1_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_yes_response", -- Great! We think Skimmer may have recently contacted one of her close friends. Go to these coordinates and see of Skimmer has been in touch and report back here with any information you uncover.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_begin_yes);

m1_begin_no = ConvoScreen:new {
	id = "m1_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_no_response", -- I'm sorry to hear that. Skimmer's stumbled onto something big. If you change your mind, let me know.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_begin_no);

m1_refused = ConvoScreen:new {
	id = "m1_refused",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused", -- I hope you've changed your mind and can help us out. We need every loyal operative we can find right now.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_info1", "m1_refused_info1"}, -- What's going on?
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_yes", "m1_refused_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_no", "m1_refused_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m1_refused);

m1_refused_info1 = ConvoScreen:new {
	id = "m1_refused_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_info1_response", -- We're trying to locate one of our operatives code named Skimmer and we have a lot of tips to follow up. It has to do with this Dead Eye project we've been hearing about.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_yes", "m1_refused_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_no", "m1_refused_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m1_refused_info1);

m1_refused_yes = ConvoScreen:new {
	id = "m1_refused_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_yes_response", -- Great! We think Skimmer may have recently contacted one of her close friends. Go to these coordinates and see of Skimmer has been in touch and report back here with any information you uncover.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_refused_yes);

m1_refused_no = ConvoScreen:new {
	id = "m1_refused_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_no_response", -- I'm sorry to hear that. Skimmer's stumbled onto something big. If you change your mind, let me know.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_refused_no);

m1_active = ConvoScreen:new {
	id = "m1_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active", -- Have you talked to Skimmer's friend yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_working", "m1_active_working"}, -- I'm still looking for her.
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_abort", "m1_active_abort"}, -- I'm not going to be able to finish the mission.
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_restart", "m1_active_restart"}, -- I need my mission profile updated.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m1_active);

m1_active_working = ConvoScreen:new {
	id = "m1_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_working_response", -- Time's of the essence here, so do your best.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_active_working);

m1_active_abort = ConvoScreen:new {
	id = "m1_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_abort_response", -- I understand. Come find me if you change your mind. We need a lot of help on this one.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_active_abort);

m1_active_restart = ConvoScreen:new {
	id = "m1_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_restart_response", -- Very well. I've uploaded our latest intel to your datapad. You should be able to continue your mission now. May the Force be with you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_active_restart);

m1_finish_encoded = ConvoScreen:new {
	id = "m1_finish_encoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_finish_encoded", -- Good Work! Wait a pulse, this disk has been locked with an old Imperial code! We have schematics for this model of coder, but the parts are obsolete. I bet only local gangs or scavengers would have some of this stuff. I'll give you the schematics, but you'll have to locate the parts and put a decoder together before we can read this intel. Report back to me when you have the disk decoded.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_finish_encoded);

m1_finish_decoded = ConvoScreen:new {
	id = "m1_finish_decoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_finish_decoded", -- Good work. We'll analyze this information and decide on a plan. Come back in a little while and we'll have more information for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m1_finish_decoded);

m2_begin_encoded = ConvoScreen:new {
	id = "m2_begin_encoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_encoded", -- I'm very busy coordinating missions. Unless you have a decoded Dead Eye data disk for me, there's not much to discuss. Come back when you've decoded it.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin_encoded);

m2_begin = ConvoScreen:new {
	id = "m2_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin", -- Excellent. This message is from Skimmer. She's hiding outside the city and says she has information on Dead Eye. Can you head to these coordinates and make sure she's still there? We don't want to send a team to a place she left twelve cycles ago.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info1", "m2_begin_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info2", "m2_begin_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin);

m2_begin_info1 = ConvoScreen:new {
	id = "m2_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_info1_response", -- Not much. She's related to two Alliance pilots who died flying for us. Her brother was on Alderaan when it was destroyed by the Empire. Later her father was killed during the assault on the Death Star. I just hope he got a chance to know it was destroyed before his Y-wing was blown up.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info2", "m2_begin_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin_info1);

m2_begin_info2 = ConvoScreen:new {
	id = "m2_begin_info2",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_info2_response", -- Don't know. Not much data on it yet. All I know is that I don't want the Imperials to be any more accurate than they already are. I'd like to get Dr. Vacca on our side if we could.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info1", "m2_begin_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin_info2);

m2_begin_yes = ConvoScreen:new {
	id = "m2_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_yes_response", -- Excellent. Make sure she's still there and then report back to me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin_yes);

m2_begin_no = ConvoScreen:new {
	id = "m2_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_no_response", -- I understand. If you change your mind, come find me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_begin_no);

m2_refused = ConvoScreen:new {
	id = "m2_refused",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused", -- I hope you've changed your mind about helping us find Skimmer. She's still out there somewhere and we need to find her before the Imperials do. Are you willing to help?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info1", "m2_refused_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info2", "m2_refused_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_refused);

m2_refused_info1 = ConvoScreen:new {
	id = "m2_refused_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_info1_response", -- Not much. She's related to two Alliance pilots who died flying for us. Her brother was on Alderaan when it was destroyed by the Empire. Later her father was killed during the assault on the Death Star. I just hope he got a chance to know it was destroyed before his B-wing was blown up.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info2", "m2_refused_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_refused_info1);

m2_refused_info2 = ConvoScreen:new {
	id = "m2_refused_info2",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_info2_response", -- Don't know. Not much data on it yet. All I know is that I don't want the Imperials to be any more accurate than they already are. I'd like to get Dr. Vacca on our side if we could.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info1", "m2_refused_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_refused_info2);

m2_refused_yes = ConvoScreen:new {
	id = "m2_refused_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_yes_response", -- Excellent. Make sure she's still there and then report back to me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_refused_yes);

m2_refused_no = ConvoScreen:new {
	id = "m2_refused_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_no_response", -- I understand. If you change your mind, come find me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_refused_no);

m2_active = ConvoScreen:new {
	id = "m2_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active", -- Have you found skimmer yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_working", "m2_active_working"}, -- Not yet. I'm working on it.
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_abort", "m2_active_abort"}, -- I'm not going to be able to finish the mission.
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_restart", "m2_active_restart"}, -- I think I need updated intel.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_active);

m2_active_working = ConvoScreen:new {
	id = "m2_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_working_response", -- The imperials are after her, so don't waste any time.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_active_working);

m2_active_abort = ConvoScreen:new {
	id = "m2_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_abort_response", -- I understand. Come find me if you change your mind. We need a lot of help on this one.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_active_abort);

m2_active_restart = ConvoScreen:new {
	id = "m2_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_restart_response", -- Things change out in the field. I'll upload our latest information to your datapad. Done. You've got our latest information. Good luck.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_active_restart);

m2_finish = ConvoScreen:new {
	id = "m2_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish", -- Lyda's alive? Thank the stars. We'll send out a team to get her right away. You do good work. If you're up for it we need someone to deliver this disk and report to one of our Rebel Commanders about Lyda and project Dead Eye.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_finish_yes", "m2_finish_yes"}, -- I'm up for anything
		{"@theme_park/alderaan/act2/rebel_missions:m2_finish_no", "m2_finish_no"}, -- I can't help you right now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m2_finish);

m2_finish_yes = ConvoScreen:new {
	id = "m2_finish_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish_yes_response", -- Good. I'll give you the coordinates of the Commander's current location. Bring him the disk and he'll take over from there.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_finish_yes);

m2_finish_no = ConvoScreen:new {
	id = "m2_finish_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish_no_response", -- I'm sorry to hear that. If you change your mind, come back. I'll have something for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m2_finish_no);

m3_begin = ConvoScreen:new {
	id = "m3_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin", -- If you're available we still need someone to bring this information about Lyda and Dead Eye to our commander. He may have another mission for you if you're willing to do some traveling.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m3_begin_yes", "m3_begin_yes"}, -- I'm up for anything.
		{"@theme_park/alderaan/act2/rebel_missions:m3_begin_no", "m3_begin_no"}, -- I can't help you right now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(m3_begin);

m3_begin_yes = ConvoScreen:new {
	id = "m3_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin_yes_response", -- Good. I'll give you the coordinates of the Commander's current location. Bring him the disk and he'll take over from there.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_begin_yes);

m3_begin_no = ConvoScreen:new {
	id = "m3_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin_no_response", -- I'm sorry to hear that. If you change your mind, come back. I'll have something for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_begin_no);

m3_active = ConvoScreen:new {
	id = "m3_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active", -- Have you finished the mission yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_working", "m3_active_working"}, -- Not yet. I'm working on it.
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_abort", "m3_active_abort"}, -- I'm not able to do this mission now.
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_restart", "m3_active_restart"}, -- I need the location of the Commander again
	}
}

rebelCoordinatorConvoTemplate:addScreen(m3_active);

m3_active_working = ConvoScreen:new {
	id = "m3_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_working_response", -- Keep up the good work. We're counting on you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_active_working);

m3_active_abort = ConvoScreen:new {
	id = "m3_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_abort_response", -- I'm not able to do this mission now.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_active_abort);

m3_active_restart = ConvoScreen:new {
	id = "m3_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_restart_response", -- Data pad troubles? That happens I suppose. I'll give you updated coordinates, but don't lose it again.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_active_restart);

m3_finish = ConvoScreen:new {
	id = "m3_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_finish", -- I heard from the Commander that you were able to find him. I hope the mission went well. We could use some good news around here.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(m3_finish);

addConversationTemplate("rebelCoordinatorConvoTemplate", rebelCoordinatorConvoTemplate);
