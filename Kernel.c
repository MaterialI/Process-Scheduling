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

    Current_Running = Init;
    char user_input;
    int prior;
    
    printf("%d",Init->PID);
    printf("Welocme to the Shift it Shift0.1 Operating System\n\n");
        
    printf( "\n\nCOMMANDS"
		 "\nC. Create"
		 "\nF. Fork"
		"\nK. Kill"
		 "\nE. Exit"
         "\n Q. Quantum"
		 "\nS. Send"
		 "\nR. Receive"
         "\nY. Reply"
        "\nN. New Semaphore"
        "\nP. Sempahore P"
        "\nV. Sempahore V"
        "\nI. Procinfo"
        "\nT. Totalinfo"
         );

         //***testing 
          createProcess(0,&PID_counter , Ready_Queues );    
        if(Current_Running == Init)
        {Current_Running ==Next_Running_Process(Ready_Queues , 3); }
        Process* new = createProcess(1,&PID_counter , Ready_Queues );
          killProcess(Current_Running , 3, Ready_Queues , Waiting_Queues);
        //***testing
    	while(1)
	{
		

       printf("\n\nEnter your command:\n");
       char user_input;
        scanf(" %c", &user_input);

		switch(user_input)	{
			case 'C':
                // Code for Create
                printf("Enter the Process priority\n");
                 scanf("%d", &prior);
                  createProcess(prior,&PID_counter , Ready_Queues );    
                 if(Current_Running == Init){Current_Running ==Next_Running_Process(Ready_Queues , 3); }
				break;

			case 'F':
            // Code for Fork
            printf("Fork\n");
            forkProcess(Current_Running, &PID_counter, Ready_Queues);
                break;

			case 'K':
            // Code for Kill
            // To Do : the case for Init as the running process
            killProcess(Current_Running , &PID_counter , Ready_Queues , Waiting_Queues);
                break;

			case 'E':
            // Code for Exit 

            // To Do : The case for Init Process
            exitProcess(Current_Running , Ready_Queues);
            Current_Running = Next_Running_Process(Ready_Queues , 3);
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
    