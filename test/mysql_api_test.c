#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "127.0.0.1" 
#define USER "root"
#define PASSWORD "PGMG7464"
#define DBNAME "test_db"

void common(MYSQL* mysql, const char* sql);
void add(MYSQL* mysql, const char* sql);
void del(MYSQL* mysql, const char* sql);
void get(MYSQL* mysql, const char* sql);
void mod(MYSQL* mysql, const char* sql);

int main()
{
	MYSQL* mysql = mysql_init(NULL);
	if(mysql == NULL)
	{
		printf("mysql_init failed\n");
		return -1;
	}

	if(mysql_real_connect(mysql, HOST, USER, PASSWORD, DBNAME, 0, NULL, 0) == NULL)
	{
		printf("mysql_real_connect failed! reason:%s\n", mysql_error(mysql));
		return -1;
	}

	mysql_set_character_set(mysql, "utf8");

	// mysql相关操作
	int flag = -1;
	while(1)
	{
		printf("choose operation\n");
		printf("1、add 2、del 3、get 4、mod 0、quit\n");
		scanf("%d", &flag);
		if(flag == 0) break;

		// 残留有 '\n’
		int c;
		while ((c = getchar()) != '\n' && c != EOF);


		printf("mysql>");
		char sql[100]; // 根据需要修改长度
		printf("请输入一行字符串：\n");
		if (fgets(sql, sizeof(sql), stdin) != NULL) 
		{
			printf("你输入的是：%s", sql);
		}
		sql[strcspn(sql, "\n")] = '\0'; // 移除末尾的换行符	

		switch(flag)
		{
		case 1:
			add(mysql, sql);
			break;
		case 2:
			del(mysql, sql);
			break;
		case 3:
			get(mysql, sql);
			break;
		case 4:
			mod(mysql, sql);
			break;
		default:
			printf("no this choice\n");
		}
	}

	mysql_close(mysql);

	return 0;
}

void common(MYSQL* mysql, const char* sql)
{
	int ret = mysql_query(mysql, sql);
	if(ret != 0)
	{
		printf("mysql query error:%s\n", mysql_error(mysql));
		return;
	}
}

void add(MYSQL* mysql, const char* sql)
{
	common(mysql, sql);
}
void del(MYSQL* mysql, const char* sql)
{
	common(mysql, sql);
}
void get(MYSQL* mysql, const char* sql)
{
	// 查询
	common(mysql, sql);
    MYSQL_RES *res = mysql_store_result(mysql);
    if (res == NULL) 
    {
        printf("mysql store result error:%s\n", mysql_error(mysql));
        return ;
    }
    int row = mysql_num_rows(res);
    int col = mysql_num_fields(res);
    printf("%10s%10s%10s%10s\n", "ID", "年龄", "姓名", "成绩");
    for (int i = 0; i < row; i++) 
    {
        MYSQL_ROW row_data = mysql_fetch_row(res);
        for (int i = 0; i < col; i++) 
        {
            printf("%10s", row_data[i]);
        }
        printf("\n");
    }
    mysql_free_result(res);
}
void mod(MYSQL* mysql, const char* sql)
{
	common(mysql, sql);
}
