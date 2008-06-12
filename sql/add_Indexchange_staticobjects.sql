ALTER TABLE `staticobjects` ADD PRIMARY KEY (`objectid`);
ALTER TABLE `staticobjects` ADD INDEX `zone_id` (`zoneid`);
ALTER TABLE `resource_spawns` ADD INDEX `resName` (`resource_name`);

