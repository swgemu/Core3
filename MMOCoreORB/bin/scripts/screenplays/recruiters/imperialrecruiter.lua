includeFile("recruiters/factionperkdata.lua")

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

function imperial_recruiter_handler:isWeapon(strItem)
	if ( imperial_weapons_armor[strItem] ~= nil ) then
		if ( imperial_weapons_armor[strItem].type == rewards.weapon ) then
			return true
		end
	end
	
	return false
end

function imperial_recruiter_handler:isArmor(strItem)
	if ( imperial_weapons_armor[strItem] ~= nil ) then
		if ( imperial_weapons_armor[strItem].type == rewards.armor ) then
			return true
		end
	end
	return false
end


function imperial_recruiter_handler:isUniform(strItem)
	if ( imperial_uniforms[strItem] ~= nil ) then
		return true
	end

	return false
end

function imperial_recruiter_handler:isFurniture(strItem)
	if ( imperial_furniture[strItem] ~= nil ) then
		return true
	end
	
	return false
end

function imperial_recruiter_handler:isContainer(strItem)
	if ( imperial_furniture[strItem] ~= nil and imperial_furniture[strItem].type == rewards.container) then
		return true
	end
	
	return false
end

function imperial_recruiter_handler:addUniforms(screen) 
	for k,v in pairs(imperial_uniform_list) do
		if ( imperial_uniforms[v] ~= nil and imperial_uniforms[v].display ~= nil and imperial_uniforms[v].cost ~= nil ) then
			screen:addOption(imperial_uniforms[v].display .. " - " .. imperial_uniforms[v].cost, v)
		end
	end
end


function imperial_recruiter_handler:addWeaponsArmor(screen)
	for k,v in pairs(imperial_weapons_armor_list) do
		if ( imperial_weapons_armor[v] ~= nill and 	imperial_weapons_armor[v].display ~= nil and imperial_weapons_armor[v].cost ~= nil ) then
				screen:addOption(imperial_weapons_armor[v].display .. " - " .. imperial_weapons_armor[v].cost, v)
		end
	end
end

function imperial_recruiter_handler:addFurniture(screen) 
	for k,v in pairs(imperial_furniture_list) do
		if ( imperial_furniture[v] ~= nil and imperial_furniture[v].display ~= nil and imperial_furniture[v].cost ~= nil ) then
			screen:addOption(imperial_furniture[v].display .. " - " .. imperial_furniture[v].cost, v)
		end
	end
end


function imperial_recruiter_handler:getItemCost(itemstring)
	local itemcost = nil
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring)  and imperial_weapons_armor[itemstring] ~= nil ) then
		if ( imperial_weapons_armor[itemstring].cost ~= nil ) then
			return imperial_weapons_armor[itemstring].cost
		end
	elseif (self:isUniform(itemstring) ) then
		if ( imperial_uniforms[itemstring].cost ~= nil ) then
			return imperial_uniforms[itemstring].cost
		end
	elseif ( self:isFurniture(itemstring) ) then
		if(imperial_furniture[itemstring].cost ~= nil) then
			return imperial_furniture[itemstring].cost
		end
	end

	return itemcost
end

function imperial_recruiter_handler:getTemplatePath(itemstring)
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring) ) then
		return imperial_weapons_armor[itemstring].item
	elseif ( self:isUniform(itemstring) ) then
		return imperial_uniforms[itemstring].item
	elseif ( self:isFurniture(itemstring) ) then
		return imperial_furniture[itemstring].item
	end
	return nil
end

