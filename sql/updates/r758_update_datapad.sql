-- ----------------------------
-- Table structure for datapad
-- ----------------------------
CREATE TABLE `datapad` (
  `inx` bigint(20) unsigned NOT NULL auto_increment,
  `character_id` bigint(20) unsigned NOT NULL,
  `name` text NOT NULL,
  `itnocrc` bigint(10) unsigned NOT NULL,
  `item_crc` bigint(20) unsigned NOT NULL,
  `file_name` tinytext NOT NULL,
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `itemMask` smallint(5) unsigned NOT NULL default '65535',
  PRIMARY KEY  (`inx`),
  KEY `char_ix` (`character_id`),
  KEY `item_ix` (`inx`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
