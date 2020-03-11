#ifndef __Data_H__
#define __Data_H__

typedef struct _Customer {

	int number;
	char name;
	int need_time;
	int std_time;

}Customer;


typedef struct _Queue {

	struct _Customer Customer;
	struct _Queue *L_Link;
	struct _Queue *R_Link;

}Queue;

typedef struct _Statistic {
	int total_customer;
	int total_proccessing_time;
}Statistic;


#endif

#define MAX_WAITING_TIME 3
#define MAX_TELLER 2
#define MAX_CUSTOMER 20

#define TRUE 1
#define FALSE 0
#define FAIL -1


