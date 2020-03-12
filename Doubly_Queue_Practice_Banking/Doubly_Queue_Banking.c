#include"ALL.h"

extern Queue *front[MAX_TELLER];
extern Queue *rear[MAX_TELLER];
extern int time_table[MAX_TELLER][MAX_QUEUE];
extern Statistic statistic_table[MAX_TELLER];

/*DOUBLY_QUEUE_BANKING_VER*/
Queue* Add_new_queue()
{
	Queue *temp = (Queue*)malloc(sizeof(Queue));
	temp->Customer.name = '\0';
	temp->Customer.number = FAIL;
	temp->Customer.need_time = FAIL;
	temp->Customer.std_time = FAIL;
	temp->L_Link = NULL;
	temp->R_Link = NULL;

	return temp;
}

//front[teller_id], rear[teller_id]�� ��ũ�� L_Link�� ���
void L_enQueue(int teller_id, Customer Ctemp)//front[teller_id]�� �߰��ȴ�.
{
	Queue *temp = Add_new_queue();
	temp->Customer.name = Ctemp.name;
	temp->Customer.number = Ctemp.number;
	temp->Customer.need_time = Ctemp.need_time;
	temp->Customer.std_time = Ctemp.std_time;

	if (front[teller_id]->L_Link == NULL)
	{
		front[teller_id]->L_Link = temp;
		rear[teller_id]->L_Link = temp;
	}
	else
	{
		front[teller_id]->L_Link->L_Link = temp;
		temp->R_Link = front[teller_id]->L_Link;
		front[teller_id]->L_Link = temp;
	}
}

void R_enQueue(int teller_id, Customer Ctemp)//rear[teller_id]�� �߰��ȴ�.
{
	Queue *temp = Add_new_queue();
	temp->Customer.name = Ctemp.name;
	temp->Customer.number = Ctemp.number;
	temp->Customer.need_time = Ctemp.need_time;
	temp->Customer.std_time = Ctemp.std_time;

	if (rear[teller_id]->L_Link == NULL)
	{
		front[teller_id]->L_Link = temp;
		rear[teller_id]->L_Link = temp;
	}
	else
	{
		rear[teller_id]->L_Link->R_Link = temp;
		temp->L_Link = rear[teller_id]->L_Link;
		rear[teller_id]->L_Link = temp;
	}
}

Customer R_deQueue(int teller_id)//rear[teller_id]���� ������.
//�ƹ��͵� ������ �ϳ��϶� �������϶�.
{
	Queue *deQueue_mem;
	Customer deQueue_nData;
	Customer result;

	deQueue_mem = rear[teller_id]->L_Link;
	deQueue_nData = rear[teller_id]->L_Link->Customer;
	result = deQueue_nData;

	if (rear[teller_id]->L_Link != front[teller_id]->L_Link)
	{

		rear[teller_id]->L_Link = deQueue_mem->L_Link;
		rear[teller_id]->L_Link->R_Link = deQueue_mem->R_Link;
		free(deQueue_mem);
	}
	else
	{
		front[teller_id]->L_Link = deQueue_mem->L_Link;
		rear[teller_id]->L_Link = deQueue_mem->L_Link;
		free(deQueue_mem);
	}

	return result;
}

Customer L_deQueue(int teller_id)//front[teller_id]���� ������. 

			   //�ƹ��͵� ������ �ϳ��϶� �������϶�.
{
	Queue *deQueue_mem;
	Customer deQueue_nData;
	Customer result;

	deQueue_mem = front[teller_id]->L_Link;
	deQueue_nData = front[teller_id]->L_Link->Customer;
	result = deQueue_nData;

	if (front[teller_id]->L_Link != rear[teller_id]->L_Link)
	{
		front[teller_id]->L_Link = deQueue_mem->R_Link;
		front[teller_id]->L_Link->L_Link = deQueue_mem->L_Link;//deQueue_mem->L_Link�̰� ��� NULL???
		free(deQueue_mem);
	}
	else
	{
		front[teller_id]->L_Link = deQueue_mem->R_Link;
		rear[teller_id]->L_Link = deQueue_mem->R_Link;
		free(deQueue_mem);
	}

	return result;
}

int IsEmpty(int teller_id)
{
	return front[teller_id]->L_Link == NULL;
}

int Count_Queue(int teller_id)
{
	int cnt = 0;
	Queue *Count = front[teller_id]->L_Link;


	while (Count != NULL)
	{
		cnt++;
		Count = Count->R_Link;
	}
	cnt++;

	return cnt;
}

void Print_Queue(int teller_id)
{
	Queue *Count = front[teller_id]->L_Link;
	
	printf("â�� ��ȣ:%d (", teller_id);
	while (Count != NULL)
	{
		Show_Customer(Count);
		Count = Count->R_Link;
	}

}

void Show_Customer(Queue *temp)
{
	printf("%d %c %d %d)\n", temp->Customer.number, temp->Customer.name, temp->Customer.std_time, temp->Customer.need_time);
}


/*BANKING*/
//Time_Table ������Ʈ�� 3���� ��� L_deQueue, R_enQueue, R_deQueue
void Time_Table_Update_L_deQueue(int teller_id)
{
	int idx;
	for (idx = 0; idx < MAX_QUEUE - 1; idx++)
	{
		time_table[teller_id][idx] = time_table[teller_id][idx + 1];
	}
	time_table[teller_id][MAX_QUEUE - 1] = 0;
}

