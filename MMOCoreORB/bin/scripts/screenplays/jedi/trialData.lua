TRIAL_LIGHTSABER = 1
TRIAL_TALK = 2
TRIAL_KILL = 3
TRIAL_HUNT = 4
TRIAL_HUNT_FACTION = 5
TRIAL_COUNCIL = 6

padawanTrialQuests = {
	{
		trialName = "architect",
		trialType = TRIAL_TALK,
		trialNpc = "devaronian_male",
		trialNpcName = "Kant Graf (an architect)",
		targetNpc = "trials_gungan_captain",
		targetKillable = true
	},
	{
		trialName = "artist",
		trialType = TRIAL_TALK,
		trialNpc = "bestine_rumor12",
		trialNpcName = "Sathme Forr (an artist)",
		targetNpc = "commoner",
		targetKillable = false
	},
	{
		trialName = "bad_cat",
		trialType = TRIAL_KILL,
		trialNpc = "bestine_capitol02",
		trialNpcName = "Yvana Bailer (an actor)",
		targetNpc = "bloodstained_prowler",
		targetKillable = true
	},
	{
		trialName = "chef",
		trialType = TRIAL_TALK,
		trialNpc = "dannik_malaan",
		trialNpcName = "Seevi Nyed (a chef)",
		targetNpc = "neo_cobral_overlord",
		targetKillable = true
	},
	{
		trialName = "craft_lightsaber",
		trialType = TRIAL_LIGHTSABER,
	},
	{
		trialName = "kill_baz_nitch",
		trialType = TRIAL_HUNT,
		trialNpc = "sullustan_male",
		trialNpcName = "Menchi (an environmentalist)",
		huntTarget = "baz_nitch",
		huntGoal = 20
	},
	{
		trialName = "kill_falumpaset",
		trialType = TRIAL_HUNT,
		trialNpc = "irenez",
		trialNpcName = "Braganta (a naturalist)",
		huntTarget = "falumpaset",
		huntGoal = 20
	},
	{
		trialName = "kill_sludge_panther",
		trialType = TRIAL_HUNT,
		trialNpc = "kima_nazith",
		trialNpcName = "Luha Kellaro (an ecologist)",
		huntTarget = "sludge_panther",
		huntGoal = 20
	},
	{
		trialName = "old_musician",
		trialType = TRIAL_TALK,
		trialNpc = "grobber",
		trialNpcName = "Grizzlo (a retired musician)",
		targetNpc = nil,
		targetLoc = { 3468, 5, -4852, "tatooine" },
		thirdTargetNpc = nil,
		thirdTargetLoc = { 469, 12, 5021, "lok" }
	},
	{
		trialName = "pannaqa",
		trialType = TRIAL_TALK,
		trialNpc = nil,
		trialLoc = { 5291.3, 78.5, -4037.8, "dathomir", "Aurilia" },
		targetNpc = "commoner",
		targetKillable = false,
		thirdTargetNpc = "commoner_male",
		thirdTargetName = "Shendo",
		thirdTargetKillable = false
	},
	{
		trialName = "peoples_soldier",
		trialType = TRIAL_KILL,
		trialNpc = "marco_vahn",
		trialNpcName = "Torin Gundo (an old soldier)",
		targetNpc = "brigand_leader",
		targetKillable = true
	},
	{
		trialName = "politician",
		trialType = TRIAL_KILL,
		trialNpc = "dorn_gestros",
		trialNpcName = "Kaul Dysen (a politician)",
		targetNpc = "bloodseeker_mite",
		targetKillable = true
	},
	{
		trialName = "sob_story",
		trialType = TRIAL_TALK,
		trialNpc = "karena_keer",
		trialNpcName = "Erim Thelcar",
		targetNpc = "object/tangible/jedi/padawan_trials_skeleton.iff",
		targetNpcName = "The remains of Josef Thelcar",
		targetKillable = false
	},
	{
		trialName = "spice_mom",
		trialType = TRIAL_TALK,
		trialNpc = "bestine_rumor10",
		trialNpcName = "Sola Nosconda",
		targetNpc = "devaronian_male",
		targetNpcName = "Evif Sulp",
		targetKillable = false
	},
	{
		trialName = "surveyor",
		trialType = TRIAL_KILL,
		trialNpc = "bestine_rumor08",
		trialNpcName = "Par Doiae (a surveyor)",
		targetNpc = "sharnaff_bull",
		targetKillable = true
	},
	{
		trialName = "the_ring",
		trialType = TRIAL_TALK,
		trialNpc = "giaal_itotr",
		trialNpcName = "Keicho",
		targetNpc = "dread_pirate",
		killMessage = "@jedi_trials:padawan_trials_received_the_ring",
		targetKillable = true
	},
}

