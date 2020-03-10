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

/*TIME*/
struct tm *get_time();

#endif

