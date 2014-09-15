require("screenplays.record_keepers.record_keeper")


tatooine_static = RecordKeeper:new {
	keeperName ="tatooine",
	quests = {
		aaph_koden_quest ="AaphKoden",
		blerx_tango_quest="BlerxTango",
		bren_kingal_quest="BrenKingal",
		farious_gletch_quest="FariousGletch",
		fixer_quest="Fixer",
		gramm_rile_quest="GrammRile",
		hedon_istee_task="HedonIstee",
		ikka_gesul_quest="IkkaGesul",
		jilljoo_jab_quest="JilljooJab",
		kaeline_ungasan_quest="KaelineUngasan",
		kitster_banai_quest="KitsterBanai",
		kormund_thrylle_quest="KormundThrylle",
		lorne_prestar_quest="LornePrestar",
		lt_harburik_quest="LtHarburik",
		mat_rags_quest="MatRags",
		nitra_vendallan_quest="NitraVendallan",
		om_aynat_task="OmAynat",
		pfilbee_jhorn_quest="PfilbeeJhorn",
		phinea_shantee_quest="PhineaShantee",
		prefect_talmont_quest="PrefectTalmont",
		rakir_banai_task="RakirBanai",
		stella_task="Stella",
		tekil_barje_task="TekilBarje",
		tolan_nokkar_quest="TolanNokkar",
		vardias_tyne_quest="VardiasTyne"
	},
	faction = 0	
}
 tatooine_static_record_keeper_convo_handler = record_keeper_conv_handler:new {
	keeper = tatooine_static
}
