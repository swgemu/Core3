coa3ImperialInfoOfficerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3ImperialInfoOfficerConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3linfoofficer:s_eb1ac0f9", -- Hello there. I'm a little busy at the moment. If you're looking for work, perhaps you should seek out the Coordinator in this city. He may have something for you to do.
	stopConversation = "true",
	options = {}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(init_default);

init_sent_by_coordinator = ConvoScreen:new {
	id = "init_sent_by_coordinator",
	leftDialog = "@conversation/coa3linfoofficer:s_a9479d34", -- Hello there. I'd be happy to share information with you about what has transpired and the plan of action we've drawn up for dealing with this messy situation.
	stopConversation = "false",
	options = {
		{"@conversation/coa3linfoofficer:s_4372123c", "situation_is_bad"}, -- What's the current situation?
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(init_sent_by_coordinator);

situation_is_bad = ConvoScreen:new {
	id = "situation_is_bad",
	leftDialog = "@conversation/coa3linfoofficer:s_ccc29df2", -- The situation was bad and now it has gotten worse. If you haven't heard already, Dr. Vacca has made the decision to side with the enemy. They are now starting the production and testing of the Dead Eye serum in many hidden research facilities. The enemy is even making the prototype available to their followers.
	options = {
		{"@conversation/coa3linfoofficer:s_159911f5", "one_hurdle"}, -- Tell me more.
		{"@conversation/coa3linfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(situation_is_bad);

one_hurdle = ConvoScreen:new {
	id = "one_hurdle",
	leftDialog = "@conversation/coa3linfoofficer:s_d3ee0e7f", -- One hurdle they have not been able to overcome is the fact that the Dead Eye serum requires flora that only grew on Alderaan. Needless to say, the supplies of that flora are finite and very limited. This is one fact that we will use to our advantage.
	options = {
		{"@conversation/coa3linfoofficer:s_a318edbd", "wont_give_up"}, -- Won't Dead Eye just fizzle out eventually?
		{"@conversation/coa3linfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(one_hurdle);

wont_give_up = ConvoScreen:new {
	id = "wont_give_up",
	leftDialog = "@conversation/coa3linfoofficer:s_d6199fa3", -- Vacca won't give up so easily.  As soon as the supply of Alderaanian Flora is gone, Dead Eye is no more so they are set on finding an alternative. They have set up a number of secret research facilities to produce the Dead Eye serum and more importantly for them, to find a substitute for the rare flora. However some recent developments have come to light that may make tracking down these facilities easier than they expect.
	options = {
		{"@conversation/coa3linfoofficer:s_77e48d5b", "scum_of_galaxy"}, -- What do you mean?
		{"@conversation/coa3linfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(wont_give_up);

scum_of_galaxy = ConvoScreen:new {
	id = "scum_of_galaxy",
	leftDialog = "@conversation/coa3linfoofficer:s_65f79c5d", -- Scum of the galaxy or not, you have to admire the intelligence work of underworld organizations. They learned of the importance of this flora well in advance of anyone else and took it upon themselves to corner the market. If we track who is buying the flora and where it is being shipped, that will lead us to their research facilities.
	options = {
		{"@conversation/coa3linfoofficer:s_1bf8e6d", "hinder_production"}, -- Was there anything else?
		{"@conversation/coa3linfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(scum_of_galaxy);

hinder_production = ConvoScreen:new {
	id = "hinder_production",
	leftDialog = "@conversation/coa3linfoofficer:s_c326ad8f", -- Well another way we can hinder the production of Dead Eye is hitting their stores of the Alderaanian Flora directly. If we can get to the flora before they do, that is that much less of the serum that can be made and used against us and that much less they can experiment with to find an alternative flora. I think the coordinator has other more immediate plans for you right now though.
	options = {
		{"@conversation/coa3linfoofficer:s_e6eebf47", "speak_with_coordinator"}, -- So what can I do to help?
		{"@conversation/coa3linfoofficer:s_7b8e8204", "didnt_mean_to_bore"}, -- I've heard enough.
	}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(hinder_production);

speak_with_coordinator = ConvoScreen:new {
	id = "speak_with_coordinator",
	leftDialog = "@conversation/coa3linfoofficer:s_3259a3bc", -- Why don't you go back and speak with the coordinator. He was analyzing some data that had to do with discovering the locations of these hidden research facilities. He's probably finished by now and he probably has some work for you to do so go back and talk to him.
	stopConversation = "true",
	options = {}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(speak_with_coordinator);

didnt_mean_to_bore = ConvoScreen:new {
	id = "didnt_mean_to_bore",
	leftDialog = "@conversation/coa3linfoofficer:s_36b24b81", -- Oh, well I didn't mean to bore you. If you ever want a recap of what is going on, just let me know. You may want to go and see if the coordinator is ready for you.
	stopConversation = "true",
	options = {}
}
coa3ImperialInfoOfficerConvoTemplate:addScreen(didnt_mean_to_bore);

addConversationTemplate("coa3ImperialInfoOfficerConvoTemplate", coa3ImperialInfoOfficerConvoTemplate);
