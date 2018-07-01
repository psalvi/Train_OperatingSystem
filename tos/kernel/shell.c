/*Name: Priyanka Salvi
  Student ID: 917163772*/

#include <kernel.h>
static WINDOW trainw ={0,0,80,10,0,0,' '};

void shell_process(PROCESS self, PARAM param);

void start_shell()
{
 
 create_process(shell_process,3,4,"Shell process");
 resign();

}


void shell_process(PROCESS self, PARAM param)
{
  char ok[20];
  char ch;
  int i=0,k,l,m=49, n=0;
  char word[100][100];
  char shell[6]={'s','h','e','l','l','\0'};// predefined value
  char help[5]={'h','e','l','p','\0'};
  char ps[3]= {'p','s','\0'};
  char pong[5]={'p','o','n','g','\0'};
  char history[8]={'h','i','s','t','o','r','y','\0'};
  char cls[4]={'c','l','s','\0'};
  char about[6]={'a','b','o','u','t','\0'};
  char train[6]={'t','r','a','i','n','\0'};
  char num[2] = {'!'};
  int window_id = wm_create(10,3,50,17);  // creating shell window
  
  wm_print(window_id,">");
  
  while (1)// main loop
  { 
   ch = keyb_get_keystroke(window_id, TRUE);// waiting for keyboard
   if(ch == 0x20) // handling white spaces
   {
    wm_print(window_id, "%c",ch);
   }
   else if(ch ==0x08)  // handling backspace
   {
    wm_print(window_id, "%c",ch);
    i--;
   }
   else if(ch == 0x0D)  // executing the command when press enter
   { 
    ok[i] ='\0';
    i=0;
    k=0;
    int response =0;
    
    // comparing the command with predefined commands
    while(ok[k] != '\0')
    {
     if (ok[k] == shell[k])
     {
      response = response+2;
     }
     else if(ok[k] == ps[k])
     {
      response= response +27;
     } 
     else if(ok[k] == help[k])
     {
      response = response +11;
     } 
     else if(ok[k] == pong[k])
     {
      response= response+1;
     } 
     else if(ok[k] == about[k])
     {
      response=response +3;
     } 
     else if(ok[k] == cls[k])
     {
      response =response +12;
     } 
     else if(ok[k] == history[k])
     {
      response = response+10;
     } 
     else if(ok[k] == train[k])
     { 
      response++;
     }
     else if(ok[0] == num[0])
     { 
      response=1;
     }
     else
     break;
     k++;
    }
   
    
   
   //executing command
   switch (response)
   {
    case 1:  // !<index number>
     {
      char yu;
      yu = ok[1]; //retrieving the number of command in the list
      l=0;
      int check=0;
      int ent =(int) yu;
      while( word[ent][l] !='\0')
      {
       if (word[ent][l] == shell[l])
       {
        check = check +2;
       }
       else if(word[ent][l]  == ps[l])
       {
        check= check + 27;
       } 
       else if(word[ent][l]  == help[l])
       {
        check =check+11;
       } 
       else if(word[ent][l]  == pong[l])
       {
        check= check +1;
       } 
       else if(word[ent][l]  == about[l])
       {
        check=check +3;
       } 
       else if(word[ent][l]  == cls[l])
       {
        check =check+12;
       } 
       else if(word[ent][l]  == history[l])
       {
        check= check+10;
       } 
       else if(word[ent][l] == train[l])
       { 
        check++;
       }
       l++;
      }
      switch (check)
      {
       case 54:
       {
        char q = NULL;
        do{
           shell_print_all_processes(window_id);
           q = keyb_get_keystroke(window_id, TRUE);//
           sleep(5);
          }while(q == NULL);
        wm_print(window_id,"\n>");
       }
       break;
   
       case 44: 
       {
        wm_print(window_id,"\n");
	wm_print(window_id,"List of TOS commands:\n");
	wm_print(window_id,"help      -displays information about all TOS commands\n");
        wm_print(window_id,"about     -Maker information\n");
	wm_print(window_id,"cls       -clears the screen\n");
	wm_print(window_id,"pong      -launches the pong game\n");
	wm_print(window_id,"ps        -prints the process table\n");
        wm_print(window_id,"history   -prints all the previous commands run on the shell\n");
        wm_print(window_id,"!<no.>    -prints the command in history list\n");
        wm_print(window_id,"train     -launches the train app\n");
	wm_print(window_id,"shell     -launches another shell\n>");
       } 
       break;

       case 10:
       { 
        create_process(shell_process,7,6,"Shell process");
        wm_print(window_id,"\n>");
       }
       break;
   
       case 36: 
       {
        wm_clear(window_id);
        wm_print(window_id,">");
       }
       break;
   
       case 30:
       { 
        start_pong();
        wm_print(window_id,"\n>");
       }
       break;
       case 5:
       { 
        start_train();
        wm_print(window_id,"\n>");
       } 
       break;
       case 15: 
       {
        wm_print(window_id,"\nShell created by Pyou :)\n>");
       }
       break;
  
       case 73:
       {
        int j=49;
        int h=1;
        wm_print(window_id,"\n");
        while(j <= m-1)
        {
         wm_print(window_id, "%d.",h);
         l=0;
         while(word[j][l] != '\0')
         {   
          wm_print(window_id,"%c",word[j][l]);
          l++;
         }
         wm_print(window_id, "\n");
         j++;
         h++;
        }
       }
       wm_print(window_id,"\n>");
       break;

       default:
       {
        wm_print(window_id,"\nInvalid command please use help\n>");
        response =0;
        break;
       }
      }
     }
     break;
  
     case 54: // ps command
     {
      char q = NULL;
      do{
         shell_print_all_processes(window_id);
         q = keyb_get_keystroke(window_id, TRUE);//
         sleep(5);
        }while(q == NULL);
      wm_print(window_id,"\n>");
     }
     break;
   
     case 44: // help command
     {
      wm_print(window_id,"\n");
      wm_print(window_id,"List of TOS commands:\n");
      wm_print(window_id,"help      -displays information about all TOS commands\n");
      wm_print(window_id,"about     -Maker information\n");
      wm_print(window_id,"cls       -clears the screen\n");
      wm_print(window_id,"pong      -launches the pong game\n");
      wm_print(window_id,"ps        -prints the process table\n");
      wm_print(window_id,"history   -prints all the previous commands run on the shell\n");
      wm_print(window_id,"!<no.>    -prints the command in history list\n");
      wm_print(window_id,"train     -launches the train app\n");
      wm_print(window_id,"shell     -launches another shell\n>");
     } 
     break;

     case 10: //shell command
     { 
      create_process(shell_process,7,6,"Shell process");
      wm_print(window_id,"\n>");
     }
     break;
   
     case 36: // cls command
     {
      wm_clear(window_id);
      wm_print(window_id,">");
     }
     break;
   
     case 30: //pong command
     { 
      start_pong();
      wm_print(window_id,"\n>");
     }
     break;
     
     case 5:
     { 
      start_train();
      wm_print(window_id,"\n>");
     } 
     break;
   
     case 15:  // about command
      wm_print(window_id,"\nShell created by Pyou :)\n>");
     break;
  
     case 73: // history command
     {
      int j =49;
      int h=1;
      wm_print(window_id,"\n");
      while(j <= m-1)
      {
       wm_print(window_id, "%d.",h);
       l=0;
       while(word[j][l] != '\0')
       {   
        wm_print(window_id,"%c",word[j][l]);
        l++;
       }
       wm_print(window_id, "\n");
       j++;
       h++;
      }
     }
     wm_print(window_id,"\n>");
     break;

     default:  // invalid command
     { 
      wm_print(window_id,"\nInvalid command please use help\n>");
      response =0;
      break;
     }
    }
    n=0;
    if(ok[0]=='!') // not to story !<index command in history list>
    { }
    else
    {
     while(ok[n] != '\0') // store all the valid commands in two dimensional array
     {  
      word[m][n] = ok[n];
      n++;
     }
     word[m][n] ='\0';
     m++;
    }
  }
  else // if enter is not pressed store the command in temp buffer and print on the shell
  {
   ok[i] = ch;
   wm_print(window_id, "%c",ch);
   i++;
  }
 }
}

