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

UART_HandleTypeDef huart1;

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

//__attribute__((section(".noinit"))) volatile uint32_t filter_mode = 0;

// reset counter, incremented on every warm reset
__attribute__((section(".noinit"))) volatile uint32_t reset_count;

struct
{
	uint mute; // star
	uint menu;
	uint phone;
	uint ok;
} button_time = { 0, 0, 0, 0 };


__attribute__((section(".noinit"))) volatile struct
{
	uint up_next_code;
	uint down_prev_code;
	uint mute_google;	// try to swap b/w mute and "hey google"
} button_state = { 0x02, 0x03, 0x2b};  // RCD330 next/prev by default, otherwise MFD Up 0x22 / Down 0x23


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

	uint filter_mode;

//} debug_mode = { 0, 0, 0, 0, 0xdc, 0, 0x5c1, 0, 0};
} debug_mode = { 0, 0, 0, 0, 0xfd, 0, 0x5c1, 0, 0};


struct
{
	  uint can1_tx_count;
	  uint can1_rx_count;
	  uint can1_last_rx_tick;

	  uint can2_tx_count;
	  uint can2_rx_count;
	  uint can2_last_rx_tick;

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

} can_stats = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



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
static void MX_USART1_UART_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


uint8_t csend[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

void UartPrintf(const char *format, ...)
{
	char buffer[128];
	uint16_t size;
	va_list args;

	va_start(args, format);
	size = vsprintf(buffer, format, args);
	va_end(args);

	HAL_UART_Transmit(&huart1, (uint8_t*)buffer, size, 1000);
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

	  debug_mode.filter_mode = 0;


	  button_state.up_next_code = 0x02;
	  button_state.down_prev_code = 0x03;
	  button_state.mute_google = 0x2b;

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
	// On the Green (new, serial) Dual Filter Board:
	//
	// CAN1 is the RCD330
	// 	GREEN	CAN High
	//	PURPLE	CAN Low

	// CAN2 is the Vehicle
	// 	BLUE	CAN High
	//	YELLOW	CAN Low

	// PQ Quadlock connector
	//	WHITE	CAN High
	//	ORANGE	CAN Low
	// 	YELLOW	12V Battery
	//	BLACK	GND

	// Strategy:
	//	Cut the CAN High/Low connections between the connectors (WHITE/ORANGE thin wires), midway.
	//	Connect the appropriate sides to the Green CAN board
	//	Note: RCD330 side has the lever connector (female pins), the vehicle is the plain connector (male pins).
	//  Cut the thin YELLOW and BLACK wires (power) that used to go to the original black box.
	//  Tap the Green boards into these and re-connect the all together.
	//	Note: the idea is that the original black box can be reconnected easily for further debugging.

	// The Green board will be shrink wrapped instead of using a case.
	// The USART1 Dupont serial connections (and Gnd) will remain, in case debugging is required.
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
//  MX_CAN1_Init();
//  MX_CAN2_Init();
  MX_USART1_UART_Init();
//  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */


  // note the standard init routines are modifed as follows (due to sleep stop mode):
  /*
  MX_GPIO_Init();
  //MX_CAN1_Init();
  //MX_CAN2_Init();
  MX_USART1_UART_Init();
  //MX_IWDG_Init();
  */
  // see after sleep command below for full initialisation


  //HAL_IWDG_Refresh(&hiwdg);

  //RetargetInit(&huart1);

  HAL_UART_Receive_IT (&huart1, serial_mode, 1);


// using these for EXTI IWDG wakeup (CAN1, CAN2 & USART1)
//  HAL_GPIO_WritePin(GPIOB, OUT1_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, OUT2_Pin,0);
//  HAL_GPIO_WritePin(GPIOB, OUT3_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);


#if 0
  // scanf / printf needs "RetargetInit(&huart1);" after MX_USART1_UART_Init();

  int n = 0;

  printrintf("\r\nYour name: ");
  scanf("%s", buf);
  printf("\r\nHello, %s [%f]!\r\n", buf, n);
#endif

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint current_tick = 0;

  UartPrintf("\r\nDual CAN Filter v1.1 (100kb/s) %s [ reset_count %u ]\r\n\r\n", (config_loss) ? "Default Config" : "Existing Config", reset_count);


  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	  UartPrintf("Reset caused by IWDGRST\r\n\r\n");
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
	  UartPrintf("Reset caused by PORRST\r\n\r\n");
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET)
	  UartPrintf("Reset caused by SFTRST\r\n\r\n");
  else
	  UartPrintf("Reset cause unknown\r\n\r\n");

  //__HAL_RCC_CLEAR_RESET_FLAGS();


  HAL_Delay(3000);

  UartPrintf("Going into to Sleep Stop Mode\r\n\r\n");

  HAL_SuspendTick();
  /* Enter Stop Mode */
  DBGMCU->CR = 0;
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  HAL_ResumeTick();


  // need to redo all the initialisation
  SystemClock_Config();
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_IWDG_Init();
  MX_USART1_UART_Init();

#ifdef DB_ADC
  MX_ADC1_Init();
#endif

  // only for printf/scan
  //RetargetInit(&huart1);

  HAL_UART_Receive_IT (&huart1, serial_mode, 1);

// using these for EXTI IWDG wakeup (CAN1, CAN2 & USART1)
//  HAL_GPIO_WritePin(GPIOB, OUT1_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, OUT2_Pin,0);
//  HAL_GPIO_WritePin(GPIOB, OUT3_Pin,1);
//  HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);


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

  UartPrintf("EXTI %d - Waking from Sleep Stop Mode\r\n\r\n", (int) EXTI->PR);

  // don't need to do much here (just print stats), as CAN Filters & USART are interrupt driven
  while(1)
  {

	  // Get time elapsed

	  if(debug_mode.stats)
	  {
		  current_tick = HAL_GetTick();
		  if(current_tick % 10000 == 0)
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


#ifdef DB_ADC
			  {

				uint16_t readValue;
				float tCelsius;

			    HAL_ADC_PollForConversion(&hadc1, 100);

			    readValue = HAL_ADC_GetValue(&hadc1);

			    tCelsius = 357.558 - 0.187364 * readValue;

			    UartPrintf("tCelsius:\t\t%d\t%f\r\n\r\n", (int) readValue, tCelsius);

			  }
#endif



		  }
	  }



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
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL_NONE;
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
  hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = ENABLE;
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
  hcan2.Init.TimeSeg1 = CAN_BS1_15TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = ENABLE;
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
  hiwdg.Init.Reload = 3125;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */


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
		HAL_GPIO_TogglePin(GPIOB, LED_Pin);

	can_stats.can1_rx_count++;
	can_stats.can1_last_rx_tick = HAL_GetTick();

	HAL_IWDG_Refresh(&hiwdg);

	if(debug_mode.can1)
	{
		if(!(debug_mode.filter_id_en && (debug_mode.filter_id_num != can2_txHeader.StdId)))
		{

			UartPrintf("%8u [%8u] CAN1 Rx: 0x%.3x ", can_stats.can1_last_rx_tick, can_stats.can1_rx_count, (int) can2_txHeader.StdId);
			UartPrintf("[%d] ", (int) can2_txHeader.DLC);

			int i;
			for(i = 0; i < (int) can2_txHeader.DLC; i++)
			{
				UartPrintf("0x%.2x ", can2_TX[i]);
			}
			UartPrintf("\r\n");
		}
	}


	// Power Down ???  These messages seem to be from the RCD330 to the car
	// added to RCD330 => vehicle side...
	if(can2_txHeader.StdId == 0x436 && can2_txHeader.DLC == 8 && can2_TX[0] == 0x01 && can2_TX[5] == 0x06)
	{
		if(debug_mode.filters)
		{
			UartPrintf("CAN1 Filter [%8u]:\t436 [8] 01 XX XX XX XX 06 XX XX\t==>\t436 [6] 01 XX XX XX XX 06\r\n", can_stats.can1_last_rx_tick);
			UartPrintf("                                                        ==>\t439 [6] 01 XX XX XX XX 06\r\n");
		}

		can_stats.filter_msg_436_pwr++;

		// reduce length
		can2_txHeader.DLC = (uint32_t) 6;

		// send 1st 0x436 message
		HAL_CAN_AddTxMessage(&hcan2, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox);
		can_stats.can2_tx_count++;

		// send 2nd 0x439 message
		can2_txHeader.StdId = (uint32_t) 0x439;
		HAL_CAN_AddTxMessage(&hcan2, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox);
		can_stats.can2_tx_count++;
	}
	else
	if(can2_txHeader.StdId == 0x439 && can2_txHeader.DLC == 8 && can2_TX[0] == 0x01 && can2_TX[5] == 0x06)
	{
		if(debug_mode.filters)
		{
			UartPrintf("CAN1 Filter [%8u]:\t439 [8] 01 XX XX XX XX 06 XX XX\t==>\t439 [6] 01 XX XX XX XX 06\r\n", can_stats.can1_last_rx_tick);
		}

		can_stats.filter_msg_439_pwr++;

		// reduce length
		can2_txHeader.DLC = (uint32_t) 6;

		// send modified message
		HAL_CAN_AddTxMessage(&hcan2, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox);
		can_stats.can2_tx_count++;
	}
	else
	{
		// default
		HAL_CAN_AddTxMessage(&hcan2, (CAN_TxHeaderTypeDef *) &can2_txHeader, can2_TX, &can2_Mailbox);
		can_stats.can2_tx_count++;
	}
}


