heroOfTatPirateLeaderConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatPirateLeaderConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_7557e310", -- Whoa! Hold on! I give up! Whew... you're pretty tough, my friend. In fact... you'd be the perfect person to help us in our little dilemma we've been facing. Right boys? Are you interested in a little task we have for you?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_446af42e", "little_skeptical"}, -- First, what's the task?
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_a6c6f57b", "lets_get_em"}, -- No! Die, fools!
	}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(intro);

little_skeptical = ConvoScreen:new {
	id = "little_skeptical",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_256d8f99", -- Little skeptical, eh? I guess I don't blame you. After all, we are pirates! Har, Har! Oh--the task, right. Some of our boys were looting a rancher's house when he walked in. He and his wife are holding our boys captive. We want you to go and help them escape. Well, what do you think?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_48566ef9", "be_in_debt"}, -- What's in it for me?
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_abc7e09d", "is_that_so"}, -- I think they deserved it. Nope, I won't help you.
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_34bde7db", "made_me_happy"}, --I guess I'll help you out.
	}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(little_skeptical);

lets_get_em = ConvoScreen:new {
	id = "lets_get_em",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_cacfa6a2", -- I guess I was mistaken. Boys, let's show this peasant how real pirates plunder! Get 'em!
	stopConversation = "true",
	options = {}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(lets_get_em);

be_in_debt = ConvoScreen:new {
	id = "be_in_debt",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_4575b29e", -- We'll be in debt to you. That's all we can offer. There might be some loot still left at the house.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_da25a2d9", "teach_a_lesson"}, -- Bad deal. No, I won't help you.
		{"@conversation/quest_hero_of_tatooine_pirate_leader:s_d57d668a", "be_quick"}, -- Yeah, I'll help.
	}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(be_in_debt);

is_that_so = ConvoScreen:new {
	id = "is_that_so",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_5a3d905f", -- Oh, is that so? Time to be taught a lesson. Boys!
	stopConversation = "true",
	options = {}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(is_that_so);

made_me_happy = ConvoScreen:new {
	id = "made_me_happy",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_543c2619", -- You just made an old pirate happy. The location of the house is around here somewhere. I marked it on your map. Be careful. Them ranchers aren't the nicest people in the galaxy. But then again, neither are we! HA HA! Oh, and don't come looking for us. You won't find us here. We pirates like to keep ourselves "on the go" if you know what I mean. Now, scram!
	stopConversation = "true",
	options = {}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(made_me_happy);

teach_a_lesson = ConvoScreen:new {
	id = "teach_a_lesson",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_d9706ae2", -- Won't help us? Boys, let's teach this peasant a lesson for wasting our time.
	stopConversation = "true",
	options = {}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(teach_a_lesson);

be_quick = ConvoScreen:new {
	id = "be_quick",
	leftDialog = "@conversation/quest_hero_of_tatooine_pirate_leader:s_e30e7484", -- Good. The rancher's house is around this location. I've marked in on your map. Be quick about it. Oh, and don't come looking for me after the deed is done. We pirates don't stay in the same place for long.
	stopConversation = "true",
	options = {}
}
heroOfTatPirateLeaderConvoTemplate:addScreen(be_quick);

addConversationTemplate("heroOfTatPirateLeaderConvoTemplate", heroOfTatPirateLeaderConvoTemplate);