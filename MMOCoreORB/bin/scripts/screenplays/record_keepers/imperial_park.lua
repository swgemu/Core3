require("screenplays.record_keepers.record_keeper")


imperial_park = RecordKeeper:new {
	keeperName ="imperial_park",
	quests = { theme_park_imperial="ThemeParkImperial"},
	faction = FACTIONIMPERIAL	
}
imperial_park_record_keeper_convo_handler = record_keeper_conv_handler:new {
	keeper = imperial_park
}
