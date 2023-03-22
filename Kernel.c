#include <stdio.h>
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
     Init = createProcess(2,&PID_counter,qLow);
    char user_input;

        printf("Welocme to the Shift it Shift0.1 Operating System\n\n");
    //PCB* init_kernel(Low , Ready_Queues , PID_counter++);
    printf( "\n\nCOMMANDS"
		 "\nC. Create"
		 "\nF. Fork"
		"\nK. Kill"
		 "\nE. Exit"
		 "\nS. Send"
		 "\nR. Receive"
         "\nY. Reply"
        "\nN. New Semaphore"
        "\nP. Sempahore P"
        "\nV. Sempahore V"
        "\nI. Procinfo"
        "\nT. Totalinfo"
         "\n\nEnter your choice: ");

    	while(1)
	{
		

       // printf("enter new message\n");
        scanf("%d",user_input);
		

		switch(user_input)	{
			case 'C':
                // Code for Create
                // int prior;
                // printf("Give the Process priority");
                // scanf("%d", prior);
                //createProcess(prior, )
                         printf("%d",Init->PID);
				continue;

			case 'F':
            // Code for Fork
                continue;

			case 'K':
            // Code for Kill
                continue;

			case 'E':
            // Code for Exit 
                continue;

			case 'S':
            // Code for Send
				continue;

			case 'R':
            // Code for Receive 
				continue;
            case 'Y':
            // Reply
                continue;
            case 'N':
            // Code for new Semaphore
                continue;
            case 'P':
            // Code for P Semaphore
                continue;
            case 'V':
            // Code for V Semaphore
                continue;
            case 'I':
            //  Code Procinfo
                continue;
            case 'T':
            // Code for Totalinfo
                continue;

			default:
                ErrorMessage();


				break;
		}
	}
	return 0;
}
    