#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include "mysql.h"
using namespace std;
int main()
{
	
	string name;
	getline(cin, name);
	

	MYSQL mysql;

	if (!mysql_init(&mysql))
		return 0;

	if (!mysql_real_connect(&mysql, "localhost", "scott", "tiger", "world", 0, NULL, 0))
		return 0;

	//mysql_query(&mysql, "select Code, Name,Region,SurfaceArea, Population, GNP from country");
	mysql_query(&mysql, name.c_str());

	MYSQL_RES* result = mysql_store_result(&mysql);
	
	if (!result)
	{
		mysql_close(&mysql);
		return 0;
	}
	MYSQL_ROW row;

	int fcount = mysql_field_count(&mysql);

	FILE* fp = fopen("sql.log", "wt"); //�˻������ �ӽ� ������ �α������� ������� ����

	while (row = mysql_fetch_row(result))
	{
		for (int i = 0; i < fcount; i++)
		{
					printf("%s,", row[i]); // �˻���� ���ڵ� ȭ�� ���
					fprintf(fp, "%s,", row[i]);//�˻���� ���ڵ� �α����Ͽ� ���
		}
		printf("\n"); // �˻���� �ٹٲ�
		fprintf(fp, "\n"); //�˻���� ���� �ٹٲ�
	}
	fclose(fp); //�α� ���� �ݱ�
	mysql_free_result(result);

	mysql_close(&mysql);

	return 0;
}