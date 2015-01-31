deathWatchTechnicianConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchTechnicianConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_technician:s_8b67f49d", -- Hmm, who are you? Actually, nevermind. I don't want to know. If the Mandalorians don't want you here, they can take care of you themselves. It's not like they ever help me. No, not them. They tell me to get a job done and then don't let me do it.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_bb1676fc", "understatement"}, -- Having problems with the Mandalorians?
		{"@conversation/death_watch_technician:s_d7a232dc", "exhaust_vent_tech"}, -- What sort of job do you do?
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(intro);

understatement = ConvoScreen:new {
	id = "understatement",
	leftDialog = "@conversation/death_watch_technician:s_f7d4b8be", -- Now that might be a little bit of an understatement. I always have problems with the Mandalorians. They just don't deal well with others... I am thinking that they probably weren't hugged enough when they were children.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_a0c1a32f", "exhaust_ports_offline"}, -- What are the Mandalorians doing to stop you from working?
		{"@conversation/death_watch_technician:s_406a4ae2", "aint_that_truth"}, -- Sounds like you do have it rough.
		{"@conversation/death_watch_technician:s_1cc2ceff", "exhaust_vent_tech"}, -- I see. So.... what sort of work do you do here?
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(understatement);

exhaust_vent_tech = ConvoScreen:new {
	id = "exhaust_vent_tech",
	leftDialog = "@conversation/death_watch_technician:s_25e933d3", -- I am an exhaust ventilation technician for the mines. It is my job to make sure that the mine's exhaust system is working correctly. Of course, that is when the Mandalorians let me do my job.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_c4446dd7", "mines_fill_gas"}, -- What happens if the mine's exhaust system isn't working?
		{"@conversation/death_watch_technician:s_406a4ae2", "aint_that_truth"}, -- Sounds like you do have it rough.
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(exhaust_vent_tech);

mines_fill_gas = ConvoScreen:new {
	id = "mines_fill_gas",
	leftDialog = "@conversation/death_watch_technician:s_45ae332c", -- The mines fill up with allum gas. That stuff can really mess up the men working inside the mines. So all the miners have to wear the rebreather gear in order to work down there, but those things are not always reliable.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_a0c1a32f", "only_way_to_help"}, -- Maybe I can help you out?
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(mines_fill_gas);

aint_that_truth = ConvoScreen:new {
	id = "aint_that_truth",
	leftDialog = "@conversation/death_watch_technician:s_bb18b90f", -- Ain't that the truth. Now, if there isn't anything else, I really need to get back to trying to figure out a way to get those dumb Mandalorians not to trash another one of my droids.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_a0c1a32f", "only_way_to_help"}, -- Maybe I can help you out?
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(aint_that_truth);

exhaust_ports_offline = ConvoScreen:new {
	id = "exhaust_ports_offline",
	leftDialog = "@conversation/death_watch_technician:s_a8fb8b64", -- The main exhaust ports are offline and I need to send in a droid to fix it. But everytime I send in one of my droids, these dumb Mandalorians shoot it to pieces. Then, they laugh about it all the while yelling at me for not having the ports back online.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_a0c1a32f", "only_way_to_help"}, -- Maybe I can help you out?
		{"@conversation/death_watch_technician:s_72f8ec3a", "yeah_yeah"}, -- Okay, well, good luck with that.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(exhaust_ports_offline);

only_way_to_help = ConvoScreen:new {
	id = "only_way_to_help",
	leftDialog = "@conversation/death_watch_technician:s_c74f6e65", -- The only thing that I can think of to help me out is if you go in with the droid and don't let the Mandalorians blow it up. If you are willing to do that, you have way more guts than I would ever have.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_technician:s_17aa7854", "release_the_droid"}, -- I can do that. Send in the droid and I will take care of the Mandalorians.
		{"@conversation/death_watch_technician:s_1a05844b", "dont_blame_you"}, -- Hmmm, I am not going to do that. Those Mandalorians are nasty.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(only_way_to_help);

release_the_droid = ConvoScreen:new {
	id = "release_the_droid",
	leftDialog = "@conversation/death_watch_technician:s_fe84832a", -- Alright, I am going to release the droid. It has to make a stop over at the tool chest to get some extra tools before it can make the repairs. Keep those Mandalorians off it until it can finish the repairs and these air vents will kick on and clear out the allum gases.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(release_the_droid);

dont_blame_you = ConvoScreen:new {
	id = "dont_blame_you",
	leftDialog = "@conversation/death_watch_technician:s_89b80057", -- Can't say I blame you.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(dont_blame_you);

yeah_yeah = ConvoScreen:new {
	id = "yeah_yeah",
	leftDialog = "@conversation/death_watch_technician:s_3f1a842c", -- Yeah, yeah.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(yeah_yeah);

quest_completed_gas_cleared = ConvoScreen:new {
	id = "quest_completed_gas_cleared",
	leftDialog = "@conversation/death_watch_technician:s_33381eda", -- I can't thank you enough for helping me out back there. The exhaust fans are back online and the miners should be safe for a while at least. That exhaust system is pretty iffy and shorts out alot. I think the Mandalorians are breaking it on purpose just so they can have their fun.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(quest_completed_gas_cleared);

cant_talk_busy = ConvoScreen:new {
	id = "cant_talk_busy",
	leftDialog = "@conversation/death_watch_technician:s_ebfed4db", -- I am sorry, but I really don't have much time to chat right now. Always too much work to do in to little time. Maybe later I will have a spare moment.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(cant_talk_busy);

should_be_escorting = ConvoScreen:new {
	id = "should_be_escorting",
	leftDialog = "@conversation/death_watch_technician:s_cba682eb", -- What are you doing back here? You are supposed to be protecting that droid. Without your protection, those Mandalorians will blow him to bits.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(should_be_escorting);

escort_in_progress = ConvoScreen:new {
	id = "should_be_escorting",
	leftDialog = "@conversation/death_watch_technician:s_1fb416ce", -- Give me a few minutes. I just sent out one of my droids on a dangerous mission with an escort. I am hoping that this works.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(escort_in_progress);

escort_failed = ConvoScreen:new {
	id = "escort_failed",
	leftDialog = "@conversation/death_watch_technician:s_bd52a08a", -- Blast it! Lost another droid. I swear those Mandalorians are just relentless when they feel the need to torment someone.
	stopConversation = "false",
	options = {
		-- Adjust depending if new droid not built yet
		--{"@conversation/death_watch_technician:s_7d875e15", "release_the_droid"}, -- Give me another chance. I know I can keep that droid alive.
		--{"@conversation/death_watch_technician:s_3bc0260c", "not_first_person"}, -- Those Mandalorians are to much for me.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(escort_failed);

building_new_droid = ConvoScreen:new {
	id = "building_new_droid",
	leftDialog = "@conversation/death_watch_technician:s_1fb416ce", -- You are going to have to give me a little while to get another droid put together. Come back and talk to me later. If I still need the help, I will be more than willing to take it.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(building_new_droid);

not_first_person = ConvoScreen:new {
	id = "building_new_droid",
	leftDialog = "@conversation/death_watch_technician:s_fc578c95", -- You are not the first person to say those words.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(building_new_droid);

intro_prev_completed_new_escort = ConvoScreen:new {
	id = "intro_prev_completed_new_escort",
	leftDialog = "@conversation/death_watch_technician:s_3cab69e3", -- Hey, you don't know how happy I am to see you again. The exhaust system went offline again and...that's right...you guessed it...those Mandalorians are at it again. You willing to give me a hand again?
	stopConversation = "false",
	options = {
		-- Adjust depending if new droid not built yet
		--{"@conversation/death_watch_technician:s_373533eb", "knew_could_count"}, -- You know it. I will protect that droid.
		--{"@conversation/death_watch_technician:s_cbf95857", "thanks_anyways"}, -- I am sorry, but I can't right now.
	}
}
deathWatchTechnicianConvoTemplate:addScreen(intro_prev_completed_new_escort);

knew_could_count = ConvoScreen:new {
	id = "knew_could_count",
	leftDialog = "@conversation/death_watch_technician:s_9a8c12bc", -- I knew I could count on you. Okay, I am going to unleash the droid now. Good luck to you.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(knew_could_count);

thanks_anyways = ConvoScreen:new {
	id = "thanks_anyways",
	leftDialog = "@conversation/death_watch_technician:s_aad4d52", -- Oh, well, I am sure I will figure something else out. Thanks anyways.
	stopConversation = "true",
	options = {
	}
}
deathWatchTechnicianConvoTemplate:addScreen(thanks_anyways);

addConversationTemplate("deathWatchTechnicianConvoTemplate", deathWatchTechnicianConvoTemplate);