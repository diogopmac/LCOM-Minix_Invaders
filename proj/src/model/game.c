#include "game.h"

extern uint8_t scancode;
extern struct packet mouse_packet;
extern int mouse_byte_index;
extern unsigned int counter;
Cursor *mouse_cursor;
Player *player;

GameState game_state = GAME_STATE_MENU;

int x = 400, y = 300; // Initial position of the rectangle

int game_loop() {
  int ipc_status;
  message msg;
  uint8_t mouse_bit_no, timer_bit_no, keyboard_bit_no;

  if(mouse_issue_cmd(MOUSE_SET_STREAM_MODE) != 0) return 1;
  if(mouse_issue_cmd(MOUSE_ENABLE_DATA_REPORTING) != 0) return 1;
  if(mouse_subscribe_int(&mouse_bit_no) != 0) return 1;

  if (timer_subscribe_int(&timer_bit_no) != 0) return 1;
  if (timer_set_frequency(0, 30) != 0) return 1;
  
  bool mouse_dirty = true;
  bool need_redraw = true;

  bool kbd_subscribed = false, mouse_subscribed = true;

  createMenuSprites();
  mouse_cursor = createCursor(cursor);

  while(game_state != EXIT_GAME) {
    if ( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("Error");
        continue;
    }
    if (is_ipc_notify(ipc_status)) { 
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: 	
              if (msg.m_notify.interrupts & timer_bit_no) { 
                  timer_int_handler();
                  if (game_state == GAME_STATE_MENU) {
                    if (mouse_dirty) {
                        if (drawCursor(mouse_cursor) != 0) return 1;
                        video_swap_buffer();
                        video_clear_buffer();
                        mouse_dirty = false;
                    }
                  }
                  else if (game_state == GAME_STATE_PLAYING) {
                      if (need_redraw) {
                          if(vg_draw_rectangle(0, 0, 200, 600, 0x0A0E30) != 0) return 1;
                          if(vg_draw_rectangle(600, 0, 200, 600, 0x0A0E30) != 0) return 1;
                          drawPlayer(player);
                          video_swap_buffer();
                          video_clear_buffer();
                          need_redraw = false;
                      }
                  }
              }
              if ((msg.m_notify.interrupts & mouse_bit_no)) { 
                if (game_state == GAME_STATE_MENU) {
                  mouse_ih();
                  mouse_place_byte();
                  if (mouse_byte_index == 3){
                    mouse_create_packet();
                    mouse_byte_index = 0;
                    cursor_update_location(mouse_cursor, &mouse_packet);
                    mouse_dirty = true;
                    
                    if (mouse_packet.rb) {
                      destroyMenuSprites();
                      mouse_cursor = NULL;
                      mouse_dirty = false;

                      game_state = GAME_STATE_PLAYING;

                      if (vg_draw_rectangle(0, 0, 800, 600, 0x000000) != 0) return 1;
                      video_swap_buffer();
                      video_clear_buffer();

                      if (mouse_unsubscribe_int() != 0) return 1;
                      if(mouse_issue_cmd(MOUSE_DISABLE_DATA_REPORTING) != 0) return 1;
                      mouse_subscribed = false;

                      if (kbd_subscribe_int(&keyboard_bit_no) != 0) return 1;
                      kbd_subscribed = true;

                      createGameSprites();
                      player = createPlayer(354, 550, 3, 0, airship);

                      printf("Player created at position (%d, %d)\n", player->x, player->y);

                      break;
                    }
                    else if (mouse_packet.lb) {
                      destroyCursor(mouse_cursor);
                      mouse_cursor = NULL;
                      mouse_dirty = false;

                      game_state = EXIT_GAME;
                      break;
                    }
                  }
                }
              }
              if ((msg.m_notify.interrupts & keyboard_bit_no) && game_state == GAME_STATE_PLAYING) { 
                  printf("Keyboard interrupt received\n");
                  kbc_ih();
                  if(scancode == MAKE_A) {
                    playerMove(player, -10);
                    need_redraw = true;
                  }
                  else if(scancode == MAKE_D) {
                    playerMove(player, 10);
                    need_redraw = true;
                  }
                  else if (scancode == BREAK_ESC) {
                    game_state = EXIT_GAME;
                    break;
                  }
              }
              break;
        }
      }
  }
  if (mouse_subscribed) {
    if (mouse_unsubscribe_int() != 0) return 1;
    if(mouse_issue_cmd(MOUSE_DISABLE_DATA_REPORTING) != 0) return 1;
  }
  if (kbd_subscribed) if (kbd_unsubscribe_int() != 0) return 1;
  if (timer_unsubscribe_int() != 0) return 1;
  return 0;
}
