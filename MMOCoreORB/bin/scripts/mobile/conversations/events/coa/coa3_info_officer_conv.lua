coa3InfoOfficerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3InfoOfficerConvoHandler",
	screens = {}
}


-- ========== -- WINNING --  Conversation Options =========

init_sent_by_coordinator_w = ConvoScreen:new {
	id = "init_sent_by_coordinator_w",
	leftDialog = "@conversation/coa3winfoofficer:s_708aa59f", -- I was told you would be arriving. I don't have much time and there's much to do, so I'll try to make this briefing quick.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_4372123c", "situation_is_good_w"}, -- What's the current situation?
	}
}
coa3InfoOfficerConvoTemplate:addScreen(init_sent_by_coordinator_w);

situation_is_good_w = ConvoScreen:new {
	id = "situation_is_good_w",
	leftDialog = "@conversation/coa3winfoofficer:s_c91c8c81", -- The situation is good. The message Princess Leia sent to Vacca did the trick. He's given us a prototype Dead Eye schematic. You can requisition one from any of our Recruiters, but you'll need some science skills to use it. It's nearly ready for use, though there are a few technical hurdles we must overcome.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_159911f5", "one_hurdle_w"}, -- Tell me more.
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(situation_is_good_w);

one_hurdle_w = ConvoScreen:new {
	id = "one_hurdle_w",
	leftDialog = "@conversation/coa3winfoofficer:s_e695be09", -- One hurdle we have not been able to overcome is the fact that the Dead Eye serum requires flora that only grew on Alderaan. Needless to say, the supplies of that flora are finite and very limited.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_a318edbd", "produce_alternative_w"}, -- Won't Dead Eye just fizzle out eventually?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(one_hurdle_w);

produce_alternative_w = ConvoScreen:new {
	id = "produce_alternative_w",
	leftDialog = "@conversation/coa3winfoofficer:s_5adb0095", -- It will unless we can produce an alternative. We have already set up a number of small research facilities where we are trying to find an alternative. If it works, and we are not hindered by the opposition, we should be able to keep Dead Eye up and running. If we don't find an alternative, Dead Eye will be useless once the current supply of Alderaanian Flora runs out. If we can even get our hands on the current supply.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_77e48d5b", "scum_of_galaxy_w"}, -- What do you mean?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(produce_alternative_w);

scum_of_galaxy_w = ConvoScreen:new {
	id = "scum_of_galaxy_w",
	leftDialog = "@conversation/coa3winfoofficer:s_8bb9b684", -- Scum of the galaxy or not, you have to admire the intelligence work of the underworld organizations. They learned of the importance of this flora well in advance of anyone else and took it upon themselves to corner the market.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_80cfbf07", "get_from_them"}, -- What do we do?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(scum_of_galaxy_w);

get_from_them_w = ConvoScreen:new {
	id = "get_from_them_w",
	leftDialog = "@conversation/coa3winfoofficer:s_f971a76c", -- We'll have to get it from them quickly. Without even a small supply we won't be able to replicate an alternative and all this work will have been for nothing.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_e6eebf47", "sent_briefings_w"}, -- So what can I do to help?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(get_from_them_w);

sent_briefings_w = ConvoScreen:new {
	id = "sent_briefings_w",
	leftDialog = "@conversation/coa3winfoofficer:s_a43858ea", -- We sent briefings to the Coordinators on some potential ways to get our hands on some of the stockpiles of the flora. Go talk with the Coordinator and he'll assign you a mission.
	stopConversation = "true",
	options = {}
}
coa3InfoOfficerConvoTemplate:addScreen(sent_briefings_w);


-- ========== -- LOSING --  Conversation Options =========

init_sent_by_coordinator_l = ConvoScreen:new {
	id = "init_sent_by_coordinator_l",
	leftDialog = "@conversation/coa3linfoofficer:s_a9479d34", -- Hello there. I'd be happy to share information with you about what has transpired and the plan of action we've drawn up for dealing with this messy situation.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_4372123c", "situation_is_bad_l"}, -- What's the current situation?
	}
}
coa3InfoOfficerConvoTemplate:addScreen(init_sent_by_coordinator_l);

situation_is_bad_l = ConvoScreen:new {
	id = "situation_is_bad_l",
	leftDialog = "@conversation/coa3linfoofficer:s_ccc29df2", --  The situation was bad and now it has gotten worse. If you haven't heard already, Dr. Vacca has made the decision to side with the enemy. They are now starting the production and testing of the Dead Eye serum in many hidden research facilities. The enemy is even making the prototype available to their followers.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_159911f5", "one_hurdle_l"}, -- Tell me more.
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(situation_is_bad_l);

one_hurdle_l = ConvoScreen:new {
	id = "one_hurdle_l",
	leftDialog = "@conversation/coa3linfoofficer:s_d3ee0e7f", -- One hurdle we have not been able to overcome is the fact that the Dead Eye serum requires flora that only grew on Alderaan. Needless to say, the supplies of that flora are finite and very limited.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_a318edbd", "produce_alternative_l"}, -- Won't Dead Eye just fizzle out eventually?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(one_hurdle_l);

produce_alternative_l = ConvoScreen:new {
	id = "produce_alternative_l",
	leftDialog = "@conversation/coa3linfoofficer:s_d6199fa3", -- Vacca won't give up so easily.  As soon as the supply of Alderaanian Flora is gone, Dead Eye is no more so they are set on finding an alternative. They have set up a number of secret research facilities to produce the Dead Eye serum and more importantly for them, to find a substitute for the rare flora. However some recent developments have come to light that may make tracking down these facilities easier than they expect.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_77e48d5b", "scum_of_galaxy_l"}, -- What do you mean?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(produce_alternative_l);

scum_of_galaxy_l = ConvoScreen:new {
	id = "scum_of_galaxy_l",
	leftDialog = "@conversation/coa3linfoofficer:s_65f79c5d", -- Scum of the galaxy or not, you have to admire the intelligence work of underworld organizations. They learned of the importance of this flora well in advance of anyone else and took it upon themselves to corner the market. If we track who is buying the flora and where it is being shipped, that will lead us to their research facilities.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_1bf8e6d", "get_from_them_l"}, -- Was there anything else?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(scum_of_galaxy_l);

get_from_them_l = ConvoScreen:new {
	id = "get_from_them_l",
	leftDialog = "@conversation/coa3linfoofficer:s_c326ad8f", --  Well another way we can hinder the production of Dead Eye is hitting their stores of the Alderaanian Flora directly. If we can get to the flora before they do, that is that much less of the serum that can be made and used against us and that much less they can experiment with to find an alternative flora. I think the coordinator has other more immediate plans for you right now though.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_e6eebf47", "sent_briefings_l"}, -- So what can I do to help?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3InfoOfficerConvoTemplate:addScreen(get_from_them_l);

sent_briefings_l = ConvoScreen:new {
	id = "sent_briefings_l",
	leftDialog = "@conversation/coa3linfoofficer:s_3259a3bc", -- Why don't you go back and speak with the coordinator. He was analyzing some data that had to do with discovering the locations of these hidden research facilities. He's probably finished by now and he probably has some work for you to do so go back and talk to him.
	stopConversation = "true",
	options = {}
}
coa3InfoOfficerConvoTemplate:addScreen(sent_briefings_l);


-- ========== General Responses =========

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3winfoofficer:s_eb1ac0f9", -- Hello there. I'm a little busy at the moment. If you're looking for work, perhaps you should seek out the Coordinator in this city. He may have something for you to do.
	stopConversation = "true",
	options = {}
}
coa3InfoOfficerConvoTemplate:addScreen(init_default);

didnt_mean_to_bore = ConvoScreen:new {
	id = "didnt_mean_to_bore",
	leftDialog = "@conversation/coa3winfoofficer:s_36b24b81", -- Oh, well I didn't mean to bore you. If you ever want a recap of what is going on, just let me know. You may want to go and see if the coordinator is ready for you. 
	stopConversation = "true",
	options = {}
}
coa3InfoOfficerConvoTemplate:addScreen(didnt_mean_to_bore);

addConversationTemplate("coa3InfoOfficerConvoTemplate", coa3InfoOfficerConvoTemplate);