
#include <kernel.h>

//WINDOW window_to ={0, 0, 80, 12, 0, 0, ' '};
//WINDOW window_bot = {0, 12, 80, 13, 0, 0, ' '};

void kernel_main()
{
    
 


 
    // this turns off the VGA hardware cursor
    // otherwise we get an annoying, meaningless,
    // blinking cursor in the middle of our screen
    outportb(0x03D4, 0x0E);
    outportb(0x03D5, 0xFF);
    outportb(0x03D4, 0x0F);
    outportb(0x03D5, 0xFF);

    init_process();
    init_dispatcher();
    init_ipc();
    init_interrupts();
    init_null_process();
    init_timer();
    init_com();
    init_wm();
    init_keyb();
    start_shell();
    
   
 /*  // poke_b(0xB8000,'A');
   // poke_b(0xB8001,0x0F);

//clear_window(&window_top);


for(int x = 0; x < 80 * 25 * 2; x++)
    {
      poke_b(0xb8000 + x , 0);
    }

output_string(&window_to,"Hello");
output_string(&window_bot,"TOS Is fun \n");
output_string(&window_bot,"-------------");

*/
    
   // create_process(user_process,7,6,"USer process");
    resign();
    while (1);
}




