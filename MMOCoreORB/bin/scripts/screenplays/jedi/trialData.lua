TRIAL_LIGHTSABER = 1
TRIAL_TALK = 2
TRIAL_KILL = 3
TRIAL_HUNT = 4

padawanTrialQuests = {
	{
		trialName = "architect",
		trialType = TRIAL_TALK,
		trialNpc = "kant_graf",
		trialNpcName = "Kant Graf (an architect)",
		targetNpc = "gungan_captain",
		targetKillable = true
	},
}

--trialsCivilizedPlanets = { "corellia", "naboo", "rori", "talus", "tatooine" }
trialsCivilizedPlanets = { "naboo" }

trialsCivilizedPlanetCities = {
	naboo = { "theed" }
}

-- Temporary until functionality for random spawn locs can be added
trialsCivilizedNpcSpawnPoints = {
	corellia = {
	},

	naboo = {
		theed = {
			{ -4686, 4005 },
			{ -4654.33, 3961.67 }
		}
	},

	rori = {
	},

	talus = {
	},

	tatooine = {
	}
}
