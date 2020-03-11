#include"ALL.h"

extern Queue *front[MAX_TELLER];
extern Queue *rear[MAX_TELLER];
extern int time_table[MAX_TELLER][3];

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

	while (Count->R_Link != NULL)
	{
		cnt++;
		Count = Count->R_Link;
	}
	cnt++;

	return cnt;
}

/*BANKING*/
void Simulate_Bank_Congestion(int customer_id)//한번 실행 할때 마다 한사람씩 처리
{
	
}

void deQueue_checker()
{
	struct tm *date;
	int cur_time;

	date = Get_time();
	cur_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);


}

void deQueue_customer(int teller_id )
{
	struct tm *date;
	int cur_time;
	date = Get_time();
	cur_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);

	if (IsEmpty(teller_id) != FALSE)
	{
		if (time_table[teller_id][0] = cur_time)
		{

		}
		else if (time_table[teller_id][0] < cur_time)
		{

		}
		else
		{

		}
	}
}

void enQueue_customer(int customer_id)//계속 랜덤으로 뽑아서 
{
	struct tm *date;
	int result;
	int teller_id;
	Customer waiting_customer;

	//나가는게 최우선, 자리이동이 2, 새로 들어오는게 3순위
	while (1)
	{
		teller_id = rand() % MAX_TELLER;
		if (Count_Queue(teller_id) < 3)//처음에는 랜덤으로 생성된 번호로 배정해줌
		{
			waiting_customer = Making_rand_customer();
			waiting_customer.number = customer_id;
			date = Get_time();
			waiting_customer.std_time = To_sec(date->tm_hour, date->tm_min, date->tm_sec);//초로 바꿔서 저장
			R_enQueue(teller_id, waiting_customer);
		}

	}
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
