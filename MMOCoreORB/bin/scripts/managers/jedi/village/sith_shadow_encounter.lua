local Encounter = require("quest.tasks.encounter")
local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

SithShadowEncounter = Encounter:new {
	-- Task properties
	taskName = "SithShadowEncounter",
	-- Encounter properties
	--minimumTimeUntilEncounter = 12 * 60 * 60 * 1000, -- 12 hours
	--maximumTimeUntilEncounter = 24 * 60 * 60 * 1000, -- 24 hours
	minimumTimeUntilEncounter = 12 * 1000, -- 12 hours
	maximumTimeUntilEncounter = 24 * 1000, -- 24 hours
	--encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	encounterDespawnTime = 60 * 1000, -- 5 minutes
	spawnObjectList = {
		{ template = "sith_shadow_datapad", minimumDistance = 32, maximumDistance = 64, referencePoint = 0, followPlayer = true },
		{ template = "sith_shadow", minimumDistance = 4, maximumDistance = 8, referencePoint = 1, followPlayer = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterClosingIn = nil,
	onEncounterAtPlayer = nil
}

return SithShadowEncounter
