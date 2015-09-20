imperialCoordinatorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialCoordinatorConvoHandler",
	screens = {}
}

act1_not_complete = ConvoScreen:new {
	id = "act1_not_complete",
	leftDialog = "@recruiting/imperial_recruit:ir13", -- Good day, and what can I do for you?
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(act1_not_complete);

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:coordinator_rebel_response", -- I have nothing to say to those who have dealings with rebel scum. I suggest you move along before you find yourself in a hail of blaster fire!
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(begin_wrong_faction);

m1_begin = ConvoScreen:new {
	id = "m1_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin", -- A rebel agent stole some very important documents concerning the Dead Eye project. We would like to stop this information from falling into the wrong hands. Would you like to help?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info1", "m1_begin_info1"}, -- Who is this agent?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info2", "m1_begin_info2"}, -- What is the Dead Eye Project?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "m1_begin_no"}, -- No thanks.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m1_begin);

m1_begin_info1 = ConvoScreen:new {
	id = "m1_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_info1_response", -- Her codename is Skimmer. Her whereabouts are unknown. She joined the rebellion after both her father and brother were killed during earlier campaigns waged against the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info2", "m1_begin_info2"}, -- What is the Dead Eye Project?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "m1_begin_no"}, -- No thanks.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m1_begin_info1);

m1_begin_info2 = ConvoScreen:new {
	id = "m1_begin_info2",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_info2_response", -- That information is need-to-know only and you don't need to know. Be assured that success of project Dead Eye is extremely important to the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info1", "m1_begin_info1"}, -- Who is this agent?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "m1_begin_no"}, -- No thanks.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m1_begin_info2);

m1_begin_yes = ConvoScreen:new {
	id = "m1_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_yes_response", -- We have an informant that has intercepted a rebel communication outlining their next move. Speak with the informant and return to me. I have added a waypoint to your data pad.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m1_begin_yes);

m1_begin_no = ConvoScreen:new {
	id = "m1_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_no_response", -- Very well. If you change your mind, come back and we'll talk.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m1_begin_no);

m1_active = ConvoScreen:new {
	id = "m1_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active", -- Have you spoken with the informant yet? This information is vital to the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_working", "m1_active_working"}, -- I'll speak with the informant immediately.
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_restart", "m1_active_restart"}, -- Are you sure those coordinates were correct?
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_abort", "m1_active_abort"}, -- I don't have time for this right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m1_active);

m1_active_working = ConvoScreen:new {
	id = "m1_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_working_response", -- Good. Carry on.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m1_active_working);

m1_active_restart = ConvoScreen:new {
	id = "m1_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_restart_response", -- It looks as though the informant has moved. Here, I've updated his current location into your datapad.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m1_active_restart);

m1_active_abort = ConvoScreen:new {
	id = "m1_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_abort_response", -- I'm sorry to hear that. Perhaps we can find someone else for the job.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m1_active_abort);

m2_begin = ConvoScreen:new {
	id = "m2_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin", -- We need to prevent that encoded message from being transmitted and retrieve it. Are you ready to get your hands dirty?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_info1", "m2_begin_info1"}, -- Get my hands dirty?
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_yes", "m2_begin_yes"}, -- I'll do what is necessary.
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_no", "m2_begin_no"}, -- I'm not so sure I'm up to this.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m2_begin);

m2_begin_info1 = ConvoScreen:new {
	id = "m2_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_info1_response", -- That's just an expression. Lethal force is authorized considering the sensitive nature of this case. You don't need to worry about any legal repercussions.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_yes", "m2_begin_yes"}, -- I'll do what is necessary.
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_no", "m2_begin_no"}, -- I'm not so sure I'm up to this.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m2_begin_info1);

m2_begin_yes = ConvoScreen:new {
	id = "m2_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_yes_response", -- Go to the slicer's location and recover the encoded message using any means. If you're not skilled in combat, bring some help. Return when you've retrieved the encoded message.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m2_begin_yes);

m2_begin_no = ConvoScreen:new {
	id = "m2_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_no_response", -- That's alright. This sort of work is not for everyone. Come on back if you change your mind though.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m2_begin_no);

m2_active = ConvoScreen:new {
	id = "m2_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active", -- Back again? Don't tell me you're getting cold feet. We have to stop that slicer and intercept that message before he's able to transmit it.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_working", "m2_active_working"}, -- I'll stop the slicer and get the encoded message.
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_restart", "m2_active_restart"}, -- I was unable to locate the slicer.
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_abort", "m2_active_abort"}, -- I can't do this right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m2_active);

m2_active_working = ConvoScreen:new {
	id = "m2_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_working_response", -- That's the spirit. Now get moving!
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m2_active_working);

m2_active_restart = ConvoScreen:new {
	id = "m2_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_restart_response", -- We received intelligence that the slicer was on the move after you had left. We have his new location and I've updated the new location to your datapad.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m2_active_restart);

m2_active_abort = ConvoScreen:new {
	id = "m2_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_abort_response", -- That's too bad. If you change your mind, please feel free to come back later.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m2_active_abort);

m3_begin = ConvoScreen:new {
	id = "m3_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin", -- We need to get that encoded message to the commander. Would you be willing to make the delivery?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m3_begin_yes", "m3_begin_yes"}, -- I will make the delivery.
		{"@theme_park/alderaan/act2/imperial_missions:m3_begin_no", "m3_begin_no"}, -- I don't have time for this right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m3_begin);

m3_begin_yes = ConvoScreen:new {
	id = "m3_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin_yes_response", -- Excellent! The commander is currently off world. I've uploaded his location to your datapad. Deliver the encoded message to him at once.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_begin_yes);

m3_begin_no = ConvoScreen:new {
	id = "m3_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin_no_response", -- In that case, come back whenever your busy schedule allows.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_begin_no);

m3_active = ConvoScreen:new {
	id = "m3_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active", -- You're still here? I've already contacted the Commander so he's expecting you. He's not the type of man you want to keep waiting.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_working", "m3_active_working"}, -- I'm leaving on the next flight out.
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_restart", "m3_active_restart"}, -- I seem to have lost the Commander's location.
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_abort", "m3_active_abort"}, -- I need to do something else right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(m3_active);

m3_active_working = ConvoScreen:new {
	id = "m3_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_working_response", -- Glad to hear it. I'm sure he will be very pleased.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_active_working);

m3_active_restart = ConvoScreen:new {
	id = "m3_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_restart_response", -- These missions are not to be taken lightly! Please be more careful next time. Here, I've uploaded the waypoint to your datapad once again.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_active_restart);

m3_active_abort = ConvoScreen:new {
	id = "m3_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_abort_response", -- How unfortunate. If you have time later on, please see me again. I hope the commander understands for both of our sakes.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_active_abort);

m3_finish = ConvoScreen:new {
	id = "m3_finish",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_finish", -- You've done well and I commend you for your admirable service to the Empire. There is nothing more I need of you at this time.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(m3_finish);

addConversationTemplate("imperialCoordinatorConvoTemplate", imperialCoordinatorConvoTemplate);
