#include"ALL.h"

//전체 코드 작성후 가변 배열로 변형
Queue *front[MAX_TELLER];
Queue *rear[MAX_TELLER];
int time_table[MAX_TELLER][3] = {0};
Statistic statistic_table[MAX_TELLER] = { 0 };

int main()
{
	struct tm *date;
	int teller_idx;
	int std_hour, std_min, std_sec;
	srand((unsigned int)time(NULL));

	for (teller_idx = 0; teller_idx < MAX_TELLER; teller_idx++)
	{
		front[teller_idx] = Add_new_queue();
		rear[teller_idx] = Add_new_queue();
	}

	date = Get_time();
	std_hour = date->tm_hour;
	std_min = date->tm_min;
	std_sec = date->tm_sec;

	while (1)
	{
		date = Get_time();

		printf("%d/%d/%d %d:%d:%d.%d\n", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);
		system("pause");
		system("cls");
	}
	


	

	
}