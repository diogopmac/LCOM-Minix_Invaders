#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "controllers/video/video.h"
#include "controllers/kbc/kbd.h"
#include "controllers/kbc/KBC.h"

extern uint8_t scancode;

int (move_rectanges)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  int ipc_status;
  message msg;

  uint8_t bit_no;
  if(kbd_subscribe_int(&bit_no) != 0) return 1;

  if (vg_draw_rectangle(x, y, width, height, color) != 0) return 1;

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
                  if(scancode == MAKE_A) {
                    if(vg_draw_rectangle(x, y, width, height, 0x000000) != 0) return 1;
                    x -= 10;
                    if(vg_draw_rectangle(x, y, width, height, color) != 0) return 1;
                  }
                  else if(scancode == MAKE_D) {
                    if(vg_draw_rectangle(x, y, width, height, 0x000000) != 0) return 1;
                    x += 10;
                    if(vg_draw_rectangle(x, y, width, height, color) != 0) return 1;
                  }
                  else if(scancode == BREAK_ESC) {
                      break;
                  }
              }
              break;
        }
      }
  }
  if (kbd_unsubscribe_int() != 0) return 1;
  return 0;
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

    if(move_rectanges(100, 100, 50, 50, 0x00FF00)!=0) return 1;

    if(vg_exit() != 0) return 1;
    return 0;
}
