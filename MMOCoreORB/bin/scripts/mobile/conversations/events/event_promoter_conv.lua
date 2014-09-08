eventPromoterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "eventPromoterConvoHandler",
	screens = {}
}

welcome = ConvoScreen:new {
	id = "welcome",
	leftDialog = "@conversation/event_promoter:s_4", -- Welcome to my shop! I rent a number of goods including decorations, venues, stand alone games and supplies. You can even hire personnel! Our reproductions are of the highest quality and are difficult to distinguish from the real thing. We have everything you need to ensure your event will be a memorable one.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_9", "explain_more"}, -- Tell me more about all of this
		{"@conversation/event_promoter:s_11", "interested_decorations"}, -- I'm interested in decorations
--		{"@conversation/event_promoter:s_26", "interested_venues"}, -- I'm interested in venues
--		{"@conversation/event_promoter:s_42", "interested_games_supplies"}, -- I'm interested in games and supplies
--		{"@conversation/event_promoter:s_80", "interested_personnel"}, -- I'm interested in hiring personnel
	}
}
eventPromoterConvoTemplate:addScreen(welcome);

explain_more = ConvoScreen:new {
	id = "explain_more",
	leftDialog = "@conversation/event_promoter:s_10", -- For a modest sum, you can rent supplies for use in your personal events. Most items rented are received in the form of a deed. Simply deploy the deed in any wilderness area or city that has allowed you zoning rights to set it up. You may rent up to five deeds at a time. The term of rental in most cases is 8 hours starting at the time of purchase. All equipment is automatically returned after that time.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_11", "interested_decorations"}, -- I'm interested in decorations
--		{"@conversation/event_promoter:s_26", "interested_venues"}, -- I'm interested in venues
--		{"@conversation/event_promoter:s_42", "interested_games_supplies"}, -- I'm interested in games and supplies
--		{"@conversation/event_promoter:s_80", "interested_personnel"}, -- I'm interested in hiring personnel
	}
}
eventPromoterConvoTemplate:addScreen(explain_more);

