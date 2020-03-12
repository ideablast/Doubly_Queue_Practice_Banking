#include"ALL.h"

//��ü �ڵ� �ۼ��� ���� �迭�� ����
Queue *front[MAX_TELLER];
Queue *rear[MAX_TELLER];
int time_table[MAX_TELLER][MAX_QUEUE] = {0};
Statistic statistic_table[MAX_TELLER] = { 0 };

int main()
{
	struct tm *date;
	int teller_idx;
	int std_hour, std_min, std_sec;
	int teller_id;
	int customer_id = 1;
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
		if (customer_id > MAX_CUSTOMER+1)
			break;

		deQueue_Customer();
		Sleep(1000);
		enQueue_Teller_Change();
		Sleep(1000);
		if (enQueue_New_Customer(customer_id) == TRUE)
			customer_id++;

	}

	for (teller_idx = 0; teller_idx < MAX_TELLER; teller_idx++)
	{
		printf("â�� ��ȣ: %d\n",teller_idx);
		printf("�� ó�� �� ����: %d  �� ó�� �ð�: %d\n", statistic_table[teller_idx].total_customer, statistic_table[teller_idx].total_proccessing_time);
	}
	
	


	

	
}