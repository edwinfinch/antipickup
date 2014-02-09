#include <pebble.h>
 
Window* window;
TextLayer *text_layer;

int lineNumber = 1;
bool goingUp = false;
bool goingDown = false;
 
void updateText(void){
	if(lineNumber == 1){
		text_layer_set_text(text_layer, "Woah! You look like I need a drink.");
	}
	else if(lineNumber == 2){
		text_layer_set_text(text_layer, "Excuse me, do you have a pen? Then you'd better get back to it before the farmer notices you're gone.");
	}
	else if(lineNumber == 3){
		text_layer_set_text(text_layer, "How much does a Polar Bear weigh? About ten pounds less than you.");
	}
	else if(lineNumber == 4){
		text_layer_set_text(text_layer, "I would like to get you wet... at least long enough to get you back to the ocean.");
	}
	else if(lineNumber == 5){
		text_layer_set_text(text_layer, "Your place or mine? Both. You go to yours and I'll go to mine.");
	}
	else if(lineNumber == 6){
		text_layer_set_text(text_layer, "I couldn't help but notice you were crying, was it because of your haircut?");
	}
	else if(lineNumber == 7){
		text_layer_set_text(text_layer, "If I could rearrange the alphabet, I'd eliminate U.");
	}
	else if(lineNumber == 8){
		text_layer_set_text(text_layer, "It must have hurt… when you dragged yourself up from Hell.");
	}
	else if(lineNumber == 9){
		text_layer_set_text(text_layer, "Have you ever considered Botox?");
	}
	else if(lineNumber == 10){
		text_layer_set_text(text_layer, "Plain and simple: I wouldn't catch a grenade for you.");
	}
	else if(lineNumber == 11){
		text_layer_set_text(text_layer, "Did you hear about the latest old classic? Screw off.");
	}
	else if(lineNumber == 12){
		text_layer_set_text(text_layer, "Are you a fire detector? Because you're loud and annoying.");
	}
	else if(lineNumber == 13){
		text_layer_set_text(text_layer, "I'd rather take your money than a drink.");
	}
	else if(lineNumber == 14){
		text_layer_set_text(text_layer, "You're uglier than Steve Buscemi");
	}
	else if(lineNumber == 15){
		text_layer_set_text(text_layer, "Are your parents retarded? Because you're special.");
	}
	else if(lineNumber > 14){
		lineNumber = 1;
	}
	else if(lineNumber < 1){
		lineNumber = 15;
	}
	
	if(lineNumber == 2){
		text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	}
	else if(lineNumber == 4){
		text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	}
	else if(lineNumber == 6){
		text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	}
	else{
		text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	}
}

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    //Free the memoery used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
	updateText();
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
     
    //Set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
     
    //Set stopped handler to free memory
    AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
     
    //Start animation
    animation_schedule((Animation*) anim);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{	
  int seconds = tick_time->tm_sec;
}

void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
	lineNumber++;
	goingUp = true;
	GRect start = GRect(0, 0, 144, 168);
    GRect finish = GRect(0, -175, 144, 168);
	animate_layer(text_layer_get_layer(text_layer), &start, &finish, 500, 0);
	GRect start1 = GRect(0, 350, 144, 168);
    GRect finish1 = GRect(0, 0, 144, 168);
	animate_layer(text_layer_get_layer(text_layer), &start1, &finish1, 500, 502);
}
 
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
	lineNumber--;
	goingDown = true;
	GRect start = GRect(0, 0, 144, 168);
    GRect finish = GRect(0, 350, 144, 168);
	animate_layer(text_layer_get_layer(text_layer), &start, &finish, 500, 0);
	GRect start1 = GRect(0, -175, 144, 168);
    GRect finish1 = GRect(0, 0, 144, 168);
	animate_layer(text_layer_get_layer(text_layer), &start1, &finish1, 500, 502);
}
 
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
}

void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

/* Load all Window sub-elements */
void window_load(Window *window)
{
	Layer *window_layer = window_get_root_layer(window);
    text_layer = text_layer_create(GRect(0, 0, 144, 168));
    text_layer_set_background_color(text_layer, GColorClear);
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_text_color(text_layer, GColorBlack);
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), (Layer*) text_layer);
 
	text_layer_set_text(text_layer, "Press up to go forward, down to go back.");
}
 
/* Un-load all Window sub-elements */
void window_unload(Window *window)
{
    text_layer_destroy(text_layer);
}
 
/* Initialize the main app elements */
void init()
{
	tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) tick_handler);
    window = window_create();
    WindowHandlers handlers = {
        .load = window_load,
        .unload = window_unload
    };
    window_set_window_handlers(window, (WindowHandlers) handlers);
	window_set_click_config_provider(window, click_config_provider);
	window_set_fullscreen(window, true);
    window_stack_push(window, true);
}
 
/* De-initialize the main app elements */
void deinit()
{
    window_destroy(window);
	tick_timer_service_unsubscribe();
}
 
/* Main app lifecycle */
int main(void)
{
    init();
    app_event_loop();
    deinit();
}