villageQuharekPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageQuharekPhase1ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_quharek:s_ebabb0f8", -- You there! Are you handy with a set of tools?
	stopConversation = "false",
	options = {
		{"@conversation/village_quharek:s_4beb938f", "sensor_array_damaged"}, -- Yes, I suppose I am.
		{"@conversation/village_quharek:s_f474ed78", "send_someone_over"}, -- Not really no.
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro);

sensor_array_damaged = ConvoScreen:new {
	id = "sensor_array_damaged",
	leftDialog = "@conversation/village_quharek:s_b2dd509a", -- Great. Our sensor array was damaged in the last attack on this village by the Sith Shadows. It needs to be repaired, but unfortunately, our chief engineer was also killed in the attack.
	stopConversation = "false",
	options = {
		{"@conversation/village_quharek:s_8abf86da", "catch_on_quick"}, -- You want me to take a look at the sensor array?
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(sensor_array_damaged);

catch_on_quick = ConvoScreen:new {
	id = "catch_on_quick",
	leftDialog = "@conversation/village_quharek:s_9cdcc110", -- That's it exactly. You catch on quick. If you will, take a look at the damage, see what needs to be repaired, and fix it up for us.
	stopConversation = "false",
	options = {
		{"@conversation/village_quharek:s_9ae334e4", "good_show"}, -- I think that I can handle that.
		{"@conversation/village_quharek:s_c9f1dbdc", "thats_a_shame"}, -- That doesn't sound like something that I can do.
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(catch_on_quick);

good_show = ConvoScreen:new {
	id = "good_show",
	leftDialog = "@conversation/village_quharek:s_27808b0b", -- Good show! If you help us out with this, I will help you learn to use the Force to enhance your assembly skills.
	stopConversation = "false",
	options = {
		{"@conversation/village_quharek:s_8459377a", "understand_the_job"}, -- Yes, I will go repair the sensor array.
		{"@conversation/village_quharek:s_75cdc0ad", "thats_a_shame"}, -- On second thought, I don't think that I can help you.
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(good_show);

understand_the_job = ConvoScreen:new {
	id = "understand_the_job",
	leftDialog = "@conversation/village_quharek:s_e26f0607", -- Of course you understand that this job will take a while, and if you agree to fix this thing, you won't be able to help anyone else with anything for a while, right?
	stopConversation = "false",
	options = {
		{"@conversation/village_quharek:s_ac061a6f", "get_to_work"}, -- That sounds fine to me.
		{"@conversation/village_quharek:s_a4a9c8e0", "send_someone_who_will"}, -- Oh, in that case I'd rather not do it.
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(understand_the_job);

get_to_work = ConvoScreen:new {
	id = "get_to_work",
	leftDialog = "@conversation/village_quharek:s_1b7f8e6d", -- Good! You'd better get to work then. The sooner we get that thing back online, the better!
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(get_to_work);

send_someone_who_will = ConvoScreen:new {
	id = "send_someone_who_will",
	leftDialog = "@conversation/village_quharek:s_52acc0", -- That's a shame. If you find someone who will... send 'em over.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(send_someone_who_will);

thats_a_shame = ConvoScreen:new {
	id = "thats_a_shame",
	leftDialog = "@conversation/village_quharek:s_8d878ba7", -- That's a shame. If you find someone who can... send 'em over.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(thats_a_shame);

send_someone_over = ConvoScreen:new {
	id = "send_someone_over",
	leftDialog = "@conversation/village_quharek:s_5ec4a1e", -- Alright, well if you see someone who is... send 'em over.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(send_someone_over);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/village_quharek:s_faf1fbe4", -- You there! Are you handy with a set of tools? Eh... looks like you're too busy to help me anyway. Nevermind.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_has_other_quest);

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/village_quharek:s_fae10418", -- What are you doing here? You shouldn't be here!
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_not_eligible);

intro_completed_quest = ConvoScreen:new {
	id = "intro_completed_quest",
	leftDialog = "@conversation/village_quharek:s_be3bc184", -- Hey! You got that all fixed up, didn't you? And just in time. You're all right, you know that?
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_completed_quest);

intro_completed_other_quest = ConvoScreen:new {
	id = "intro_completed_other_quest",
	leftDialog = "@conversation/village_quharek:s_f1a421d", -- Say, I know you. They tell me you've been a great help. Good job.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_completed_other_quest);

intro_wrong_phase = ConvoScreen:new {
	id = "intro_wrong_phase",
	leftDialog = "@conversation/village_quharek:s_e05cc4d4", -- What's going on here? I'm all confused! I don't know what's going on!
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_wrong_phase);

intro_inprogress = ConvoScreen:new {
	id = "intro_inprogress",
	leftDialog = "@conversation/village_quharek:s_16cc0ae1", -- What are you waiting for? Go get that sensor array repaired!
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_inprogress);

intro_noquest = ConvoScreen:new {
	id = "intro_noquest",
	leftDialog = "@conversation/village_quharek:s_6a934b47", -- Master... I must find the master.
	stopConversation = "true",
	options = {
	}
}
villageQuharekPhase1ConvoTemplate:addScreen(intro_noquest);

addConversationTemplate("villageQuharekPhase1ConvoTemplate", villageQuharekPhase1ConvoTemplate);
