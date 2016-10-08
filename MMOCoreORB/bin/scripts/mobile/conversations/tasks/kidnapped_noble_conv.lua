kidnappedNobleConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "kidnappedNobleConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@theme_park/royal_kidnapping/nobles:start", -- Ach! Another wretched pirate. You'll never get away with this! You filthy disease-ridden scum will pay! Pay dearly! I have friends in powerful places! Poweful friends in powerful places! That's right! Poweful! They know how to deal with the likes of you!
	stopConversation = "false",
	options = {
		{"@theme_park/royal_kidnapping/nobles:reply_1", "of_course"}, -- I'm not a pirate. I'm here to rescue you.
	}
}
kidnappedNobleConvoTemplate:addScreen(init);

of_course = ConvoScreen:new {
	id = "of_course",
	leftDialog = "@theme_park/royal_kidnapping/nobles:noble_1", -- You're not? Oh, well, I mean of course you're not. I knew that. I could tell just by looking at you. You have that heroic sort of aura about you. Indeed you do.
	stopConversation = "false",
	options = {
		{"@theme_park/royal_kidnapping/nobles:noble_1_reply_1", "my_hero"}, -- You're free to go
	}
}
kidnappedNobleConvoTemplate:addScreen(of_course);

my_hero = ConvoScreen:new {
	id = "my_hero",
	leftDialog = "@theme_park/royal_kidnapping/nobles:noble_2", -- Hooray! You're my hero!
	stopConversation = "true",
	options = {}
}
kidnappedNobleConvoTemplate:addScreen(my_hero);

addConversationTemplate("kidnappedNobleConvoTemplate", kidnappedNobleConvoTemplate);
