biogenicSecurityTechConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicSecurityTechConvoHandler",
	screens = {}
}

init_firsttalk = ConvoScreen:new {
	id = "init_firsttalk",
	leftDialog = "@conversation/biogenic_securitytech:s_7df9e17e", -- Aargh. More of those foul creatures have escaped. Wait a minute, how did you get in here?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_d7b11a2","sith_spit"}, -- Through a large opening in the side of a hill.
		{"@conversation/biogenic_securitytech:s_55b3a778","seismic_event"}, -- Nevermind that. What's going on here?
		{"@conversation/biogenic_securitytech:s_d14c9940","forget_you_saw"} -- The same way that I'm leaving. Good-bye.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(init_firsttalk);

sith_spit = ConvoScreen:new {
	id = "sith_spit",
	leftDialog = "@conversation/biogenic_securitytech:s_5b2ec95c", -- Sith spit. That must mean the holo-generator is offline. Add one more thing to the list of what's gone wrong.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_2ba5e1a3","seismic_event"}, -- I'm sorry. What seems to be going on here?
		{"@conversation/biogenic_securitytech:s_db64ccb5","stay_out_of_way"} -- Sound like you have your hands full. I'll leave you alone.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(sith_spit);

seismic_event = ConvoScreen:new {
	id = "seismic_event",
	leftDialog = "@conversation/biogenic_securitytech:s_164b2134", -- We recently experienced some type of seismic event. It seems to have wrecked havoc with our security and containment systems. Many of my security officers have died as a result.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_77c97efc","could_use_help"}, -- Do you need a hand in getting it under control?
		{"@conversation/biogenic_securitytech:s_db64ccb5","stay_out_of_way"}, -- Sound like you have your hands full. I'll leave you alone.
		{"@conversation/biogenic_securitytech:s_28594fa2","your_funeral"}, -- I'd like to see more of this complex. Is there anything I should know?
		{"@conversation/biogenic_securitytech:s_c9c438be","mutating_creatures"}, -- What of those creatures you mentioned earlier?
		{"@conversation/biogenic_securitytech:s_db64ccb5","stay_out_of_way"} -- Sound like you have your hands full. I'll leave you alone.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(seismic_event);

im_very_busy = ConvoScreen:new {
	id = "im_very_busy",
	leftDialog = "@conversation/biogenic_securitytech:s_9749167c", -- I'm sorry, but I am very busy. What do you need?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_8cd04dbf","sentry_droids"},
		{"@conversation/biogenic_securitytech:s_1ea74b0a","creatures_modified"},
		{"@conversation/biogenic_securitytech:s_a57fff7e","just_punch_code"},
		{"@conversation/biogenic_securitytech:s_e8b00610","dont_come_back"}
	}
}

biogenicSecurityTechConvoTemplate:addScreen(im_very_busy);

forget_you_saw = ConvoScreen:new {
	id = "forget_you_saw",
	leftDialog = "@conversation/biogenic_securitytech:s_3605064", -- Yes, good. Just turn around and forget that you ever saw this place.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(forget_you_saw);

fine_stay_out_of_way = ConvoScreen:new {
	id = "fine_stay_out_of_way",
	leftDialog = "@conversation/biogenic_securitytech:s_4abac946", -- Fine, just stay out of my way.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(fine_stay_out_of_way);

first_thing = ConvoScreen:new {
	id = "first_thing",
	leftDialog = "@conversation/biogenic_securitytech:s_7cb640f8", -- The first thing that we need to do is to kill any of those mutant creatures that might have escaped. Then we'll have a good chance of getting this place back under control.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_4a0eda9c","no_problem"}, -- OK. I'll be on my way then. Thank you.
		{"@conversation/biogenic_securitytech:s_e32d6faf","staying_here"}, -- Are you coming with me?
		{"@conversation/biogenic_securitytech:s_6c0c46c5","fine_stay_out_of_way"} -- On second thought, I'd better just leave it to you.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(first_thing);


no_problem = ConvoScreen:new {
	id = "no_problem",
	leftDialog = "@conversation/biogenic_securitytech:s_802edca9", -- No problem. Now please go take care of those creatures.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(no_problem);

staying_here = ConvoScreen:new {
	id = "staying_here",
	leftDialog = "@conversation/biogenic_securitytech:s_19aa7018", -- No, I'm going to stay here and try to get the security system back online. Just go and help the others. I'm sure they're in trouble.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_2ea369ee","best_of_luck"}, -- Alright. I'll do my best.
		{"@conversation/biogenic_securitytech:s_6c0c46c5","fine_stay_out_of_way"} -- On second thought, I'd better just leave it to you.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(staying_here);

could_use_help = ConvoScreen:new {
	id = "could_use_help",
	leftDialog = "@conversation/biogenic_securitytech:s_2066c897", -- Actually, I could use some help, but if you're going further into the compound, you'll need a code to get through that security door. Punch in the code 12872 and you can get through. There are some things you should watch out for though.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_83dc19a","aware_sentry_droids"} -- What kind of things do I need to watch out for?
	}
}

biogenicSecurityTechConvoTemplate:addScreen(could_use_help);

dont_come_back = ConvoScreen:new {
	id = "dont_come_back",
	leftDialog = "@conversation/biogenic_securitytech:s_1a87eec", -- No, don't come back. Just turn around and forget you ever saw this place.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(dont_come_back);

best_of_luck = ConvoScreen:new {
	id = "best_of_luck",
	leftDialog = "@conversation/biogenic_securitytech:s_d8be16a3", -- Best of luck to you, friend. And be careful.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(best_of_luck);

your_funeral = ConvoScreen:new {
	id = "your_funeral",
	leftDialog = "@conversation/biogenic_securitytech:s_e4c5332b", -- It's your funeral. You'll need to punch in the code 12872 to get through that security door. Just make sure none of those creatures gets in here before I get security back online.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(your_funeral);

creatures_modified = ConvoScreen:new {
	id = "creatures_modified",
	leftDialog = "@conversation/biogenic_securitytech:s_54c04cd6", -- These creatures have been modified to become very powerful. When the earthquake hit, our containment system went down, and now they are able to leave their cages and roam the halls. That is about all I know.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(creatures_modified);

sentry_droids = ConvoScreen:new {
	id = "sentry_droids",
	leftDialog = "@conversation/biogenic_securitytech:s_8913cdec", -- With our security system down, the droids' targeting protocol will be offline. They are likely to shoot at anything and everything that moves. They are positioned in halls throughout the complex.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(sentry_droids);

aware_sentry_droids = ConvoScreen:new {
	id = "aware_sentry_droids",
	leftDialog = "@conversation/biogenic_securitytech:s_914ffdda", -- Specifically, you will need to be aware of the sentry droids, and any creatures that might have escaped from their cages.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_6e7f3aa6","first_thing"}, -- OK. What would you like for me to do?
		{"@conversation/biogenic_securitytech:s_6c0c46c5","fine_stay_out_of_way"} -- On second thought, I'd better just leave it to you.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(aware_sentry_droids);

just_punch_code = ConvoScreen:new {
	id = "just_punch_code",
	leftDialog = "@conversation/biogenic_securitytech:s_6dcc098c", -- Just punch in the code 12872 to get through the security door.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(just_punch_code);

best_of_luck = ConvoScreen:new {
	id = "best_of_luck",
	leftDialog = "@conversation/biogenic_securitytech:s_d8be16a3", -- Best of luck to you, friend. And be careful.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(best_of_luck);

stay_out_of_way = ConvoScreen:new {
	id = "stay_out_of_way",
	leftDialog = "@conversation/biogenic_securitytech:s_18376ecf", -- Alright, just be sure to stay out of the way.
	stopConversation = "true",
	options = {
	}
}

biogenicSecurityTechConvoTemplate:addScreen(stay_out_of_way);

mutating_creatures = ConvoScreen:new {
	id = "mutating_creatures",
	leftDialog = "@conversation/biogenic_securitytech:s_6738bb52", -- Many of the experiments in this compound revolve around genetically mutating certain creatures. The earthquake that we experienced recently seems to have shut down out containment systems.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_securitytech:s_77c97efc","could_use_help"}, -- Do you need a hand in getting it under control?
		{"@conversation/biogenic_securitytech:s_db64ccb5","stay_out_of_way"} -- Sound like you have your hands full. I'll leave you alone.
	}
}

biogenicSecurityTechConvoTemplate:addScreen(mutating_creatures);

addConversationTemplate("biogenicSecurityTechConvoTemplate", biogenicSecurityTechConvoTemplate);