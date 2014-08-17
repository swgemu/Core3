bestineArtist06ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist06:s_8a659170", -- Expand you mind, my friend. There's more to see than what your eyes tell you.
	stopConversation = "false",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist06:s_bf3a373", -- Open your eyes! New visions of the world are all around you. If nothing else, you should be to go to the Bestine Museum and see my painting on display there.
	stopConversation = "false",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist06:s_54e93392", -- Don't close yourself off... there's more to see than what your eyes tell you.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist06:s_7154d52c", -- Arrgh... not with Corellian ale or spice! Open yourself to news ways of experiencing the galaxy. Don't just blindly follow your feet. Truly see to truly know.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist06:s_30df2fe8", -- And that's as a painter, I surely hope. But it's a good start... that is, if you're truly looking and not just humoring me.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist06:s_23697fe2", -- And naturally they desire another of mine. I paint common subjects in abstraction. My goal isn't to replicate the look of my subjects, but rather to use their shapes to find higher art. For me, the petals of a flower are simply organic shapes used in my composition.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist06:s_66605741", -- Forgotten me already? You were just here. Truly, you move through the world with your mind closed. I paint common subjects in abstraction. My goal isn't to replicate the look of my subjects, but rather to use their shapes to find higher art. For me, the petals of a flower are simply organic shapes used in my composition.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist06:s_29026317", -- And they are considering mine? Glorious! I paint common subjects in abstraction. My goal isn't to replicate the look of my subjects, but rather to use their shapes to find higher art. For me, the petals of a flower are simply organic shapes used in my composition.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist06:s_582eefe3", -- Right... we've already gone over this as you would know if you weren't so closed off. I paint common subjects in abstraction. My goal isn't to replicate the look of my subjects, but rather to use their shapes to find higher art. For me, the petals of a flower are simply organic shapes used in my composition.
	stopConversation = "true",
	options = {}
}
bestineArtist06ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist06ConvoTemplate", bestineArtist06ConvoTemplate);