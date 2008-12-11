SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for player_storage
-- ----------------------------
DROP TABLE IF EXISTS `player_storage`;
CREATE TABLE `player_storage` (
  `item_id` bigint(20) unsigned NOT NULL,
  `structure_id` bigint(20) unsigned NOT NULL,
  `name` text NOT NULL,
  `template_crc` bigint(20) unsigned NOT NULL,
  `template_type` int(10) unsigned NOT NULL,
  `template_name` tinytext NOT NULL,
  `container` bigint(20) unsigned NOT NULL default '0',
  `parent_id` bigint(20) unsigned NOT NULL,
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `itemMask` smallint(5) NOT NULL,
  `X` float NOT NULL,
  `Y` float NOT NULL,
  `Z` float NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `dropped_by_character` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  (`item_id`),
  KEY `structure_ix` (`structure_id`),
  KEY `container_ix` (`container`),
  KEY `parent_ix` (`parent_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


-- ----------------------------
-- Table structure for friendlist
-- ----------------------------
DROP TABLE IF EXISTS `friendlist`;
CREATE TABLE `friendlist` (
  `character_id` mediumint(8) unsigned NOT NULL,
  `friend_id` mediumint(8) NOT NULL,
  `friend_galaxy` varchar(50) NOT NULL,
  `ix` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`ix`),
  KEY `char_id_ix` (`character_id`),
  KEY `friend_id` (`friend_id`),
  KEY `friend_galaxy_ix` (`friend_galaxy`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for friendlist_reverse
-- ----------------------------
DROP TABLE IF EXISTS `friendlist_reverse`;
CREATE TABLE `friendlist_reverse` (
  `charID` mediumint(8) unsigned NOT NULL auto_increment,
  `gotMePOID` bigint(20) NOT NULL default '0',
  PRIMARY KEY  (`charID`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;
