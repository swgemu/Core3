imperialCommanderConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialCommanderConvoHandler",
	screens = {}
}

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:commander_rebel_response", -- We know all about your dealings with those rebel terrorists. You're lucky I don't order your execution right now where you stand. Now get out of here!
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(begin_wrong_faction);

m4_finish_incomplete = ConvoScreen:new {
	id = "m4_finish_incomplete",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m4_finish_incomplete", -- Hello citizen, if you're looking to do some work for the Empire you should contact one of our Imperial Coordinators. Coordinators have been dispatched to Talus, Naboo, Tatooine, Corellia and Rori. I don't need anything from you right now but our coordinators could certainly use your help.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m4_finish_incomplete);

m4_finish = ConvoScreen:new {
	id = "m4_finish",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m4_finish", -- You've done well. I'll see to it that our cryptologists get to decoding this right away. If you are willing, there is one final task I'd like completed.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m4_finish);

m5_begin_undeclared = ConvoScreen:new {
	id = "m5_begin_undeclared",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_undeclared", -- I'm sorry, this mission is too sensitive to entrust to just anyone. If you decide to officially declare your faction affiliation with the Empire, come back and we'll talk.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_undeclared);

m5_begin_declared = ConvoScreen:new {
	id = "m5_begin_declared",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_declared", -- Dr. Vacca has been working with Drall on project Dead Eye. We have been very tolerant so far. However, some of them have made statements against the Empire. We need a message sent.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_deadeye", "m5_begin_deadeye"}, -- What is project Dead Eye?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_drall", "m5_begin_drall"}, -- What do the Drall have to do with this?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_vacca", "m5_begin_vacca"}, -- Who is Dr. Vacca?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_message", "m5_begin_message"}, -- What is the message?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_yes", "m5_begin_yes"}, -- I'll complete your task.
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_no", "m5_begin_no"}, -- I'm not up to this now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_declared);

m5_begin_deadeye = ConvoScreen:new {
	id = "m5_begin_deadeye",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_deadeye_response", -- The details of project Dead Eye are none of your concern. Just know that the success of this project is of the utmost importance for the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_drall", "m5_begin_drall"}, -- What do the Drall have to do with this?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_vacca", "m5_begin_vacca"}, -- Who is Dr. Vacca?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_message", "m5_begin_message"}, -- What is the message?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_yes", "m5_begin_yes"}, -- I'll complete your task.
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_no", "m5_begin_no"}, -- I'm not up to this now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_deadeye);

m5_begin_drall = ConvoScreen:new {
	id = "m5_begin_drall",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_drall_response", -- The Drall have great knowledge of pharmaceuticals. Vacca believes their assistance is invaluable, so we've tolerated their presence. But open dissent is a threat to the project.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_deadeye", "m5_begin_deadeye"}, -- What is project Dead Eye?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_vacca", "m5_begin_vacca"}, -- Who is Dr. Vacca?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_message", "m5_begin_message"}, -- What is the message?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_yes", "m5_begin_yes"}, -- I'll complete your task.
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_no", "m5_begin_no"}, -- I'm not up to this now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_drall);

m5_begin_vacca = ConvoScreen:new {
	id = "m5_begin_vacca",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_vacca_response", -- Dr. Vacca is the lead of project Dead Eye. He is very valuable to us. He does have a bit of history though, so we have been keeping a very close eye on him.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_deadeye", "m5_begin_deadeye"}, -- What is project Dead Eye?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_drall", "m5_begin_drall"}, -- What do the Drall have to do with this?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_message", "m5_begin_message"}, -- What is the message?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_yes", "m5_begin_yes"}, -- I'll complete your task.
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_no", "m5_begin_no"}, -- I'm not up to this now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_vacca);

m5_begin_message = ConvoScreen:new {
	id = "m5_begin_message",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_message_response", -- Vacca needs to know what can happen if he chooses to cross the Empire. Killing a few of his Drall friends who have expressed open distain for the Empire should be message enough.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_deadeye", "m5_begin_deadeye"}, -- What is project Dead Eye?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_drall", "m5_begin_drall"}, -- What do the Drall have to do with this?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_vacca", "m5_begin_vacca"}, -- Who is Dr. Vacca?
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_yes", "m5_begin_yes"}, -- I'll complete your task.
		{"@theme_park/alderaan/act2/imperial_missions:m5_begin_no", "m5_begin_no"}, -- I'm not up to this now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_message);

m5_begin_yes = ConvoScreen:new {
	id = "m5_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_yes_response", -- Good. A group of Drall are on this planet collecting samples. Go to these coordinates and destroy every one you find there. Killing some of his Drall friends will let Vacca know what can happen should he cross the Empire. Be warned. These Drall are suspected of having Rebel support and attacking a Rebel base will leave you open to retaliation from other declared rebel forces for short time. Be on your guard.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_yes);

m5_begin_no = ConvoScreen:new {
	id = "m5_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_begin_no_response", -- If you decide to change you mind come back and let me know. You just may earn yourself a medal for your distinguished service.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_begin_no);

m5_active = ConvoScreen:new {
	id = "m5_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_active", -- You haven't done as I've asked. You are to go to that encampment of anti-imperialist Drall and exterminate them. The waypoint is already in your datapad. Do not fail me.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m5_active_working", "m5_active_working"}, -- I'll get right on it.
		{"@theme_park/alderaan/act2/imperial_missions:m5_active_restart", "m5_active_restart"}, -- Are you sure this waypoint is correct?
		{"@theme_park/alderaan/act2/imperial_missions:m5_active_abort", "m5_active_abort"}, -- I can't do this right now.
	}
}

imperialCommanderConvoTemplate:addScreen(m5_active);

m5_active_working = ConvoScreen:new {
	id = "m5_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_active_working_response", -- Good. Get out there and finish the job. Success in this mission will earn you the gratitude of the Empire.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_active_working);

m5_active_restart = ConvoScreen:new {
	id = "m5_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_active_restart_response", -- Hmm. It is possible that the data was faulty. I will upload the information to your datapad once again. Done. Now move out and finish the job.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_active_restart);

m5_active_abort = ConvoScreen:new {
	id = "m5_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_active_abort_response", -- I usually do not tolerate failure. I will overlook it this time given your history of diligent service to the Empire. You are relieved of your obligation. Return if you change your mind.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_active_abort);

m5_finish = ConvoScreen:new {
	id = "m5_finish",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m5_finish", -- The Empire owes you deep gratitude. Rebel meddling has been prevented and Dead Eye will continue on schedule without dissention. There is nothing more we need from you at this time.
	stopConversation = "true",
	options = {}
}

imperialCommanderConvoTemplate:addScreen(m5_finish);

addConversationTemplate("imperialCommanderConvoTemplate", imperialCommanderConvoTemplate);
