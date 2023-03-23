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

    Init = Init_Process(Running , 0 , PID );
    Current_Running = Init_Process;


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
        
    	while(1)
	{
		

       printf("\n\nEnter your command:\n");
       char user_input;
        scanf(" %c", &user_input);

		switch(user_input)	{
			case 'C':
                // Code for Create
                createProcess(1);
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
            
            case 'Q':
            //code for Quantum
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
    