knightTrialQuests = {
	{
		trialName = "tusken_raider",
		trialType = TRIAL_HUNT,
		huntTarget = "tusken_raider",
		huntGoal = 19
	},
	{
		trialName = "ancient_bull_rancor",
		trialType = TRIAL_HUNT,
		huntTarget = "ancient_bull_rancor",
		huntGoal = 8
	},
	{
		trialName = "stintaril_prowler",
		trialType = TRIAL_HUNT,
		huntTarget = "stintaril_prowler",
		huntGoal = 8
	},
	{
		trialName = "blurrg_raptor",
		trialType = TRIAL_HUNT,
		huntTarget = "blurrg_raptor",
		huntGoal = 3
	},
	{
		trialName = "enraged_kimogila",
		trialType = TRIAL_HUNT,
		huntTarget = "enraged_kimogila",
		huntGoal = 3
	},
	{
		trialName = "peko_peko_albatross",
		trialType = TRIAL_HUNT,
		huntTarget = "peko_peko_albatross",
		huntGoal = 2
	},
	{
		trialName = "graul_marauder",
		trialType = TRIAL_HUNT,
		huntTarget = "graul_marauder",
		huntGoal = 2
	},
	{
		trialName = "light_or_dark",
		trialType = TRIAL_COUNCIL
	},
	{
		trialName = "enemy_soldier",
		trialType = TRIAL_HUNT_FACTION,
		rebelTarget = "storm_commando",
		imperialTarget = "rebel_commando",
		huntGoal = 47
	},
	{
		trialName = "high_general",
		trialType = TRIAL_HUNT_FACTION,
		rebelTarget = "imperial_surface_marshal;imperial_high_general;imperial_general",
		imperialTarget = "rebel_high_general;rebel_surface_marshal;rebel_general",
		huntGoal = 22
	},
	{
		trialName = "corvette_officer",
		trialType = TRIAL_HUNT_FACTION,
		rebelTarget = "stormtrooper_novatrooper_elite_commander",
		imperialTarget = "corvette_rebel_rear_admiral",
		huntGoal = 4
	},
	{
		trialName = "geonosian_bunker_acklay",
		trialType = TRIAL_HUNT,
		huntTarget = "geonosian_acklay_bunker_boss",
		huntGoal = 1
	},
	{
		trialName = "nightsister_elder",
		trialType = TRIAL_HUNT,
		huntTarget = "nightsister_elder",
		huntGoal = 1
	},
	{
		trialName = "kiin_dray",
		trialType = TRIAL_HUNT,
		huntTarget = "gaping_spider_recluse_giant_kiin_dray",
		huntGoal = 1
	},
	{
		trialName = "giant_canyon_krayt",
		trialType = TRIAL_HUNT,
		huntTarget = "giant_canyon_krayt_dragon",
		huntGoal = 1
	},
}

trialsCivilizedPlanets = { "corellia", "naboo", "rori", "talus", "tatooine" }

trialsCivilizedPlanetCities = {
	corellia = { "coronet", "tyrena", "kor_vella", "doaba_guerfel", "bela_vistal" },
	naboo = { "theed", "moenia", "keren", "kaadara", "deeja_peak" },
	rori = { "narmle", "restuss" },
	talus = { "dearic", "nashal" },
	tatooine = { "bestine", "mos_espa", "mos_eisley", "mos_entha" }
}

