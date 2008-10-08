SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for datapad
-- ----------------------------
DROP TABLE IF EXISTS `datapad`;
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
  `obj_id` bigint(20) unsigned NOT NULL,
  PRIMARY KEY  (`inx`),
  KEY `char_ix` (`character_id`),
  KEY `item_ix` (`inx`)
) ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
