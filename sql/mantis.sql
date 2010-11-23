-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.1.36-community-log


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema swgemu
--

CREATE DATABASE IF NOT EXISTS swgemu;
USE swgemu;

--
-- Definition of table `mantis_bug_file_table`
--

DROP TABLE IF EXISTS `mantis_bug_file_table`;
CREATE TABLE `mantis_bug_file_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `title` varchar(250) NOT NULL DEFAULT '',
  `description` varchar(250) NOT NULL DEFAULT '',
  `diskfile` varchar(250) NOT NULL DEFAULT '',
  `filename` varchar(250) NOT NULL DEFAULT '',
  `folder` varchar(250) NOT NULL DEFAULT '',
  `filesize` int(11) NOT NULL DEFAULT '0',
  `file_type` varchar(250) NOT NULL DEFAULT '',
  `date_added` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `content` longblob,
  PRIMARY KEY (`id`),
  KEY `idx_bug_file_bug_id` (`bug_id`),
  KEY `idx_diskfile` (`diskfile`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_file_table`
--

/*!40000 ALTER TABLE `mantis_bug_file_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bug_file_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bug_history_table`
--

DROP TABLE IF EXISTS `mantis_bug_history_table`;
CREATE TABLE `mantis_bug_history_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `date_modified` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `field_name` varchar(64) NOT NULL,
  `old_value` varchar(255) NOT NULL,
  `new_value` varchar(255) NOT NULL,
  `type` smallint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `idx_bug_history_bug_id` (`bug_id`),
  KEY `idx_history_user_id` (`user_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_history_table`
--

/*!40000 ALTER TABLE `mantis_bug_history_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bug_history_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bug_monitor_table`
--

DROP TABLE IF EXISTS `mantis_bug_monitor_table`;
CREATE TABLE `mantis_bug_monitor_table` (
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`user_id`,`bug_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_monitor_table`
--

/*!40000 ALTER TABLE `mantis_bug_monitor_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bug_monitor_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bug_relationship_table`
--

DROP TABLE IF EXISTS `mantis_bug_relationship_table`;
CREATE TABLE `mantis_bug_relationship_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `source_bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `destination_bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `relationship_type` smallint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `idx_relationship_source` (`source_bug_id`),
  KEY `idx_relationship_destination` (`destination_bug_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_relationship_table`
--

/*!40000 ALTER TABLE `mantis_bug_relationship_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bug_relationship_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bug_table`
--

DROP TABLE IF EXISTS `mantis_bug_table`;
CREATE TABLE `mantis_bug_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `reporter_id` int(10) unsigned NOT NULL DEFAULT '0',
  `handler_id` int(10) unsigned NOT NULL DEFAULT '0',
  `duplicate_id` int(10) unsigned NOT NULL DEFAULT '0',
  `priority` smallint(6) NOT NULL DEFAULT '30',
  `severity` smallint(6) NOT NULL DEFAULT '50',
  `reproducibility` smallint(6) NOT NULL DEFAULT '10',
  `status` smallint(6) NOT NULL DEFAULT '10',
  `resolution` smallint(6) NOT NULL DEFAULT '10',
  `projection` smallint(6) NOT NULL DEFAULT '10',
  `category` varchar(64) NOT NULL DEFAULT '',
  `date_submitted` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `last_updated` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `eta` smallint(6) NOT NULL DEFAULT '10',
  `bug_text_id` int(10) unsigned NOT NULL DEFAULT '0',
  `os` varchar(32) NOT NULL DEFAULT '',
  `os_build` varchar(32) NOT NULL DEFAULT '',
  `platform` varchar(32) NOT NULL DEFAULT '',
  `version` varchar(64) NOT NULL DEFAULT '',
  `fixed_in_version` varchar(64) NOT NULL DEFAULT '',
  `build` varchar(32) NOT NULL DEFAULT '',
  `profile_id` int(10) unsigned NOT NULL DEFAULT '0',
  `view_state` smallint(6) NOT NULL DEFAULT '10',
  `summary` varchar(128) NOT NULL DEFAULT '',
  `sponsorship_total` int(11) NOT NULL DEFAULT '0',
  `sticky` tinyint(4) NOT NULL DEFAULT '0',
  `target_version` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `idx_bug_sponsorship_total` (`sponsorship_total`),
  KEY `idx_bug_fixed_in_version` (`fixed_in_version`),
  KEY `idx_bug_status` (`status`),
  KEY `idx_project` (`project_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_table`
--

--
-- Definition of table `mantis_bug_tag_table`
--

DROP TABLE IF EXISTS `mantis_bug_tag_table`;
CREATE TABLE `mantis_bug_tag_table` (
  `bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `tag_id` int(10) unsigned NOT NULL DEFAULT '0',
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `date_attached` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  PRIMARY KEY (`bug_id`,`tag_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_tag_table`
--

/*!40000 ALTER TABLE `mantis_bug_tag_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bug_tag_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bug_text_table`
--

DROP TABLE IF EXISTS `mantis_bug_text_table`;
CREATE TABLE `mantis_bug_text_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `description` longtext NOT NULL,
  `steps_to_reproduce` longtext NOT NULL,
  `additional_information` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bug_text_table`
--
--
-- Definition of table `mantis_bugnote_table`
--

DROP TABLE IF EXISTS `mantis_bugnote_table`;
CREATE TABLE `mantis_bugnote_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `bug_id` int(10) unsigned NOT NULL DEFAULT '0',
  `reporter_id` int(10) unsigned NOT NULL DEFAULT '0',
  `bugnote_text_id` int(10) unsigned NOT NULL DEFAULT '0',
  `view_state` smallint(6) NOT NULL DEFAULT '10',
  `date_submitted` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `last_modified` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `note_type` int(11) DEFAULT '0',
  `note_attr` varchar(250) DEFAULT '',
  `time_tracking` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `idx_bug` (`bug_id`),
  KEY `idx_last_mod` (`last_modified`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bugnote_table`
--

/*!40000 ALTER TABLE `mantis_bugnote_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bugnote_table` ENABLE KEYS */;


