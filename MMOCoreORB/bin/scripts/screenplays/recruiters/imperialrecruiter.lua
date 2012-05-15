imperial_recruiter_handler = recruiter_convo_handler:new {
}

function imperial_recruiter_handler:getRecruiterFactionHashCode()
	return 3679112276
end

function imperial_recruiter_handler:getRecruiterFactionString()
	return "imperial"
end

function imperial_recruiter_handler:getEnemyFactionHashCode()
	return 370444368
end

function imperial_recruiter_handler:getEnemyFactionString()
	return "rebel"
end

function imperial_recruiter_handler:addRankReviewOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_312", "confirm_promotion")
end

function imperial_recruiter_handler:getRejectPromotionString()
	return "@conversation/faction_recruiter_imperial:s_320"
end

function imperial_recruiter_handler:addBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_398", "confirm_bribe")
end

function imperial_recruiter_handler:add100kBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_406", "accepted_bribe_100k")
end