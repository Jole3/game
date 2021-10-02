#include <mysql.h>
#include <stdio.h>
#include "database.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASSWD "sjj19971012!"
#define DB_NAME "push_box"
#define DB_PORT 3308

bool connectDB(MYSQL &mysql);
int debug = 1;

/**********************************************
 *功能：获取用户信息
 *输入：
	user - 保存用户信息的结构体变量
 *返回值：
	获取成功返回true，获取失败返回false
***********************************************/
bool getUserInfo(useInfo &user) {
	MYSQL mysql;
	MYSQL_RES *result; //定义结果集
	MYSQL_ROW row;	//记录结构体
	char sql[256];	//将sql语句存入其中
	int ret;

	//连接到数据库
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql,256,"select id,level_id from user where username='%s' and password=md5('%s');", user.name.c_str(), user.pwd.c_str());
	ret=mysql_query(&mysql, sql);	//成功返回0

	if (ret) {
		printf("查询数据失败，%s，原因：%s",sql,mysql_error(&mysql));
		mysql_close(&mysql); //关闭数据库
		return false;
	}

	//获取结果
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);	//结果读出

	if (row == NULL) {		//没有查询到数据
		mysql_free_result(result);	//释放结果集
		mysql_close(&mysql);	//关闭数据库
		return false;
	}

	user.id = atoi(row[0]);		//atoi将字符串转为int
	user.levelID = atoi(row[1]);

	mysql_free_result(result);	//释放结果集
	mysql_close(&mysql);	//关闭数据库

	if (debug) printf("user id: %d  name: %s levelID: %d\n", user.id, user.name.c_str(),user.levelID);

	return true;
}

//连接数据库
bool connectDB(MYSQL &mysql) {
	mysql_init(&mysql);	//初始化句柄

	//设置字符编码
	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"gbk");

	//连接数据库
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
		printf("数据库连接失败，原因：%s",mysql_error(&mysql));
		return false;
	}

	return true;
}

/**********************************************
 *功能：获取关卡信息
 *输入：
	level - 保存关卡信息的结构体变量
	level_id - 传入的关卡id，根据id获取关卡信息
 *返回值：
	获取成功返回true，获取失败返回false
***********************************************/
bool getLevelInfo(levelInfo &level,int level_id) {
	MYSQL mysql;
	MYSQL_RES *result; //定义结果集
	MYSQL_ROW row;	//记录结构体
	char sql[256];	//将sql语句存入其中
	int ret;

	//连接到数据库
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql, 256, "select name,map_row,map_column,map_data,next_level_id from levels where id='%d';", level_id);
	ret = mysql_query(&mysql, sql);	//成功返回0

	if (ret) {
		printf("查询数据失败，%s，原因：%s", sql, mysql_error(&mysql));
		mysql_close(&mysql); //关闭数据库
		return false;
	}

	//获取结果
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);	//结果读出

	if (row == NULL) {		//没有查询到数据
		mysql_free_result(result);	//释放结果集
		mysql_close(&mysql);	//关闭数据库
		return false;
	}

	level.name = row[0];		//atoi将字符串转为int
	level.map_row = atoi(row[1]);
	level.map_column = atoi(row[2]);
	level.map_data = row[3];
	level.next_level = atoi(row[4]);

	mysql_free_result(result);	//释放结果集
	mysql_close(&mysql);	//关闭数据库

	if (debug) printf("level id: %d  name: %s map row: %d  map column: %d map data: %s next level: %d\n", 
		level_id, level.name.c_str(), level.map_row, level.map_column, level.map_data.c_str(), level.next_level);

	return true;
}

/**********************************************
 *功能：加载关卡信息
 *输入：
	level - 保存关卡信息的结构体变量
 *返回值：
	获取成功返回true，获取失败返回false
***********************************************/
bool loadLevel(levelInfo &level, int map[MAP_LINE][MAP_COLUMN]) {
	if (level.map_row > MAP_LINE || level.map_column > MAP_COLUMN) {
		printf("地图设计太大了，请重新设计！\n");
		return false;
	}

	if (level.map_data.length() < 1) {
		printf("地图有误，请重新设计！\n");
		return false;
	}

	int start = 0, end = 0;
	int row = 0, column = 0;

	do {		
		end = level.map_data.find("|", start);		//从start开始找(即从字符串第一个字符开始)，直到找到|符号，返回|所在位置的下标，没找到返回-1

		//当找到最后一串时，后面没有|符号了，end一定是返回-1，所以需要手动将end指向字符串结束符
		if (end < 0) {
			end = level.map_data.length();
		}

		string line = level.map_data.substr(start, end - start);	//把字符串取出来
		printf("line: %s\n", line.c_str());

		char *next_data = NULL;
		char *item = strtok_s((char *)line.c_str(), ",", &next_data);	//根据逗号解析字符串，返回

		column = 0;		//给列清零重新开始计数
		while (item && column<level.map_column) {	//一直解析到字符串结束
			printf("*item: %s\n", item);
			map[row][column] = atoi(item);
			column++;

			item = strtok_s(NULL, ",", &next_data);		//指向字符串中的下一个字符
		}

		printf("\n");

		if (column < level.map_column) {
			printf("地图数据有误，请重新设计\n");
			return false;
		}

		row++;

		if (row >= level.map_row) {		//读完每一行后退出
			break;
		}
		start = end + 1;	//指向下一串字符
	} while (1);
	
	if (row < level.map_row) {
		printf("地图数据有误，请重新设计\n");
		return false;
	}

	return true;
}

//更新用户关卡信息
bool updateUserLevel(int nextLevel, useInfo &user) {
	MYSQL mysql;
	char sql[256];	//将sql语句存入其中
	int ret;

	//连接到数据库
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql, 256, "update user set level_id=%d where id='%d';", nextLevel,user.id);
	ret = mysql_query(&mysql, sql);	//成功返回0

	if (ret) {
		printf("更新数据失败，%s，原因：%s", sql, mysql_error(&mysql));
		mysql_close(&mysql); //关闭数据库
		return false;
	}

	mysql_close(&mysql);	//关闭数据库

	return true;
}