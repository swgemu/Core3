bestineArtist01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_museum_artist_conv_handler",
	screens = {}
}

init_curvote = ConvoScreen:new {
	id = "init_curvote",
	leftDialog = "@conversation/bestine_artist01:s_7afc26f5", -- Yes, I'll pay... I'll pay. Wait a minute... who are you? Look, I'm busy. I don't really have time to talk right now.
	stopConversation = "false",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(init_curvote);

init_wonvote = ConvoScreen:new {
	id = "init_wonvote",
	leftDialog = "@conversation/bestine_artist01:s_b7a88f36", -- Are you here to collect a debt? No fear... I've got a work of art that's being featured in the Bestine Museum. It can't be long before riches follow. Oh, you're not here about money... well, even better. 
	stopConversation = "false",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(init_wonvote);

init_novote = ConvoScreen:new {
	id = "init_novote",
	leftDialog = "@conversation/bestine_artist01:s_506f2192", -- Are you from the debt collector? I've barely a few credits to my name at the moment, so you'll get nothing from me. Begone.
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(init_novote);

passby_response_curvote = ConvoScreen:new {
	id = "passby_response_curvote",
	leftDialog = "@conversation/bestine_artist01:s_e60617b5", -- Oh. Okay then. I apologize. It's just that... well, no point in going into the dirty little details. Let's just forget the whole thing. 
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(passby_response_curvote);

passby_response_wonvote = ConvoScreen:new {
	id = "passby_response_wonvote",
	leftDialog = "@conversation/bestine_artist01:s_62dd13f8", -- Just wait and see... my time has come. You'll see. Soon I'll be famous all across the galaxy. Well, maybe not on Dantooine... but no one there really matters anyway. 
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(passby_response_wonvote);

painting_response_wonvote = ConvoScreen:new {
	id = "painting_response_wonvote",
	leftDialog = "@conversation/bestine_artist01:s_62dd13f8", -- Oh... well then let me tell you about my work. In my paintings, I bring to life the image of a single plant in each of my paintings. These are mostly plants I've encountered in youth when I was more of a traveller. My work is painterly, yet accurately depicts its subject.
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(painting_response_wonvote);

painting_response_wonvote_prev = ConvoScreen:new {
	id = "painting_response_wonvote_prev",
	leftDialog = "@conversation/bestine_artist01:s_22e081ab", -- Wait... I remember you. You asked about my artwork recently. I guess if you want to hear it again, there's no harm to me. In my paintings, I bring to life the image of a single plant in each of my paintings. These are mostly plants I've encountered in youth when I was more of a traveller. My work is painterly, yet accurately depicts its subject.
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(painting_response_wonvote_prev);

painting_response_curvote = ConvoScreen:new {
	id = "painting_response_curvote",
	leftDialog = "@conversation/bestine_artist01:s_f58736af", -- Oh... well... why didn't you say so earlier. In my paintings, I bring to life the image of a single plant in each of my paintings. These are mostly plants I've encountered in youth when I was more of a traveller. My work is painterly, yet accurately depicts its subject. 
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(painting_response_curvote);

painting_response_curvote_prev = ConvoScreen:new {
	id = "painting_response_curvote_prev",
	leftDialog = "@conversation/bestine_artist01:s_378506ca", -- Wait... I remember you. You mentioned that once before. Guess there's no harm in saying it again. In my paintings, I bring to life the image of a single plant in each of my paintings. These are mostly plants I've encountered in youth when I was more of a traveller. My work is painterly, yet accurately depicts its subject.
	stopConversation = "true",
	options = {}
}
bestineArtist01ConvoTemplate:addScreen(painting_response_curvote_prev);

addConversationTemplate("bestineArtist01ConvoTemplate", bestineArtist01ConvoTemplate);