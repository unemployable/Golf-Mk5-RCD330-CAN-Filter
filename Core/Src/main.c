/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

IWDG_HandleTypeDef hiwdg;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
CAN_RxHeaderTypeDef can1_rxHeader; //CAN Bus Rx Header
CAN_RxHeaderTypeDef can2_rxHeader; //CAN Bus Rx Header

CAN_TxHeaderTypeDef can1_txHeader; //CAN Bus Tx Header
CAN_TxHeaderTypeDef can2_txHeader; //CAN Bus Tx Header

uint8_t can1_RX[8] = {0,0,0,0,0,0,0,0};  //CAN1 Bus Receive Buffer
uint8_t can1_TX[8] = {0,0,0,0,0,0,0,0};  //CAN1 Bus Transmit Buffer

uint8_t can2_RX[8] = {0,0,0,0,0,0,0,0};  //CAN2 Bus Receive Buffer
uint8_t can2_TX[8] = {0,0,0,0,0,0,0,0};  //CAN2 Bus Transmit Buffer

CAN_FilterTypeDef canfil; //CAN Bus Filter

uint32_t can1_Mailbox; //CAN Bus Mail box variable
uint32_t can2_Mailbox; //CAN Bus Mail box variable

// just enough for one char to change modes
uint8_t serial_mode[1] = {0};
uint8_t num_str[4] = {0,0,0,0};

// keep some variables in SRAM that survive a reset (as long as power remains)
// https://interrupt.memfault.com/blog/noinit-memory
uint config_loss;
// For GCC or Clang or derived toolchains, use the "section" __attribute__ .
//__attribute__((section(".noinit"))) volatile int magic_number;

// Two non-initialized variables, used to demonstrate keeping information
// through chip reset. Marked 'volatile' to ensure the compiler doesn't optimize
// away the STR's to these addresses
#define RESET_MAGIC 0xDEADBEEF
// magic value used to check if the variables are initialized
__attribute__((section(".noinit"))) volatile uint32_t reset_count_magic;

// reset counter, incremented on every warm reset
__attribute__((section(".noinit"))) volatile uint32_t reset_count;

#define WATCHDOG


// stuff to support the button state machine
enum button_states
{
	IDLE,
	DELAY_1,
	DELAY_2,
	DELAY_3,
	DELAY_4,
	DELAY_5,
	SEND_MSG_1,
	SEND_MSG_2,
	SEND_CLEAR_1,
	SEND_CLEAR_2,
	SEND_CLEAR_3,
	SEND_CLEAR_4,
	SEND_CLEAR_5
};

uint key = 0;
uint key_delay = DELAY_1;
enum button_states current_state = IDLE;
enum button_states next_state = IDLE;
uint last_key_time = 0;
CAN_HandleTypeDef *key_hcan = &hcan2;

// suppress clear msgs ?
int tx_clear_msg = 1;

int print_flag = 1;

struct
{
	uint mute; // star
	uint menu;
	uint phone;
	uint ok;

	// needed for the "MFD undo" code...
	uint up;
	uint down;

} button_time = { 0, 0, 0, 0, 0, 0 };


__attribute__((section(".noinit"))) volatile struct
{
	uint up_next_code;
	uint down_prev_code;
//	uint mute_google;	// try to swap b/w mute and "hey google"
} button_state = { 0x02, 0x03 /*, 0x2b*/};  // RCD330 next/prev by default, otherwise MFD Up 0x22 / Down 0x23


__attribute__((section(".noinit"))) volatile struct
{
	uint can1;
	uint can2;
	uint filters;
	uint stats;
	uint max_illum;
	uint filter_id_en;
	uint filter_id_num;

	uint enable_led;

	uint buttons;
} debug_mode = { 0, 0, 0, 0, 0xdc, 0, 0x5c1, 0, 1};


struct
{
	  uint can1_tx_count;
	  uint can1_rx_count;
	  uint can1_last_rx_tick;
	  uint can1_last_tx_tick;

	  uint can2_tx_count;
	  uint can2_rx_count;
	  uint can2_last_rx_tick;
	  uint can2_last_tx_tick;

	  uint iwdg_msg;
	  uint filter_msg_phone;
	  uint filter_msg_up_next;
	  uint filter_msg_down_prev;
	  uint filter_msg_vol_up;
	  uint filter_msg_vol_down;
	  uint filter_msg_menu;
	  uint filter_msg_mute;
	  uint filter_msg_ok;
	  uint filter_msg_dlc;
	  uint filter_msg_635_illum;

	  uint filter_msg_436_pwr;
	  uint filter_msg_439_pwr;
} can_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


#ifndef max
    #define min(a,b) ((a) < (b) ? (a) : (b))
	#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_CAN2_Init(void);
static void MX_UART4_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef HAL_CAN_AddTxMessagex(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *can_txHeader, uint8_t *can_TX, uint32_t *can_Mailbox);
void UartPrintf(const char *format, ...);
void can_send_button(CAN_HandleTypeDef *hcan, uint key);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void UartPrintf(const char *format, ...)
{
	char buffer[128];
	uint16_t size;
	va_list args;

	va_start(args, format);
	size = vsprintf(buffer, format, args);
	va_end(args);

	if(print_flag)
		HAL_UART_Transmit(&huart4, (uint8_t*)buffer, size, 1000);
}


