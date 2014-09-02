require("screenplays.record_keepers.record_keeper")


dantooine_static = RecordKeeper:new {
	keeperName ="dantooine",
	-- we skip the ris armor quests as it doesnt use a theme park logic
	quests = {
		drakka_judarrl_quest="DrakkaJudarrl", 
		jatrian_lytus_quest="JatrianLytus", 
		kelvus_naria_quest="KelvusNaria", 
		luthik_uwyr_quest="LuthikUwyr", 
		lx_466_quest="LX466", 
		sg_567_quest="SG567", 
		stoos_olko_quest="StoosOlko", 
		xaan_talmaron_quest="XaanTalmaron"
	},
	faction = 0	
}
dantooine_static_record_keeper_convo_handler = record_keeper_conv_handler:new {
	keeper = dantooine_static
}

