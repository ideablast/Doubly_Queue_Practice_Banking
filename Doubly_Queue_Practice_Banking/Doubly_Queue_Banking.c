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

//front[teller_id], rear[teller_id]의 링크중 L_Link만 사용
void L_enQueue(int teller_id, Customer Ctemp)//front[teller_id]로 추가된다.
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

void R_enQueue(int teller_id, Customer Ctemp)//rear[teller_id]로 추가된다.
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

Customer R_deQueue(int teller_id)//rear[teller_id]부터 나간다.
//아무것도 없을때 하나일때 여러개일때.
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

Customer L_deQueue(int teller_id)//front[teller_id]부터 나간다. 

			   //아무것도 없을때 하나일때 여러개일때.
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
		front[teller_id]->L_Link->L_Link = deQueue_mem->L_Link;//deQueue_mem->L_Link이거 대신 NULL???
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
	
	printf("창구 번호:%d (", teller_id);
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
//Time_Table 업데이트의 3가지 경우 L_deQueue, R_enQueue, R_deQueue
void Time_Table_Update_L_deQueue(int teller_id)
{
	int idx;
	for (idx = 0; idx < MAX_QUEUE - 1; idx++)
	{
		time_table[teller_id][idx] = time_table[teller_id][idx + 1];
	}
	time_table[teller_id][MAX_QUEUE - 1] = 0;
}

void Time_Table_Update_teller_change_R_deQueue(int teller_id)//정확히 필요한 전달인자만 넘겨주는것이 습관상 좋은가?
//RdeQueue후에 할 생각
{
	time_table[teller_id][Count_Queue(teller_id)] = 0;//이전큐의 rear 개체 deQueue시간을 0으로 초기화 해줌
	//이전 큐의 갯수는 이미 줄어들었으므로 갯수와 업데이트 해야할 인덱스와 같아지게 됨
}

void Time_Table_Update_R_enQueue(int teller_id, Customer temp)
//RenQueue후에 업데이트->1개가 늘어난 후에 즉 큐의 갯수는 최소 1부터~
{
	if (Count_Queue(teller_id) == 1)
	{
		time_table[teller_id][0] = temp.std_time + temp.need_time;//개체가 들어온 시간 + 개체가 필요한 시간
	}
	else
	{
		//새로 들어갈 큐의 새로운 rear 개체가 필요한 시간을 이전 rear 개체의 deQueue시간에 더해서 업데이트 해준다.
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
				Time_Table_Update_L_deQueue(teller_id);//deQueue 시간표 업데이트
				statistic_table[teller_id].total_customer++;//통계 계산
				statistic_table[teller_id].total_proccessing_time += temp.need_time;//통계 계산
			}
			else if (time_table[teller_id][0] < cur_time)
			{
				temp = L_deQueue(teller_id);
				Time_Table_Update_L_deQueue(teller_id);
				statistic_table[teller_id].total_customer++;
				statistic_table[teller_id].total_proccessing_time += temp.need_time;
				deQueue_Customer();//시간이 밀렸다는 뜻으로 밀린게 없을때 까지 계속 반복
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
					min_idx = idx;//대기 시간이 가장 짧은 창구 번호
			}
			temp = R_deQueue(teller_id);
			Time_Table_Update_teller_change_R_deQueue(teller_id);
			R_enQueue_Banking_ver(min_idx, temp);
		}
		Print_Queue(teller_id);
	}
	
}

//enQueue도 두종류 신규 고객이 들어오는것 기존 고객이 창구를 바꾸는것!

int enQueue_New_Customer(int customer_id)//계속 랜덤으로 뽑아서 
{
	int result;
	int teller_id;
	Customer waiting_customer;

	//나가는게 최우선, 자리이동이 2, 새로 들어오는게 3순위
	while (1)
	{
		teller_id = rand() % MAX_TELLER;
		if (Count_Queue(teller_id) < MAX_QUEUE)//처음에는 랜덤으로 생성된 번호로 배정해줌
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
struct tm *Get_time()//함수가 실행될때 마다 현재 시간을 구할 수 있음
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
