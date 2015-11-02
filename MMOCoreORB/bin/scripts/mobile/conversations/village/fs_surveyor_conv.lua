villageSurveyorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSurveyorConvoHandler",
	screens = {}
}

intro_wrong_phase = ConvoScreen:new {
	id = "intro_wrong_phase",
	leftDialog = "@quest/force_sensitive/fs_survey:wrong_phase", -- There's not really anything I need right now. Perhaps you should talk to some of the other villagers and see if they need your help.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(intro_wrong_phase);

intro_no_skill = ConvoScreen:new {
	id = "intro_no_skill",
	leftDialog = "@quest/force_sensitive/fs_survey:no_skill", -- I'm sorry, but I'm looking for someone who is skilled in sampling for resources. My intelligence reports tell me that you don't have that particular skill.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(intro_no_skill);

intro_completed_current_phase = ConvoScreen:new {
	id = "intro_completed_current_phase",
	leftDialog = "@quest/force_sensitive/fs_survey:thanks", -- I want to thank you for all your help. I see you got your new survey tool. You can use it just like any other survey tool, only it has a modified chip that will allow you to scan for any type of inorganic resource. It will find energy, gas, ore, chemicals, you name it. You may want to speak with Noldan who can train you in any of the new skills you're interested in learning about.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(intro_completed_current_phase);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@quest/force_sensitive/fs_survey:youre_busy", -- I'm sorry, but according to the rumor mill here in the village you already have something to do. Come back and see me when you have more free time.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(intro_has_other_quest);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "", -- Set by convo handler
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(intro_in_progress);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@quest/force_sensitive/fs_survey:want_task", -- Hello! Good tidings and all that. There's some work I need done, and I need someone to do it. You look like the kind of person who could take on such a task. Could you? Would you? Are you interested in helping with my work?
	stopConversation = "false",
	options = {
		{ "@quest/force_sensitive/fs_survey:explain", "we_need_resources" }, -- What is it you want me to do?
		{ "@quest/force_sensitive/fs_survey:no_task", "sorry_to_hear_that" } -- Sorry, I'm not interested right now.
	}
}
villageSurveyorConvoTemplate:addScreen(intro);

we_need_resources = ConvoScreen:new {
	id = "we_need_resources",
	leftDialog = "@quest/force_sensitive/fs_survey:explanation", -- We need resources. Resources that will allow us to better the defenses of our village here. I don't need you to actually bring me the resources, I have a team for that. I just need you to find me the best places to set up our harvesting. I need your surveying skills, and your ability to survive outside this village. It's dangerous out there, and some of the villagers just aren't up to it. The resources we need may not even be on Dathomir, they could be on any planet. Can you help us?
	stopConversation = "false",
	options = {
		{ "@quest/force_sensitive/fs_survey:sure", "one_more_thing" }, -- Yeah, I know how to survey. Anything else I need to know?
		{ "@quest/force_sensitive/fs_survey:no_task", "sorry_to_hear_that" } -- Sorry, I'm not interested right now.
	}
}
villageSurveyorConvoTemplate:addScreen(we_need_resources);

one_more_thing = ConvoScreen:new {
	id = "one_more_thing",
	leftDialog = "@quest/force_sensitive/fs_survey:last_piece", -- There is one more thing. If you're going to work for me you're not going to be able to help out any of the other villagers while you do it. This is a commitment. I need someone focused on finding me the best places to harvest resources. I also need you to look for some special resources for me.
	stopConversation = "false",
	options = {
		{ "@quest/force_sensitive/fs_survey:special_question", "special_answer" }, -- Special Resources?
		{ "@quest/force_sensitive/fs_survey:no_task", "sorry_to_hear_that" } -- Sorry, I'm not interested right now.
	}
}
villageSurveyorConvoTemplate:addScreen(one_more_thing);

special_answer = ConvoScreen:new {
	id = "special_answer",
	leftDialog = "", -- Set by convo handler depending on phase
	stopConversation = "false",
	options = {
		-- Set by convo handler depending on phase
		--{ "@quest/force_sensitive/fs_survey:yes_task", "" }, -- I'd be happy to help.
		--{ "@quest/force_sensitive/fs_survey:no_task", "sorry_to_hear_that" } -- Sorry, I'm not interested right now.
	}
}
villageSurveyorConvoTemplate:addScreen(special_answer);

sorry_to_hear_that = ConvoScreen:new {
	id = "sorry_to_hear_that",
	leftDialog = "@quest/force_sensitive/fs_survey:too_bad", -- I'm so sorry to hear that. I was rather hoping you could get this done. I'm not sure who else I can get to help me out.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(sorry_to_hear_that);

sample_phase_2 = ConvoScreen:new {
	id = "sample_phase_2",
	leftDialog = "@quest/force_sensitive/fs_survey:sample_for_aluminum", -- I need you to find an area where we can survey Aluminum. It should have at least a 50% density. Once you get there, take a sample and try to find some special resources. When you've done that, check your journal; it should tell you what to look for next.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(sample_phase_2);

sample_phase_3 = ConvoScreen:new {
	id = "sample_phase_3",
	leftDialog = "@quest/force_sensitive/fs_survey:sample_for_iron", -- I need you to find an area where we can survey Iron. It should have at least a 50% density. Once you get there, take a sample and try to find some special resources. When you've done that, check your journal; it should tell you what to look for next.
	stopConversation = "true",
	options = {}
}
villageSurveyorConvoTemplate:addScreen(sample_phase_3);

addConversationTemplate("villageSurveyorConvoTemplate", villageSurveyorConvoTemplate);