--
-- Definition of table `mantis_bugnote_text_table`
--

DROP TABLE IF EXISTS `mantis_bugnote_text_table`;
CREATE TABLE `mantis_bugnote_text_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `note` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_bugnote_text_table`
--

/*!40000 ALTER TABLE `mantis_bugnote_text_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_bugnote_text_table` ENABLE KEYS */;


--
-- Definition of table `mantis_config_table`
--

DROP TABLE IF EXISTS `mantis_config_table`;
CREATE TABLE `mantis_config_table` (
  `config_id` varchar(64) NOT NULL,
  `project_id` int(11) NOT NULL DEFAULT '0',
  `user_id` int(11) NOT NULL DEFAULT '0',
  `access_reqd` int(11) DEFAULT '0',
  `type` int(11) DEFAULT '90',
  `value` longtext NOT NULL,
  PRIMARY KEY (`config_id`,`project_id`,`user_id`),
  KEY `idx_config` (`config_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_config_table`
--

/*!40000 ALTER TABLE `mantis_config_table` DISABLE KEYS */;
INSERT INTO `mantis_config_table` VALUES  ('database_version',0,0,90,1,'63');
/*!40000 ALTER TABLE `mantis_config_table` ENABLE KEYS */;


--
-- Definition of table `mantis_custom_field_project_table`
--

DROP TABLE IF EXISTS `mantis_custom_field_project_table`;
CREATE TABLE `mantis_custom_field_project_table` (
  `field_id` int(11) NOT NULL DEFAULT '0',
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `sequence` smallint(6) NOT NULL DEFAULT '0',
  PRIMARY KEY (`field_id`,`project_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_custom_field_project_table`
--

/*!40000 ALTER TABLE `mantis_custom_field_project_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_custom_field_project_table` ENABLE KEYS */;


--
-- Definition of table `mantis_custom_field_string_table`
--

DROP TABLE IF EXISTS `mantis_custom_field_string_table`;
CREATE TABLE `mantis_custom_field_string_table` (
  `field_id` int(11) NOT NULL DEFAULT '0',
  `bug_id` int(11) NOT NULL DEFAULT '0',
  `value` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`field_id`,`bug_id`),
  KEY `idx_custom_field_bug` (`bug_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_custom_field_string_table`
--

/*!40000 ALTER TABLE `mantis_custom_field_string_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_custom_field_string_table` ENABLE KEYS */;


--
-- Definition of table `mantis_custom_field_table`
--

DROP TABLE IF EXISTS `mantis_custom_field_table`;
CREATE TABLE `mantis_custom_field_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT '',
  `type` smallint(6) NOT NULL DEFAULT '0',
  `possible_values` varchar(255) NOT NULL DEFAULT '',
  `default_value` varchar(255) NOT NULL DEFAULT '',
  `valid_regexp` varchar(255) NOT NULL DEFAULT '',
  `access_level_r` smallint(6) NOT NULL DEFAULT '0',
  `access_level_rw` smallint(6) NOT NULL DEFAULT '0',
  `length_min` int(11) NOT NULL DEFAULT '0',
  `length_max` int(11) NOT NULL DEFAULT '0',
  `advanced` tinyint(4) NOT NULL DEFAULT '0',
  `require_report` tinyint(4) NOT NULL DEFAULT '0',
  `require_update` tinyint(4) NOT NULL DEFAULT '0',
  `display_report` tinyint(4) NOT NULL DEFAULT '1',
  `display_update` tinyint(4) NOT NULL DEFAULT '1',
  `require_resolved` tinyint(4) NOT NULL DEFAULT '0',
  `display_resolved` tinyint(4) NOT NULL DEFAULT '0',
  `display_closed` tinyint(4) NOT NULL DEFAULT '0',
  `require_closed` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `idx_custom_field_name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_custom_field_table`
--

/*!40000 ALTER TABLE `mantis_custom_field_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_custom_field_table` ENABLE KEYS */;


--
-- Definition of table `mantis_email_table`
--

DROP TABLE IF EXISTS `mantis_email_table`;
CREATE TABLE `mantis_email_table` (
  `email_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `email` varchar(64) NOT NULL DEFAULT '',
  `subject` varchar(250) NOT NULL DEFAULT '',
  `submitted` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `metadata` longtext NOT NULL,
  `body` longtext NOT NULL,
  PRIMARY KEY (`email_id`),
  KEY `idx_email_id` (`email_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_email_table`
--

/*!40000 ALTER TABLE `mantis_email_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_email_table` ENABLE KEYS */;


--
-- Definition of table `mantis_filters_table`
--

DROP TABLE IF EXISTS `mantis_filters_table`;
CREATE TABLE `mantis_filters_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL DEFAULT '0',
  `project_id` int(11) NOT NULL DEFAULT '0',
  `is_public` tinyint(4) DEFAULT NULL,
  `name` varchar(64) NOT NULL DEFAULT '',
  `filter_string` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_filters_table`
--

/*!40000 ALTER TABLE `mantis_filters_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_filters_table` ENABLE KEYS */;


--
-- Definition of table `mantis_news_table`
--

DROP TABLE IF EXISTS `mantis_news_table`;
CREATE TABLE `mantis_news_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `poster_id` int(10) unsigned NOT NULL DEFAULT '0',
  `date_posted` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `last_modified` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `view_state` smallint(6) NOT NULL DEFAULT '10',
  `announcement` tinyint(4) NOT NULL DEFAULT '0',
  `headline` varchar(64) NOT NULL DEFAULT '',
  `body` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_news_table`
--

/*!40000 ALTER TABLE `mantis_news_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_news_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_category_table`
--

DROP TABLE IF EXISTS `mantis_project_category_table`;
CREATE TABLE `mantis_project_category_table` (
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `category` varchar(64) NOT NULL DEFAULT '',
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`project_id`,`category`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_category_table`
--

/*!40000 ALTER TABLE `mantis_project_category_table` DISABLE KEYS */;
INSERT INTO `mantis_project_category_table` VALUES  (1,'Account/Billing',0),
 (1,'Sample Category 2',0);
/*!40000 ALTER TABLE `mantis_project_category_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_file_table`
--

DROP TABLE IF EXISTS `mantis_project_file_table`;
CREATE TABLE `mantis_project_file_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `title` varchar(250) NOT NULL DEFAULT '',
  `description` varchar(250) NOT NULL DEFAULT '',
  `diskfile` varchar(250) NOT NULL DEFAULT '',
  `filename` varchar(250) NOT NULL DEFAULT '',
  `folder` varchar(250) NOT NULL DEFAULT '',
  `filesize` int(11) NOT NULL DEFAULT '0',
  `file_type` varchar(250) NOT NULL DEFAULT '',
  `date_added` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `content` longblob,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_file_table`
--

/*!40000 ALTER TABLE `mantis_project_file_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_project_file_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_hierarchy_table`
--

DROP TABLE IF EXISTS `mantis_project_hierarchy_table`;
CREATE TABLE `mantis_project_hierarchy_table` (
  `child_id` int(10) unsigned NOT NULL,
  `parent_id` int(10) unsigned NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_hierarchy_table`
--

/*!40000 ALTER TABLE `mantis_project_hierarchy_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_project_hierarchy_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_table`
--

DROP TABLE IF EXISTS `mantis_project_table`;
CREATE TABLE `mantis_project_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(128) NOT NULL DEFAULT '',
  `status` smallint(6) NOT NULL DEFAULT '10',
  `enabled` tinyint(4) NOT NULL DEFAULT '1',
  `view_state` smallint(6) NOT NULL DEFAULT '10',
  `access_min` smallint(6) NOT NULL DEFAULT '10',
  `file_path` varchar(250) NOT NULL DEFAULT '',
  `description` longtext NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_project_name` (`name`),
  KEY `idx_project_id` (`id`),
  KEY `idx_project_view` (`view_state`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_table`
--

/*!40000 ALTER TABLE `mantis_project_table` DISABLE KEYS */;
INSERT INTO `mantis_project_table` VALUES  (1,'SWGEmu',10,1,10,10,'','The Swgemu project');
/*!40000 ALTER TABLE `mantis_project_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_user_list_table`
--

DROP TABLE IF EXISTS `mantis_project_user_list_table`;
CREATE TABLE `mantis_project_user_list_table` (
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `access_level` smallint(6) NOT NULL DEFAULT '10',
  PRIMARY KEY (`project_id`,`user_id`),
  KEY `idx_project_user` (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_user_list_table`
--

/*!40000 ALTER TABLE `mantis_project_user_list_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_project_user_list_table` ENABLE KEYS */;


--
-- Definition of table `mantis_project_version_table`
--

DROP TABLE IF EXISTS `mantis_project_version_table`;
CREATE TABLE `mantis_project_version_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `version` varchar(64) NOT NULL DEFAULT '',
  `date_order` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `description` longtext NOT NULL,
  `released` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_project_version` (`project_id`,`version`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_project_version_table`
--

/*!40000 ALTER TABLE `mantis_project_version_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_project_version_table` ENABLE KEYS */;


--
-- Definition of table `mantis_sponsorship_table`
--

DROP TABLE IF EXISTS `mantis_sponsorship_table`;
CREATE TABLE `mantis_sponsorship_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `bug_id` int(11) NOT NULL DEFAULT '0',
  `user_id` int(11) NOT NULL DEFAULT '0',
  `amount` int(11) NOT NULL DEFAULT '0',
  `logo` varchar(128) NOT NULL DEFAULT '',
  `url` varchar(128) NOT NULL DEFAULT '',
  `paid` tinyint(4) NOT NULL DEFAULT '0',
  `date_submitted` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `last_updated` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  PRIMARY KEY (`id`),
  KEY `idx_sponsorship_bug_id` (`bug_id`),
  KEY `idx_sponsorship_user_id` (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_sponsorship_table`
--

/*!40000 ALTER TABLE `mantis_sponsorship_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_sponsorship_table` ENABLE KEYS */;


--
-- Definition of table `mantis_tag_table`
--

DROP TABLE IF EXISTS `mantis_tag_table`;
CREATE TABLE `mantis_tag_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(100) NOT NULL DEFAULT '',
  `description` longtext NOT NULL,
  `date_created` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `date_updated` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  PRIMARY KEY (`id`,`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_tag_table`
--

/*!40000 ALTER TABLE `mantis_tag_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_tag_table` ENABLE KEYS */;


--
-- Definition of table `mantis_tokens_table`
--

DROP TABLE IF EXISTS `mantis_tokens_table`;
CREATE TABLE `mantis_tokens_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `owner` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `timestamp` datetime NOT NULL,
  `expiry` datetime DEFAULT NULL,
  `value` longtext NOT NULL,
  PRIMARY KEY (`id`),
  KEY `idx_typeowner` (`type`,`owner`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_tokens_table`
--

/*!40000 ALTER TABLE `mantis_tokens_table` DISABLE KEYS */;
INSERT INTO `mantis_tokens_table` VALUES  (3,1,1,'2010-11-22 23:53:11','2010-11-23 00:53:11','a:40:{s:8:\"_version\";s:2:\"v8\";s:10:\"_view_type\";s:6:\"simple\";s:13:\"show_category\";a:1:{i:0;s:1:\"0\";}s:13:\"show_severity\";a:1:{i:0;i:0;}s:11:\"show_status\";a:1:{i:0;i:0;}s:8:\"per_page\";i:50;s:17:\"highlight_changed\";i:6;s:11:\"reporter_id\";a:1:{i:0;i:0;}s:10:\"handler_id\";a:1:{i:0;i:0;}s:10:\"project_id\";a:1:{i:0;i:-3;}s:4:\"sort\";s:12:\"last_updated\";s:3:\"dir\";s:4:\"DESC\";s:11:\"start_month\";i:11;s:9:\"start_day\";i:1;s:10:\"start_year\";i:2010;s:9:\"end_month\";i:11;s:7:\"end_day\";i:22;s:8:\"end_year\";i:2010;s:6:\"search\";s:0:\"\";s:11:\"hide_status\";a:1:{i:0;i:-2;}s:16:\"and_not_assigned\";b:0;s:15:\"show_resolution\";a:1:{i:0;i:0;}s:10:\"show_build\";a:1:{i:0;s:1:\"0\";}s:12:\"show_version\";a:1:{i:0;s:1:\"0\";}s:17:\"do_filter_by_date\";b:0;s:16:\"fixed_in_version\";a:1:{i:0;s:1:\"0\";}s:14:\"target_version\";a:1:{i:0;s:1:\"0\";}s:13:\"show_priority\";a:1:{i:0;i:0;}s:12:\"user_monitor\";a:1:{i:0;i:0;}s:10:\"view_state\";i:0;s:13:\"custom_fields\";a:0:{}s:13:\"sticky_issues\";s:3:\"off\";s:17:\"relationship_type\";i:-1;s:16:\"relationship_bug\";i:0;s:12:\"show_profile\";a:1:{i:0;i:0;}s:8:\"platform\";a:1:{i:0;i:0;}s:2:\"os\";a:1:{i:0;i:0;}s:8:\"os_build\";a:1:{i:0;i:0;}s:10:\"tag_string\";s:0:\"\";s:10:\"tag_select\";i:0;}'),
 (4,1,3,'2010-11-22 23:53:16','2010-11-24 00:09:26','1'),
 (5,1,4,'2010-11-23 00:12:47','2010-11-23 00:18:35','1');
/*!40000 ALTER TABLE `mantis_tokens_table` ENABLE KEYS */;


--
-- Definition of table `mantis_user_pref_table`
--

DROP TABLE IF EXISTS `mantis_user_pref_table`;
CREATE TABLE `mantis_user_pref_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `project_id` int(10) unsigned NOT NULL DEFAULT '0',
  `default_profile` int(10) unsigned NOT NULL DEFAULT '0',
  `default_project` int(10) unsigned NOT NULL DEFAULT '0',
  `advanced_report` tinyint(4) NOT NULL DEFAULT '0',
  `advanced_view` tinyint(4) NOT NULL DEFAULT '0',
  `advanced_update` tinyint(4) NOT NULL DEFAULT '0',
  `refresh_delay` int(11) NOT NULL DEFAULT '0',
  `redirect_delay` tinyint(4) NOT NULL DEFAULT '0',
  `bugnote_order` varchar(4) NOT NULL DEFAULT 'ASC',
  `email_on_new` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_assigned` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_feedback` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_resolved` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_closed` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_reopened` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_bugnote` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_status` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_priority` tinyint(4) NOT NULL DEFAULT '0',
  `email_on_priority_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_status_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_bugnote_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_reopened_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_closed_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_resolved_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_feedback_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_assigned_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_on_new_min_severity` smallint(6) NOT NULL DEFAULT '10',
  `email_bugnote_limit` smallint(6) NOT NULL DEFAULT '0',
  `language` varchar(32) NOT NULL DEFAULT 'english',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_user_pref_table`
--

/*!40000 ALTER TABLE `mantis_user_pref_table` DISABLE KEYS */;
INSERT INTO `mantis_user_pref_table` VALUES  (1,1,0,0,1,0,0,0,30,2,'ASC',1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,'english');
/*!40000 ALTER TABLE `mantis_user_pref_table` ENABLE KEYS */;


--
-- Definition of table `mantis_user_print_pref_table`
--

DROP TABLE IF EXISTS `mantis_user_print_pref_table`;
CREATE TABLE `mantis_user_print_pref_table` (
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `print_pref` varchar(64) NOT NULL,
  PRIMARY KEY (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_user_print_pref_table`
--

/*!40000 ALTER TABLE `mantis_user_print_pref_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_user_print_pref_table` ENABLE KEYS */;


--
-- Definition of table `mantis_user_profile_table`
--

DROP TABLE IF EXISTS `mantis_user_profile_table`;
CREATE TABLE `mantis_user_profile_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL DEFAULT '0',
  `platform` varchar(32) NOT NULL DEFAULT '',
  `os` varchar(32) NOT NULL DEFAULT '',
  `os_build` varchar(32) NOT NULL DEFAULT '',
  `description` longtext NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_user_profile_table`
--

/*!40000 ALTER TABLE `mantis_user_profile_table` DISABLE KEYS */;
/*!40000 ALTER TABLE `mantis_user_profile_table` ENABLE KEYS */;


--
-- Definition of table `mantis_user_table`
--

DROP TABLE IF EXISTS `mantis_user_table`;
CREATE TABLE `mantis_user_table` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(32) NOT NULL DEFAULT '',
  `realname` varchar(64) NOT NULL DEFAULT '',
  `email` varchar(64) NOT NULL DEFAULT '',
  `password` varchar(32) NOT NULL DEFAULT '',
  `date_created` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `last_visit` datetime NOT NULL DEFAULT '1970-01-01 00:00:01',
  `enabled` tinyint(4) NOT NULL DEFAULT '1',
  `protected` tinyint(4) NOT NULL DEFAULT '0',
  `access_level` smallint(6) NOT NULL DEFAULT '10',
  `login_count` int(11) NOT NULL DEFAULT '0',
  `lost_password_request_count` smallint(6) NOT NULL DEFAULT '0',
  `failed_login_count` smallint(6) NOT NULL DEFAULT '0',
  `cookie_string` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_user_cookie_string` (`cookie_string`),
  UNIQUE KEY `idx_user_username` (`username`),
  KEY `idx_enable` (`enabled`),
  KEY `idx_access` (`access_level`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `mantis_user_table`
--

/*!40000 ALTER TABLE `mantis_user_table` DISABLE KEYS */;
INSERT INTO `mantis_user_table` VALUES  (1,'administrator','','root@localhost','7c6afe50f993ce148d2bdbca6b831d47','2010-10-18 00:27:23','2010-11-23 00:13:35',1,0,90,6,0,0,'6b1a815f8bfa1fdc934f284a5c10f712d57dd1a96afb0f3ff9300ae5aefe4829');
/*!40000 ALTER TABLE `mantis_user_table` ENABLE KEYS */;


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

