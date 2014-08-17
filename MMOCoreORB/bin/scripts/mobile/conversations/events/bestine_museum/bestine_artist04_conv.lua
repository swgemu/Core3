bestineArtist04ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist04:s_71aaaca6", -- Why do you bother Kahfr? Kahfr is a great artist and is very busy.
	stopConversation = "false",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist04:s_17cd5bb6", -- You must experience Kahfr's painting. Kahfr's artwork graces the walls of the Museum in Bestine. Kahfr is a great artist!
	stopConversation = "false",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist04:s_d4ede5f2", -- Do not bother Kahfr? Kahfr is a great artist and is very busy. You must go now.
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist04:s_7766385", -- Kahfr is impressed by your understanding. Kahfr thanks you and bids you farewell. Though Kahfr wonders if this is sarcasm...  
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist04:s_179635e7", -- Kahfr does not understand why you are saying that. Kahfr thinks perhaps you've been wandering the Dune Sea for too long.
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist04:s_cf179f96", -- Kahfr is interested. Kahfr has long expected such an honor as is her due. Kahfr's art is the art of people. Faces. Right now Mon Calamari faces. Taken out of context, a person's face can be quite abstract. This is what Kahfr does. 
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist04:s_bf1648b1", -- Kahfr thinks you've asked that before. But Kahfr does not mind. Kahfr's art is the art of people. Faces. Right now Mon Calamari faces. Taken out of context, a person's face can be quite abstract. This is what Kahfr does.
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist04:s_cf179f96", -- Kahfr is interested. Kahfr has long expected such an honor as is her due. Kahfr's art is the art of people. Faces. Right now Mon Calamari faces. Taken out of context, a person's face can be quite abstract. This is what Kahfr does.
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist04:s_40f271aa", -- You ask Kahfr again? Always Kahfr must repeat herself. Kahfr's art is the art of people. Faces. Right now Mon Calamari faces. Taken out of context, a person's face can be quite abstract. This is what Kahfr does.
	stopConversation = "true",
	options = {}
}
bestineArtist04ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist04ConvoTemplate", bestineArtist04ConvoTemplate);