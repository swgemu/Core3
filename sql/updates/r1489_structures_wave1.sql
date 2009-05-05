/* character_structures is deprecated */
TRUNCATE `swgemu`.`character_structures`;
CREATE TABLE  `swgemu`.`structures` (
  `structureID` bigint(20) unsigned NOT NULL default '0',
  `ownerID` bigint(20) unsigned NOT NULL default '0',
  `zoneID` int(10) NOT NULL default '0',
  `objectCRC` int(10) unsigned NOT NULL default '0',
  `customName` tinytext NOT NULL,
  `stfFile` tinytext NOT NULL,
  `stfName` tinytext NOT NULL,
  `objectType` int(10) NOT NULL default '0',
  `objectSubType` int(10) NOT NULL default '0',
  `x` float NOT NULL default '0',
  `z` float NOT NULL default '0',
  `oX` float NOT NULL default '0',
  `oY` float NOT NULL default '0',
  `oZ` float NOT NULL default '0',
  `oW` float NOT NULL default '0',
  `attributes` text NOT NULL,
  `permissionList` text NOT NULL,
  PRIMARY KEY  (`structureID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

CREATE TABLE  `swgemu`.`harvester_hoppers` (
  `structureID` bigint(20) unsigned NOT NULL,
  `hopper` text NOT NULL,
  PRIMARY KEY  (`structureID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;