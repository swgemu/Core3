bestineArtist03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist03:s_1054ba24", -- Greetings friends. Have you heard about the time I crossed the Dune Sea without drinking even a single drop of water? Ha...who needs water when you've got a good Corellian ale!
	stopConversation = "false",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist03:s_a9fe5eb6", -- Hello. Have you heard about the time one of my paintings was featured in the Bestine Museum? That time is now! I encourage you to rush to Bestine and see for yourself.
	stopConversation = "false",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist03:s_77b94789", -- Greetings friends. Have you heard about the time I tricked an underling of Jabba into giving me his money? Who needs a bank account with all the gullible thugs Jabba employs.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist03:s_14cd5816", -- Oh, well then have you heard about the time I single-handedly defeated an entire unit of stormtroopers? It's true... they're really terrible at sabacc.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist03:s_ae2d8845", -- Oh sure. Closest thing this planet has to an art museum. Though, have you heard about the time I tried to open an art gallery for Tusken Raiders? Ends up they really don't like art. Or maybe it was just me... I'm not sure.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist03:s_b53cc4bf", -- How could I not leap at the chance yet again! Well, as someone who enjoys exploring this waste of a planet, I've sometimes used painting as a journal of sorts to memorialize things I've seen. Those that truly made an impression on me and are unique to Tatooine.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist03:s_77eb5b90", -- Have we talked about this already? You want to hear it again? Okay. As someone who enjoys exploring this waste of a planet, I've sometimes used painting as a journal of sorts to memorialize things I've seen. Those that truly made an impression on me and are unique to Tatooine.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist03:s_46c7e15a", -- Say no more. As someone who enjoys exploring this waste of a planet, I've sometimes used painting as a journal of sorts to memorialize things I've seen. Those that truly made an impression on me and are unique to Tatooine.
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist03:s_1eebe4c5", -- Do you get the feeling we've done this before? Anyway, as someone who enjoys exploring this waste of a planet, I've sometimes used painting as a journal of sorts to memorialize things I've seen. Those that truly made an impression on me and are unique to Tatooine. 
	stopConversation = "true",
	options = {}
}
bestineArtist03ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist03ConvoTemplate", bestineArtist03ConvoTemplate);