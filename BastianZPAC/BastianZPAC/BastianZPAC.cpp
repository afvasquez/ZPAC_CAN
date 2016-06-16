/*
 * BastianZPAC.cpp
 *
 * Created: 6/14/2016 3:31:38 PM
 *  Author: avasquez
 */ 

#include "src/asf.h"
#include "bastian_sercom.h"

void tsk_busy(void);
void tsk_debug(void);
void tsk_error(void);

int main(void)
{
	/* Initialize the SAM system */
	system_init();
	
	//////////////////////////////////////////////////////////////////////////
	// Set the LED outputs for this board.
	struct port_config led_out;
	port_get_config_defaults(&led_out);
	
	led_out.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_BUSY, &led_out);
	port_pin_set_config(LED_ERROR, &led_out);
	port_pin_set_config(LED_DEBUG, &led_out);
	
	struct port_config led_in;
	port_get_config_defaults(&led_in);
	led_in.direction = PORT_PIN_DIR_INPUT;
	
	port_pin_set_config(CAN_PIN_SENSE, &led_in);
	
	// Start the trace logger
	//vTraceInitTraceData();
	
	/* Initialization code - create the channel label for a VTracePrintF*/
	//event_channel = xTraceOpenLabel("Debug");

	// Create the task
	xTaskCreate(tsk_busy,
	(const char *)"IrDA",
	configMINIMAL_STACK_SIZE,
	NULL,
	3,
	NULL );
	
	xTaskCreate(tsk_debug,
	(const char *)"IrDA",
	configMINIMAL_STACK_SIZE,
	NULL,
	3,
	NULL );
	
	xTaskCreate(tsk_error,
	(const char *)"IrDA",
	configMINIMAL_STACK_SIZE,
	NULL,
	3,
	NULL );
	
	// Enable global interrupts
	//system_interrupt_enable_global();
	
	// ..and let FreeRTOS run tasks!
	vTaskStartScheduler();

	/* Replace with your application code */
	while (1)
	{
	}
}

void tsk_busy(void) {
	while (1) {
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_BUSY, true);
		vTaskDelay(450);
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_BUSY, false);
		vTaskDelay(450);
	}
}


void tsk_debug(void) {
	while (1) {
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_DEBUG, true);
		vTaskDelay(300);
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_DEBUG, false);
		vTaskDelay(300);
	}
}

void tsk_error(void) {
	while (1) {
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_ERROR, true);
		vTaskDelay(550);
		if ( !port_pin_get_input_level(CAN_PIN_SENSE) ) port_pin_set_output_level(LED_ERROR, false);
		vTaskDelay(550);
	}
}