-- x, y, radius
trialsCivilizedNpcSpawnPoints = {
	corellia = {
		coronet = {
			{ -14, -4619, 150 },
			{ -170, -4462, 200 },
			{ -327, -4596, 150 },
			{ -107, -4320, 150 }
		},
		tyrena = {
			{ -5132, -2426, 175 },
			{ -5535, -2701, 125 }
		},
		kor_vella = {
			{ -3130, 2798, 20 },
			{ -3332, 3271, 30 },
			{ -3473, 3149, 60 },
			{ -3403, 3026, 20 },
			{ -3673, 3107, 30 },
			{ -3771, 3207, 30 }
		},
		doaba_guerfel = {
			{ 3325, 5504, 40 },
			{ 3214, 5348, 100 },
			{ 3137, 5172, 80 },
			{ 3180, 4985, 30 }
		},
		bela_vistal = {
			{ 6707, -5894, 30 },
			{ 6793, -5733, 100 },
			{ 6712, -5574, 20 },
			{ 6929, -5551, 20 }
		}
	},

	naboo = {
		theed = {
			{ -4675, 3970, 50 },
			{ -4607, 4110, 40 },
			{ -4926, 4027, 40 },
			{ -5173, 4225, 40 },
			{ -5426, 4150, 75 },
			{ -5538, 4307, 60 },
			{ -5948, 4308, 50 },
			{ -5801, 4131, 45 }
		},
		moenia = {
			{ 4892, -4842, 50 },
			{ 4961, -4948, 40 },
			{ 4755, -4948, 60 },
			{ 4698, -4889, 30 }
		},
		keren = {
			{ 1677, 2950, 20 },
			{ 1714, 2664, 75 },
			{ 1780, 2519, 60 },
			{ 1934, 2711, 50 },
			{ 1986, 2479, 60 }
		},
		kaadara = {
			{ 5138, 6630, 40 },
			{ 4987, 6761, 40 },
			{ 5164, 6776, 60 }
		},
		deeja_peak = {
			{ 5114, -1503, 30 },
			{ 5027, -1444, 30 },
			{ 4959, -1517, 30 }
		}
	},

	rori = {
		narmle = {
			{ -5354, -2079, 20 },
			{ -5412, -2238, 20 },
			{ -5215, -2252, 50 },
			{ -5067, -2303, 75 },
			{ -5151, -2461, 60 }
		},
		restuss = {
			{ 5434, 5589, 60 },
			{ 5216, 5627, 80 },
			{ 5186, 5751, 60 },
			{ 5394, 5840, 40 }
		}
	},

	talus = {
		dearic = {
			{ 202, -2846, 30 },
			{ 195, -3040, 40 },
			{ 435, -3063, 100 },
			{ 526, -2946, 100 },
			{ 667, -3066, 80 }
		},
		nashal = {
			{ 4364, 5340, 100 },
			{ 4491, 5188, 40 },
			{ 4365, 5163, 15 },
			{ 4223, 5132, 25 },
			{ 4095, 5280, 25 }
		}
	},

	tatooine = {
		bestine = {
			{ -1401, -3725, 20 },
			{ -1344, -3911, 20 },
			{ -1219, -3565, 100 },
			{ -1095, -3584, 75 },
			{ -1064, -3692, 40 }
		},
		mos_espa = {
			{ -2896, 2009, 150 },
			{ -3057, 2161, 100 },
			{ -2905, 2340, 200 }
		},
		mos_eisley = {
			{ 3495, -4828, 100 },
			{ 3434, -4952, 75 },
			{ 3387, -4715, 200 }
		},
		mos_entha = {
			{ 1332, 3114, 100 },
			{ 1352, 3259, 150 },
			{ 1413, 3341, 150 },
			{ 1507, 3097, 100 },
			{ 1702, 3090, 50 }
		}
	}
}
