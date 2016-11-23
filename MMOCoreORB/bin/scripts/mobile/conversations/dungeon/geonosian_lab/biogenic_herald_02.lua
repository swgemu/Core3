biogenicHerald2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "biogenic_herald2_conv_handler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/biogenic_herald_02:s_41db0c1b", -- Unless you have official Imperial business, I suggest that you move along.
	stopConversation = "true",
	options = {}
}
biogenicHerald2ConvoTemplate:addScreen(no_faction);

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/biogenic_herald_02:s_9c1f1aa9", -- Ah, excellent. I'm glad that you're here. I have an assignment that I need to delegate, and you look like you would be prefect for the task.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_d029dd34", "not_an_order"}, -- What is it that you would have me do?
		{"@conversation/biogenic_herald_02:s_66a4dded", "suggest_return"}, -- I don't have time for menial tasks, sorry.
	}
}
biogenicHerald2ConvoTemplate:addScreen(init);

suggest_return = ConvoScreen:new {
	id = "suggest_return",
	leftDialog = "@conversation/biogenic_herald_02:s_40cc2c96", -- Alright, but I suggest that you return when you get a chance. As a loyal servant of the Empire, I'm sure that you do not want to displease your superiors.
	stopConversation = "true",
	options = {}
}
biogenicHerald2ConvoTemplate:addScreen(suggest_return);

not_an_order = ConvoScreen:new {
	id = "not_an_order",
	leftDialog = "@conversation/biogenic_herald_02:s_16124dd5", -- This is not an official order, but rather a simple reconnaissance assignment. We're concerned about one of our agents stationed on Yavin IV. I'll give you some more details if you take the assignment. Do you accept?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_8d4bd762", "excellent"}, -- Yes, I will accept.
		{"@conversation/biogenic_herald_02:s_657f5904", "suggest_reconsider"}, -- No, I will decline.
	}
}
biogenicHerald2ConvoTemplate:addScreen(not_an_order);

suggest_reconsider = ConvoScreen:new {
	id = "suggest_reconsider",
	leftDialog = "@conversation/biogenic_herald_02:s_87f743f", -- Alright, but I suggest you reconsider. As a loyal servant of the Empire, I'm sure that you don't want to displease your superiors.
	stopConversation = "true",
	options = {}
}
biogenicHerald2ConvoTemplate:addScreen(suggest_reconsider);

excellent = ConvoScreen:new {
	id = "excellent",
	leftDialog = "@conversation/biogenic_herald_02:s_86248d8c", -- Most excellent. Your superiors will be pleased. Now for the details. We have had an agent stationed on Yavin IV for a while now. He was tasked with observing a hidden Geonosian bio-genetics facility.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_9288900f", "supposed_to_report"}, -- I understand.
		{"@conversation/biogenic_herald_02:s_edb238bc", "supposed_to_report"}, -- Go on.
	}
}
biogenicHerald2ConvoTemplate:addScreen(excellent);

supposed_to_report = ConvoScreen:new {
	id = "supposed_to_report",
	leftDialog = "@conversation/biogenic_herald_02:s_c6f4650", -- The agent is supposed to report in at regular intervals but we have not heard from him in quite a while. We suspect that he might have been kidnapped by the Geonosians, who may be now working in league with the Rebellion.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_d736fda3", "travel_to_yavin"}, -- Please continue.
		{"@conversation/biogenic_herald_02:s_373c8ad", "travel_to_yavin"}, -- So what is it you want me to do?
	}
}
biogenicHerald2ConvoTemplate:addScreen(supposed_to_report);

travel_to_yavin = ConvoScreen:new {
	id = "travel_to_yavin",
	leftDialog = "@conversation/biogenic_herald_02:s_978ff349", -- We want you to travel to Yavin IV, find the hidden bio-genetics laboratory, and see what happened to our agent. Unfortunately we do not know specifically where the compound is.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_678d7eec", "mining_outpost"}, -- So how do I find the facility?
	}
}
biogenicHerald2ConvoTemplate:addScreen(travel_to_yavin);

mining_outpost = ConvoScreen:new {
	id = "mining_outpost",
	leftDialog = "@conversation/biogenic_herald_02:s_ee774a3d", -- Our missing agent is the only one who knew exactly where it is. Why don't you go to the Mining Outpost on Yavin IV to try and get some leads. See if the locals there have seen or noticed anything out of the ordinary.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_herald_02:s_9326b612", "when_you_do"}, -- I will see if I can find your missing agent.
	}
}
biogenicHerald2ConvoTemplate:addScreen(mining_outpost);

when_you_do = ConvoScreen:new {
	id = "when_you_do",
	leftDialog = "@conversation/biogenic_herald_02:s_8f9bb5cc", -- When you do, we will send a team to the bio-genetics facility to deal with the traitorous Geonosians. Good luck on your assignment.
	stopConversation = "true",
	options = {}
}
biogenicHerald2ConvoTemplate:addScreen(when_you_do);

addConversationTemplate("biogenicHerald2ConvoTemplate", biogenicHerald2ConvoTemplate);
