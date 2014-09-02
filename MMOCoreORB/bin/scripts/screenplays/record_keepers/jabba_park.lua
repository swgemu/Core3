require("screenplays.record_keepers.record_keeper")


jabba_park = RecordKeeper:new {
	keeperName ="jabba_park",
	quests = {theme_park_jabba="ThemeParkJabba"},
	faction = 0
}

jabba_park_record_keeper_convo_handler = record_keeper_conv_handler:new {
	keeper = jabba_park
}
