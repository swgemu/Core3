bestineArtist02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist02:s_5722b971", -- Hello. Sit and have a drink with me.
	stopConversation = "false",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist02:s_5b1aeaab", -- Hello. Did you know I have a painting in the Bestine Museum? It's true. I'm trying to be humble, but I've never been so proud of myself.
	stopConversation = "false",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist02:s_4823f472", -- Hello Friend. Slow down a bit and enjoy the day.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist02:s_707098b5", -- Er... um... on second thought, maybe I'd be better off drinking alone.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist02:s_8f58f4f9", -- Thank you. I encourage you to go see my painting. I did mention that it's in the Bestine Museum, yes?
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist02:s_5b1a751", -- Yet another opportunity! I always wanted to design buildings, but never had the motivation to take the steps necessary to actually become an architect. Instead, I do paintings of buildings. Not quite the same thing, but I find it satisfying.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist02:s_9467cd8b", -- Wait, didn't we already... I mean... ah nevermind. I always wanted to design buildings, but never had the motivation to take the steps necessary to actually become an architect. Instead, I do paintings of buildings. Not quite the same thing, but I find it satisfying.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist02:s_3a6247ed", -- How exciting! I've been involved in such things before and always enjoy the opportunity. I always wanted to design buildings, but never had the motivation to take the steps necessary to actually become an architect. Instead, I do paintings of buildings. Not quite the same thing, but I find it satisfying.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist02:s_1fa7f38", -- Didn't you already ask me about that? Oh well... I always wanted to design buildings, but never had the motivation to take the steps necessary to actually become an architect. Instead, I do paintings of buildings. Not quite the same thing, but I find it satisfying.
	stopConversation = "true",
	options = {}
}
bestineArtist02ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist02ConvoTemplate", bestineArtist02ConvoTemplate);