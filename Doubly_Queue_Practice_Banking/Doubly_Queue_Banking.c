#include"ALL.h"

extern Queue *front[MAX_TELLER];
extern Queue *rear[MAX_TELLER];

Queue* Add_new_queue()
{
	Queue *temp = (Queue*)malloc(sizeof(Queue));
	temp->Customer.name = '\0';
	temp->Customer.number = FAIL;
	temp->Customer.time = FAIL;
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
	temp->Customer.time = Ctemp.time;

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
	temp->Customer.time = Ctemp.time;

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

	if (rear[teller_id]->L_Link == NULL)
	{
		result.name = '\0';
		result.number = FAIL;
		result.time = FAIL;
	}
	else
	{
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
		
	}
	
	return result;
}

Customer L_deQueue(int teller_id)//front[teller_id]부터 나간다. 

			   //아무것도 없을때 하나일때 여러개일때.
{
	Queue *deQueue_mem;
	Customer deQueue_nData;
	Customer result;

	if (front[teller_id]->L_Link == NULL)
	{
		result.name = '\0';
		result.number = FAIL;
		result.time = FAIL;
	}
	else
	{
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
	}

	return result;
}

int IsEmpty(int teller_id)
{
	return (front[teller_id]->L_Link == NULL) && (rear[teller_id]->L_Link == NULL);
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
