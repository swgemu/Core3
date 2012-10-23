includeFile("recruiters/factionperkdata.lua")

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

function rebel_recruiter_handler:isWeapon(strItem)
	if ( faction_reward_data.rebel_weapons_armor[strItem] ~= nil ) then
		
		if ( faction_reward_data.rebel_weapons_armor[strItem].type == faction_reward_type.weapon ) then
			return true
		end
	end
	
	return false
end

function rebel_recruiter_handler:isArmor(strItem)
	if ( faction_reward_data.rebel_weapons_armor[strItem] ~= nil ) then
		if ( faction_reward_data.rebel_weapons_armor[strItem].type == faction_reward_type.armor ) then
			return true
		end
	end
	
	return false
end

-- rebels don't get unifroms
function rebel_recruiter_handler:isUniform(strItem)
	return false
end

function rebel_recruiter_handler:isFurniture(strItem)
	if ( faction_reward_data.rebel_furniture[strItem] ~= nil ) then
		return true
	end
	
	return false
end

function rebel_recruiter_handler:isContainer(strItem)
	if ( faction_reward_data.rebel_furniture[strItem] ~= nil and faction_reward_data.rebel_furniture[strItem].type == faction_reward_type.container) then
		return true
	end
	
	return false
end

function rebel_recruiter_handler:getItemCost(itemstring)
	local itemcost = nil
	
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring)  and faction_reward_data.rebel_weapons_armor[itemstring] ~= nil ) then
		if ( faction_reward_data.rebel_weapons_armor[itemstring].cost ~= nil ) then
			return faction_reward_data.rebel_weapons_armor[itemstring].cost
		end
	elseif ( self:isFurniture(itemstring) ) then
		if(faction_reward_data.rebel_furniture[itemstring].cost ~= nil) then
			return faction_reward_data.rebel_furniture[itemstring].cost
		end
	end

	return itemcost
end


function rebel_recruiter_handler:addWeaponsArmor(screen)
	for k,v in pairs(faction_reward_data.rebel_weapons_armor_list) do
		if ( faction_reward_data.rebel_weapons_armor[v] ~= nill and 	faction_reward_data.rebel_weapons_armor[v].display ~= nil and faction_reward_data.rebel_weapons_armor[v].cost ~= nil ) then
				screen:addOption(faction_reward_data.rebel_weapons_armor[v].display .. " - " .. faction_reward_data.rebel_weapons_armor[v].cost, v)
		end
	end
end

function rebel_recruiter_handler:addFurniture(screen) 
	for k,v in pairs(faction_reward_data.rebel_furniture_list) do
		if ( faction_reward_data.rebel_furniture[v] ~= nil and faction_reward_data.rebel_furniture[v].display ~= nil and faction_reward_data.rebel_furniture[v].cost ~= nil ) then
			screen:addOption(faction_reward_data.rebel_furniture[v].display .. " - " .. faction_reward_data.rebel_furniture[v].cost, v)
		end
	end
end


function rebel_recruiter_handler:getTemplatePath(itemstring)
	
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring) ) then
		return faction_reward_data.rebel_weapons_armor[itemstring].item
	elseif ( self:isFurniture(itemstring) ) then
		return faction_reward_data.rebel_furniture[itemstring].item
	end
	return nil
end