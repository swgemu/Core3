/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 1/24/2009 3:58:40 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for skills
-- ----------------------------
DROP TABLE IF EXISTS `swgemu`.`datapad`;
CREATE TABLE  `swgemu`.`datapad` (
  `item_id` bigint(20) unsigned NOT NULL,
  `character_id` bigint(20) unsigned NOT NULL,
  `name` text NOT NULL,
  `itno_crc` bigint(10) unsigned NOT NULL,
  `tano_crc` bigint(20) unsigned NOT NULL,
  `tano_type` int(10) unsigned NOT NULL,
  `tano_name` tinytext NOT NULL,
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `itemMask` smallint(5) unsigned NOT NULL default '65535',
  PRIMARY KEY  (`item_id`),
  KEY `char_ix` (`character_id`),
  KEY `item_ix` (`item_id`)
) ENGINE=MyISAM AUTO_INCREMENT=185 DEFAULT CHARSET=latin1;