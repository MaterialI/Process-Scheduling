#include <stdio.h>
#include "Kernel.h"
#include "Queue.h"
#include "PCB.h"
#include "Semaphore.h"



Queue** Ready_Queues[3];
Queue** Waiting_Queues[3]; 
//PCB* Running;
//Semaphore** Kernel_Semaphores[5];
static unsigned int PID_counter  = 0;





int main(){
    // We create our 5 main queues 
    Queue* Low = Queue_create(); Queue* Norm = Queue_create(); Queue* High = Queue_create(); 
    Queue* Waiting_Receive = Queue_create(); Queue* Waiting_Sender = Queue_create(); 

    Ready_Queues[2] = Low; Ready_Queues[1] = Norm; Ready_Queues[0] = High;
    Waiting_Queues[0] = Waiting_Receive; Waiting_Queues[1] = Waiting_Sender;
    char user_input;

    //PCB* init_kernel(Low , Ready_Queues , PID_counter++);

    	while(1)
	{
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


        scanf("%c",user_input);
		
		switch(user_input)	{
			case 'C':
                // Code for Create
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
            // 
                break;
            case 'T':
                break;

			default:
				printf("Wrong Input\n\n");
                printf("Dog Fault");!!!!!	
				break;
		}
	}
	return 0;
}
    

}
