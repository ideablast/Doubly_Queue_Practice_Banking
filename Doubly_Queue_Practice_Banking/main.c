#include"ALL.h"

Queue *front[MAX_TELLER];
Queue *rear[MAX_TELLER];

int main()
{
	int teller_idx;

	for (teller_idx = 0; teller_idx < MAX_TELLER; teller_idx++)
	{
		front[teller_idx] = Add_new_queue();
		rear[teller_idx] = Add_new_queue();
	}
	

	
}