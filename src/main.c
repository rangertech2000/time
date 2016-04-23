#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);


  time_t rawtime = time(NULL); 
  char trainDeparts[8] = "12:56PM"; 
  
  
  struct tm * currentTime;
  struct tm * departTime;
  
  char bufferCurrent [16];
  char bufferDepart [16];
  
  // Get departure time hours and min
  char *pSeparator = strchr(trainDeparts, ':');
  char trainDeparts_hr[3];
  char trainDeparts_mn[3];
  int *pDepartHr;
  
  if (strlen(trainDeparts) == 6) {
    int DepartHr = atoi(strncpy(trainDeparts_hr, pSeparator-1, 1));
    pDepartHr = &DepartHr;
  }
  else if (strlen(trainDeparts) == 7) {
    int DepartHr = atoi(strncpy(trainDeparts_hr, pSeparator-2, 2));
    pDepartHr = &DepartHr;
  }
  else {
    
  }
  
  int departMn = atoi(strncpy(trainDeparts_mn, pSeparator+1, 2));
  // manually terminate the string
  trainDeparts_hr[2] = '\0';
  trainDeparts_mn[2] = '\0';
  
  //time(&rawtime);
  currentTime = localtime (&rawtime);
  departTime = localtime (&rawtime);
  strftime (bufferCurrent, 16, "%Ih:%Mm", currentTime);
  departTime->tm_hour = *pDepartHr;
  departTime->tm_min = departMn;
  mktime (departTime);
  strftime (bufferDepart, 16, "%X", departTime);

  
  //trainDeparts_hr = strlen(trainDeparts);
  APP_LOG(APP_LOG_LEVEL_INFO, bufferCurrent);
  APP_LOG(APP_LOG_LEVEL_INFO, bufferDepart);
  APP_LOG(APP_LOG_LEVEL_INFO, trainDeparts_mn);
  APP_LOG(APP_LOG_LEVEL_INFO, trainDeparts_hr) ;
  

  
  text_layer = text_layer_create(GRect(0, 0, 120, 40));
  text_layer_set_text(text_layer, bufferCurrent);
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorSpringBud);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));
  
  window_stack_push(my_window, false);
}

void handle_deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

