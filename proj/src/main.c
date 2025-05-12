#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "controllers/video/video.h"
#include "controllers/kbc/kbd.h"
#include "controllers/kbc/KBC.h"

extern uint8_t scancode;

int (ESC_key)(){
  int ipc_status;
  message msg;

  uint8_t bit_no;
  if(kbd_subscribe_int(&bit_no) != 0) return 1;

  while(scancode != BREAK_ESC) {
    if ( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("Error");
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: 	
              if (msg.m_notify.interrupts & bit_no) { 
                  kbc_ih();
              }
              break;
    }
  }
  if (kbd_unsubscribe_int() != 0) return 1;
  return 0;
  }
}


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char* argv[]) {
    if(video_map_memory(0x14A) !=0) return 1;
    if(video_set_mode(0x14A) != 0) return 1;

    if(vg_draw_rectangle(100, 100, 100, 100, 0xFFFFFF) != 0) return 1;
    if(vg_draw_rectangle(200, 200, 100, 100, 0xFFFFFF) != 0) return 1;
    if(vg_draw_rectangle(300, 300, 100, 100, 0x51A78D) != 0) return 1;

    if (ESC_key() != 0) return 1;

    if(vg_exit() != 0) return 1;
    return 0;
}
