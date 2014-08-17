bestineArtist05ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist05:s_b31048ea", -- Greetings. I'm afraid I have little to offer you as I am but an impoverished artist.
	stopConversation = "false",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist05:s_3671ce2c", -- Greetings my friend. Times are good. I have a painting being featured at the Bestine Museum. 
	stopConversation = "false",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist05:s_b31048ea", -- Greetings. I'm afraid I have little to offer you as I am but an impoverished artist.
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist05:s_b5220a73", -- Not even that. I'm scraping together every bit I can just to purchase my painting supplies. At this rate I'll be stuck in this sand ball forever. 
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist05:s_74b54572", -- Indeed. I'm hoping to earn enough money to travel once again. I'd like to see more of the galaxy if I can. 
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist05:s_55a9443f", -- Truly?! Perhaps they would like another of my paintings. I do still life paintings. Usually, just of plants in the wild, because... well... those don't cost anything. I guess that could be considered a landscape painting, but I don't paint much more than just the plant.
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist05:s_991f684c", -- You return to hear about my paintings again? Wouldn't it be easier to just go see the one at the Bestine Museum? I do still life paintings. Usually, just of plants in the wild, because... well... those don't cost anything. I guess that could be considered a landscape painting, but I don't paint much more than just the plant.
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist05:s_4af78c89", -- Truly?! Perhaps they would like my paintings. I do still life paintings. Usually, just of plants in the wild, because... well... those don't cost anything. I guess that could be considered a landscape painting, but I don't paint much more than just the plant.
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist05:s_f4165153", -- Seems like we've done this already. Once before. Once again? Very well. I do still life paintings. Usually, just of plants in the wild, because... well... those don't cost anything. I guess that could be considered a landscape painting, but I don't paint much more than just the plant.
	stopConversation = "true",
	options = {}
}
bestineArtist05ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist05ConvoTemplate", bestineArtist05ConvoTemplate);