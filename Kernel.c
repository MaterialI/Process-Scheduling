#include <stdio.h>
#include "PCB.h"
#include "Queue.h"
#include "Semaphore.h"



Queue** Ready_Queues[3];
Queue** Waiting_Queues[2]; 
Process* Current_Running;
Process* Init;
S** Kernel_Semaphores[5];
static unsigned int  PID_counter = 0;


void ErrorMessage(){

    printf("Skull Crashing Fault!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\n  Wrong input\n");
   FILE *fp;
   char* ch;
   fp = fopen("fault.txt", "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      return;
   }

   

   while((ch = fgetc(fp)) != EOF)
      printf("%c", ch);

   fclose(fp);
   printf("\n\n");
   return ;
}


int main(){ 

    // We create our 5 main queues 
    Queue* qLow = Queue_create(); Queue* qNorm = Queue_create(); Queue* qHigh = Queue_create();
    Queue* qReceive = Queue_create(); Queue* qSend = Queue_create();
    Ready_Queues[Low] = qLow;
    Ready_Queues[Medium] = qNorm;
    Ready_Queues[High] = qHigh;
    Waiting_Queues[High] = qReceive; 
    Waiting_Queues[Low] = qSend;
    Init = createProcess(2,&PID_counter,1);
    char user_input;

        printf("Welocme to the Shift it Shift0.1 Operating System\n\n");
    //PCB* init_kernel(Low , Ready_Queues , PID_counter++);
    // printf( "\n\nCOMMANDS"
	// 	 "\nC. Create"
	// 	 "\nF. Fork"
	// 	"\nK. Kill"
	// 	 "\nE. Exit"
    //      "\n Q. Quantum"
	// 	 "\nS. Send"
	// 	 "\nR. Receive"
    //      "\nY. Reply"
    //     "\nN. New Semaphore"
    //     "\nP. Sempahore P"
    //     "\nV. Sempahore V"
    //     "\nI. Procinfo"
    //     "\nT. Totalinfo"
    //      );

    	while(1)
	{
		

       printf("\n\nEnter your command:\n");
        user_input = getc(stdin);
    // swallow the '\n'
    getc(stdin);
		
        int prior; 
        printf("Give the Process priority");
        // scanf("%d", prior);
        // printf("%d", prior);
        printf("%d", PID_counter);
        printf("WHAT");
        createProcess(0, &PID_counter, 1);
        printf("%d",Init->PID);
				

		switch(user_input)	{
			case 'C':
                // Code for Create
                // int prior;
                // printf("Give the Process priority");
                // scanf("%d", prior);
                //createProcess(prior, )
                printf("%d",Init->PID);
				break;

			case 'F':
            // Code for Fork
                break;

			case 'K':
            // Code for Kill
                break;

			case 'E':
            // Code for Exit 
                break;

			case 'S':
            // Code for Send
				break;

			case 'R':
            // Code for Receive 
				break;
            case 'Y':
            // Reply
                break;
            case 'N':
            // Code for new Semaphore
                break;
            case 'P':
            // Code for P Semaphore
                break;
            case 'V':
            // Code for V Semaphore
                break;
            case 'I':
            //  Code Procinfo
                break;
            case 'T':
            // Code for Totalinfo
                break;

			default:
                ErrorMessage();


				break;
		}
	}
	return 0;
}
    