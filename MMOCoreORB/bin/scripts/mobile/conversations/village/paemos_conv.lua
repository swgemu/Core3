paemosConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "paemosConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_experience_converter:s_962f82a6", -- Welcome, friend! Come here and tell me what insight I may provide for you today?
	stopConversation = "false",
	options = {
		{"@conversation/fs_experience_converter:s_73ab6ff4", "learn_crafting"}, -- I wish to learn more about using the Force for crafting.
		{"@conversation/fs_experience_converter:s_76fa10e4", "learn_combat"}, -- I wish to learn more about using the Force for combat.
		{"@conversation/fs_experience_converter:s_968c3ff6", "learn_senses"}, -- I wish to learn more about using the Force to enchance my senses.
		{"@conversation/fs_experience_converter:s_2734c210", "learn_reflex"}, -- I wish to learn more about using the Force to enhance my reflexes.
		-- Was used to convert old jedi system to new
		--{"@conversation/fs_experience_converter:s_69a7c6ca", "learn_force"}, -- I wish to learn new uses of the Force.
		{"@conversation/fs_experience_converter:s_e4c01185", "what_aspects"} -- What aspects of the Force am I ready to learn?
	}
}
paemosConvoTemplate:addScreen(intro);

learn_crafting = ConvoScreen:new {
	id = "learn_crafting",
	leftDialog = "@conversation/fs_experience_converter:s_7542cfea", -- Allow me to help you understand your experiences...
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(learn_crafting);

learn_combat = ConvoScreen:new {
	id = "learn_combat",
	leftDialog = "@conversation/fs_experience_converter:s_7542cfea", -- Allow me to help you understand your experiences...
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(learn_combat);

learn_senses = ConvoScreen:new {
	id = "learn_senses",
	leftDialog = "@conversation/fs_experience_converter:s_7542cfea", -- Allow me to help you understand your experiences...
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(learn_senses);

learn_reflex = ConvoScreen:new {
	id = "learn_reflex",
	leftDialog = "@conversation/fs_experience_converter:s_7542cfea", -- Allow me to help you understand your experiences...
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(learn_reflex);

learn_force = ConvoScreen:new {
	id = "learn_force",
	leftDialog = "@conversation/fs_experience_converter:s_433c2a58", -- Allow me to help you to open your mind to new possibilities...
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(learn_force);

what_aspects = ConvoScreen:new {
	id = "what_aspects",
	leftDialog = "@conversation/fs_experience_converter:s_7abe0196", -- I sense that you are able to learn the following: %TO
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(what_aspects);

cant_convert = ConvoScreen:new {
	id = "cant_convert",
	leftDialog = "@conversation/fs_experience_converter:s_37fbfae6", -- I am sorry, stranger.  Your mind is still too cloudy for me to help you.  Remove your doubts with journey and mediation.  Then return to me.
	stopConversation = "true",
	options = {}
}
paemosConvoTemplate:addScreen(cant_convert);

addConversationTemplate("paemosConvoTemplate", paemosConvoTemplate);
