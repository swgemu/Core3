rebelCommanderConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebelCommanderConvoHandler",
	screens = {}
}

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:commander_imperial_response", -- You've got a lot of nerve trying to talk to me. You think we don't know how much you've done for the Empire? You better leave unless you like the thought of spending your golden years floating in bacta.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(begin_wrong_faction);

m4_finish_incomplete = ConvoScreen:new {
	id = "m4_finish_incomplete",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m4_finish_incomplete", -- I'm sorry I don't have time to talk to you now. Why don't you go find one of our Rebel Coordinators? They may have something for you to do.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m4_finish_incomplete);

m4_finish = ConvoScreen:new {
	id = "m4_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m4_finish", -- You've got info on Lyda and Dead Eye? We've been waiting for you! We'll process the data and comm the Princess to see how to proceed! Talk to me in a little bit. We might have one final mission for you.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m4_finish);

m5_begin_undeclared = ConvoScreen:new {
	id = "m5_begin_undeclared",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_begin_undeclared", -- The information you delivered is significant. Unfortunately, we can't trust the next part of the operation to anyone who hasn't officially joined the Alliance. Securing Dr. Vacca's cooperation is too important to give to just anyone.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_begin_undeclared);

m5_begin = ConvoScreen:new {
	id = "m5_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_begin", -- Oh yes, you're the one who found Lyda. We're all glad she's safe. It's only right that you take on the last part of this operation. Are you up for it?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m5_begin_yes", "m5_begin_yes"}, -- I want to finish what I started.
		{"@theme_park/alderaan/act2/rebel_missions:m5_begin_info1", "m5_begin_info1"}, -- How is Lyda doing?
		{"@theme_park/alderaan/act2/rebel_missions:m5_begin_no", "m5_begin_no"}, -- I don't think I'm ready yet.
	}
}

rebelCommanderConvoTemplate:addScreen(m5_begin);

m5_begin_info1 = ConvoScreen:new {
	id = "m5_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_begin_info1_response", -- Fine, but headstrong as ever. She is already requesting more assignments. She should be careful what she wishes for. This isn't her first time jumping to light speed without checking her charts.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m5_begin_yes", "m5_begin_yes"}, -- I want to finish what I started.
		{"@theme_park/alderaan/act2/rebel_missions:m5_begin_no", "m5_begin_no"}, -- I don't think I'm ready yet.
	}
}

rebelCommanderConvoTemplate:addScreen(m5_begin_info1);

m5_begin_yes = ConvoScreen:new {
	id = "m5_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_begin_yes_response", -- Excellent. The Princess wants us to deliver this coded message to Dr. Vacca to convince him to join the Alliance. To do so, you'll need to take over an Imperial relay station and use this interface override device to send the message. Be warned, when you attack the station's guards, you will be a target for any other Imperial in the galaxy. Be sure you want to do this. May the Force Be With You.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_begin_yes);

m5_begin_no = ConvoScreen:new {
	id = "m5_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_begin_no_response", -- If you change your mind come see me, but time is running out.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_begin_no);

m5_refused = ConvoScreen:new {
	id = "m5_refused",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_refused", -- You're still here? Look, I don't have a lot of time for you unless you have decided to help us with this mission. I know you've done a lot for us already. But I need to know, are you onboard or not?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m5_refused_yes", "m5_refused_yes"}, -- I want to finish what I started.
		{"@theme_park/alderaan/act2/rebel_missions:m5_refused_info1", "m5_refused_info1"}, -- How is Lyda doing?
		{"@theme_park/alderaan/act2/rebel_missions:m5_refused_no", "m5_refused_no"}, -- I don't think I'm ready yet.
	}
}

rebelCommanderConvoTemplate:addScreen(m5_refused);

m5_refused_info1 = ConvoScreen:new {
	id = "m5_refused_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_refused_info1_response", -- Fine, but headstrong as ever. She is already requesting more assignments. She should be careful what she wishes for. This isn't her first time jumping to light speed without checking her charts.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m5_refused_yes", "m5_refused_yes"}, -- I want to finish what I started.
		{"@theme_park/alderaan/act2/rebel_missions:m5_refused_no", "m5_refused_no"}, -- I don't think I'm ready yet.
	}
}

rebelCommanderConvoTemplate:addScreen(m5_refused_info1);

m5_refused_yes = ConvoScreen:new {
	id = "m5_refused_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_refused_yes_response", -- Excellent. The Princess wants us to deliver this coded message to Dr. Vacca to convince him to join the Alliance. To do so, you'll need to take over an Imperial relay station and use this interface override device to send the message. Be warned, when you attack the station's guards, you will be a target for any other Imperial in the galaxy. Be sure you want to do this. May the Force Be With You.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_refused_yes);

m5_refused_no = ConvoScreen:new {
	id = "m5_refused_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_refused_no_response", -- If you change your mind come see me, but time is running out.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_refused_no);

m5_active = ConvoScreen:new {
	id = "m5_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_active", -- Have you sent the message yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m5_active_working", "m5_active_working"}, -- Not yet. I'm working on it.
		{"@theme_park/alderaan/act2/rebel_missions:m5_active_abort", "m5_active_abort"}, -- I'm not able to do this mission now.
		{"@theme_park/alderaan/act2/rebel_missions:m5_active_restart", "m5_active_restart"}, -- I need to get my mission profile updated.
	}
}

rebelCommanderConvoTemplate:addScreen(m5_active);

m5_active_working = ConvoScreen:new {
	id = "m5_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_active_working_response", -- Do what you have to. This one is important to the Princess.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_active_working);

m5_active_abort = ConvoScreen:new {
	id = "m5_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_active_abort_response", -- That's too bad. Come back when you're able to help out.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_active_abort);

m5_active_restart = ConvoScreen:new {
	id = "m5_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_active_restart_response", -- I've uploaded the most recent intel we have on the relay facility. You should be able to find it now.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_active_restart);

m5_finish = ConvoScreen:new {
	id = "m5_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m5_finish", -- I'm glad you made it back here. I wanted to thank you personally for your hard work on this. If Dr. Vacca can be persuaded to join the Rebellion, it will make a huge impact on the war. Good job.
	stopConversation = "true",
	options = {}
}

rebelCommanderConvoTemplate:addScreen(m5_finish);

addConversationTemplate("rebelCommanderConvoTemplate", rebelCommanderConvoTemplate);
