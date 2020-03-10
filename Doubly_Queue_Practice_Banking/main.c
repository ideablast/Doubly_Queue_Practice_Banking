#include"ALL.h"

Queue *front[MAX_TELLER];
Queue *rear[MAX_TELLER];

int main()
{
	struct tm *date;
	int teller_idx;
	

	for (teller_idx = 0; teller_idx < MAX_TELLER; teller_idx++)
	{
		front[teller_idx] = Add_new_queue();
		rear[teller_idx] = Add_new_queue();
	}

	date = get_time();
	while (1)
	{
		date = get_time();

		printf("%d/%d/%d %d:%d:%d\n", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min, date->tm_sec);
		system("pause");
		system("cls");
	}
	


	

	
}