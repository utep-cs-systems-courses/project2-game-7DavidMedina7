#ifndef stateMachine_included
#define stateMachine_included

// the following resemble the status of all states
unsigned char poweroff_on;
unsigned char whistle_down_on;
unsigned char dim_light_on;
unsigned char play_c_major_scale_on;
unsigned char play_lavender_town_on;
extern int SecCnter;
extern int DimCnter;
extern int SecCnter2;

// machine functionality
void select_machine();
void poweroff_machine();
void whistle_down();
void dim_light();
void play_c_major_scale();
void play_lavender_town();

#endif // included
