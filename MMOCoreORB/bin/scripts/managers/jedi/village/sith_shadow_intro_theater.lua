local GoToTheater = require("quest.tasks.go_to_theater")

SithShadowIntroTheater = GoToTheater:new {
	-- Task properties
	taskName = "SithShadowIntroTheater",
	-- GoToTheater properties
	minimumDistance = 1024,
	maximumDistance = 1536,
	--theater = "object/static/structure/tatooine/tent_house_tatooine_style_01.iff",
	theater = "object/building/poi/anywhere_fs_intro_camp.iff",
	waypointDescription = "@quest/force_sensitive/intro:theater_sum",
	mobileList = {
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 },
		{ template = "sith_shadow", minimumDistance = 12, maximumDistance = 24, referencePoint = 0 }
	},
	despawnTime = 2 * 60* 60* 1000, -- 2 hours
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil
}

return SithShadowIntroTheater