/*
 * CAN2 is connected to the vehicle CAN (which was connected to the RDC330)
 *
 * It will filter the vehicle CAN messages and send the modified versions via CAN1 to the RCD330
 */

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan2)
{
	HAL_CAN_GetRxMessage(hcan2, CAN_RX_FIFO1, &can2_rxHeader, can2_RX);

	uint curr_tick = HAL_GetTick();


	// defaults
	can1_txHeader.RTR = CAN_RTR_DATA;
	can1_txHeader.IDE = CAN_ID_STD;
	can1_txHeader.TransmitGlobalTime = DISABLE;


	// copy over useful stuff for tx-ing
	__disable_irq();

	can1_txHeader.StdId = can2_rxHeader.StdId;
	can1_txHeader.DLC = can2_rxHeader.DLC;

	for(int i=0; i < 8; i++)
	{
		can1_TX[i] = can2_RX[i];
	}

	__enable_irq();

	can1_txHeader.RTR = CAN_RTR_DATA;
	can1_txHeader.IDE = CAN_ID_STD;
	can1_txHeader.TransmitGlobalTime = DISABLE;


	if(debug_mode.enable_led)
		HAL_GPIO_TogglePin(GPIOB, LED_Pin);

	can_stats.can2_rx_count++;
	can_stats.can2_last_rx_tick = curr_tick;

	if(debug_mode.can2)
	{

		if(!(debug_mode.filter_id_en && (debug_mode.filter_id_num != can1_txHeader.StdId)))
		{
				UartPrintf("%8u [%8u] can2 Rx: 0x%.3x ", can_stats.can2_last_rx_tick, can_stats.can2_rx_count, (int) can1_txHeader.StdId);
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
		HAL_IWDG_Refresh(&hiwdg);

		can_stats.iwdg_msg++;

		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
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



		// presumably button active msgs are sent every 100ms while pressed
		// as soon as the clear msgs 0x00 arrives, check the time from 1st active msg.

#ifdef DB_CLEAR
		if(can1_TX[0] == 0x00)	// clear
		{
			// all buttons off, so check for a long press on useful buttons

			// force length 8
			can1_txHeader.DLC = (uint32_t) 8;

			// note that currently the msgs are still sent via the filter code below
			// we are not yet stopping messages getting to the radio, only changing which button is being identified...
			// in future, perhaps we can block the short msgs in the filter and send them manually via the short press detection in this routine...


			// mute ?
			uint dur = curr_tick - button_time.mute;

			// check for a long press (> 1sec)
			if(button_time.mute > 0)
			{
				if(dur > 1000)
				{
					UartPrintf("CAN2 Mute Long press\t[%u]\r\n", dur);
				}
				else
				{
					UartPrintf("CAN2 Mute Short press\t[%u]\r\n", dur);
				}
			}
			button_time.mute = 0;


			// menu ?
			dur = curr_tick - button_time.menu;

			if(button_time.menu > 0)
			{
				if(dur > 1000)
				{
					if(++debug_mode.filter_mode > 2)	// cycle through available modes on menu long press
						debug_mode.filter_mode = 0;

					UartPrintf("CAN2 Menu Long press\tfilter_mode: %u\t[%u]\r\n", debug_mode.filter_mode, dur);
				}
				else
				{
					UartPrintf("CAN2 Menu Short press\tfilter_mode: %u\t[%u]\r\n", debug_mode.filter_mode, dur);
				}
			}
			button_time.menu = 0;

			// phone ?
			dur = curr_tick - button_time.phone;

			if(button_time.phone > 0)
			{
				if(dur > 1000)
				{
					UartPrintf("CAN2 Phone Long press\t[%u]\r\n", dur);
				}
				else
				{
					UartPrintf("CAN2 Phone Short press\t[%u]\r\n", dur);
				}
			}
			button_time.phone = 0;

			// ok ?
			dur = curr_tick - button_time.ok;

			if(button_time.ok > 0)
			{
				if(dur > 1000)
				{
					UartPrintf("CAN2 Ok Long press\t[%u]\r\n", dur);
				}
				else
				{
					UartPrintf("CAN2 Ok Short press\t[%u]\r\n", dur);
				}
			}
			button_time.ok = 0;
		}
		else  // below here are the individual button filters
#endif
		if(can1_TX[0] == 0x1d || can1_TX[0] == 0x1e) // Some unknown buttons => Phone
		{
			// this is code from the Chinese can filter, might not be applicable to the Golf Mk5?

			uint8_t old_data = can1_TX[0];
			can1_TX[0] = (uint8_t) 0x1a;

			can_stats.filter_msg_phone++;
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;


			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] %02x XX XX XX XX XX XX XX\t==>\t5c1 [8] 1a 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, old_data);
			}
		}
		else
		if(can1_TX[0] == 0x22) // Up / Next
		{
			// Note the Up/Down buttons are a pain as they always change the MFD
			// By hitting "menu" it is possible to stop them affecting the radius (i.e. MFD only mode)
			// but this is still crap, annoying behaviour

			// Perhaps it is possible to "undo" the MFD changes while in "radio" mode?
			// We could send the opposite command back to the car and hope it updates the MFD.
			// i.e. press "ok" (radio mode), "up"=next (0x06 is sent to radio, 0x23,0x00 is sent via CAN1 to the car)
			//                             "down"=prev (0x07 is sent to radio, 0x22,0x00 is sent to car)

			// if this happens quick enough, maybe we won't notice the MFD glitching...?

			can1_TX[0] = (uint8_t) button_state.up_next_code;

			can_stats.filter_msg_up_next++;
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;


			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 22 XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0]);
			}
		}
		else
		if(can1_TX[0] == 0x23) // Down / Prev
		{
			can1_TX[0] = (uint8_t) button_state.down_prev_code;

			can_stats.filter_msg_down_prev++;
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;


			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 23 XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0]);
			}

		}
		else
		if(can1_TX[0] == 0x2b) // Mute / google
		{
			// check for long press
			if(button_time.mute == 0)
			{
				// was off, so save time of first press msg
				button_time.mute = curr_tick;
			}

			can1_TX[0] = (uint8_t) button_state.mute_google;
			can_stats.filter_msg_mute++;

			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;


			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 2b XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0]);
			}
		}
