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
CREATE TABLE `datapad` (
  `object_id` bigint(20) unsigned NOT NULL,
  `character_id` bigint(20) unsigned NOT NULL,
  `object_type` bigint(20) NOT NULL,
  `custom_name` tinytext NOT NULL,
  `stringFile` tinytext NOT NULL,
  `stringName` tinytext NOT NULL,
  `object_crc` bigint(10) unsigned NOT NULL,
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `linked_tano_id` bigint(20) unsigned NOT NULL,
  `deleted` bit(1) NOT NULL DEFAULT '\0',
  PRIMARY KEY (`object_id`),
  KEY `char_ix` (`character_id`),
  KEY `item_ix` (`object_id`)
) ENGINE=MyISAM AUTO_INCREMENT=185 DEFAULT CHARSET=latin1;


DROP TABLE IF EXISTS `swgemu`.`datapad_items`;
CREATE TABLE `datapad_items` (
  `item_id` bigint(20) unsigned NOT NULL,
  `character_id` bigint(20) unsigned NOT NULL,
  `name` text NOT NULL,
  `template_crc` bigint(20) unsigned NOT NULL,
  `template_type` int(10) unsigned NOT NULL,
  `template_type_name` tinytext NOT NULL,
  `template_name` tinytext NOT NULL,
  `container` bigint(20) unsigned NOT NULL DEFAULT '0',
  `equipped` tinyint(1) unsigned NOT NULL,
  `deleted` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `attributes` text NOT NULL,
  `appearance` mediumtext NOT NULL,
  `itemMask` smallint(5) unsigned NOT NULL DEFAULT '65535',
  `optionsBitmask` int(10) unsigned NOT NULL DEFAULT '0',
  `in_bank` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`item_id`),
  KEY `container_ix` (`container`),
  KEY `deleted_ix` (`deleted`),
  KEY `char_ix` (`character_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

ALTER TABLE `character_items` ADD `template_type_name` tinytext NOT NULL
