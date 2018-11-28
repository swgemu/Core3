coa3RebelInfoOfficerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3RebelInfoOfficerConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3winfoofficer:s_eb1ac0f9", -- Hello there. I'm a little busy at the moment. If you're looking for work, perhaps you should seek out the Coordinator in this city. He may have something for you to do.
	stopConversation = "true",
	options = {}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(init_default);

init_sent_by_coordinator = ConvoScreen:new {
	id = "init_sent_by_coordinator",
	leftDialog = "@conversation/coa3winfoofficer:s_708aa59f", -- I was told you would be arriving. I don't have much time and there's much to do, so I'll try to make this briefing quick.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_4372123c", "situation_is_good"}, -- What's the current situation?
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(init_sent_by_coordinator);

situation_is_good = ConvoScreen:new {
	id = "situation_is_good",
	leftDialog = "@conversation/coa3winfoofficer:s_c91c8c81", -- The situation is good. The message Princess Leia sent to Vacca did the trick. He's given us a prototype Dead Eye schematic. You can requisition one from any of our Recruiters, but you'll need some science skills to use it. It's nearly ready for use, though there are a few technical hurdles we must overcome.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_159911f5", "one_hurdle"}, -- Tell me more.
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(situation_is_good);

situation_is_good = ConvoScreen:new {
	id = "situation_is_good",
	leftDialog = "@conversation/coa3winfoofficer:s_e695be09", -- One hurdle we have not been able to overcome is the fact that the Dead Eye serum requires flora that only grew on Alderaan. Needless to say, the supplies of that flora are finite and very limited.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_a318edbd", "produce_alternative"}, -- Won't Dead Eye just fizzle out eventually?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(situation_is_good);

produce_alternative = ConvoScreen:new {
	id = "produce_alternative",
	leftDialog = "@conversation/coa3winfoofficer:s_5adb0095", -- It will unless we can produce an alternative. We have already set up a number of small research facilities where we are trying to find an alternative. If it works, and we are not hindered by the opposition, we should be able to keep Dead Eye up and running. If we don't find an alternative, Dead Eye will be useless once the current supply of Alderaanian Flora runs out. If we can even get our hands on the current supply.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_77e48d5b", "scum_of_galaxy"}, -- What do you mean?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(produce_alternative);

scum_of_galaxy = ConvoScreen:new {
	id = "scum_of_galaxy",
	leftDialog = "@conversation/coa3winfoofficer:s_8bb9b684", -- Scum of the galaxy or not, you have to admire the intelligence work of the underworld organizations. They learned of the importance of this flora well in advance of anyone else and took it upon themselves to corner the market.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_80cfbf07", "get_from_them"}, -- What do we do?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(scum_of_galaxy);

get_from_them = ConvoScreen:new {
	id = "get_from_them",
	leftDialog = "@conversation/coa3winfoofficer:s_f971a76c", -- We'll have to get it from them quickly. Without even a small supply we won't be able to replicate an alternative and all this work will have been for nothing.
	stopConversation = "false",
	options = {
		{"@conversation/coa3winfoofficer:s_e6eebf47", "sent_briefings"}, -- So what can I do to help?
		{"@conversation/coa3winfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(get_from_them);

sent_briefings = ConvoScreen:new {
	id = "sent_briefings",
	leftDialog = "@conversation/coa3winfoofficer:s_a43858ea", -- We sent briefings to the Coordinators on some potential ways to get our hands on some of the stockpiles of the flora. Go talk with the Coordinator and he'll assign you a mission.
	stopConversation = "true",
	options = {}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(sent_briefings);

didnt_mean_to_bore = ConvoScreen:new {
	id = "didnt_mean_to_bore",
	leftDialog = "@conversation/coa3winfoofficer:s_36b24b81", -- Oh, well I didn't mean to bore you. If you ever want a recap of what is going on, just let me know. You may want to go and see if the coordinator is ready for you. 
	stopConversation = "true",
	options = {}
}
coa3RebelInfoOfficerConvoTemplate:addScreen(didnt_mean_to_bore);

addConversationTemplate("coa3RebelInfoOfficerConvoTemplate", coa3RebelInfoOfficerConvoTemplate);