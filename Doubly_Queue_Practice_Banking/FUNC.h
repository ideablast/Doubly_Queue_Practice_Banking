#pragma once
#include"ALL.h"

#ifndef __FUNC_H__
#define __FUNC_H__

/*DOUBLY_QUEUE_BANKING_VER*/
Queue* Add_new_queue();
void L_enQueue(int teller_id, Customer Ctemp);
void R_enQueue(int teller_id, Customer Ctemp);
Customer L_deQueue(int teller_id);
Customer R_deQueue(int teller_id);
int IsEmpty(int teller_id);
int Count_Queue(int teller_id);
/*BANKING*/
void Simulate_Bank_Congestion();
Customer Making_rand_customer();

/*TIME*/
struct tm *Get_time();
int To_sec(int hour, int min, int sec);

#endif

