#include <stdio.h>
#include "Queue.h"
#include "PCB.h"
#include "Semaphore.h"



Queue** Ready_Queues[3];
Queue** Waiting_Queues[3]; 
//PCB* Running;
//Semaphore** Kernel_Semaphores[5];
static unsigned int PID_counter  = 0;


void ErrorMessage(){

    printf("Wrong Input\n\n");
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
    char user_input;

        printf("Welocme to the Shift it Shift0.1 Operating System\n\n");

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
    

}
