deathWatchInsaneMinerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchHaldoConvoHandler",
	screens = {}
}

intro_noquest = ConvoScreen:new {
	id = "intro_noquest",
	leftDialog = "@conversation/death_watch_insane_miner:s_c2b7bf76", -- You cannot help me! No one can help me...go away!
	stopConversation = "true",
	options = {}
}
deathWatchInsaneMinerConvoTemplate:addScreen(intro_noquest);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_insane_miner:s_21632dd", -- My head! I cannot think straight. Please get me some help before I hurt anyone...it has to be allum sickness!
	stopConversation = "false",
	options = {
		-- Handled by convo handler
		--{"@conversation/death_watch_insane_miner:s_dad50efa", "please_give"}, -- I have some of the medicine on me.
		--{"@conversation/death_watch_insane_miner:s_3fb7180e", "medical_droid"}, -- Allum sickness? What can I do to help you?
		--{"@conversation/death_watch_insane_miner:s_4fe1bc67", "wont_help"}, -- I don't think so! Sorry, but you need to be taken down.
	}
}
deathWatchInsaneMinerConvoTemplate:addScreen(intro);

please_give = ConvoScreen:new {
	id = "please_give",
	leftDialog = "@conversation/death_watch_insane_miner:s_ea390b92", -- Please, you must give it to me. Without that medicine I will surely die!
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_829888a9", "thank_you"}, -- Here you go.
	}
}
deathWatchInsaneMinerConvoTemplate:addScreen(please_give);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/death_watch_insane_miner:s_e810685f", -- Thank you, thank you. You have saved my life. I should be fine with just a little rest. Please take this back to my foreman. I took it in my dementia.
	stopConversation = "true",
	options = {}
}
deathWatchInsaneMinerConvoTemplate:addScreen(thank_you);

wont_help = ConvoScreen:new {
	id = "wont_help",
	leftDialog = "@conversation/death_watch_insane_miner:s_99f3d3be", -- You won't help me...no you must...no...arrrrgh!!!
	stopConversation = "true",
	options = {}
}
deathWatchInsaneMinerConvoTemplate:addScreen(wont_help);

medical_droid = ConvoScreen:new {
	id = "medical_droid",
	leftDialog = "@conversation/death_watch_insane_miner:s_87bb258b", -- The medical droid upstairs? Yes! The medical droid has the antidote. I need it...I must have some before it is to late.
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_16968d33", "please_hurry"}, -- Don't worry I will go get you some right now.
		--{"@conversation/death_watch_insane_miner:s_4fe1bc67", "wont_help"}, -- I don't think so! Sorry, but you need to be taken down.
	}
}
deathWatchInsaneMinerConvoTemplate:addScreen(medical_droid);

please_hurry = ConvoScreen:new {
	id = "please_hurry",
	leftDialog = "@conversation/death_watch_insane_miner:s_2ff0df5", -- Please hurry! I don't know how much longer I can hold onto my sanity. If I don't get that medicine quick I am going to lose control.
	stopConversation = "true",
	options = {}
}
deathWatchInsaneMinerConvoTemplate:addScreen(please_hurry);

return_intro = ConvoScreen:new {
	id = "return_intro",
	leftDialog = "@conversation/death_watch_insane_miner:s_ce67a12e", -- You are back. Please tell me that you have the medicine. I am really struggling to keep my sanity right now and that medicine is my only hope.
	stopConversation = "false",
	options = {
		-- Handled by convo handler
		{"@conversation/death_watch_insane_miner:s_42a2316b", "thank_you"}, -- Yes I have it. Here you go.
		{"@conversation/death_watch_insane_miner:s_7c83bd45", "must_hurry"}, -- Sorry but I don't have it yet. I will come back when I get it.
		--{"@conversation/death_watch_insane_miner:s_7c3e9069", "wont_help"}, -- You are a danger to everyone and need to be taken down.
	}
}
deathWatchInsaneMinerConvoTemplate:addScreen(return_intro);

must_hurry = ConvoScreen:new {
	id = "must_hurry",
	leftDialog = "@conversation/death_watch_insane_miner:s_2efed805", -- You must hurry! I cannot hold onto my sanity for very much longer.
	stopConversation = "true",
	options = {}
}
deathWatchInsaneMinerConvoTemplate:addScreen(must_hurry);

addConversationTemplate("deathWatchInsaneMinerConvoTemplate", deathWatchInsaneMinerConvoTemplate);