more_about_games_supplies = ConvoScreen:new {
	id = "more_about_games_supplies",
	leftDialog = "@conversation/event_promoter:s_48", -- What are you interested in hearing more about?
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_62", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(more_about_games_supplies);

explain_capture_the_flag_game = ConvoScreen:new {
	id = "explain_capture_the_flag_game",
	leftDialog = "@conversation/event_promoter:s_52", -- When you deploy the deed for this game a neutral flag is created where you stand. You will be able to specify a time limit for the game. When the game starts, overt members of a faction may attempt to capture the flag and change it to their own. The one who holds the flag for the longest wins the game. Multiple games may be run during rental period.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_62", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(explain_capture_the_flag_game);

explain_lottery_droid = ConvoScreen:new {
	id = "explain_lottery_droid",
	leftDialog = "@conversation/event_promoter:s_60", -- The lottery droid will allow you to run a lottery. You can set how long the lottery will run, registration cost and percentage of the total purse that will be paid out. Registration fees are added to the purse. You may also sweeten the pot with your own credits. When the lottery ends, a winner is chosen. Funds are automatically transferred to the winner and any percentage of the pot set aside as the owner's take is also transferred.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_62", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(explain_lottery_droid);

explain_scavenger_hunt_droid = ConvoScreen:new {
	id = "explain_scavenger_hunt_droid",
	leftDialog = "@conversation/event_promoter:s_64", -- This droid will allow you to setup and run a scavenger hunt. When deployed, you will show the droid a number of items you would like your participants to find. When the droid is initialized, the game begins. The first one to find all of the items wins.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(explain_scavenger_hunt_droid);

explain_treasure_chest = ConvoScreen:new {
	id = "explain_treasure_chest",
	leftDialog = "@conversation/event_promoter:s_68", -- A variety of styles of chests are available. Styles range from a standard container, to those with special effects and even a very realistic humanoid skeleton. You may place the chest in the wilderness or in any city that has allowed you zoning rights. You (and only you) may add items to the chest. Anyone happening along the chest may take one item from it.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_62", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(explain_treasure_chest);

explain_shuttle_beacon = ConvoScreen:new {
	id = "explain_shuttle_beacon",
	leftDialog = "@conversation/event_promoter:s_72", -- The shuttle beacon is a special effects utility that will allow you to call down one of a number of shuttles. You can use the shuttle beacon to have a shuttle land and then to order the shuttle to take off again. Shuttles may be called for the duration of the rental term.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_62", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_109", "explain_jukebox"}, -- How does the jukebox work?
	}
}
eventPromoterConvoTemplate:addScreen(explain_shuttle_beacon);

explain_honor_guard = ConvoScreen:new {
	id = "explain_honor_guard",
	leftDialog = "@conversation/event_promoter:s_86", -- An honor guard is military style formation of actors, dressed in one of a variety of authentic looking official dress, who will stand at attention for your event. They come in a variety of numbers and formations.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_100", "sale_personnel"}, -- Hire Personnel
		{"@conversation/event_promoter:s_104", "sale_imperial_personnel"}, -- Hire Imperial Personnel
		{"@conversation/event_promoter:s_108", "sale_rebel_personnel"}, -- Hire Alliance Personnel
		{"@conversation/event_promoter:s_88", "explain_hired_actor"}, -- What can a hired actor do?
	}
}
eventPromoterConvoTemplate:addScreen(explain_honor_guard);

explain_hired_actor = ConvoScreen:new {
	id = "explain_hired_actor",
	leftDialog = "@conversation/event_promoter:s_90", -- A hired actor can be deployed anywhere in the wilderness or in a city that has given you zoning rights. You can select the name, race and stage name the actor will use. You may also dress the actor as you see fit and give the actor a line to say. The actor will repeat their line to any that happen across them.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_100", "sale_personnel"}, -- Hire Personnel
		{"@conversation/event_promoter:s_104", "sale_imperial_personnel"}, -- Hire Imperial Personnel
		{"@conversation/event_promoter:s_108", "sale_rebel_personnel"}, -- Hire Alliance Personnel
		{"@conversation/event_promoter:s_84", "explain_honor_guard"}, -- What is an Honor Guard?
	}
}
eventPromoterConvoTemplate:addScreen(explain_hired_actor);

explain_jukebox = ConvoScreen:new {
	id = "explain_jukebox",
	leftDialog = "@conversation/event_promoter:s_110", -- When purchased you will recieve a jukebox in your inventory. You can then drop the jukebox in your home or any other structure you have access rights too. After placing the jukebox, you can use it and select a song to play. Anyone entering the room will hear the music. The jukebox rental term is eight hours, after which it will expire.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_30", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_50", "explain_capture_the_flag_game"}, -- What is the Capture the Flag Game?
		{"@conversation/event_promoter:s_58", "explain_lottery_droid"}, -- What is the Lottery Droid?
		{"@conversation/event_promoter:s_64", "explain_scavenger_hunt_droid"}, -- What is the Scavenger Hunt Droid?
		{"@conversation/event_promoter:s_66", "explain_treasure_chest"}, -- What is the Treasure Chest?
		{"@conversation/event_promoter:s_70", "explain_shuttle_beacon"}, -- What is the Shuttle Beacon?
	}
}
eventPromoterConvoTemplate:addScreen(explain_jukebox);

interested_decorations = ConvoScreen:new {
	id = "interested_decorations",
	leftDialog = "@conversation/event_promoter:s_12", -- Decorations are simply single items ranging from flags to reproductions of vehicles and other equipment. When you purchase a decoration, simply move to the location where you would like to place it and deploy. The decoration will be placed where you stand.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_14", "sale_decorations"}, -- Rent Decorations
		{"@conversation/event_promoter:s_18", "sale_imperial_decorations"}, -- Rent Imperial Themed Decorations
		{"@conversation/event_promoter:s_22", "sale_rebel_decorations"}, -- Rent Alliance Themed Decorations
	}
}
eventPromoterConvoTemplate:addScreen(interested_decorations);

