/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : test_company

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 29/12/2023 16:29:47
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee`  (
  `NAME` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `NUMBER` int NULL DEFAULT NULL,
  `DEPT` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO `employee` VALUES ('刘晨', 1, 'zhigong');
INSERT INTO `employee` VALUES ('刘星', 2, 'zhigong');
INSERT INTO `employee` VALUES ('张三', 3, 'zhigong');
INSERT INTO `employee` VALUES ('李四', 4, 'zhigong');
INSERT INTO `employee` VALUES ('王明', 5, 'zhigong');
INSERT INTO `employee` VALUES ('李勇', 6, 'daiban');

-- ----------------------------
-- Table structure for salary
-- ----------------------------
DROP TABLE IF EXISTS `salary`;
CREATE TABLE `salary`  (
  `NAME` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `SALARIES` int NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of salary
-- ----------------------------
INSERT INTO `salary` VALUES ('刘星', 3000);
INSERT INTO `salary` VALUES ('刘晨', 3000);
INSERT INTO `salary` VALUES ('张三', 3000);
INSERT INTO `salary` VALUES ('李勇', 5000);
INSERT INTO `salary` VALUES ('李四', 3000);
INSERT INTO `salary` VALUES ('王明', 3000);

SET FOREIGN_KEY_CHECKS = 1;