void Time_Table_Update_teller_change_R_deQueue(int teller_id)//��Ȯ�� �ʿ��� �������ڸ� �Ѱ��ִ°��� ������ ������?
//RdeQueue�Ŀ� �� ����
{
	time_table[teller_id][Count_Queue(teller_id)] = 0;//����ť�� rear ��ü deQueue�ð��� 0���� �ʱ�ȭ ����
	//���� ť�� ������ �̹� �پ������Ƿ� ������ ������Ʈ �ؾ��� �ε����� �������� ��
}

void Time_Table_Update_R_enQueue(int teller_id, Customer temp)
//RenQueue�Ŀ� ������Ʈ->1���� �þ �Ŀ� �� ť�� ������ �ּ� 1����~
{
	if (Count_Queue(teller_id) == 1)
	{
		time_table[teller_id][0] = temp.std_time + temp.need_time;//��ü�� ���� �ð� + ��ü�� �ʿ��� �ð�
	}
	else
	{
		//���� �� ť�� ���ο� rear ��ü�� �ʿ��� �ð��� ���� rear ��ü�� deQueue�ð��� ���ؼ� ������Ʈ ���ش�.
		time_table[teller_id][Count_Queue(teller_id) - 1] = time_table[teller_id][Count_Queue(teller_id) - 2] + temp.need_time;
	}
}

void Banking_Congestion_Simulation()
{

}

void deQueue_Customer( )
{
	struct tm *date;
	int cur_time;
	Customer temp;
	int teller_id;
	date = Get_time();
	cur_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);

	for (teller_id = 0; teller_id < MAX_TELLER; teller_id++)
	{
		if (IsEmpty(teller_id) == FALSE)
		{
			if (time_table[teller_id][0] = cur_time)
			{
				temp = L_deQueue(teller_id);
				Time_Table_Update_L_deQueue(teller_id);//deQueue �ð�ǥ ������Ʈ
				statistic_table[teller_id].total_customer++;//��� ���
				statistic_table[teller_id].total_proccessing_time += temp.need_time;//��� ���
			}
			else if (time_table[teller_id][0] < cur_time)
			{
				temp = L_deQueue(teller_id);
				Time_Table_Update_L_deQueue(teller_id);
				statistic_table[teller_id].total_customer++;
				statistic_table[teller_id].total_proccessing_time += temp.need_time;
				deQueue_Customer();//�ð��� �зȴٴ� ������ �и��� ������ ���� ��� �ݺ�
			}
			else
			{

			}
			Print_Queue(teller_id);
		}
	}

	
}

void enQueue_Teller_Change()
{
	int idx;
	int min_idx;
	int teller_id;
	struct tm *date;
	int deQueue_time[MAX_TELLER] = { 0 };
	Customer temp;

	for (teller_id = 0; teller_id < MAX_TELLER; teller_id++)
	{
		if (IsEmpty(teller_id) == FALSE)
		{
			for (idx = 0; idx < MAX_TELLER; idx++)
			{
				deQueue_time[idx] = time_table[idx][Count_Queue(teller_id) - 1];
			}

			min_idx = 0;
			for (idx = 0; idx < MAX_TELLER; idx++)
			{
				if (deQueue_time[min_idx] > deQueue_time[idx])
					min_idx = idx;//��� �ð��� ���� ª�� â�� ��ȣ
			}
			temp = R_deQueue(teller_id);
			Time_Table_Update_teller_change_R_deQueue(teller_id);
			R_enQueue_Banking_ver(min_idx, temp);
		}
		Print_Queue(teller_id);
	}
	
}

//enQueue�� ������ �ű� ���� �����°� ���� ���� â���� �ٲٴ°�!

int enQueue_New_Customer(int customer_id)//��� �������� �̾Ƽ� 
{
	int result;
	int teller_id;
	Customer waiting_customer;

	//�����°� �ֿ켱, �ڸ��̵��� 2, ���� �����°� 3����
	while (1)
	{
		teller_id = rand() % MAX_TELLER;
		if (Count_Queue(teller_id) < MAX_QUEUE)//ó������ �������� ������ ��ȣ�� ��������
		{
			waiting_customer = Making_rand_customer();
			waiting_customer.number = customer_id;
			R_enQueue_Banking_ver(teller_id, waiting_customer);
			result = TRUE;
			Print_Queue(teller_id);
			break;
		}
	}
	return result;
}

void R_enQueue_Banking_ver(int teller_id, Customer temp)
{
	struct tm *date;
	date = Get_time();
	temp.std_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);
	R_enQueue(teller_id, temp);
	Time_Table_Update_R_enQueue(teller_id, temp);
}


Customer Making_rand_customer()
{
	Customer temp;
	temp.name = rand() % 26 + 65;
	temp.need_time = rand() % MAX_WAITING_TIME + 1;

	return temp;
}

/*TIME*/
struct tm *Get_time()//�Լ��� ����ɶ� ���� ���� �ð��� ���� �� ����
{
	const time_t t = time(NULL);
	return localtime(&t);
}

int To_sec(int hour, int min, int sec)
{
	return (hour * 3600) + (min * 60) + sec;
}


#ifdef NOTYET

void deQueue_Checker()
{
	struct tm *date;
	int cur_time;

	date = Get_time();
	cur_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);


}

int Cal_ms(void)
{
	int* random_array, x = 0;
	double total = 0;
	LARGE_INTEGER Frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;


	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&start);

	random_array = (int*)malloc(MAX_ARRAY * sizeof(int));

	while (x < MAX_ARRAY)
	{
		random_array[x] = rand() % 10;
		total += random_array[x];
		x++;
	}

	QueryPerformanceCounter(&end);

	double ms = (end.QuadPart - start.QuadPart) * 1000.0 / Frequency.QuadPart;

	//printf(" x = %d\n", x);
	printf("Total : %f   Time : %.3f ms", total, ms);

	getchar();
	return 0;
}

#endif
