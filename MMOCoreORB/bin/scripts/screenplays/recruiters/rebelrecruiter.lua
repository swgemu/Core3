rebel_recruiter_handler = recruiter_convo_handler:new {
}

function rebel_recruiter_handler:getRecruiterFactionHashCode()
	return 370444368
end

function rebel_recruiter_handler:getRecruiterFactionString()
	return "rebel"
end

function rebel_recruiter_handler:getEnemyFactionHashCode()
	return 3679112276
end

function rebel_recruiter_handler:getEnemyFactionString()
	return "imperial"
end

function rebel_recruiter_handler:addRankReviewOption(screen)
	screen:addOption("@conversation/faction_recruiter_rebel:s_468", "confirm_promotion")
end

function rebel_recruiter_handler:getRejectPromotionString()
	return "@conversation/faction_recruiter_rebel:s_478"
end

function rebel_recruiter_handler:addBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_rebel:s_568", "confirm_bribe")
end

function rebel_recruiter_handler:add100kBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_rebel:s_576", "accepted_bribe_100k")
end