#if 0
		else
		if(can1_TX[0] == 0x1a)	// phone - no filter
		{
			// check for long press
			if(button_time.phone == 0)
			{
				// was off, so save time of first press msg
				button_time.phone = curr_tick;
			}

			// this is the same as default - don't change
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] %02x XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0], can1_TX[0]);
			}

		}
#endif
		else
		if(can1_TX[0] == 0x0a) // Menu, switch up/next functions (+google/seek testing)
		{
			// check for long press
			if(button_time.menu == 0)
			{
				// was off, so save time of first press msg
				button_time.menu = curr_tick;
			}

			button_state.up_next_code = 0x22;
			button_state.down_prev_code = 0x23;
			button_state.mute_google = 0x2a;
			//button_state.up_vol_seek = 0x04;
			//button_state.down_vol_seek = 0x05;

			can_stats.filter_msg_menu++;
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 0a XX XX XX XX XX XX XX\t==>\t5c1 [8] 0a 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick);
			}

		}
		else
		if(can1_TX[0] == 0x28) // Ok, switch to next/prev functions (+ vol/mute)
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

			button_state.up_next_code = 0x02;
			button_state.down_prev_code = 0x03;
			button_state.mute_google = 0x2b;
			//button_state.up_vol_seek = 0x06;
			//button_state.down_vol_seek = 0x07;

			can_stats.filter_msg_ok++;

			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] 28 XX XX XX XX XX XX XX\t==>\t5c1 [8] 28 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick);
			}
		}
		else // default to original msg but forcing 8 byte length
		{
			can1_txHeader.DLC = (uint32_t) 8;
			can_stats.filter_msg_dlc++;

			if(debug_mode.filters)
			{
				UartPrintf("CAN2 Filter [%8u]:\t5c1 [X] %02x XX XX XX XX XX XX XX\t==>\t5c1 [8] %02x 00 00 00 00 00 00 00\r\n", can_stats.can2_last_rx_tick, can1_TX[0], can1_TX[0]);
			}
		}

		// clear all bytes but first
		for(int i = 1; i < 8; i++)
			can1_TX[i] = (uint8_t) 0x00;

		// send modified msg
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
		can_stats.can1_tx_count++;
	}

