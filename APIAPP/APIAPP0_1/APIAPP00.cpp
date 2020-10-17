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

	FILE* fp = fopen("sql.log", "wt"); //검색결과를 임시 저장할 로그파일을 쓰기모드로 열기

	while (row = mysql_fetch_row(result))
	{
		for (int i = 0; i < fcount; i++)
		{
					printf("%s,", row[i]); // 검색결과 레코드 화면 출력
					fprintf(fp, "%s,", row[i]);//검색결과 레코드 로그파일에 출력
		}
		printf("\n"); // 검색결과 줄바꿈
		fprintf(fp, "\n"); //검색결과 파일 줄바꿈
	}
	fclose(fp); //로그 파일 닫기
	mysql_free_result(result);

	mysql_close(&mysql);

	return 0;
}