// send a "fake" button message back to the vehicle MFD (hopefully to undo things...)
void can_send_button(CAN_HandleTypeDef *hcan, uint key)
{
	can2_txHeader.RTR = CAN_RTR_DATA;
	can2_txHeader.IDE = CAN_ID_STD;
	can2_txHeader.TransmitGlobalTime = DISABLE;

	can2_txHeader.StdId = 0x5c1;

	if(hcan == &hcan1)
		can2_txHeader.DLC = 8;
	else
		can2_txHeader.DLC = 1;

	can2_TX[0] = key;

 	for(int i=1; i < can2_txHeader.DLC; i++)
	{
		can2_TX[i] = 0x00;
	}

	HAL_CAN_AddTxMessagex(hcan, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	/*
	 * need this changed/added in the linker script:
	 *
	 * MEMORY
	 * {
	 *   RAM     (xrw)    : ORIGIN = 0x20000000,   LENGTH = 64K - 0x100
	 *   NOINIT  (rwx)    : ORIGIN = 0x20000000 + 64K - 0x100, LENGTH = 0x100
	 *   FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 128K
	 * }
	 *
	 *
	 *   .noinit (NOLOAD):
     * {
     *   KEEP(*(*.noinit*))
     * } > NOINIT
	 */

	// check for loss of data in the non-initialised SRAM variables

	if (reset_count_magic != RESET_MAGIC)
	{
	  reset_count_magic = RESET_MAGIC;
	  reset_count = 0;

	  config_loss = 1;

	  debug_mode.can1 = 0;
	  debug_mode.can2 = 0;
	  debug_mode.enable_led = 0;
	  debug_mode.filter_id_en = 0;
	  debug_mode.filter_id_num = 0x5c1;
	  debug_mode.filters = 0;
	  debug_mode.max_illum = 0xdc;
	  debug_mode.stats = 0;

	  debug_mode.buttons = 1;

	  button_state.up_next_code = 0x02;
	  button_state.down_prev_code = 0x03;
	  //button_state.mute_google = 0x2b;

	}
	else
	{
		config_loss = 0;
		reset_count++;
	}

	// The whole purpose of the Dual CAN Filter project is to fix an issue with upgrading the radio in a Golf Mk5 to an RCD330

	// There are already Chinese "blackbox" CAN filters available to fix some issues with power down & steering wheel buttons.
	// However they don't fix everything, including screen brightness issues:
	// https://rcd330plus.com/showthread.php?tid=6741&page=3

	// it would be really nice to have an open source alternative to these clever mystery boxes...

	// Excellent work on figuring out which CAN message impact on the brightness
	// although choice of h/w seems a bit too complicated:
	// https://oshwlab.com/Mrpanini/canbus6

	// Rather than cobble together the h/w from various bits and pieces, I sought out something that already existed
	// that could be re-purposed.

	// H/W hacked is the 18 in 1 CAN Filter Board on AliExpress/eBay
	// they use either STM32F105 or STM32F107 DUal CAN chips
	// this rules out Arduino IDE as they are not supported yet.
	// so using STM32CubeIDE & HAL Libraries directly

	// About the h/w:
	// Blue boards use SWD and need ST-Link, Green use USART1 (via internal bootloader)

	// Blue has 4 GPIO ports available (conf pins)
	// This provides access to UART5 (Tx) & UART4 (Tx/Rx) + potetially other peripherals...
	// thankfully no need for softwareserial :)

	// "new" Green has only 3 GPIO ports (conf pins), but already has a RED LED & USART1 available.
	// "old" green (Yaseuh original?) seems similar to Blue, except for lack of LED & using USART1
	// the two green boards use completely different GPIO conf pins!
	// the "new" green board is also s/w locked - so needs to be erased first (oh well)


	// CAN S/W Inspired by:

	// Reverse engineered Chinese Boards "milage rollback devices":
	// https://dangerouspayload.com/2020/03/10/hacking-a-mileage-manipulator-can-bus-filter-device/
	// https://giddi.net/posts/reversing-a-canbus-odometer-filter-manipulator/
	// Two independent hacks of these boards
	// Inspired me to learn Ghidra...
	// Found interesting code choices and bugs :)

	// "new" green board: https://i.imgur.com/Oss24pO.jpeg
	// mine came with an STM32F107RB (same PCB)


	// First ideas for the S/W:
	// https://www.dailyduino.com/index.php/2020/06/01/stm32-can-bus/

	// Similar dual can idea:
	// https://github.com/damienmaguire/CAN-BUS-Man-In-The-Middle

	// very helpful stuff here on fixing CAN2 Rx Interrupt issues:
	// although it suffered from the CAN2 Int filter config issue
	// https://community.st.com/s/question/0D50X00009XkXHxSAN/can2-interrupt-not-working
	// https://community.st.com/s/question/0D53W00000Di8EeSAJ/heres-how-to-get-can2-working


	// other useful things:
	// UartPrintf/scanf
	// https://shawnhymel.com/1873/how-to-use-UartPrintf-on-stm32/
	// http://www.emcu.eu/how-to-implement-UartPrintf-for-send-message-via-usb-on-stm32-nucleo-boards-using-atollic/

	// enable floats:
	// https://community.st.com/s/question/0D50X0000B0AEJbSQO/uUartPrintffloat-where-to-set-for-clinker-in-stm32cubeide

	// STM32F1xx Docs:
	// https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
	// https://www.st.com/resource/en/datasheet/cd00220364.pdf


	// CAN bit timing:
	// http://www.bittiming.can-wiki.info/



	// STM32 Cabling and CAN connections to the RCD330 Quadlock Wiring Harness (steering button adaptor)
	//
	// On the Blue (SWD) Dual Filter Board:
	// (Note: this matches the "new" green board)
	//
	// CAN1 is the RCD330
	// 	GREEN	CAN High
	//	PURPLE	CAN Low

	// CAN2 is the Vehicle
	// 	BLUE	CAN High
	//	YELLOW	CAN Low

	// PQ Quadlock connector (cheap one)
	//	Green	CAN High
	//	Purple	CAN Low
	// 	YELLOW	12V Battery
	//	BLACK	GND

	// Strategy:
	//	Cut the CAN High/Low connections between the connectors, midway.
	//	Connect the appropriate sides to the Blue CAN board
	//	Note: RCD330 side has the lever connector (female pins), the vehicle is the plain connector (male pins).
	//  Cut the thin YELLOW and BLACK wires (power) that used to go to the original black box.
	//  Tap the Blue boards power into these and re-connect them all together.

	// The Blue board will be shrink wrapped instead of using a case.
	// The USART4 Dupont serial connections (and Gnd) will remain, in case debugging is required.
	// The FTDI serial adaptor will not be permanently connected.

	// Once power consumption is known, an in-line fuse will be added - just in case!!!


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_CAN1_Init();
  //MX_CAN2_Init();
  MX_UART4_Init();
  //MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT (&huart4, serial_mode, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint current_tick = 0;
  uint last_tick = 0;

  // v1.2 works on the Blue Board, with only EXTI on Vehicle CAN Rx
  // Also, IWDG is now only reset by Vehicle CAN Msgs.

  // CONf_S4 is the external LED
  // CONf_W222 is UART4_Rx
  // CONf_W166 is UART4_Tx
  // CONf_BMW is EXTI (Vehicle CAN2 Rx)

  UartPrintf("\r\nDual CAN Filter v1.2 Blue Board (100kb/s) %s [ reset_count %u ]\r\n\r\n", (config_loss) ? "Default Config" : "Existing Config", reset_count);

  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	  UartPrintf("Reset caused by IWDGRST\r\n\r\n");
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
	  UartPrintf("Reset caused by PORRST\r\n\r\n");
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET)
	  UartPrintf("Reset caused by SFTRST\r\n\r\n");
  else
	  UartPrintf("Reset cause unknown\r\n\r\n");

  //__HAL_RCC_CLEAR_RESET_FLAGS();

  UartPrintf("Pausing 5s...\r\n\r\n");

  HAL_Delay(5000);

  UartPrintf("Starting...\r\n\r\n");

  UartPrintf("Going into to Sleep/Stop Mode\r\n\r\n");

#ifdef WATCHDOG

  HAL_SuspendTick();
  HAL_GPIO_WritePin(CONF_S4_LED_GPIO_Port, CONF_S4_LED_Pin, GPIO_PIN_SET);  // turn off
  /* Enter Stop Mode */
  //DBGMCU->CR = 0;
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  HAL_ResumeTick();


  // need to redo all the initialisation
  //HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_UART4_Init();
  HAL_UART_Receive_IT (&huart4, serial_mode, 1);
  MX_IWDG_Init();

#endif

  UartPrintf("EXTI %d - Waking from Sleep Stop Mode\r\n\r\n", (int) EXTI->PR);

  print_flag = 1;

  UartPrintf("Printing: %s\r\n\r\n", (print_flag) ? "On" : "Off");

// using these for EXTI IWDG wakeup (CAN1, CAN2 & USART1)
//  HAL_GPIO_WritePin(GPIOB, OUT1_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, OUT2_Pin,0);
//  HAL_GPIO_WritePin(GPIOB, OUT3_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, CONF_S4_LED_Pin, GPIO_PIN_RESET);

  // CAN1
  canfil.FilterBank = 0;
  canfil.FilterMode = CAN_FILTERMODE_IDMASK;
  canfil.FilterFIFOAssignment = CAN_RX_FIFO0;
  canfil.FilterIdHigh = 0;
  canfil.FilterIdLow = 0;
  canfil.FilterMaskIdHigh = 0;
  canfil.FilterMaskIdLow = 0;
  canfil.FilterScale = CAN_FILTERSCALE_32BIT;
  canfil.FilterActivation = ENABLE;
  canfil.SlaveStartFilterBank = 14;	// important!

  HAL_CAN_ConfigFilter(&hcan1,&canfil);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);

  // CAN2
  canfil.FilterBank = 14;	// important !!
  canfil.FilterMode = CAN_FILTERMODE_IDMASK;
  canfil.FilterFIFOAssignment = CAN_RX_FIFO1;
  canfil.FilterIdHigh = 0;
  canfil.FilterIdLow = 0;
  canfil.FilterMaskIdHigh = 0;
  canfil.FilterMaskIdLow = 0;
  canfil.FilterScale = CAN_FILTERSCALE_32BIT;
  canfil.FilterActivation = ENABLE;
  //canfil.FilterActivation = DISABLE;
  canfil.SlaveStartFilterBank = 14;	// important !!!

  HAL_CAN_ConfigFilter(&hcan2,&canfil);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO1_MSG_PENDING);


  // don't need to do much here (just print stats), as CAN Filters & USART are interrupt driven
  while (1)
  {
	  // Get time elapsed
	  current_tick = HAL_GetTick();

	  if(debug_mode.stats)
	  {
//		  if(current_tick % 10000 == 0)
		  if(current_tick - last_tick > 10000)
		  {
			  UartPrintf("\r\nStats (elasped time %u sec, reset count %u):\r\n", current_tick/1000, reset_count);
			  UartPrintf("can1_tx_cnt:\t\t%d\r\n", can_stats.can1_tx_count);
			  UartPrintf("can1_rx_cnt:\t\t%d\r\n", can_stats.can1_rx_count);
			  UartPrintf("can2_tx_cnt:\t\t%d\r\n", can_stats.can2_tx_count);
			  UartPrintf("can2_rx_cnt:\t\t%d\r\n", can_stats.can2_rx_count);

			  UartPrintf("iwdg_msg:\t\t%d\r\n", can_stats.iwdg_msg);
			  UartPrintf("filter_msg_phone:\t%d\r\n", can_stats.filter_msg_phone);
			  UartPrintf("filter_msg_up_next:\t%d\r\n", can_stats.filter_msg_up_next);
			  UartPrintf("filter_msg_down_prev:\t%d\r\n", can_stats.filter_msg_down_prev);
			  UartPrintf("filter_msg_vol_up:\t%d\r\n", can_stats.filter_msg_vol_up);
			  UartPrintf("filter_msg_vol_down:\t%d\r\n", can_stats.filter_msg_vol_down);
			  UartPrintf("filter_msg_menu:\t%d\r\n", can_stats.filter_msg_menu);
			  UartPrintf("filter_msg_mute:\t%d\r\n", can_stats.filter_msg_mute);
			  UartPrintf("filter_msg_ok:\t\t%d\r\n", can_stats.filter_msg_ok);
			  UartPrintf("filter_msg_dlc:\t\t%d\r\n", can_stats.filter_msg_dlc);
			  UartPrintf("filter_msg_436_pwr:\t%d\r\n", can_stats.filter_msg_436_pwr);
			  UartPrintf("filter_msg_439_pwr:\t%d\r\n", can_stats.filter_msg_439_pwr);
			  UartPrintf("filter_msg_635_illum:\t%d\r\n\r\n", can_stats.filter_msg_635_illum);

			  last_tick = current_tick;
		  }
	  }


	// button send state machine
	// main loop runs every 100ms (the standard button message interval)
	// delay a bit (i.e. wait for last button completion), then cycle through the required set/clear messages

	switch(current_state)
	{
		case IDLE :
			last_key_time = HAL_GetTick();

			if(key == 0)
			{
				next_state = IDLE;
			}
			else
			{
				if(debug_mode.buttons)
					UartPrintf("IDLE %u\t[%u]\r\n", key, current_tick-last_key_time);

				next_state = key_delay;  // choose which state to start (i.e. variable delay) - default DELAY_1
			}
		break;

		// each delay adds 100ms
		case DELAY_1 :
			next_state = DELAY_2;
		break;
		case DELAY_2 :
			next_state = DELAY_3;
		break;
		case DELAY_3 :
			next_state = DELAY_4;
		break;
		case DELAY_4 :
			next_state = DELAY_5;
		break;
		case DELAY_5 :
			next_state = SEND_MSG_1;
		break;

		case SEND_MSG_1 :
			if(debug_mode.buttons)
				UartPrintf("SEND_MSG_1 0x%02x\t[%u]\r\n", key, current_tick-last_key_time);
			can_send_button(key_hcan, key);
			next_state = SEND_MSG_2;
			last_key_time = HAL_GetTick();
		break;
		case SEND_MSG_2 :
			if(debug_mode.buttons)
				UartPrintf("SEND_MSG_2 0x%02x\t[%u]\r\n", key, current_tick-last_key_time);
			can_send_button(key_hcan, key);
			next_state = SEND_CLEAR_1;
			last_key_time = HAL_GetTick();
		break;

		case SEND_CLEAR_1 :
			if(debug_mode.buttons)
				UartPrintf("SEND_CLEAR_1\t[%u]\r\n", current_tick-last_key_time);
			can_send_button(key_hcan, 0x00);
			next_state = SEND_CLEAR_2;
			last_key_time = HAL_GetTick();
		break;
		case SEND_CLEAR_2 :
			if(debug_mode.buttons)
				UartPrintf("SEND_CLEAR_2\t[%u]\r\n", current_tick-last_key_time);
			can_send_button(key_hcan, 0x00);
			next_state = SEND_CLEAR_3;
			last_key_time = HAL_GetTick();
		break;
		case SEND_CLEAR_3 :
			if(debug_mode.buttons)
				UartPrintf("SEND_CLEAR_3\t[%u]\r\n", current_tick-last_key_time);
			can_send_button(key_hcan, 0x00);
			next_state = SEND_CLEAR_4;
			last_key_time = HAL_GetTick();
		break;
		case SEND_CLEAR_4 :
			if(debug_mode.buttons)
				UartPrintf("SEND_CLEAR_4\t[%u]\r\n", current_tick-last_key_time);
			can_send_button(key_hcan, 0x00);
			next_state = SEND_CLEAR_5;
			last_key_time = HAL_GetTick();
		break;
		case SEND_CLEAR_5 :
			if(debug_mode.buttons)
				UartPrintf("SEND_CLEAR_5\t[%u]\r\n", current_tick-last_key_time);
			can_send_button(key_hcan, 0x00);
			key = 0;
			next_state = IDLE;
			last_key_time = HAL_GetTick();
		break;

		default :
			UartPrintf("Default - Error\t[%u]\r\n", current_tick);
		break;
	}

	current_state = next_state;

	HAL_Delay(100);  // match the max CAN msg rate for button presses...

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 20;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 20;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CONF_S4_LED_GPIO_Port, CONF_S4_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA5 CONF_BMW_EXTI_Pin */
//  GPIO_InitStruct.Pin = GPIO_PIN_11|CONF_BMW_EXTI_Pin;

  // CAN1 Rx (PA11) EXTI
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : CONF_S4_LED_Pin */
  GPIO_InitStruct.Pin = CONF_S4_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CONF_S4_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 */
//  GPIO_InitStruct.Pin = GPIO_PIN_4;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CAN2 Rx (PB5) EXTI */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
//  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

// wrapper function to enable Tx debug msgs
HAL_StatusTypeDef HAL_CAN_AddTxMessagex(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *can_txHeader, uint8_t *can_TX, uint32_t *can_Mailbox)
{
	char *canbus;

	uint tick = HAL_GetTick();
	uint tx_count;

	if(hcan == &hcan1)
	{
		canbus = "CAN1    ";
		can_stats.can1_last_tx_tick = tick;
		tx_count = can_stats.can1_tx_count;
	}
	else
	{
		canbus = "    CAN2";
		can_stats.can2_last_tx_tick = tick;
		tx_count = can_stats.can2_tx_count;
	}

	//if(!(debug_mode.filter_id_en && (debug_mode.filter_id_num != can1_txHeader.StdId)))
	if( (hcan==&hcan1 && debug_mode.can1) || (hcan==&hcan2 && debug_mode.can2) )
	{
		UartPrintf("%8u [%8u] %s Tx  : 0x%.3x ", tick, tx_count, canbus, (int) can_txHeader->StdId);
		UartPrintf("[%d] ", (int) can_txHeader->DLC);

		int i;
		for(i = 0; i < (int) can_txHeader->DLC; i++)
		{
			UartPrintf("0x%.2x ", can_TX[i]);
		}
		UartPrintf("\r\n");
	}

	return HAL_CAN_AddTxMessage(hcan, can_txHeader, can_TX, can_Mailbox);
}


/*
 * CAN1 is connected to the RCD330 CAN bus (used to be connected to the vehicle)
 */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1)
{
	HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &can1_rxHeader, can1_RX);

	/*
		  txHeader.DLC = 8;
		  txHeader.IDE = CAN_ID_STD;
		  txHeader.RTR = CAN_RTR_DATA;
		  txHeader.StdId = 0x030;
		  txHeader.ExtId = 0x02;
		  txHeader.TransmitGlobalTime = DISABLE;
	*/

	can2_txHeader.RTR = CAN_RTR_DATA;
	can2_txHeader.IDE = CAN_ID_STD;
	can2_txHeader.TransmitGlobalTime = DISABLE;

	// copy over useful stuff for tx-ing
	__disable_irq();

	can2_txHeader.StdId = can1_rxHeader.StdId;
	can2_txHeader.DLC = can1_rxHeader.DLC;

	for(int i=0; i < 8; i++)
	{
		can2_TX[i] = can1_RX[i];
	}

	__enable_irq();

	if(debug_mode.enable_led)
		HAL_GPIO_TogglePin(CONF_S4_LED_GPIO_Port, CONF_S4_LED_Pin);

	can_stats.can1_rx_count++;
	can_stats.can1_last_rx_tick = HAL_GetTick();

