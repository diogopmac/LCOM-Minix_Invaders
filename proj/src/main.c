#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "controllers/video/video.h"
#include "controllers/kbc/kbd.h"
#include "controllers/kbc/KBC.h"
#include "controllers/kbc/mouse.h"

#include "sprites/sprite.h"

extern uint8_t scancode;
extern struct packet mouse_packet;
extern int mouse_byte_index;
extern int x;
extern int y;
extern unsigned int counter;

int (move_mouse)() {
  int ipc_status;
  message msg;
  uint8_t mouse_bit_no, timer_bit_no;
  if(mouse_issue_cmd(MOUSE_SET_STREAM_MODE) != 0) return 1;
  if(mouse_issue_cmd(MOUSE_ENABLE_DATA_REPORTING) != 0) return 1;
  if(mouse_subscribe_int(&mouse_bit_no) != 0) return 1;

  if (timer_subscribe_int(&timer_bit_no) != 0) return 1;
  if (timer_set_frequency(0, 30) != 0) return 1;
  
  bool mouse_rb = false;
  bool mouse_dirty = true;

  createMenuSprites();

  while(!mouse_rb) {
    if ( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("Error");
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: 	
              if (msg.m_notify.interrupts & timer_bit_no) { 
                  timer_int_handler();
                  if (mouse_dirty) {
                    if (draw_sprite(cursor, x, y) != 0) return 1;
                    video_swap_buffer();
                    video_clear_buffer();
                    mouse_dirty = false;
                  }
              }
              if (msg.m_notify.interrupts & mouse_bit_no) { 
                  mouse_ih();
                  mouse_place_byte();
                  if (mouse_byte_index == 3){
                    mouse_create_packet();
                    mouse_byte_index = 0;
                    mouse_update_location();
                    mouse_dirty = true;
                    
                    if (mouse_packet.rb) {
                      mouse_rb = true;
                      break;
                    }
                  }
              }
              break;
        }
      }
  }
  destroyMenuSprites();
  if (mouse_unsubscribe_int() != 0) return 1;
  if(mouse_issue_cmd(MOUSE_DISABLE_DATA_REPORTING) != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;
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
    if(video_map_memory(0x115) !=0) return 1;
    if(video_set_mode(0x115) != 0) return 1;

    if(move_mouse()!=0) return 1;

    if(vg_exit() != 0) return 1;
    return 0;
}
