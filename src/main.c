#include <pebble.h>
#include <stdio.h>
#define HEALTH 10;
#define THEIRHEALTH 10;

Window *window;
TextLayer *text_layer;
int health;
int theirhealth;
int me;


void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  char *h = (char*)malloc(64*sizeof(char));
  health -= 2;
  if (health <= 0) { text_layer_set_text(text_layer, "YOU LOSE!"); }
  else {
    int total = HEALTH;
    snprintf(h, 64, "ME \nHP: %d/%d jjjjjjjjjjjjjjjjjjj", health, total);
	  text_layer_set_text(text_layer, h);
  }
}

/*void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (me == 1) {
    char h[24];
    theirhealth = THEIRHEALTH;
    int theirtotal = THEIRHEALTH;
    me = 0;
    snprintf(h, 24, "ENEMY: \nHP: %d/%d \nLvl: 1 \nD: 2", health, total);
	  text_layer_set_text(text_layer, h);
  }
  else if (me == 0) {
    char h[24];
    health = HEALTH;
    int total = HEALTH;
    int me = 1;
    snprintf(h, 24, "ME: \nHP: %d/%d \nLvl: 1 \nD: 2", health, total);
  	text_layer_set_text(text_layer, h);
  }
  
  char *h = (char*)malloc(64*sizeof(char));
  health -= 2;
  if (health <= 0) { text_layer_set_text(text_layer, "YOU LOSE!"); }
  else {
    int total = HEALTH;
    snprintf(h, 64, "HP: %d/%d", health, total);
	  text_layer_set_text(text_layer, h);
  }
}*/

void config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  //window_single_click_subscribe(BUTTON_ID_SELECT, up_click_handler);
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
  //text_layer_set_text(text_layer, "HP:");
  //const char h[] = "HP:";
  char h[50];
  health = HEALTH;
  int total = HEALTH;
  int me = 1;
  snprintf(h, 50, "ME: \nHP: %d/%d \nLvl: 1 \nDamage: 2", health, total);
  APP_LOG(0, h);
	text_layer_set_text(text_layer, h);
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
  
  window_set_click_config_provider(window, config_provider);

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}