#ifdef WATCHDOG
	//HAL_IWDG_Refresh(&hiwdg);
#endif

	if(debug_mode.can1)
	{
		if(!(debug_mode.filter_id_en && (debug_mode.filter_id_num != can2_txHeader.StdId)))
		{

			UartPrintf("%8u [%8u] CAN1       Rx: 0x%.3x ", can_stats.can1_last_rx_tick, can_stats.can1_rx_count, (int) can2_txHeader.StdId);
			UartPrintf("[%d] ", (int) can2_txHeader.DLC);

			int i;
			for(i = 0; i < (int) can2_txHeader.DLC; i++)
			{
				UartPrintf("0x%.2x ", can2_TX[i]);
			}
			UartPrintf("\r\n");
		}
	}

	// default
	if(HAL_CAN_AddTxMessagex(&hcan2, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox) != HAL_OK)
		UartPrintf("CAN2 Tx Failed - default\r\n");
	can_stats.can2_tx_count++;
}


/*
 * CAN2 is connected to the vehicle CAN (which was connected to the RDC330)
 *
 * It will filter the vehicle CAN messages and send the modified versions via CAN1 to the RCD330
 */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan2_rx)
{
	HAL_CAN_GetRxMessage(hcan2_rx, CAN_RX_FIFO1, &can2_rxHeader, can2_RX);

	uint curr_tick = HAL_GetTick();

	// defaults
	can1_txHeader.RTR = CAN_RTR_DATA;
	can1_txHeader.IDE = CAN_ID_STD;
	can1_txHeader.TransmitGlobalTime = DISABLE;

	// copy over useful stuff for tx-ing
	// modify as appropriate below...
	__disable_irq();

	can1_txHeader.StdId = can2_rxHeader.StdId;
	can1_txHeader.DLC = can2_rxHeader.DLC;

	for(int i=0; i < can2_rxHeader.DLC; i++)
	{
		can1_TX[i] = can2_RX[i];
	}

	__enable_irq();

	can1_txHeader.RTR = CAN_RTR_DATA;
	can1_txHeader.IDE = CAN_ID_STD;
	can1_txHeader.TransmitGlobalTime = DISABLE;

	if(debug_mode.enable_led)
		HAL_GPIO_TogglePin(CONF_S4_LED_GPIO_Port, CONF_S4_LED_Pin);

	can_stats.can2_rx_count++;
	can_stats.can2_last_rx_tick = curr_tick;

	if(debug_mode.can2)
	{
		if(!(debug_mode.filter_id_en && (debug_mode.filter_id_num != can1_txHeader.StdId)))
		{
				UartPrintf("%8u [%8u]     CAN2   Rx: 0x%.3x ", can_stats.can2_last_rx_tick, can_stats.can2_rx_count, (int) can1_txHeader.StdId);
				UartPrintf("[%d] ", (int) can1_txHeader.DLC);

				int i;
				for(i = 0; i < (int) can1_txHeader.DLC; i++)
				{
					UartPrintf("0x%.2x ", can1_TX[i]);
				}
				UartPrintf("\r\n");
		}
	}


	/*
	 * This is the CAN Filtering behaviour of the Chinese black box adapter cable:
	 *
	 * Watchdog:
	 *
	 * If StdID == 2c3 (Ignition Position) (or 575 PWR, depending on version):
     *   Reset the Watchdog timeout
     *
     *
     * Steering wheel buttons:
     *
     * If StdID == 5c1:
     *         5c1 x [ 1E/1D X X X X X X X ] => 5c1 8 [ 1a 0 0 0 0 0 0 0 ]     Phone
     *         where (a) is sram[0]
     *         5c1 x [ 22 X X X X X X X ]    => 5c1 8 [ (a)   0 0 0 0 0 0 0 ]  Up/Next based on Menu or Ok last pressed
     *         5c1 x [ 23 X X X X X X X ]    => 5c1 8 [ (a+1) 0 0 0 0 0 0 0 ]  Down/Prev based on Menu or Ok last pressed
     *         5c1 x [ 0a X X X X X X X ]    => 5c1 8 [ 0a    0 0 0 0 0 0 0 ]  Press Menu => MK5 Mode (MFD Up/Down)
     *         SRAM:   (a) = 0x22
     *                 (a+1) = 0x23
     *         5c1 x [ 28 X X X X X X X ]    => 5c1 8 [ 28 0 0 0 0 0 0 0 ]     Press Ok => RCD330 Mode (Track Next/Prev)
     *         SRAM:   (a) = 2
     *                 (a+1) = 3
     *         5c1 x [  N X X X X X X X ]    => 5c1 8 [  N 0 0 0 0 0 0 0 ]     All other messages of any length are fixed to 8 data bytes
     *
     *
     * Power/shutodwn:
     *
     * Note: Y = un-initialised data, the bytes are not explicitly cleared or copied from Rx buffer (so maybe random?)
     *       This implementation will copy them across
     *
     * If StdID == 436 && DLC == 8
     *         436 8 [ 1 X X X X 6 X X ]     => 436 6 [ 1 Y Y Y Y Y 6 ]
     *                                       => 439 6 [ 1 Y Y Y Y Y 6 ]
     *
     * If StdID == 439 && DLC == 8
     *         439 8 [ 1 X X X X 6 X X ]     => 439 6 [ 1 Y Y Y Y Y 6 ]
	 *
	 */

	// IWDG
	if(can1_txHeader.StdId == 0x2c3 || can1_txHeader.StdId == 0x575)
	{
#ifdef WATCHDOG
		HAL_IWDG_Refresh(&hiwdg);
#endif

		can_stats.iwdg_msg++;

		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - IWDG\r\n");
		can_stats.can1_tx_count++;
	}
	else
	// Steering Buttons
	if(can1_txHeader.StdId == 0x5c1)
	{
		/*
		 * 0x5c1 Data[0] button
		 * 0x00 No buttons pressed
		 * 0x06 Volume up
		 * 0x07 Volume down
		 * 0x2b mute
		 * 0x1a phone
		 * 0x0a menu
		 * 0x22 up
		 * 0x23 down
		 * 0x28 ok
		 */

		// default is to tx msgs (long press buttons will suppress this)
		int tx_msg = 1;

		// default full delay for new button press requests in state machine...
		key_delay = DELAY_1;

		// if new msg is not a clear, new button sequence so disable the clear suppression flag
		// needed for short press mute, where we send a completely new msg (so discard old mute msgs)
		if(tx_clear_msg == 0)
			if(can1_TX[0] != 0x00)
				tx_clear_msg = 1;

		// presumably button active msgs are sent every 100ms while pressed
		// as soon as the clear msgs 0x00 arrives, check the time from 1st active msg.

		if(can1_TX[0] == 0x00)	// ************** Clear
		{
			// all buttons off, so check for a long press on useful buttons

			// note that currently the msgs are still sent via the filter code below
			// we are not yet stopping messages getting to the radio, only changing which button is being identified...
			// in future, perhaps we can block the short msgs in the filter and send them manually via the short press detection in this routine...


			// ************** Up
			// if in RCD330 mode, we want to fake a down msg to the MFD, so it does not seem impacted
			// these might be sent too quickly, so might have to build a 100ms state machine triggered in the main loop  - just to send button presses...?

			// Up Cleared
			if(button_time.up > 0)
			{
				uint dur = curr_tick - button_time.up;

				// check for RCD330 mode
				if(button_state.up_next_code == 0x02)
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Up RCD330 (clear) - send fake down\t[%u]\r\n", dur);
					}

					// need to trigger a state machine button send in the main routine...

					key = 0x23;
					key_delay = DELAY_2;
					key_hcan = &hcan2;

				}
				button_time.up = 0;
			}

			// Down cleared
			if(button_time.down > 0)
			{
				uint dur = curr_tick - button_time.down;

				// check for RCD330 mode
				if(button_state.up_next_code == 0x02)
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Down RCD330 (clear) - send fake up\t[%u]\r\n", dur);
					}


					// need to trigger a state machine button send in the main routine...

					key = 0x22;
					key_delay = DELAY_2;
					key_hcan = &hcan2;
				}
				button_time.down = 0;
			}


			// ************** Mute (Star)
			// Short Press Mute, Long press "Google Assitant"

			// check for a long press (> 1sec)
			if(button_time.mute > 0)
			{
				uint dur = curr_tick - button_time.mute;

				if(dur > 1000)
				{
					// long press mute will be handled in the main button route (not here in the clear routine)
					// this is so the long press can be activated while the button is still being pressed (rather than on release)
					// so long press will hijack the real active msgs below.

					// note RCD330 still only activates Google Assistant on button release...

					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Mute Long press (clear)\t[%u]\r\n", dur);
					}
//					can1_TX[0] = (uint8_t) 0x2a;
				}
				else
				{
					// only send short press mute here
					// short press mute is done as a new button press (so there will be a delay)

					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Mute Short press (clear)\t[%u]\r\n", dur);
					}

					// suppress remaining mute clear msgs
					tx_clear_msg = 0;

					// request a completely new mute button be sent
					key = 0x2b;
					key_delay = SEND_MSG_1;	// skip delay
					key_hcan = &hcan1;
				}

				button_time.mute = 0;
			}

			//************** menu button clear
			// swap between MFD & RCD330 Mode (default) using short/long press of menu button

			if(button_time.menu > 0)
			{
				int dur = curr_tick - button_time.menu;

				if(dur > 1000)
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Menu Long press (clear)\t[%u]\r\n", dur);
					}

					//button_state.up_next_code = 0x02;
					//button_state.down_prev_code = 0x03;
					////button_state.mute_google = 0x2b;
				}
				else
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Menu Short press (clear)\t[%u]\r\n", dur);
					}
					button_state.up_next_code = 0x22;
					button_state.down_prev_code = 0x23;
					//button_state.mute_google = 0x2a;
				}
				button_time.menu = 0;
			}

			// ************** ok ?

			if(button_time.ok > 0)
			{
				int dur = curr_tick - button_time.ok;

				if(dur > 1000)
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Ok Long press\t[%u]\r\n", dur);
					}
				}
				else
				{
					if(debug_mode.buttons)
					{
						UartPrintf("CAN2 Ok Short press\t[%u]\r\n", dur);
					}
				}
				button_time.ok = 0;
			}
		} // ************** End of clear msg handler
		else  // below here are the individual button filters
		if(can1_TX[0] == 0x1d || can1_TX[0] == 0x1e) // Some unknown buttons => Phone
		{
			// this is code from the Chinese can filter, might not be applicable to the Golf Mk5?

			uint8_t old_data = can1_TX[0];
			can1_TX[0] = (uint8_t) 0x1a;

			can_stats.filter_msg_phone++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] %02x XX XX XX XX XX XX XX\t==>\t5c1 [8] 1a 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, old_data);
			}
		}
		else
		if(can1_TX[0] == 0x22) // ************** Up / Next
		{
			// Note the Up/Down buttons are a pain as they always change the MFD
			// By hitting "menu" it is possible to stop them affecting the radius (i.e. MFD only mode)
			// but this is still crap, annoying behaviour

			// Perhaps it is possible to "undo" the MFD changes while in "radio" mode?
			// We could send the opposite command back to the car and hope it updates the MFD.
			// i.e. press "ok" (radio mode), "up"=next (0x06 is sent to radio, 0x23,0x00 is sent via CAN1 to the car)
			//                             "down"=prev (0x07 is sent to radio, 0x22,0x00 is sent to car)

			// if this happens quick enough, maybe we won't notice the MFD glitching...?

			// used to track up button release in clear code above - for fake down
			if(button_time.up == 0)
			{
				// was off, so save time of first press msg
				button_time.up = curr_tick;
			}

			can1_TX[0] = (uint8_t) button_state.up_next_code;

			can_stats.filter_msg_up_next++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 22 XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0]);
			}
		}
		else
		if(can1_TX[0] == 0x23) // ************** Down / Prev
		{
			// used to track down button release in clear code above - for fake up
			if(button_time.down == 0)
			{
				// was off, so save time of first press msg
				button_time.down = curr_tick;
			}

			can1_TX[0] = (uint8_t) button_state.down_prev_code;

			can_stats.filter_msg_down_prev++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 23 XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0]);
			}
		}
		else
		if(can1_TX[0] == 0x2b) // ************** Mute / google
		{
			// check for long press
			if(button_time.mute == 0)
			{
				// was off, so save time of first press msg
				button_time.mute = curr_tick;
			}

			// handle long press detection, while still being pressed
			uint dur = curr_tick - button_time.mute;

			// assuming a long press is typically around 1 sec
			// detect at 800ms, which should allow at least 2 modified msgs through, before the button is release
			if(dur > 800)
			{
				if(debug_mode.buttons)
				{
					UartPrintf("CAN2 Mute Long press (active)\t[%u]\r\n", dur);
				}
				can1_TX[0] = (uint8_t) 0x2a;
			}
			else
			{
				// flag to not send mute msgs immediately
				// check the clear msgs above and send based on short/long press...
				tx_msg = 0;
			}
		}
		else
		if(can1_TX[0] == 0x0a) // ************** Menu, switch up/next functions (+google/seek testing)
		{
			// check for long press
			if(button_time.menu == 0)
			{
				// was off, so save time of first press msg
				button_time.menu = curr_tick;
			}

			// handle long press detection, while still being pressed
			uint dur = curr_tick - button_time.menu;

			// assuming a long press is typically around 1 sec
			// detect at 800ms, which should allow at least 2 modified msgs through, before the button is release
			if(dur > 800)
			{
				if(debug_mode.buttons)
				{
					UartPrintf("CAN2 Menu Long press (active)\t[%u]\r\n", dur);
				}

				button_state.up_next_code = 0x02;
				button_state.down_prev_code = 0x03;
				//button_state.mute_google = 0x2b;
			}
			else
			{
				// flag to not send menu msgs immediately
				// check the clear msgs above and send based on short/long press...
				tx_msg = 1;
			}

			can_stats.filter_msg_menu++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 0a XX XX XX XX XX XX XX\t==>\t5c1 [8] 0a 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick);
			}
		}
		else
		if(can1_TX[0] == 0x28) // ************** Ok, switch to next/prev functions (+ vol/mute)
		{
			// it would be good to remove the dependancy on "ok" to switch to radio mode
			// this is because "ok" still affects the MFD on some screens which can be annoying

			// the proposal is to use "menu" long press to toggle the mode
			// as "menu" has no impact on my Golf Mk5 midline (MFD) screen
			// can probably just use "menu" short press to toggle

			// check for long press
			if(button_time.ok == 0)
			{
				// was off, so save time of first press msg
				button_time.ok = curr_tick;
			}


			can_stats.filter_msg_ok++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 28 XX XX XX XX XX XX XX\t==>\t5c1 [8] 28 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick);
			}
		}
		else // ************** default to original msg but forcing 8 byte length
		{
			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] %02x XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0], can1_TX[0]);
			}
		}

		// all 0x5c1 are forced to DLC 8
		can1_txHeader.DLC = (uint32_t) 8;
		can_stats.filter_msg_dlc++;

		// clear all bytes but first
		for(int i = 1; i < 8; i++)
			can1_TX[i] = (uint8_t) 0x00;

		// send modified msg
		if(tx_msg)
		{
			if(!(can1_TX[0] == 0x00 && tx_clear_msg == 0))
			{
				if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
					UartPrintf("CAN1 Tx Failed - 0x5c1 (%02x)\r\n", can1_TX[0]);
				can_stats.can1_tx_count++;
			}
		}
	}
	else
	// ************** Power Down ???  These messages seem to be from the RCD330 to the car
	if(can1_txHeader.StdId == 0x436 && can1_txHeader.DLC == 8 && can1_TX[0] == 0x01 && can1_TX[5] == 0x06)
	{
		if(debug_mode.filters)
		{
			UartPrintf("CAN2 Filter [%8u]:\t436 [8] 01 XX XX XX XX 06 XX XX\t==>\t436 [6] 01 XX XX XX XX 06\r\n", can_stats.can2_last_rx_tick);
			UartPrintf("                                                        ==>\t439 [6] 01 XX XX XX XX 06\r\n");
		}

		can_stats.filter_msg_436_pwr++;

		// reduce length
		can1_txHeader.DLC = (uint32_t) 6;

		// send 1st 0x436 message
		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - 0x436\r\n");
		can_stats.can1_tx_count++;

		// send 2nd 0x439 message
		can1_txHeader.StdId = (uint32_t) 0x439;
		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - 0x439\r\n");
		can_stats.can1_tx_count++;
	}
	else
	if(can1_txHeader.StdId == 0x439 && can1_txHeader.DLC == 8 && can1_TX[0] == 0x01 && can1_TX[5] == 0x06)
	{
		if(debug_mode.filters)
		{
			UartPrintf("CAN2 Filter [%8u]:\t439 [8] 01 XX XX XX XX 06 XX XX\t==>\t439 [6] 01 XX XX XX XX 06\r\n", can_stats.can2_last_rx_tick);
		}

		can_stats.filter_msg_439_pwr++;

		// reduce length
		can1_txHeader.DLC = (uint32_t) 6;

		// send modified message
		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - 0x439 2\r\n");
		can_stats.can1_tx_count++;
	}
	else
	// ************** Illumination
	if(can1_txHeader.StdId == 0x635 && can1_txHeader.DLC == 3 && can1_TX[0] == 0x00 && can1_TX[1] == 0x00 && can1_TX[2] == 0x00)
	{
		// from observation, when lights are on, data[0] (backlight) varies 0x1d-0x62 (based on dash brightness setting).
		// this will be sent through without changes.

		// when lights are off, this is set to 0x00, RCD330 then uses data[2] for max brightness level
		// max brightness data[2] seems to be 0xfd, 0xffe & 0xff seem to be dimmer...
		// default 0xdc seems to be ok...

		if(debug_mode.filters)
			UartPrintf("CAN2 Filter [%8u]:\t635 [3] 00 00 00               \t==>\t635 [3] 00 00 %02x\r\n", can_stats.can2_last_rx_tick, debug_mode.max_illum);

		can1_TX[2] = (uint8_t) debug_mode.max_illum;
		can_stats.filter_msg_635_illum++;

		// send modified msg
		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - 0x635\r\n");
		can_stats.can1_tx_count++;
	}
	else
	{
		// ************** default is to send remaining msgs unchanged
		if(HAL_CAN_AddTxMessagex(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox) != HAL_OK)
			UartPrintf("CAN1 Tx Failed - default\r\n");
		can_stats.can1_tx_count++;
	}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // real time debug options
    switch(*serial_mode)
    {
    	case '1':
    		debug_mode.can1 = !debug_mode.can1;
    		UartPrintf("Debug CAN1 mode: %s\r\n", (debug_mode.can1) ? "On" : "Off");
    	break;

    	case '2':
        	debug_mode.can2 = !debug_mode.can2;
            UartPrintf("Debug CAN2 mode: %s\r\n", (debug_mode.can2) ? "On" : "Off");
       	break;

    	case 'f':
        	debug_mode.filters = !debug_mode.filters;
            UartPrintf("Debug filters mode: %s\r\n", (debug_mode.filters) ? "On" : "Off");
       	break;

    	case 's':
        	debug_mode.stats = !debug_mode.stats;
            UartPrintf("Debug stats mode: %s\r\n", (debug_mode.stats) ? "On" : "Off");
       	break;

    	case 'i':
        	if(debug_mode.max_illum == 0xff)
        		debug_mode.max_illum = 0x00;
        	else
        		debug_mode.max_illum++;
            UartPrintf("Debug max_illum mode: %02x\r\n", debug_mode.max_illum);
       	break;

    	case 'p':
        	debug_mode.filter_id_en = !debug_mode.filter_id_en;
            UartPrintf("Debug filter_id mode [%02x]: %s\r\n", debug_mode.filter_id_num, (debug_mode.filter_id_en) ? "On" : "Off");
       	break;

    	case '+':
    		debug_mode.filter_id_num++;

            UartPrintf("filter_id_num: %02x\r\n", debug_mode.filter_id_num);
       	break;

    	case '-':
    		debug_mode.filter_id_num--;

            UartPrintf("filter_id_num: %02x\r\n", debug_mode.filter_id_num);
       	break;

    	case '=':
    		debug_mode.filter_id_num += 0x10;

            UartPrintf("filter_id_num: %02x\r\n", debug_mode.filter_id_num);
       	break;

    	case '_':
    		debug_mode.filter_id_num -= 0x10;

            UartPrintf("filter_id_num: %02x\r\n", debug_mode.filter_id_num);
       	break;

    	case 'b':
    		NVIC_SystemReset();
    	break;

    	case 'l':
    		debug_mode.enable_led = !debug_mode.enable_led;
    		UartPrintf("Debug LED mode: %s\r\n", (debug_mode.enable_led) ? "On" : "Off");
    	break;

    	case 'c':
    		reset_count_magic = 0x0;
    	break;

    	case 'm':
    		if(key == 0)
    		{
    			UartPrintf("sending key Mute 0x2b to RCD330\r\n");
    			key = 0x2b;
    			key_hcan = &hcan1;
    		}
    		else
    			UartPrintf("key already being sent (%x)\r\n", key);
    	break;

    	case 'u':
    		if(key == 0)
    		{
    			UartPrintf("sending key Up 0x22 to vehicle\r\n");
    			key = 0x22;
    			key_hcan = &hcan2;
    		}
    		else
    			UartPrintf("key already being sent (%x)\r\n", key);
    	break;

    	case 'd':
    		if(key == 0)
    		{
    			UartPrintf("sending key Down 0x23 to vehicle\r\n");
    			key = 0x23;
    			key_hcan = &hcan2;
    		}
    		else
    			UartPrintf("key already being sent (%x)\r\n", key);
    	break;

    	case 'z':
    		print_flag = !print_flag;
    		if(print_flag)
                UartPrintf("Printing: %s\r\n", (print_flag) ? "On" : "Off");
    	break;

    	case 't':
        	debug_mode.buttons = !debug_mode.buttons;
            UartPrintf("Debug buttons mode: %s\r\n", (debug_mode.buttons) ? "On" : "Off");
     	break;

    	default:
    	break;

    }
    HAL_UART_Receive_IT(&huart4, serial_mode, 1);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

