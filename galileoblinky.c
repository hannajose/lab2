/*=================================================*/
/*== 		      File Header		 			 ==*/
/*=================================================*/
/* C Program for Intel Galileo  Gen 2              */
/* Author: Hanna Jose                              */
/*                                                 */
/*                                                 */
/*                                                 */
/*=================================================*/
/*== 		      includes 			 			 ==*/
/*=================================================*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


/*=================================================*/
/*== 		      DEFINE 			 			 ==*/
/*=================================================*/
#define 	SYSFS_GPIO_DIR	"/sys/class/gpio/"
#define		GPIO_D0_PIN61 61
#define		GPIO_D1_PIN62 62
#define		GPIO_D2_PIN38 38
#define		GPIO_D3_PIN40 40
#define		GPIO_STROBE_PIN36 36 
#define		GPIO_STROBEMUX_PIN6 6


#define 	LENGTH		18

volatile long countdown_delay = 200000;

int export(unsigned int gpio)
{
   	char buff[LENGTH];
	FILE * file;
	
	/* export GPIO */
	file = fopen(SYSFS_GPIO_DIR"export", "w");
	
	if (file == NULL) {
		printf("unable to open "SYSFS_GPIO_DIR"export\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	snprintf(buff, LENGTH, "%d", gpio);
	if (fprintf(file, buff) != strlen(buff)) {
		printf("error writing to "SYSFS_GPIO_DIR"export\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return 0;
}

int direction(int gpio, char * dir)
{
	char buff[LENGTH];
	FILE * file;

	snprintf(buff, LENGTH, SYSFS_GPIO_DIR"gpio%d/direction", gpio);
	
	file = fopen(buff, "w");
	if (file == NULL) {
		printf("unable to open %s\n", buff);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	snprintf(buff, LENGTH, dir);
	if (fprintf(file, buff) != strlen(buff)) {
		printf("error writing\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return 0;	
}


int dirve(int gpio, char * dir)
{
	char buff[LENGTH];
	FILE * file;

	snprintf(buff, LENGTH, SYSFS_GPIO_DIR"gpio%d/drive", gpio);
	
	file = fopen(buff, "w");
	if (file == NULL) {
		printf("unable to open %s\n", buff);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	snprintf(buff, LENGTH, dir);
	if (fprintf(file, buff) != strlen(buff)) {
		printf("error writing\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return 0;	
}



int getval(int gpio)
{
	char buff[LENGTH];
	FILE * file;
	int value = 0;

	snprintf(buff, LENGTH, SYSFS_GPIO_DIR"gpio%d/value", gpio);
	file = fopen(buff, "r");
	if (file == NULL) {
		printf("unable to open %s\n", buff);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	if (fscanf(file, "%d", &value) != 1) {
		printf("error reading\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	printf("[INFO] gpio%d : %d\n", gpio,value);
	
	return value;
}


int setval(int gpio, int val)
{
	char buff[LENGTH];
	FILE * file;

	snprintf(buff, LENGTH, SYSFS_GPIO_DIR"gpio%d/value", gpio);
	file = fopen(buff, "w");
	if (file == NULL) {
		printf("unable to open %s\n", buff);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	snprintf(buff, LENGTH, "%d", val);
	if (fprintf(file, buff) != strlen(buff)) {
		printf("error writing\n");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	return 0;
}

void main()
{
	int i = 0;
	/* make GPIO_D0_PIN61 an accessible IO pin. 
	 * Which is equvilant to linux command
     *  echo -n "GPIO_D0_PIN61" > /sys/class/gpio/export
	 */
	export(GPIO_D0_PIN61);
	
	/* Set Direction for GPIO_D0_PIN61. (direction) 
	 * Which is equvilant to linux command
     *  echo -n "out" > /sys/class/gpio/gpio61/direction
	 */
	direction(GPIO_D0_PIN61, "out" );
	
	/* Set Drive for GPIO_D0_PIN61. (drive) 
	 * Which is equvilant to linux command
     *  echo -n "strong" > /sys/class/gpio/gpio61/drive
	 */
	dirve(GPIO_D0_PIN61, "strong" );
	
	/* Set Value for GPIO_D0_PIN61. (value) 
	 * Which is equvilant to linux command
     * cat /sys/class/gpio/gpio61/value
	 */
	 
	 for (i = 1; 1<20; i++)
	 {
		 setval(GPIO_D0_PIN61, 1);
		 while(! (countdown_delay--))
		 {
			 // delay
		 }
		 setval(GPIO_D0_PIN61, 0);
		 while(! (countdown_delay--))
		 {
			 // delay
		 }
		
	 }
}



