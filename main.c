#include<stdio.h>

#define OFF 0
#define ON 1
#define ENGINE_TEMP_CONTROLLER 1
typedef struct{
	char engine_state;
	char Ac_state;
	int speed;
	float room_temp;
	int engine_temp_controller_state;
	float engine_temp;
}vehicle;
/************** function prototype ***************/
void menufun(vehicle*v);
void sensormenu(vehicle*v);
void trafficlight(vehicle*v);
void roomtemp(vehicle*v);
void enginetemp(vehicle*v);
void display_vehiclestate(vehicle*v);

/************** function definition ***************/

int main(void)
{
	vehicle v;
	// Vehicle state initial values
	v.speed = 50;
	v.engine_temp = 90;
	v.room_temp = 35;
	v.engine_state = OFF;
	v.Ac_state=OFF;
	v.engine_temp_controller_state= OFF;
	menufun(&v);

}
//menu function
void menufun(vehicle*v){
	char input;
	printf("choose from the list:\n");
	printf("a. Turn on the vehicle engine\n"
			"b. Turn off the vehicle engine\n"
			"c. Quit the system\n");
	fflush(stdin);              fflush(stdout);
	scanf(" %c",&input);
	if(input == 'a'){
		printf("Engine is ON..\n");
		v->engine_state= ON;
		sensormenu(v);
	}
	else if(input == 'b'){
		printf("Engine Off..\n");
		menufun(v);
	}
	else if(input == 'c'){
		printf("Quit the system");
	}
}
//sensor menu function
void sensormenu(vehicle*v)
{
	char input;
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if (ENGINE_TEMP_CONTROLLER==1)            /*if this #define is 1 then compile/run the code lines
	                                           that are related to the “Engine Temperature Controller,
		                                       else do not compile/run*/
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif

	fflush(stdin);              fflush(stdout);
	scanf(" %c",&input);
	if(input == 'a'){
		menufun(v);
	}
	else if(input == 'b'){
		trafficlight(v);
		display_vehiclestate(v);
		printf("\n\n");
		menufun(v);
	}
	else if(input == 'c'){
		roomtemp(v);
		display_vehiclestate(v);
		printf("\n\n");
		menufun(v);
	}
	else if(input == 'd'){
#if(ENGINE_TEMP_CONTROLLER==1)
		enginetemp(v);
#endif
		display_vehiclestate(v);
		printf("\n\n");
		menufun(v);
	}
}
//b. Traffic Light function
void trafficlight(vehicle*v)
{
	char color;
	printf("Enter the required color (G - O - R):\n");
	fflush(stdin);              fflush(stdout);
	scanf(" %c",&color);
	switch(color){
	case'G':
	{
		v->speed=100;
		break;
	}
	case'O':
	{
		v->speed=30;
		v->Ac_state = ON;
#if(ENGINE_TEMP_CONTROLLER==1)
		v->engine_temp_controller_state = ON;
#endif
		break;
	}
	case'R':
	{
		v->speed=0;
		break;
	}
	}

}
//c. Room temperature function
void roomtemp(vehicle*v){
	printf("Enter room temperature:\n");
	fflush(stdout);
	scanf("%f", &v->room_temp);
	if(v->room_temp < 10 || v->room_temp > 30)
	{
		v->Ac_state = ON;
		v->room_temp = 20;
	}
	else
	{
		v->Ac_state = OFF;
	}
}
//d. engine temperature function
#if (ENGINE_TEMP_CONTROLLER==1)
void enginetemp(vehicle*v)
{
	printf("Enter the engine temperature:\n");
	fflush(stdout);
	scanf("%f", &v->engine_temp);
	if(v->engine_temp < 100 || v->engine_temp > 150)
	{
		v->engine_temp_controller_state = ON;
		v->engine_temp = 125;
	}
	else
	{
		v->engine_temp_controller_state = OFF;
	}
}
#endif
// Display the current vehicle state
void display_vehiclestate(vehicle*v)
{
	if(v->speed == 30){
		if(v->Ac_state == ON){
			v->room_temp=v->room_temp* (5.0/4) + 1;
		}
#if(ENGINE_TEMP_CONTROLLER==1)
		if(v->engine_temp_controller_state == ON){
			v->engine_temp=v->engine_temp* (5.0/4) + 1;
		}
#endif
	}

	if(v->engine_state == 1)
	{
		printf("i. Engine state: ON\n");
	}
	else
	{
		printf("i. Engine state: OFF\n");
	}
	if(v->Ac_state == 1)
	{
		printf("ii. AC: ON\n");
	}
	else
	{
		printf("ii. AC: OFF\n");
	}
	printf("iii. Vehicle speed: %d km/h\n", v->speed);
	printf("iv. Room temperature: %.1f degrees\n", v->room_temp);
#if(ENGINE_TEMP_CONTROLLER==1)
	if(v->engine_temp_controller_state == 1)
	{
		printf("v. Engine temperature controller state: ON\n");
	}
	else
	{
		printf("v. Engine temperature controller state: OFF\n");
	}
#endif
	printf("vi. Engine temperature: %.1f degrees\n", v->engine_temp);
}
