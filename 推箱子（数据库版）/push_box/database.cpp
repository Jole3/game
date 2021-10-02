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
 *���ܣ���ȡ�û���Ϣ
 *���룺
	user - �����û���Ϣ�Ľṹ�����
 *����ֵ��
	��ȡ�ɹ�����true����ȡʧ�ܷ���false
***********************************************/
bool getUserInfo(useInfo &user) {
	MYSQL mysql;
	MYSQL_RES *result; //��������
	MYSQL_ROW row;	//��¼�ṹ��
	char sql[256];	//��sql����������
	int ret;

	//���ӵ����ݿ�
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql,256,"select id,level_id from user where username='%s' and password=md5('%s');", user.name.c_str(), user.pwd.c_str());
	ret=mysql_query(&mysql, sql);	//�ɹ�����0

	if (ret) {
		printf("��ѯ����ʧ�ܣ�%s��ԭ��%s",sql,mysql_error(&mysql));
		mysql_close(&mysql); //�ر����ݿ�
		return false;
	}

	//��ȡ���
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);	//�������

	if (row == NULL) {		//û�в�ѯ������
		mysql_free_result(result);	//�ͷŽ����
		mysql_close(&mysql);	//�ر����ݿ�
		return false;
	}

	user.id = atoi(row[0]);		//atoi���ַ���תΪint
	user.levelID = atoi(row[1]);

	mysql_free_result(result);	//�ͷŽ����
	mysql_close(&mysql);	//�ر����ݿ�

	if (debug) printf("user id: %d  name: %s levelID: %d\n", user.id, user.name.c_str(),user.levelID);

	return true;
}

//�������ݿ�
bool connectDB(MYSQL &mysql) {
	mysql_init(&mysql);	//��ʼ�����

	//�����ַ�����
	mysql_options(&mysql,MYSQL_SET_CHARSET_NAME,"gbk");

	//�������ݿ�
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
		printf("���ݿ�����ʧ�ܣ�ԭ��%s",mysql_error(&mysql));
		return false;
	}

	return true;
}

/**********************************************
 *���ܣ���ȡ�ؿ���Ϣ
 *���룺
	level - ����ؿ���Ϣ�Ľṹ�����
	level_id - ����Ĺؿ�id������id��ȡ�ؿ���Ϣ
 *����ֵ��
	��ȡ�ɹ�����true����ȡʧ�ܷ���false
***********************************************/
bool getLevelInfo(levelInfo &level,int level_id) {
	MYSQL mysql;
	MYSQL_RES *result; //��������
	MYSQL_ROW row;	//��¼�ṹ��
	char sql[256];	//��sql����������
	int ret;

	//���ӵ����ݿ�
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql, 256, "select name,map_row,map_column,map_data,next_level_id from levels where id='%d';", level_id);
	ret = mysql_query(&mysql, sql);	//�ɹ�����0

	if (ret) {
		printf("��ѯ����ʧ�ܣ�%s��ԭ��%s", sql, mysql_error(&mysql));
		mysql_close(&mysql); //�ر����ݿ�
		return false;
	}

	//��ȡ���
	result = mysql_store_result(&mysql);
	row = mysql_fetch_row(result);	//�������

	if (row == NULL) {		//û�в�ѯ������
		mysql_free_result(result);	//�ͷŽ����
		mysql_close(&mysql);	//�ر����ݿ�
		return false;
	}

	level.name = row[0];		//atoi���ַ���תΪint
	level.map_row = atoi(row[1]);
	level.map_column = atoi(row[2]);
	level.map_data = row[3];
	level.next_level = atoi(row[4]);

	mysql_free_result(result);	//�ͷŽ����
	mysql_close(&mysql);	//�ر����ݿ�

	if (debug) printf("level id: %d  name: %s map row: %d  map column: %d map data: %s next level: %d\n", 
		level_id, level.name.c_str(), level.map_row, level.map_column, level.map_data.c_str(), level.next_level);

	return true;
}

/**********************************************
 *���ܣ����عؿ���Ϣ
 *���룺
	level - ����ؿ���Ϣ�Ľṹ�����
 *����ֵ��
	��ȡ�ɹ�����true����ȡʧ�ܷ���false
***********************************************/
bool loadLevel(levelInfo &level, int map[MAP_LINE][MAP_COLUMN]) {
	if (level.map_row > MAP_LINE || level.map_column > MAP_COLUMN) {
		printf("��ͼ���̫���ˣ���������ƣ�\n");
		return false;
	}

	if (level.map_data.length() < 1) {
		printf("��ͼ������������ƣ�\n");
		return false;
	}

	int start = 0, end = 0;
	int row = 0, column = 0;

	do {		
		end = level.map_data.find("|", start);		//��start��ʼ��(�����ַ�����һ���ַ���ʼ)��ֱ���ҵ�|���ţ�����|����λ�õ��±꣬û�ҵ�����-1

		//���ҵ����һ��ʱ������û��|�����ˣ�endһ���Ƿ���-1��������Ҫ�ֶ���endָ���ַ���������
		if (end < 0) {
			end = level.map_data.length();
		}

		string line = level.map_data.substr(start, end - start);	//���ַ���ȡ����
		printf("line: %s\n", line.c_str());

		char *next_data = NULL;
		char *item = strtok_s((char *)line.c_str(), ",", &next_data);	//���ݶ��Ž����ַ���������

		column = 0;		//�����������¿�ʼ����
		while (item && column<level.map_column) {	//һֱ�������ַ�������
			printf("*item: %s\n", item);
			map[row][column] = atoi(item);
			column++;

			item = strtok_s(NULL, ",", &next_data);		//ָ���ַ����е���һ���ַ�
		}

		printf("\n");

		if (column < level.map_column) {
			printf("��ͼ�����������������\n");
			return false;
		}

		row++;

		if (row >= level.map_row) {		//����ÿһ�к��˳�
			break;
		}
		start = end + 1;	//ָ����һ���ַ�
	} while (1);
	
	if (row < level.map_row) {
		printf("��ͼ�����������������\n");
		return false;
	}

	return true;
}

//�����û��ؿ���Ϣ
bool updateUserLevel(int nextLevel, useInfo &user) {
	MYSQL mysql;
	char sql[256];	//��sql����������
	int ret;

	//���ӵ����ݿ�
	if (!connectDB(mysql)) {
		return false;
	}
	snprintf(sql, 256, "update user set level_id=%d where id='%d';", nextLevel,user.id);
	ret = mysql_query(&mysql, sql);	//�ɹ�����0

	if (ret) {
		printf("��������ʧ�ܣ�%s��ԭ��%s", sql, mysql_error(&mysql));
		mysql_close(&mysql); //�ر����ݿ�
		return false;
	}

	mysql_close(&mysql);	//�ر����ݿ�

	return true;
}