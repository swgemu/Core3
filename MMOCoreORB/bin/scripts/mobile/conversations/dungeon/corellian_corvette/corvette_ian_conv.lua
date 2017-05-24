corvetteIanConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvetteIanConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/corvette_ian_rebel_rescue_target:s_7ed61042", -- I'm glad to see you guys. I've been trying to work out a escape plan ever since they got me on this vessel but they have kept a close eye on me. How did you find me here?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_ian_rebel_rescue_target:s_9b4d81d1","safe_haven"}, -- We asked that coward Adar Tallon for help, but he refused. So we did it on our own.
		{"@conversation/corvette_ian_rebel_rescue_target:s_2960a6e2","excellent_work"}, -- Adar Tallon put together a plan for us. We couldn't have done it without him.
	}
}
corvetteIanConvoTemplate:addScreen(intro);

already_rescued = ConvoScreen:new {
	id = "already_rescued",
	leftDialog = "@conversation/corvette_ian_rebel_rescue_target:s_9447b2d6", -- I'd like nothing more than to hear of your adventures getting onto this ship, but now's not the time. Let's get off this thing first.
	stopConversation = "true",
	options = { }
}
corvetteIanConvoTemplate:addScreen(already_rescued);

safe_haven = ConvoScreen:new {
	id = "safe_haven",
	leftDialog = "@conversation/corvette_ian_rebel_rescue_target:s_4f0f61e", -- Er... hmmm. That doesn't sound much like the Adar Tallon I know. Um well... anyway, I know of a Rebel safe haven that's not too far from here. I'll take an escape pod to there. Er... yes. Thank you again.
	stopConversation = "true",
	options = { }
}
corvetteIanConvoTemplate:addScreen(safe_haven);

excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corvette_ian_rebel_rescue_target:s_3764c8de", -- Ah, I should have known. Adar is as competent as he is brave. Excellent work. I know of a Rebel safe haven that's not too far from here. I'll take an escape pod to there. Thank you again.
	stopConversation = "true",
	options = {}
}
corvetteIanConvoTemplate:addScreen(excellent_work);

addConversationTemplate("corvetteIanConvoTemplate", corvetteIanConvoTemplate);
