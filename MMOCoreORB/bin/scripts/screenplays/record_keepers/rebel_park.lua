require("screenplays.record_keepers.record_keeper")


rebel_park = RecordKeeper:new {
	keeperName ="rebel_park",
	quests = {theme_park_rebel = "ThemeParkRebel"},
	faction = FACTIONREBEL
}
rebel_park_record_keeper_convo_handler = record_keeper_conv_handler:new {
	keeper = rebel_park
}