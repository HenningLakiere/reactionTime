#include <linux/stdlib.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/module.h>

#include <rtdm/rtdm_driver.h>

#define GPIO_BUTTON 22 //pin 15
#define GPIO_LED 23 //pin 16

static rtdm_irq_t irq_rtdm;

//static int counter = 0;

nanosecs_abs_t startTime = 0;
nanosecs_abs_t currentTime = 0;
nanosecs_abs_t dropTimer = 0;
nanosecs_abs_t difference = 0;
nanosecs_abs_t pressTime = 0;
//static int exitTime = 0;

static int button_interruption; 

static int handler_interruption_button(rtdm_irq_t * irq){

	rtdm_printk("button pressed\n");

	//difference = currentTime - startTime;

	currentTime = rtdm_clock_read() - startTime - dropTimer;


	if(currentTime>0){
		pressTime = rtdm_clock_read();

		//difference = (pressTime - currentTime);
		rtdm_printk("Reactie tijd = %lld s\n", currentTime);
	}
	else
	{
		//currentTime = rtdm_clock_read();
	}

	rtdm_printk("currentTime:%lld \n startTime:%lld \n difference:%lld \n", currentTime, startTime, difference);

	return RTDM_IRQ_HANDLED;
}

static void ledtask(void * p){
	int value = 1;
	gpio_set_value(GPIO_LED, value);

	dropTimer = 10000000000;

	rtdm_task_sleep(dropTimer);

	value = 0;
	gpio_set_value(GPIO_LED, value);
}

static int __init reactionTime_init (void)
{
	int err;

	rtdm_printk("INITIAZILING...\n");

	button_interruption = gpio_to_irq(GPIO_BUTTON);

	if ((err = gpio_request(GPIO_BUTTON, THIS_MODULE->name)) != 0) {
		return err;
	}
	if ((err = gpio_direction_input(GPIO_BUTTON)) != 0) {
		gpio_free(GPIO_BUTTON);
		return err;
	}
	if ((err = gpio_request(GPIO_LED, THIS_MODULE->name)) != 0) {
		gpio_free(GPIO_BUTTON);
		return err;
	}
	if ((err = gpio_direction_output(GPIO_LED, 1)) != 0) {
		gpio_free(GPIO_LED);
		gpio_free(GPIO_BUTTON);
		return err;
	}

	irq_set_irq_type(button_interruption,  IRQF_TRIGGER_RISING);

	if ((err = rtdm_irq_request(& irq_rtdm, 
	                 button_interruption, handler_interruption_button, 
	                 RTDM_IRQTYPE_EDGE,
	                 THIS_MODULE->name, NULL)) != 0) {
		gpio_free(GPIO_LED);
		gpio_free(GPIO_BUTTON);
		return err;
	}

	if((err = rtdm_task_init(&ledtask, "ledtask", ledtask, NULL, 99, 0)) != 0)
	{
		gpio_free(GPIO_LED);
		return err;
	}

	rtdm_irq_enable(& irq_rtdm);
	startTime = rtdm_clock_read();
	currentTime = rtdm_clock_read();


	rtdm_printk("INITIALIZING COMPLETED with startTime:%lld \n", startTime);

	return 0;
}

static void __exit reactionTime_exit (void)
{
	rtdm_irq_disable(& irq_rtdm);
	rtdm_irq_free(& irq_rtdm);
	gpio_free(GPIO_LED);
	gpio_free(GPIO_BUTTON);
}


module_init(reactionTime_init);
module_exit(reactionTime_exit);
MODULE_LICENSE("GPL");
