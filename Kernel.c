#include <stdio.h>
#include "PCB.h"
#include "list.h"



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

    createProcess(0);
    display_OS_Info();
    killProcess(1);
    display_OS_Info();

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
		
        display_OS_Info();
       printf("\n\nEnter your command:\n");
       char user_input;
        scanf(" %c", &user_input);

		switch(user_input)	{
			case 'C':
                // Code for Create
                scanf("%d", &pr);
                createProcess(pr);
				break;

			case 'F':
            // Code for Fork
            forkProcess();
                break;

			case 'K':
            // Code for Kill   
            scanf("%d", &pr);
             killProcess(pr);
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
    