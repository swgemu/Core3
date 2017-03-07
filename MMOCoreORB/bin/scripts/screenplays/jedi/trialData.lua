TRIAL_LIGHTSABER = 1
TRIAL_TALK = 2
TRIAL_KILL = 3
TRIAL_HUNT = 4

padawanTrialQuests = {
	{
		trialName = "architect",
		trialType = TRIAL_TALK,
		trialNpc = "devaronian_male",
		trialNpcName = "Kant Graf (an architect)",
		targetNpc = "gungan_captain",
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
}

--trialsCivilizedPlanets = { "corellia", "naboo", "rori", "talus", "tatooine" }
trialsCivilizedPlanets = { "naboo" }

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
	},

	talus = {
	},

	tatooine = {
	}
}
