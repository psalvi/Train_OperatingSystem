/* 
Name : Priyanka Salvi
SF state ID: 917163772
*/
#include <kernel.h>
#define trainno "20\0"
void train_process(PROCESS self, PARAM param);
void init_switches();
void set_switch(char , char );
void comSending(char*);
void concatenate_string(char*, char*);
void clear_membuf();
void speed(char);
void reverse();
int configure1();
int zamboniCheck();
int trackStatus(char*);
int configCheck();
int configure1wzam();
int configure2wzam();
int configure3wzam();
int configure4wzam();
int configure2();
int configure4();
int configure3();


int ticks =12;


//**************************
//run the train application
//**************************

void init_train(WINDOW* wnd)
{
 create_process(train_process,5,0,"train process"); 
}

void train_process(PROCESS self, PARAM param)
{
 
 int train = wm_create(1,3,40,10);
 wm_clear(train);
 wm_print(train,"Starting Train Application\n");
 wm_print(train,"Initializing switches\n");
 wm_print(train,"Looking for Zamboni\n");
 
 int zambo = 0;
 int configuration =0;
 init_switches();
 void clear_membuf();
 
 zambo = zamboniCheck();
 
 if(zambo)
 { 
  wm_print(train,"zamboni found\n");
  if(zambo == 7)
  {
   wm_print(train,"zamboni is rotating clockwise\n");
  }
  else if(zambo == 13)
  {
   wm_print(train,"zamboni is rotating anticlockwise\n");
  }
 }
 else
 wm_print(train,"zamboni not found\n");
 
 configuration = configCheck();
 if(configuration == 1 && zambo)
 { 
  wm_print(train,"configuration with zam = %d\n",configuration);
  int k = configure1wzam();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
 else if(configuration == 1)
 { 
  wm_print(train,"configuration = %d\n",configuration);
  int k = configure1();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
 else if(configuration == 2 && zambo)
 { 
  wm_print(train,"configuration with zam = %d\n",configuration);
  int k = configure2wzam();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
  else if(configuration == 2)
 { 
  wm_print(train,"configuration = %d\n",configuration);
  int k = configure2();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
 else if(configuration == 3 && zambo)
 { 
  wm_print(train,"configuration with zam = %d\n",configuration);
  int k = configure3wzam();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
  else if(configuration == 3)
 { 
  wm_print(train,"configuration = %d\n",configuration);
  int k = configure3();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
 else if(configuration == 4 && zambo)
 { 
  wm_print(train,"configuration with zam = %d\n",configuration);
  int k = configure4wzam();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
 else if(configuration == 4)
 { 
  wm_print(train,"configuration = %d\n",configuration);
  int k = configure4();
  if(k)
  wm_print(train,"Reached home base safely\n");
 }
  
 wm_print(train,"You win Tata:)\nHave a great day !!!!\n");
 remove_ready_queue(active_proc);
 resign();
 while(1);

  
}

void init_switches()
{
 set_switch('5','G');
 set_switch('8','G');
 set_switch('9','R');
 set_switch('1','G');
 set_switch('4','G');
}

void set_switch(char swt , char rg)
{
 char data[5];
 data[0] = 'M';
 data[1] = swt;
 data[2] = rg;
 data[3] = '\0';
 comSending(data);
}

void comSending(char* cdata)
{
 char finaldata[15];
 finaldata[0] = '\0';
 COM_Message message;
 
 concatenate_string(finaldata, cdata);
 concatenate_string(finaldata, "\015");
 
 char input[15];
 int length =0;
 
 message.output_buffer = finaldata;
 message.len_input_buffer = length;
 message.input_buffer = input;
 sleep(ticks);
 send(com_port,&message);
}

void concatenate_string(char* data1, char* data2)
{
 while(*data1 != '\0')
 { 
  data1++;
 }
 while(*data2 != '\0')
 { 
  *data1 = *data2;
  data1++;
  data2++;
 }
 *data1 ='\0';
}

void clear_membuf()
{
 char data[10];
 data[0] = 'R';
 data[1] = '\0';
 comSending(data);
}

int zamboniCheck()
{
 int zambonifound = 0;
 int i=0;
 for(i=0;i<20;i++)
 {
  sleep(ticks);
  if(trackStatus("4"))
  { 
   zambonifound = 1;
   break;
  }
 }
 if(zambonifound == 1)
 {
 for(i=0;i<20;i++)
 {
  sleep(ticks);
  if(trackStatus("7"))
  { 
   return 7;
  }
  sleep(ticks);
  if(trackStatus("13"))
  { 
   return 13;
  }
 }
 }
 if(zambonifound ==1)
 { 
  return 1;
 }
 else
 return 0;
}

int trackStatus(char* d)
{
 char data[15];
 clear_membuf();
 data[0] = 'C';
 data[1] = '\0';
 concatenate_string(data,d);
 concatenate_string(data,"\015");
 
 COM_Message message;
 char inputdata[10];
 int inputlength=3;

 message.output_buffer = data;
 message.len_input_buffer = inputlength;
 message.input_buffer = inputdata;

 sleep(ticks);
 send(com_port,&message);
 if(message.input_buffer[1]=='1')
 { 
  return 1;
 }
 else
 return 0; 
}

int configCheck()
{
 if(trackStatus("8")&& trackStatus("11"))
 {
  return 1;
 }
 else if(trackStatus("12")&& trackStatus("2"))
 {
  return 2;
 }
 else if(trackStatus("5")&& trackStatus("11"))
 {
  return 3;
 }
 else if(trackStatus("16")&& trackStatus("9"))
 {
  return 4;
 }
 else 
 return 0;
}

void speed(char g)
{
 char data[10];
 
 data[0] = 'L';
 data[1] = '\0';
 concatenate_string(data, trainno);
 data[3] = 'S'; 
 data[4] = g;
 data[5] = '\0';
 comSending(data);
}

void reverse()
{
 char data[10];
 
 data[0] = 'L';
 data[1] = '\0';
 concatenate_string(data, trainno);
 data[3] = 'D';
 data[4] = '\0';
 comSending(data);
}

int configure1()
{
 set_switch('5','R');
 set_switch('6','G');
 speed('4');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 speed('4');
 while(!(trackStatus("12")));
 speed('0');
 set_switch('7','R');
 reverse();
 speed('4');
 while(!(trackStatus("13")));
 speed('0');
 reverse();
 speed('4');
 set_switch('6','R');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 speed('4');
 while(!(trackStatus("8")));
 speed('0');
 return 1;
 //wm_print(train, "Returned to home base safely");
}

int configure1wzam()
{
 while(!(trackStatus("7")));
 speed('2');
 while(!(trackStatus("10")));
 set_switch('5','R');
 set_switch('6','G');
 set_switch('2','R');
 speed('4');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 speed('4');
 while(!(trackStatus("12")));
 set_switch('5','G');
 speed('0');
 set_switch('7','R');
 reverse();
 while(!(trackStatus("14")));
 speed('4');
 while(!(trackStatus("13")));
 set_switch('8','R');
 speed('0');
 reverse();
 speed('4');
 set_switch('7','G');
 while(!(trackStatus("12")));
 set_switch('7','G');
 speed('0');
 reverse();
 while(!(trackStatus("7")));
 speed('3');
 while(!(trackStatus("10")));
 speed('4');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 set_switch('5','R');
 set_switch('6','R');
 speed('5');
 while(!(trackStatus("8")));
 speed('0');
 set_switch('5','G');
 return 1;
 //wm_print(train, "Returned to home base safely");
}

int configure2()
{
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 reverse();
 set_switch('1','R');
 set_switch('2','G');
 speed('4');
 while(!(trackStatus("6")));
 speed('0');
 reverse();
 set_switch('4','R');
 set_switch('3','G');
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 reverse();
 set_switch('2','R');
 speed('4');
 while(!(trackStatus("12")));
 speed('0');
 return 1;
}

int configure2wzam()
{
 while(!(trackStatus("14")));
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 reverse();
 set_switch('1','R');
 set_switch('2','G');
 speed('4');
 while(!(trackStatus("1")));
 set_switch('1','G');
 speed('0');
 while(!(trackStatus("4")));
 speed('4');
 while(!(trackStatus("6")));
 speed('0');
 reverse();
 set_switch('4','R');
 set_switch('3','G');
 speed('4');
 while(!(trackStatus("2")));
 set_switch('4','G');
 speed('0');
 while(!(trackStatus("14")));
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 set_switch('1','R');
 reverse();
 set_switch('2','R');
 speed('4');
 while(!(trackStatus("12")));
 speed('0');
 set_switch('1','G');
 return 1;
}

int configure4()
{
 speed('4');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 set_switch('5','R');
 set_switch('6','G');
 speed('4');
 while(!(trackStatus("14")));
 speed('0');
 reverse();
 set_switch('9','G');
 speed('4');
 while(!(trackStatus("16")));
 speed('0');
 return 1;
}

int configure4wzam()
{
 while(!(trackStatus("13")));
 speed('4');
 while(!(trackStatus("14")));
 speed('0');
 reverse();
 speed('4');
 set_switch('1','R');
 set_switch('2','R');
 while(!(trackStatus("12")));
 set_switch('1','G');
 speed('0');
 while(!(trackStatus("10")));
 set_switch('7','G');
 speed('1');
 while(!(trackStatus("6")));
 speed('4');
 while(!(trackStatus("7")));
 speed('0');
 reverse();
 set_switch('5','R');
 set_switch('6','G');
 speed('4');
 while(!(trackStatus("9")));
 set_switch('5','G');
 speed('0');
 while(!(trackStatus("3")));
 speed('1');
 while(!(trackStatus("13")));
 speed('4');
 while(!(trackStatus("14")));
 speed('0');
 reverse();
 set_switch('9','G');
 speed('4');
 while(!(trackStatus("16")));
 set_switch('9','R');
 speed('0');
 return 1;
}

int configure3()
{
 speed('4');
 while(!(trackStatus("13")));
 speed('0');
 reverse();
 set_switch('8','R');
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 reverse();
 set_switch('2','G');
 speed('4');
 while(!(trackStatus("6")));
 speed('0');
 reverse();
 set_switch('4','R');
 set_switch('3','R');
 speed('4');
 while(!(trackStatus("5")));
 speed('0');
 return 1;
}

int configure3wzam()
{
 while(!(trackStatus("7")));
 speed('4');
 while(!(trackStatus("6")));
 speed('0');
 reverse();
 set_switch('4','R');
 set_switch('3','G');
 speed('4');
 while(!(trackStatus("2")));
 set_switch('4','G');
 while(!(trackStatus("1")));
 speed('0');
 while(!(trackStatus("3")));
 speed('4');
 while(!(trackStatus("15")));
 speed('0');
 reverse();
 set_switch('1','R');
 set_switch('2','R');
 speed('4');
 while(!(trackStatus("12")));
 set_switch('1','G');
 speed('0');
 set_switch('7','R');
 while(!(trackStatus("14")));
 speed('4');
 while(!(trackStatus("13")));
 speed('0');
 reverse();
 set_switch('8','R');
 speed('4');
 while(!(trackStatus("11")));
 set_switch('8','G');
 while(!(trackStatus("12")));
 speed('0');
 reverse();
 set_switch('7','G');
 speed('4');
 while(!(trackStatus("9")));
 speed('0');
 while(!(trackStatus("10")));
 set_switch('1','R');
 set_switch('2','R');
 set_switch('7','R');
 speed('4');
 set_switch('4','R');
 set_switch('3','R');
 while(!(trackStatus("5")));
 speed('0');
 return 1;
}
