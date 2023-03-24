#include <stdio.h>
#include "PCB.h"
#include "list.h"
#include "Semaphore.h"


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

    start_OS();
    int pr ;
    int t_pid, val;
    char* msg = malloc(sizeof(char)*100);



    printf("Welocme to the Shift it Shift0.1 Operating System\n\n");
        
    
        
    	while(1)
	{

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
        "\nT. Totalinfo\n"
         );

        display_OS_Info();
       printf("\n\nEnter your command:\n");
       char user_input;
        scanf(" %c", &user_input);

		switch(user_input)	{
			case 'C':
                // Code for Create
                printf("Enter pid for the process\n");
                scanf("%d", &pr);
                createProcess(pr);
				break;

			case 'F':
            // Code for Fork
            forkProcess();
                break;

			case 'K':
            // Code for Kill
            printf("Enter pid for the process to be killed\n");   
            scanf("%d", &pr);
             killProcess(pr);
                break;

			case 'E':
            exitProcess();
            // Code for Exit 

            
                break;
            
            case 'Q':
            quantumProcess();
            //code for Quantum
                break;

			case 'S':
            // Code for Send
            printf("Enter pid and message to be sent\n");
            scanf("%d", &t_pid);
            scanf("%s", &msg);
            sendProcess(t_pid, &msg);
				break;

			case 'R':
            // Code for Receive 
            receiveProcess();
				break;
            case 'Y':
            // Reply
            printf("Enter pid and message to be sent\n");
            scanf("%d", &t_pid);
            scanf("%s", &msg);
            replyProcess(t_pid, &msg);
                break;
            case 'N':
            // Code for new Semaphore
            printf("Enter semaphore id (0-4) and value of the semaphore\n");
            scanf("%d", &t_pid);
            scanf("%d", &val);
            newSemaphore(t_pid, val);
                break;
            case 'P':
            // Code for P Semaphore
            printf("Enter the id of the semaphore:");
            scanf("%d", &t_pid);
            P(t_pid);
                break;
            case 'V':
            // Code for V Semaphore
            printf("Enter the id of the semaphore:");
            scanf("%d", &t_pid);
            V(t_pid);
                break;
            case 'I':
            //  Code Procinfo
            scanf("%d", &pr);
            Procinfo(pr);
            
                break;
            case 'T':
            // Code for Totalinfo
            Totalinfo();
                break;

			default:
                ErrorMessage();


				break;
		}
	}
	return 0;
}
    