void shell_print_process_heading(int window_id)
{
    wm_print(window_id, "\nState           Active Prio Name\n");
    wm_print(window_id, "------------------------------------------------\n");
}

void shell_print_process_details(int window_id, PROCESS p)
{
    static const char *state[] = 
	{ "READY          ",
	  "SEND_BLOCKED   ",
	  "REPLY_BLOCKED  ",
	  "RECEIVE_BLOCKED",
	  "MESSAGE_BLOCKED",
	  "INTR_BLOCKED   "
	};
    if (!p->used) {
	wm_print(window_id, "PCB slot unused!\n");
	return;
    }
    /* State */
    wm_print(window_id, state[p->state]);
    /* Check for active_proc */
    if (p == active_proc)
	wm_print(window_id, " *      ");
    else
	wm_print(window_id, "        ");
    /* Priority */
    wm_print(window_id, "  %2d", p->priority);
    /* Name */
    wm_print(window_id, " %s\n", p->name);
}

void shell_print_all_processes(int window_id)
{
    int i;
    PCB* p = pcb;
    
    shell_print_process_heading(window_id);
    for (i = 0; i < MAX_PROCS; i++, p++) {
	if (!p->used)
	    continue;
	shell_print_process_details(window_id, p);
    }
}

void start_train()
{
 init_train(&trainw);
 //wprintf(&trainw,"yayayay");
}