interested_venues = ConvoScreen:new {
	id = "interested_venues",
	leftDialog = "@conversation/event_promoter:s_28", -- Venues are full set designs and include things such as performance stages, wedding pavilions and even realistic military exhibitions. Some venues also include hired personnel as part of the package. When deployed, your venue will be automatically arranged at a location close to where you used the deed.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_30", "sale_venues"}, -- Rent Venue
		{"@conversation/event_promoter:s_34", "sale_imperial_venues"}, -- Rent Imperial Themed Venue
		{"@conversation/event_promoter:s_38", "sale_rebel_venues"}, -- Rent Rebel Themed Venue
	}
}
eventPromoterConvoTemplate:addScreen(interested_venues);

interested_games_supplies = ConvoScreen:new {
	id = "interested_games_supplies",
	leftDialog = "@conversation/event_promoter:s_44", -- These include stand alone gaming devices as well as supplies to help you with running your own games or events. These include various gaming droids, beacons to call shuttles and chests that you can stock, place and hide for others to find.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_76", "sale_games_supplies"}, -- Rent Games and Supplies
		{"@conversation/event_promoter:s_46", "more_about_games_supplies"}, -- Tell me more about games and supplies.
	}
}
eventPromoterConvoTemplate:addScreen(interested_games_supplies);

interested_personnel = ConvoScreen:new {
	id = "interested_personnel",
	leftDialog = "@conversation/event_promoter:s_82", -- Here is what I have to offer.
	stopConversation = "false",
	options = {
		{"@conversation/event_promoter:s_100", "sale_personnel"}, -- Hire Personnel
		{"@conversation/event_promoter:s_104", "sale_imperial_personnel"}, -- Hire Imperial Personnel
		{"@conversation/event_promoter:s_108", "sale_rebel_personnel"}, -- Hire Alliance Personnel
		{"@conversation/event_promoter:s_84", "explain_honor_guard"}, -- What is an Honor Guard?
		{"@conversation/event_promoter:s_88", "explain_hired_actor"}, -- What can a hired actor do?
	}
}
eventPromoterConvoTemplate:addScreen(interested_personnel);

sale_decorations = ConvoScreen:new {
	id = "sale_decorations",
	leftDialog = "@conversation/event_promoter:s_16", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_decorations);

sale_imperial_decorations = ConvoScreen:new {
	id = "sale_imperial_decorations",
	leftDialog = "@conversation/event_promoter:s_20", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_imperial_decorations);

sale_rebel_decorations = ConvoScreen:new {
	id = "sale_rebel_decorations",
	leftDialog = "@conversation/event_promoter:s_24", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_rebel_decorations);

sale_venues = ConvoScreen:new {
	id = "sale_venues",
	leftDialog = "@conversation/event_promoter:s_32", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_venues);

sale_imperial_venues = ConvoScreen:new {
	id = "sale_imperial_venues",
	leftDialog = "@conversation/event_promoter:s_36", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_imperial_venues);

sale_rebel_venues = ConvoScreen:new {
	id = "sale_rebel_venues",
	leftDialog = "@conversation/event_promoter:s_40", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_rebel_venues);

sale_games_supplies = ConvoScreen:new {
	id = "sale_games_supplies",
	leftDialog = "@conversation/event_promoter:s_78", -- Here is what I have to offer.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_games_supplies);

sale_personnel = ConvoScreen:new {
	id = "sale_personnel",
	leftDialog = "@conversation/event_promoter:s_102", -- This is who we have available.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_personnel);

sale_imperial_personnel = ConvoScreen:new {
	id = "sale_imperial_personnel",
	leftDialog = "@conversation/event_promoter:s_102", -- This is who we have available.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_imperial_personnel);

sale_rebel_personnel = ConvoScreen:new {
	id = "sale_rebel_personnel",
	leftDialog = "@conversation/event_promoter:s_102", -- This is who we have available.
	stopConversation = "true",
	options = {}
}
eventPromoterConvoTemplate:addScreen(sale_rebel_personnel);

addConversationTemplate("eventPromoterConvoTemplate", eventPromoterConvoTemplate);