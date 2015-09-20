rebelLydaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebelLydaConvoHandler",
	screens = {}
}

m1_sympathizer_invalid = ConvoScreen:new {
	id = "m1_sympathizer_invalid",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_sympathizer_invalid", -- I'm sorry, I can't chat right now. I'm waiting for a friend to arrive.
	stopConversation = "true",
	options = {}
}

rebelLydaConvoTemplate:addScreen(m1_sympathizer_invalid);

m2_lydasaved = ConvoScreen:new {
	id = "m2_lydasaved",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved", -- Thanks for the assist. I thought I was bantha fodder for sure that time. The Empire must have a reward out for me. If you're here you got my message to the Alliance. Thanks. I owe you two, I guess.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info1", "m2_lydasaved_info1"}, -- What happened on your mission?
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info2", "m2_lydasaved_info2"}, -- How did your cover get blown?
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_done", "m2_lydasaved_done"}, -- I have to go and tell the Alliance you're all right.
	}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved);

m2_lydasaved_info1 = ConvoScreen:new {
	id = "m2_lydasaved_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info1_response", -- I'd been assigned some safe, boring undercover work. Just watch and report on troop movements at an Imperial signals facility. One night this file got routed to my station. It looked important, so I stole Wes's...uh...my supervisor's security cylinder to decode it and make a copy. It was a little outside my mission profile, but it seemed important.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info1a", "m2_lydasaved_info1a"}, -- That file was about Dead Eye?
	}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved_info1);

m2_lydasaved_info1a = ConvoScreen:new {
	id = "m2_lydasaved_info1a",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info1a_response", -- It was all about Dead Eye. A report on the project and Dr. Vacca's past. Not enough to duplicate the process, just how it works and some details like the fact that it uses some rare plant that used to grow on Alderaan.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info2", "m2_lydasaved_info2"}, -- How did your cover get blown?
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_done", "m2_lydasaved_done"}, -- I have to go and tell the Alliance you're all right.
	}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved_info1a);

m2_lydasaved_info2 = ConvoScreen:new {
	id = "m2_lydasaved_info2",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info2_response", -- Well, I had become close friends with one of the Imperial officers. When they discovered his security cylinders were used to access the Dead Eye plans, he knew I was the only one who could have taken them. I'm pretty sure he had to turn me in or they would think he was a spy.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info2a", "m2_lydasaved_info2a"}, -- Did this officer know you're a Rebel?
	}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved_info2);

m2_lydasaved_info2a = ConvoScreen:new {
	id = "m2_lydasaved_info2a",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info2a_response", -- Not a chance. He's a good man who joined the Empire before he realized what kind of people they are. If he turned me in, it was only because he had no choice. I'm sure of it. I even think he might be willing to help the rebellion once his tour's up.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_info1", "m2_lydasaved_info1"}, -- What happened on your mission?
		{"@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_done", "m2_lydasaved_done"}, -- I have to go and tell the Alliance you're all right.
	}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved_info2a);

m2_lydasaved_done = ConvoScreen:new {
	id = "m2_lydasaved_done",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_lydasaved_done_response", -- Good. Report back to the Rebel Coordinator who sent you here that I'm ready to come back in. You will be told what to do next.
	stopConversation = "true",
	options = {}
}

rebelLydaConvoTemplate:addScreen(m2_lydasaved_done);

addConversationTemplate("rebelLydaConvoTemplate", rebelLydaConvoTemplate);
