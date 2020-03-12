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
void Print_Queue(int teller_id);
void Show_Customer(Queue *temp);
/*BANKING*/
void Time_Table_Update_L_deQueue(int teller_id);
void Time_Table_Update_teller_change_R_deQueue(int teller_id);
void Time_Table_Update_R_enQueue(int teller_id, Customer temp);
void deQueue_Customer();
void enQueue_Teller_Change();
int enQueue_New_Customer(int customer_id);
void R_enQueue_Banking_ver(int teller_id, Customer temp);
Customer Making_rand_customer();

/*TIME*/
struct tm *Get_time();
int To_sec(int hour, int min, int sec);

#endif