#ifdef DB_POWER_CAN2
	else
	// Power Down ???  These messages seem to be from the RCD330 to the car
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
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
		can_stats.can1_tx_count++;

		// send 2nd 0x439 message
		can1_txHeader.StdId = (uint32_t) 0x439;
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
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
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
		can_stats.can1_tx_count++;
	}
#endif

	else
	// Illumination
	if(can1_txHeader.StdId == 0x635 && can1_txHeader.DLC == 3 && can1_TX[0] == 0x00 && can1_TX[1] == 0x00 && can1_TX[2] == 0x00)
	{

		// from observation, when lights are on, this varies 0x1d-0x62 (based on dash brightness setting).
		// when lights are off, this is set to 0x00 (which RCD330 takes as min brightness)
		// max brightness seems to be 0xfd, 0xffe & 0xff seem to be dimmer...
		// default 0xdc seems to be ok...

		if(debug_mode.filters)
			UartPrintf("CAN2 Filter [%8u]:\t635 [3] 00 00 00               \t==>\t635 [3] 00 00 %02x\r\n", can_stats.can2_last_rx_tick, debug_mode.max_illum);

		can1_TX[2] = (uint8_t) debug_mode.max_illum;
		can_stats.filter_msg_635_illum++;

		// send modified msg
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
		can_stats.can1_tx_count++;
	}
	else
	{
		// default is to send remaining msgs unchanged
		HAL_CAN_AddTxMessage(&hcan1, (CAN_TxHeaderTypeDef *) &can1_txHeader, can1_TX, &can1_Mailbox);
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


    	default:
    	break;

    }
    HAL_UART_Receive_IT(&huart1, serial_mode, 1);


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

