typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned int    uint;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined7;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef struct SPI2 SPI2, *PSPI2;

struct SPI2 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    uint SR; // status register
    uint DR; // data register
    uint CRCPR; // CRC polynomial register
    uint RXCRCR; // RX CRC register
    uint TXCRCR; // TX CRC register
    uint I2SCFGR; // I2S configuration register
    uint I2SPR; // I2S prescaler register
};

typedef struct SPI1 SPI1, *PSPI1;

struct SPI1 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    uint SR; // status register
    uint DR; // data register
    uint CRCPR; // CRC polynomial register
    uint RXCRCR; // RX CRC register
    uint TXCRCR; // TX CRC register
    uint I2SCFGR; // I2S configuration register
    uint I2SPR; // I2S prescaler register
};

typedef struct COMP COMP, *PCOMP;

struct COMP {
    uint CSR; // control and status register
};

typedef struct IWDG IWDG, *PIWDG;

struct IWDG {
    uint KR; // Key register
    uint PR; // Prescaler register
    uint RLR; // Reload register
    uint SR; // Status register
    uint WINR; // Window register
};

typedef struct Flash Flash, *PFlash;

struct Flash {
    uint ACR; // Flash access control register
    uint KEYR; // Flash key register
    uint OPTKEYR; // Flash option key register
    uint SR; // Flash status register
    uint CR; // Flash control register
    uint AR; // Flash address register
    undefined field6_0x18;
    undefined field7_0x19;
    undefined field8_0x1a;
    undefined field9_0x1b;
    uint OBR; // Option byte register
    uint WRPR; // Write protection register
};

typedef struct struct_gpio_config struct_gpio_config, *Pstruct_gpio_config;

struct struct_gpio_config {
    uint 1;
    byte 2;
    byte 3;
    byte 4;
    byte 5;
};

typedef struct RCC RCC, *PRCC;

struct RCC {
    uint CR; // Clock control register
    uint CFGR; // Clock configuration register           (RCC_CFGR)
    uint CIR; // Clock interrupt register           (RCC_CIR)
    uint APB2RSTR; // APB2 peripheral reset register           (RCC_APB2RSTR)
    uint APB1RSTR; // APB1 peripheral reset register           (RCC_APB1RSTR)
    uint AHBENR; // AHB Peripheral Clock enable register           (RCC_AHBENR)
    uint APB2ENR; // APB2 peripheral clock enable register           (RCC_APB2ENR)
    uint APB1ENR; // APB1 peripheral clock enable register           (RCC_APB1ENR)
    uint BDCR; // Backup domain control register           (RCC_BDCR)
    uint CSR; // Control/status register           (RCC_CSR)
    uint AHBRSTR; // AHB peripheral reset register
    uint CFGR2; // Clock configuration register 2
    uint CFGR3; // Clock configuration register 3
    uint CR2; // Clock control register 2
};

typedef struct CEC CEC, *PCEC;

struct CEC {
    uint CR; // control register
    uint CFGR; // configuration register
    uint TXDR; // Tx data register
    uint RXDR; // Rx Data Register
    uint ISR; // Interrupt and Status Register
    uint IER; // interrupt enable register
};

typedef struct struct_can_config struct_can_config, *Pstruct_can_config;

struct struct_can_config {
    ushort prescaler;
    byte mode;
    byte sync_jump_width;
    byte timeseg_1;
    byte timeseg_2;
    byte time_triggered_mode;
    byte auto_bus_off;
    byte auto_wakeup;
    byte auto_retransmit;
    byte receiver_fifo_locked;
    byte tx_fifo_priority;
};

typedef struct struct_gpio_registers struct_gpio_registers, *Pstruct_gpio_registers;

struct struct_gpio_registers {
    uint GPIO_MODER;
    uint GPIO_OTYPER;
    uint GPIO_OSPEEDR;
    uint GPIO_PUPDR;
    uint GPIO_IDR;
    uint GPIO_ODR;
    uint GPIO_BSRR;
    uint GPIO_LCKR;
    uint GPIO_AFRL;
    uint GPIO_AFRH;
    uint GPIO_BRR;
};

typedef struct PWR PWR, *PPWR;

struct PWR {
    uint CR; // power control register
    uint CSR; // power control/status register
};

typedef struct struct_exti_registers struct_exti_registers, *Pstruct_exti_registers;

struct struct_exti_registers {
    uint EXTI_IMR;
    uint EXTI_EMR;
    uint EXTI_RTSR;
    uint EXTI_FTSR;
    uint EXTI_SWIER;
    uint EXTI_PR;
};

typedef struct struct_can_registers struct_can_registers, *Pstruct_can_registers;

struct struct_can_registers {
    uint CAN_MCR;
    uint CAN_MSR;
    uint CAN_TSR;
    uint CAN_MRF0R;
    uint CAN_MRF1R;
    uint CAN_RF1R;
    uint CAN_IER;
    uint CAN_ESR;
    uint CAN_BTR;
};

typedef struct struct_can_filter_config struct_can_filter_config, *Pstruct_can_filter_config;

struct struct_can_filter_config {
    ushort filter_canid_high;
    ushort filter_canid_low;
    ushort filter_maskid_high;
    ushort filter_maskid_low;
    ushort filter_fifo;
    byte filter_num;
    byte filter_mode;
    byte filter_scale;
    byte filter_enabled;
};

typedef struct I2C1 I2C1, *PI2C1;

struct I2C1 {
    uint CR1; // Control register 1
    uint CR2; // Control register 2
    uint OAR1; // Own address register 1
    uint OAR2; // Own address register 2
    uint TIMINGR; // Timing register
    uint TIMEOUTR; // Status register 1
    uint ISR; // Interrupt and Status register
    uint ICR; // Interrupt clear register
    uint PECR; // PEC register
    uint RXDR; // Receive data register
    uint TXDR; // Transmit data register
};

typedef struct RTC RTC, *PRTC;

struct RTC {
    uint TR; // time register
    uint DR; // date register
    uint CR; // control register
    uint ISR; // initialization and status           register
    uint PRER; // prescaler register
    undefined field5_0x14;
    undefined field6_0x15;
    undefined field7_0x16;
    undefined field8_0x17;
    undefined field9_0x18;
    undefined field10_0x19;
    undefined field11_0x1a;
    undefined field12_0x1b;
    uint ALRMAR; // alarm A register
    undefined field14_0x20;
    undefined field15_0x21;
    undefined field16_0x22;
    undefined field17_0x23;
    uint WPR; // write protection register
    uint SSR; // sub second register
    uint SHIFTR; // shift control register
    uint TSTR; // timestamp time register
    uint TSDR; // timestamp date register
    uint TSSSR; // time-stamp sub second register
    uint CALR; // calibration register
    uint TAFCR; // tamper and alternate function configuration           register
    uint ALRMASSR; // alarm A sub second register
    undefined field27_0x48;
    undefined field28_0x49;
    undefined field29_0x4a;
    undefined field30_0x4b;
    undefined field31_0x4c;
    undefined field32_0x4d;
    undefined field33_0x4e;
    undefined field34_0x4f;
    uint BKP0R; // backup register
    uint BKP1R; // backup register
    uint BKP2R; // backup register
    uint BKP3R; // backup register
    uint BKP4R; // backup register
};

typedef struct struct_gpio_exti_data struct_gpio_exti_data, *Pstruct_gpio_exti_data;

struct struct_gpio_exti_data {
    uint bit_mask;
    byte offset;
    byte trigger_register_offset;
    byte enable;
};

typedef struct EXTI EXTI, *PEXTI;

struct EXTI {
    uint IMR; // Interrupt mask register           (EXTI_IMR)
    uint EMR; // Event mask register (EXTI_EMR)
    uint RTSR; // Rising Trigger selection register           (EXTI_RTSR)
    uint FTSR; // Falling Trigger selection register           (EXTI_FTSR)
    uint SWIER; // Software interrupt event register           (EXTI_SWIER)
    uint PR; // Pending register (EXTI_PR)
};

typedef struct WWDG WWDG, *PWWDG;

struct WWDG {
    uint CR; // Control register
    uint CFR; // Configuration register
    uint SR; // Status register
};

typedef struct USART1 USART1, *PUSART1;

struct USART1 {
    uint CR1; // Control register 1
    uint CR2; // Control register 2
    uint CR3; // Control register 3
    uint BRR; // Baud rate register
    uint GTPR; // Guard time and prescaler           register
    uint RTOR; // Receiver timeout register
    uint RQR; // Request register
    uint ISR; // Interrupt & status           register
    uint ICR; // Interrupt flag clear register
    uint RDR; // Receive data register
    uint TDR; // Transmit data register
};

typedef struct USART2 USART2, *PUSART2;

struct USART2 {
    uint CR1; // Control register 1
    uint CR2; // Control register 2
    uint CR3; // Control register 3
    uint BRR; // Baud rate register
    uint GTPR; // Guard time and prescaler           register
    uint RTOR; // Receiver timeout register
    uint RQR; // Request register
    uint ISR; // Interrupt & status           register
    uint ICR; // Interrupt flag clear register
    uint RDR; // Receive data register
    uint TDR; // Transmit data register
};

typedef struct GPIOC GPIOC, *PGPIOC;

struct GPIOC {
    uint MODER; // GPIO port mode register
    uint OTYPER; // GPIO port output type register
    uint OSPEEDR; // GPIO port output speed           register
    uint PUPDR; // GPIO port pull-up/pull-down           register
    uint IDR; // GPIO port input data register
    uint ODR; // GPIO port output data register
    uint BSRR; // GPIO port bit set/reset           register
    uint LCKR; // GPIO port configuration lock           register
    uint AFRL; // GPIO alternate function low           register
    uint AFRH; // GPIO alternate function high           register
    uint BRR; // Port bit reset register
};

typedef struct TIM14 TIM14, *PTIM14;

struct TIM14 {
    uint CR1; // control register 1
    undefined field1_0x4;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    undefined field5_0x8;
    undefined field6_0x9;
    undefined field7_0xa;
    undefined field8_0xb;
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register (input           mode)
    undefined field13_0x1c;
    undefined field14_0x1d;
    undefined field15_0x1e;
    undefined field16_0x1f;
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    undefined field21_0x30;
    undefined field22_0x31;
    undefined field23_0x32;
    undefined field24_0x33;
    uint CCR1; // capture/compare register 1
    undefined field26_0x38;
    undefined field27_0x39;
    undefined field28_0x3a;
    undefined field29_0x3b;
    undefined field30_0x3c;
    undefined field31_0x3d;
    undefined field32_0x3e;
    undefined field33_0x3f;
    undefined field34_0x40;
    undefined field35_0x41;
    undefined field36_0x42;
    undefined field37_0x43;
    undefined field38_0x44;
    undefined field39_0x45;
    undefined field40_0x46;
    undefined field41_0x47;
    undefined field42_0x48;
    undefined field43_0x49;
    undefined field44_0x4a;
    undefined field45_0x4b;
    undefined field46_0x4c;
    undefined field47_0x4d;
    undefined field48_0x4e;
    undefined field49_0x4f;
    uint OR; // option register
};

typedef struct GPIOF GPIOF, *PGPIOF;

struct GPIOF {
    uint MODER; // GPIO port mode register
    uint OTYPER; // GPIO port output type register
    uint OSPEEDR; // GPIO port output speed           register
    uint PUPDR; // GPIO port pull-up/pull-down           register
    uint IDR; // GPIO port input data register
    uint ODR; // GPIO port output data register
    uint BSRR; // GPIO port bit set/reset           register
    uint LCKR; // GPIO port configuration lock           register
    uint AFRL; // GPIO alternate function low           register
    uint AFRH; // GPIO alternate function high           register
    uint BRR; // Port bit reset register
};

typedef struct GPIOA GPIOA, *PGPIOA;

struct GPIOA {
    uint MODER; // GPIO port mode register
    uint OTYPER; // GPIO port output type register
    uint OSPEEDR; // GPIO port output speed           register
    uint PUPDR; // GPIO port pull-up/pull-down           register
    uint IDR; // GPIO port input data register
    uint ODR; // GPIO port output data register
    uint BSRR; // GPIO port bit set/reset           register
    uint LCKR; // GPIO port configuration lock           register
    uint AFRL; // GPIO alternate function low           register
    uint AFRH; // GPIO alternate function high           register
    uint BRR; // Port bit reset register
};

typedef struct TIM17 TIM17, *PTIM17;

struct TIM17 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    undefined field2_0x8;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register 1 (input           mode)
    undefined field10_0x1c;
    undefined field11_0x1d;
    undefined field12_0x1e;
    undefined field13_0x1f;
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    uint RCR; // repetition counter register
    uint CCR1; // capture/compare register 1
    undefined field20_0x38;
    undefined field21_0x39;
    undefined field22_0x3a;
    undefined field23_0x3b;
    undefined field24_0x3c;
    undefined field25_0x3d;
    undefined field26_0x3e;
    undefined field27_0x3f;
    undefined field28_0x40;
    undefined field29_0x41;
    undefined field30_0x42;
    undefined field31_0x43;
    uint BDTR; // break and dead-time register
    uint DCR; // DMA control register
    uint DMAR; // DMA address for full transfer
};

typedef struct GPIOB GPIOB, *PGPIOB;

struct GPIOB {
    uint MODER; // GPIO port mode register
    uint OTYPER; // GPIO port output type register
    uint OSPEEDR; // GPIO port output speed           register
    uint PUPDR; // GPIO port pull-up/pull-down           register
    uint IDR; // GPIO port input data register
    uint ODR; // GPIO port output data register
    uint BSRR; // GPIO port bit set/reset           register
    uint LCKR; // GPIO port configuration lock           register
    uint AFRL; // GPIO alternate function low           register
    uint AFRH; // GPIO alternate function high           register
    uint BRR; // Port bit reset register
};

typedef struct TIM16 TIM16, *PTIM16;

struct TIM16 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    undefined field2_0x8;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register 1 (input           mode)
    undefined field10_0x1c;
    undefined field11_0x1d;
    undefined field12_0x1e;
    undefined field13_0x1f;
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    uint RCR; // repetition counter register
    uint CCR1; // capture/compare register 1
    undefined field20_0x38;
    undefined field21_0x39;
    undefined field22_0x3a;
    undefined field23_0x3b;
    undefined field24_0x3c;
    undefined field25_0x3d;
    undefined field26_0x3e;
    undefined field27_0x3f;
    undefined field28_0x40;
    undefined field29_0x41;
    undefined field30_0x42;
    undefined field31_0x43;
    uint BDTR; // break and dead-time register
    uint DCR; // DMA control register
    uint DMAR; // DMA address for full transfer
};

typedef struct USB USB, *PUSB;

struct USB {
    uint EP0R; // endpoint 0 register
    uint EP1R; // endpoint 1 register
    uint EP2R; // endpoint 2 register
    uint EP3R; // endpoint 3 register
    uint EP4R; // endpoint 4 register
    uint EP5R; // endpoint 5 register
    uint EP6R; // endpoint 6 register
    uint EP7R; // endpoint 7 register
    undefined field8_0x20;
    undefined field9_0x21;
    undefined field10_0x22;
    undefined field11_0x23;
    undefined field12_0x24;
    undefined field13_0x25;
    undefined field14_0x26;
    undefined field15_0x27;
    undefined field16_0x28;
    undefined field17_0x29;
    undefined field18_0x2a;
    undefined field19_0x2b;
    undefined field20_0x2c;
    undefined field21_0x2d;
    undefined field22_0x2e;
    undefined field23_0x2f;
    undefined field24_0x30;
    undefined field25_0x31;
    undefined field26_0x32;
    undefined field27_0x33;
    undefined field28_0x34;
    undefined field29_0x35;
    undefined field30_0x36;
    undefined field31_0x37;
    undefined field32_0x38;
    undefined field33_0x39;
    undefined field34_0x3a;
    undefined field35_0x3b;
    undefined field36_0x3c;
    undefined field37_0x3d;
    undefined field38_0x3e;
    undefined field39_0x3f;
    uint CNTR; // control register
    uint ISTR; // interrupt status register
    uint FNR; // frame number register
    uint DADDR; // device address
    uint BTABLE; // Buffer table address
    uint LPMCSR; // LPM control and status           register
    uint BCDR; // Battery charging detector
};

typedef struct struct_nvic_data struct_nvic_data, *Pstruct_nvic_data;

struct struct_nvic_data {
    byte nvic_bit_num;
    byte nvic_ipro_data;
    byte write;
};

typedef struct CAN CAN, *PCAN;

struct CAN {
    uint CAN_MCR; // CAN_MCR
    uint CAN_MSR; // CAN_MSR
    uint CAN_TSR; // CAN_TSR
    uint CAN_RF0R; // CAN_RF0R
    uint CAN_RF1R; // CAN_RF1R
    uint CAN_IER; // CAN_IER
    uint CAN_ESR; // CAN_ESR
    uint CAN_BTR; // CAN_BTR
    undefined field8_0x20;
    undefined field9_0x21;
    undefined field10_0x22;
    undefined field11_0x23;
    undefined field12_0x24;
    undefined field13_0x25;
    undefined field14_0x26;
    undefined field15_0x27;
    undefined field16_0x28;
    undefined field17_0x29;
    undefined field18_0x2a;
    undefined field19_0x2b;
    undefined field20_0x2c;
    undefined field21_0x2d;
    undefined field22_0x2e;
    undefined field23_0x2f;
    undefined field24_0x30;
    undefined field25_0x31;
    undefined field26_0x32;
    undefined field27_0x33;
    undefined field28_0x34;
    undefined field29_0x35;
    undefined field30_0x36;
    undefined field31_0x37;
    undefined field32_0x38;
    undefined field33_0x39;
    undefined field34_0x3a;
    undefined field35_0x3b;
    undefined field36_0x3c;
    undefined field37_0x3d;
    undefined field38_0x3e;
    undefined field39_0x3f;
    undefined field40_0x40;
    undefined field41_0x41;
    undefined field42_0x42;
    undefined field43_0x43;
    undefined field44_0x44;
    undefined field45_0x45;
    undefined field46_0x46;
    undefined field47_0x47;
    undefined field48_0x48;
    undefined field49_0x49;
    undefined field50_0x4a;
    undefined field51_0x4b;
    undefined field52_0x4c;
    undefined field53_0x4d;
    undefined field54_0x4e;
    undefined field55_0x4f;
    undefined field56_0x50;
    undefined field57_0x51;
    undefined field58_0x52;
    undefined field59_0x53;
    undefined field60_0x54;
    undefined field61_0x55;
    undefined field62_0x56;
    undefined field63_0x57;
    undefined field64_0x58;
    undefined field65_0x59;
    undefined field66_0x5a;
    undefined field67_0x5b;
    undefined field68_0x5c;
    undefined field69_0x5d;
    undefined field70_0x5e;
    undefined field71_0x5f;
    undefined field72_0x60;
    undefined field73_0x61;
    undefined field74_0x62;
    undefined field75_0x63;
    undefined field76_0x64;
    undefined field77_0x65;
    undefined field78_0x66;
    undefined field79_0x67;
    undefined field80_0x68;
    undefined field81_0x69;
    undefined field82_0x6a;
    undefined field83_0x6b;
    undefined field84_0x6c;
    undefined field85_0x6d;
    undefined field86_0x6e;
    undefined field87_0x6f;
    undefined field88_0x70;
    undefined field89_0x71;
    undefined field90_0x72;
    undefined field91_0x73;
    undefined field92_0x74;
    undefined field93_0x75;
    undefined field94_0x76;
    undefined field95_0x77;
    undefined field96_0x78;
    undefined field97_0x79;
    undefined field98_0x7a;
    undefined field99_0x7b;
    undefined field100_0x7c;
    undefined field101_0x7d;
    undefined field102_0x7e;
    undefined field103_0x7f;
    undefined field104_0x80;
    undefined field105_0x81;
    undefined field106_0x82;
    undefined field107_0x83;
    undefined field108_0x84;
    undefined field109_0x85;
    undefined field110_0x86;
    undefined field111_0x87;
    undefined field112_0x88;
    undefined field113_0x89;
    undefined field114_0x8a;
    undefined field115_0x8b;
    undefined field116_0x8c;
    undefined field117_0x8d;
    undefined field118_0x8e;
    undefined field119_0x8f;
    undefined field120_0x90;
    undefined field121_0x91;
    undefined field122_0x92;
    undefined field123_0x93;
    undefined field124_0x94;
    undefined field125_0x95;
    undefined field126_0x96;
    undefined field127_0x97;
    undefined field128_0x98;
    undefined field129_0x99;
    undefined field130_0x9a;
    undefined field131_0x9b;
    undefined field132_0x9c;
    undefined field133_0x9d;
    undefined field134_0x9e;
    undefined field135_0x9f;
    undefined field136_0xa0;
    undefined field137_0xa1;
    undefined field138_0xa2;
    undefined field139_0xa3;
    undefined field140_0xa4;
    undefined field141_0xa5;
    undefined field142_0xa6;
    undefined field143_0xa7;
    undefined field144_0xa8;
    undefined field145_0xa9;
    undefined field146_0xaa;
    undefined field147_0xab;
    undefined field148_0xac;
    undefined field149_0xad;
    undefined field150_0xae;
    undefined field151_0xaf;
    undefined field152_0xb0;
    undefined field153_0xb1;
    undefined field154_0xb2;
    undefined field155_0xb3;
    undefined field156_0xb4;
    undefined field157_0xb5;
    undefined field158_0xb6;
    undefined field159_0xb7;
    undefined field160_0xb8;
    undefined field161_0xb9;
    undefined field162_0xba;
    undefined field163_0xbb;
    undefined field164_0xbc;
    undefined field165_0xbd;
    undefined field166_0xbe;
    undefined field167_0xbf;
    undefined field168_0xc0;
    undefined field169_0xc1;
    undefined field170_0xc2;
    undefined field171_0xc3;
    undefined field172_0xc4;
    undefined field173_0xc5;
    undefined field174_0xc6;
    undefined field175_0xc7;
    undefined field176_0xc8;
    undefined field177_0xc9;
    undefined field178_0xca;
    undefined field179_0xcb;
    undefined field180_0xcc;
    undefined field181_0xcd;
    undefined field182_0xce;
    undefined field183_0xcf;
    undefined field184_0xd0;
    undefined field185_0xd1;
    undefined field186_0xd2;
    undefined field187_0xd3;
    undefined field188_0xd4;
    undefined field189_0xd5;
    undefined field190_0xd6;
    undefined field191_0xd7;
    undefined field192_0xd8;
    undefined field193_0xd9;
    undefined field194_0xda;
    undefined field195_0xdb;
    undefined field196_0xdc;
    undefined field197_0xdd;
    undefined field198_0xde;
    undefined field199_0xdf;
    undefined field200_0xe0;
    undefined field201_0xe1;
    undefined field202_0xe2;
    undefined field203_0xe3;
    undefined field204_0xe4;
    undefined field205_0xe5;
    undefined field206_0xe6;
    undefined field207_0xe7;
    undefined field208_0xe8;
    undefined field209_0xe9;
    undefined field210_0xea;
    undefined field211_0xeb;
    undefined field212_0xec;
    undefined field213_0xed;
    undefined field214_0xee;
    undefined field215_0xef;
    undefined field216_0xf0;
    undefined field217_0xf1;
    undefined field218_0xf2;
    undefined field219_0xf3;
    undefined field220_0xf4;
    undefined field221_0xf5;
    undefined field222_0xf6;
    undefined field223_0xf7;
    undefined field224_0xf8;
    undefined field225_0xf9;
    undefined field226_0xfa;
    undefined field227_0xfb;
    undefined field228_0xfc;
    undefined field229_0xfd;
    undefined field230_0xfe;
    undefined field231_0xff;
    undefined field232_0x100;
    undefined field233_0x101;
    undefined field234_0x102;
    undefined field235_0x103;
    undefined field236_0x104;
    undefined field237_0x105;
    undefined field238_0x106;
    undefined field239_0x107;
    undefined field240_0x108;
    undefined field241_0x109;
    undefined field242_0x10a;
    undefined field243_0x10b;
    undefined field244_0x10c;
    undefined field245_0x10d;
    undefined field246_0x10e;
    undefined field247_0x10f;
    undefined field248_0x110;
    undefined field249_0x111;
    undefined field250_0x112;
    undefined field251_0x113;
    undefined field252_0x114;
    undefined field253_0x115;
    undefined field254_0x116;
    undefined field255_0x117;
    undefined field256_0x118;
    undefined field257_0x119;
    undefined field258_0x11a;
    undefined field259_0x11b;
    undefined field260_0x11c;
    undefined field261_0x11d;
    undefined field262_0x11e;
    undefined field263_0x11f;
    undefined field264_0x120;
    undefined field265_0x121;
    undefined field266_0x122;
    undefined field267_0x123;
    undefined field268_0x124;
    undefined field269_0x125;
    undefined field270_0x126;
    undefined field271_0x127;
    undefined field272_0x128;
    undefined field273_0x129;
    undefined field274_0x12a;
    undefined field275_0x12b;
    undefined field276_0x12c;
    undefined field277_0x12d;
    undefined field278_0x12e;
    undefined field279_0x12f;
    undefined field280_0x130;
    undefined field281_0x131;
    undefined field282_0x132;
    undefined field283_0x133;
    undefined field284_0x134;
    undefined field285_0x135;
    undefined field286_0x136;
    undefined field287_0x137;
    undefined field288_0x138;
    undefined field289_0x139;
    undefined field290_0x13a;
    undefined field291_0x13b;
    undefined field292_0x13c;
    undefined field293_0x13d;
    undefined field294_0x13e;
    undefined field295_0x13f;
    undefined field296_0x140;
    undefined field297_0x141;
    undefined field298_0x142;
    undefined field299_0x143;
    undefined field300_0x144;
    undefined field301_0x145;
    undefined field302_0x146;
    undefined field303_0x147;
    undefined field304_0x148;
    undefined field305_0x149;
    undefined field306_0x14a;
    undefined field307_0x14b;
    undefined field308_0x14c;
    undefined field309_0x14d;
    undefined field310_0x14e;
    undefined field311_0x14f;
    undefined field312_0x150;
    undefined field313_0x151;
    undefined field314_0x152;
    undefined field315_0x153;
    undefined field316_0x154;
    undefined field317_0x155;
    undefined field318_0x156;
    undefined field319_0x157;
    undefined field320_0x158;
    undefined field321_0x159;
    undefined field322_0x15a;
    undefined field323_0x15b;
    undefined field324_0x15c;
    undefined field325_0x15d;
    undefined field326_0x15e;
    undefined field327_0x15f;
    undefined field328_0x160;
    undefined field329_0x161;
    undefined field330_0x162;
    undefined field331_0x163;
    undefined field332_0x164;
    undefined field333_0x165;
    undefined field334_0x166;
    undefined field335_0x167;
    undefined field336_0x168;
    undefined field337_0x169;
    undefined field338_0x16a;
    undefined field339_0x16b;
    undefined field340_0x16c;
    undefined field341_0x16d;
    undefined field342_0x16e;
    undefined field343_0x16f;
    undefined field344_0x170;
    undefined field345_0x171;
    undefined field346_0x172;
    undefined field347_0x173;
    undefined field348_0x174;
    undefined field349_0x175;
    undefined field350_0x176;
    undefined field351_0x177;
    undefined field352_0x178;
    undefined field353_0x179;
    undefined field354_0x17a;
    undefined field355_0x17b;
    undefined field356_0x17c;
    undefined field357_0x17d;
    undefined field358_0x17e;
    undefined field359_0x17f;
    uint CAN_TI0R; // CAN_TI0R
    uint CAN_TDT0R; // CAN_TDT0R
    uint CAN_TDL0R; // CAN_TDL0R
    uint CAN_TDH0R; // CAN_TDH0R
    uint CAN_TI1R; // CAN_TI1R
    uint CAN_TDT1R; // CAN_TDT1R
    uint CAN_TDL1R; // CAN_TDL1R
    uint CAN_TDH1R; // CAN_TDH1R
    uint CAN_TI2R; // CAN_TI2R
    uint CAN_TDT2R; // CAN_TDT2R
    uint CAN_TDL2R; // CAN_TDL2R
    uint CAN_TDH2R; // CAN_TDH2R
    uint CAN_RI0R; // CAN_RI0R
    uint CAN_RDT0R; // CAN_RDT0R
    uint CAN_RDL0R; // CAN_RDL0R
    uint CAN_RDH0R; // CAN_RDH0R
    uint CAN_RI1R; // CAN_RI1R
    uint CAN_RDT1R; // CAN_RDT1R
    uint CAN_RDL1R; // CAN_RDL1R
    uint CAN_RDH1R; // CAN_RDH1R
    undefined field380_0x1d0;
    undefined field381_0x1d1;
    undefined field382_0x1d2;
    undefined field383_0x1d3;
    undefined field384_0x1d4;
    undefined field385_0x1d5;
    undefined field386_0x1d6;
    undefined field387_0x1d7;
    undefined field388_0x1d8;
    undefined field389_0x1d9;
    undefined field390_0x1da;
    undefined field391_0x1db;
    undefined field392_0x1dc;
    undefined field393_0x1dd;
    undefined field394_0x1de;
    undefined field395_0x1df;
    undefined field396_0x1e0;
    undefined field397_0x1e1;
    undefined field398_0x1e2;
    undefined field399_0x1e3;
    undefined field400_0x1e4;
    undefined field401_0x1e5;
    undefined field402_0x1e6;
    undefined field403_0x1e7;
    undefined field404_0x1e8;
    undefined field405_0x1e9;
    undefined field406_0x1ea;
    undefined field407_0x1eb;
    undefined field408_0x1ec;
    undefined field409_0x1ed;
    undefined field410_0x1ee;
    undefined field411_0x1ef;
    undefined field412_0x1f0;
    undefined field413_0x1f1;
    undefined field414_0x1f2;
    undefined field415_0x1f3;
    undefined field416_0x1f4;
    undefined field417_0x1f5;
    undefined field418_0x1f6;
    undefined field419_0x1f7;
    undefined field420_0x1f8;
    undefined field421_0x1f9;
    undefined field422_0x1fa;
    undefined field423_0x1fb;
    undefined field424_0x1fc;
    undefined field425_0x1fd;
    undefined field426_0x1fe;
    undefined field427_0x1ff;
    uint CAN_FMR; // CAN_FMR
    uint CAN_FM1R; // CAN_FM1R
    undefined field430_0x208;
    undefined field431_0x209;
    undefined field432_0x20a;
    undefined field433_0x20b;
    uint CAN_FS1R; // CAN_FS1R
    undefined field435_0x210;
    undefined field436_0x211;
    undefined field437_0x212;
    undefined field438_0x213;
    uint CAN_FFA1R; // CAN_FFA1R
    undefined field440_0x218;
    undefined field441_0x219;
    undefined field442_0x21a;
    undefined field443_0x21b;
    uint CAN_FA1R; // CAN_FA1R
    undefined field445_0x220;
    undefined field446_0x221;
    undefined field447_0x222;
    undefined field448_0x223;
    undefined field449_0x224;
    undefined field450_0x225;
    undefined field451_0x226;
    undefined field452_0x227;
    undefined field453_0x228;
    undefined field454_0x229;
    undefined field455_0x22a;
    undefined field456_0x22b;
    undefined field457_0x22c;
    undefined field458_0x22d;
    undefined field459_0x22e;
    undefined field460_0x22f;
    undefined field461_0x230;
    undefined field462_0x231;
    undefined field463_0x232;
    undefined field464_0x233;
    undefined field465_0x234;
    undefined field466_0x235;
    undefined field467_0x236;
    undefined field468_0x237;
    undefined field469_0x238;
    undefined field470_0x239;
    undefined field471_0x23a;
    undefined field472_0x23b;
    undefined field473_0x23c;
    undefined field474_0x23d;
    undefined field475_0x23e;
    undefined field476_0x23f;
    uint F0R1; // Filter bank 0 register 1
    uint F0R2; // Filter bank 0 register 2
    uint F1R1; // Filter bank 1 register 1
    uint F1R2; // Filter bank 1 register 2
    uint F2R1; // Filter bank 2 register 1
    uint F2R2; // Filter bank 2 register 2
    uint F3R1; // Filter bank 3 register 1
    uint F3R2; // Filter bank 3 register 2
    uint F4R1; // Filter bank 4 register 1
    uint F4R2; // Filter bank 4 register 2
    uint F5R1; // Filter bank 5 register 1
    uint F5R2; // Filter bank 5 register 2
    uint F6R1; // Filter bank 6 register 1
    uint F6R2; // Filter bank 6 register 2
    uint F7R1; // Filter bank 7 register 1
    uint F7R2; // Filter bank 7 register 2
    uint F8R1; // Filter bank 8 register 1
    uint F8R2; // Filter bank 8 register 2
    uint F9R1; // Filter bank 9 register 1
    uint F9R2; // Filter bank 9 register 2
    uint F10R1; // Filter bank 10 register 1
    uint F10R2; // Filter bank 10 register 2
    uint F11R1; // Filter bank 11 register 1
    uint F11R2; // Filter bank 11 register 2
    uint F12R1; // Filter bank 4 register 1
    uint F12R2; // Filter bank 12 register 2
    uint F13R1; // Filter bank 13 register 1
    uint F13R2; // Filter bank 13 register 2
    uint F14R1; // Filter bank 14 register 1
    uint F14R2; // Filter bank 14 register 2
    uint F15R1; // Filter bank 15 register 1
    uint F15R2; // Filter bank 15 register 2
    uint F16R1; // Filter bank 16 register 1
    uint F16R2; // Filter bank 16 register 2
    uint F17R1; // Filter bank 17 register 1
    uint F17R2; // Filter bank 17 register 2
    uint F18R1; // Filter bank 18 register 1
    uint F18R2; // Filter bank 18 register 2
    uint F19R1; // Filter bank 19 register 1
    uint F19R2; // Filter bank 19 register 2
    uint F20R1; // Filter bank 20 register 1
    uint F20R2; // Filter bank 20 register 2
    uint F21R1; // Filter bank 21 register 1
    uint F21R2; // Filter bank 21 register 2
    uint F22R1; // Filter bank 22 register 1
    uint F22R2; // Filter bank 22 register 2
    uint F23R1; // Filter bank 23 register 1
    uint F23R2; // Filter bank 23 register 2
    uint F24R1; // Filter bank 24 register 1
    uint F24R2; // Filter bank 24 register 2
    uint F25R1; // Filter bank 25 register 1
    uint F25R2; // Filter bank 25 register 2
    uint F26R1; // Filter bank 26 register 1
    uint F26R2; // Filter bank 26 register 2
    uint F27R1; // Filter bank 27 register 1
    uint F27R2; // Filter bank 27 register 2
};

typedef struct ADC ADC, *PADC;

struct ADC {
    uint ISR; // interrupt and status register
    uint IER; // interrupt enable register
    uint CR; // control register
    uint CFGR1; // configuration register 1
    uint CFGR2; // configuration register 2
    uint SMPR; // sampling time register
    undefined field6_0x18;
    undefined field7_0x19;
    undefined field8_0x1a;
    undefined field9_0x1b;
    undefined field10_0x1c;
    undefined field11_0x1d;
    undefined field12_0x1e;
    undefined field13_0x1f;
    uint TR; // watchdog threshold register
    undefined field15_0x24;
    undefined field16_0x25;
    undefined field17_0x26;
    undefined field18_0x27;
    uint CHSELR; // channel selection register
    undefined field20_0x2c;
    undefined field21_0x2d;
    undefined field22_0x2e;
    undefined field23_0x2f;
    undefined field24_0x30;
    undefined field25_0x31;
    undefined field26_0x32;
    undefined field27_0x33;
    undefined field28_0x34;
    undefined field29_0x35;
    undefined field30_0x36;
    undefined field31_0x37;
    undefined field32_0x38;
    undefined field33_0x39;
    undefined field34_0x3a;
    undefined field35_0x3b;
    undefined field36_0x3c;
    undefined field37_0x3d;
    undefined field38_0x3e;
    undefined field39_0x3f;
    uint DR; // data register
    undefined field41_0x44;
    undefined field42_0x45;
    undefined field43_0x46;
    undefined field44_0x47;
    undefined field45_0x48;
    undefined field46_0x49;
    undefined field47_0x4a;
    undefined field48_0x4b;
    undefined field49_0x4c;
    undefined field50_0x4d;
    undefined field51_0x4e;
    undefined field52_0x4f;
    undefined field53_0x50;
    undefined field54_0x51;
    undefined field55_0x52;
    undefined field56_0x53;
    undefined field57_0x54;
    undefined field58_0x55;
    undefined field59_0x56;
    undefined field60_0x57;
    undefined field61_0x58;
    undefined field62_0x59;
    undefined field63_0x5a;
    undefined field64_0x5b;
    undefined field65_0x5c;
    undefined field66_0x5d;
    undefined field67_0x5e;
    undefined field68_0x5f;
    undefined field69_0x60;
    undefined field70_0x61;
    undefined field71_0x62;
    undefined field72_0x63;
    undefined field73_0x64;
    undefined field74_0x65;
    undefined field75_0x66;
    undefined field76_0x67;
    undefined field77_0x68;
    undefined field78_0x69;
    undefined field79_0x6a;
    undefined field80_0x6b;
    undefined field81_0x6c;
    undefined field82_0x6d;
    undefined field83_0x6e;
    undefined field84_0x6f;
    undefined field85_0x70;
    undefined field86_0x71;
    undefined field87_0x72;
    undefined field88_0x73;
    undefined field89_0x74;
    undefined field90_0x75;
    undefined field91_0x76;
    undefined field92_0x77;
    undefined field93_0x78;
    undefined field94_0x79;
    undefined field95_0x7a;
    undefined field96_0x7b;
    undefined field97_0x7c;
    undefined field98_0x7d;
    undefined field99_0x7e;
    undefined field100_0x7f;
    undefined field101_0x80;
    undefined field102_0x81;
    undefined field103_0x82;
    undefined field104_0x83;
    undefined field105_0x84;
    undefined field106_0x85;
    undefined field107_0x86;
    undefined field108_0x87;
    undefined field109_0x88;
    undefined field110_0x89;
    undefined field111_0x8a;
    undefined field112_0x8b;
    undefined field113_0x8c;
    undefined field114_0x8d;
    undefined field115_0x8e;
    undefined field116_0x8f;
    undefined field117_0x90;
    undefined field118_0x91;
    undefined field119_0x92;
    undefined field120_0x93;
    undefined field121_0x94;
    undefined field122_0x95;
    undefined field123_0x96;
    undefined field124_0x97;
    undefined field125_0x98;
    undefined field126_0x99;
    undefined field127_0x9a;
    undefined field128_0x9b;
    undefined field129_0x9c;
    undefined field130_0x9d;
    undefined field131_0x9e;
    undefined field132_0x9f;
    undefined field133_0xa0;
    undefined field134_0xa1;
    undefined field135_0xa2;
    undefined field136_0xa3;
    undefined field137_0xa4;
    undefined field138_0xa5;
    undefined field139_0xa6;
    undefined field140_0xa7;
    undefined field141_0xa8;
    undefined field142_0xa9;
    undefined field143_0xaa;
    undefined field144_0xab;
    undefined field145_0xac;
    undefined field146_0xad;
    undefined field147_0xae;
    undefined field148_0xaf;
    undefined field149_0xb0;
    undefined field150_0xb1;
    undefined field151_0xb2;
    undefined field152_0xb3;
    undefined field153_0xb4;
    undefined field154_0xb5;
    undefined field155_0xb6;
    undefined field156_0xb7;
    undefined field157_0xb8;
    undefined field158_0xb9;
    undefined field159_0xba;
    undefined field160_0xbb;
    undefined field161_0xbc;
    undefined field162_0xbd;
    undefined field163_0xbe;
    undefined field164_0xbf;
    undefined field165_0xc0;
    undefined field166_0xc1;
    undefined field167_0xc2;
    undefined field168_0xc3;
    undefined field169_0xc4;
    undefined field170_0xc5;
    undefined field171_0xc6;
    undefined field172_0xc7;
    undefined field173_0xc8;
    undefined field174_0xc9;
    undefined field175_0xca;
    undefined field176_0xcb;
    undefined field177_0xcc;
    undefined field178_0xcd;
    undefined field179_0xce;
    undefined field180_0xcf;
    undefined field181_0xd0;
    undefined field182_0xd1;
    undefined field183_0xd2;
    undefined field184_0xd3;
    undefined field185_0xd4;
    undefined field186_0xd5;
    undefined field187_0xd6;
    undefined field188_0xd7;
    undefined field189_0xd8;
    undefined field190_0xd9;
    undefined field191_0xda;
    undefined field192_0xdb;
    undefined field193_0xdc;
    undefined field194_0xdd;
    undefined field195_0xde;
    undefined field196_0xdf;
    undefined field197_0xe0;
    undefined field198_0xe1;
    undefined field199_0xe2;
    undefined field200_0xe3;
    undefined field201_0xe4;
    undefined field202_0xe5;
    undefined field203_0xe6;
    undefined field204_0xe7;
    undefined field205_0xe8;
    undefined field206_0xe9;
    undefined field207_0xea;
    undefined field208_0xeb;
    undefined field209_0xec;
    undefined field210_0xed;
    undefined field211_0xee;
    undefined field212_0xef;
    undefined field213_0xf0;
    undefined field214_0xf1;
    undefined field215_0xf2;
    undefined field216_0xf3;
    undefined field217_0xf4;
    undefined field218_0xf5;
    undefined field219_0xf6;
    undefined field220_0xf7;
    undefined field221_0xf8;
    undefined field222_0xf9;
    undefined field223_0xfa;
    undefined field224_0xfb;
    undefined field225_0xfc;
    undefined field226_0xfd;
    undefined field227_0xfe;
    undefined field228_0xff;
    undefined field229_0x100;
    undefined field230_0x101;
    undefined field231_0x102;
    undefined field232_0x103;
    undefined field233_0x104;
    undefined field234_0x105;
    undefined field235_0x106;
    undefined field236_0x107;
    undefined field237_0x108;
    undefined field238_0x109;
    undefined field239_0x10a;
    undefined field240_0x10b;
    undefined field241_0x10c;
    undefined field242_0x10d;
    undefined field243_0x10e;
    undefined field244_0x10f;
    undefined field245_0x110;
    undefined field246_0x111;
    undefined field247_0x112;
    undefined field248_0x113;
    undefined field249_0x114;
    undefined field250_0x115;
    undefined field251_0x116;
    undefined field252_0x117;
    undefined field253_0x118;
    undefined field254_0x119;
    undefined field255_0x11a;
    undefined field256_0x11b;
    undefined field257_0x11c;
    undefined field258_0x11d;
    undefined field259_0x11e;
    undefined field260_0x11f;
    undefined field261_0x120;
    undefined field262_0x121;
    undefined field263_0x122;
    undefined field264_0x123;
    undefined field265_0x124;
    undefined field266_0x125;
    undefined field267_0x126;
    undefined field268_0x127;
    undefined field269_0x128;
    undefined field270_0x129;
    undefined field271_0x12a;
    undefined field272_0x12b;
    undefined field273_0x12c;
    undefined field274_0x12d;
    undefined field275_0x12e;
    undefined field276_0x12f;
    undefined field277_0x130;
    undefined field278_0x131;
    undefined field279_0x132;
    undefined field280_0x133;
    undefined field281_0x134;
    undefined field282_0x135;
    undefined field283_0x136;
    undefined field284_0x137;
    undefined field285_0x138;
    undefined field286_0x139;
    undefined field287_0x13a;
    undefined field288_0x13b;
    undefined field289_0x13c;
    undefined field290_0x13d;
    undefined field291_0x13e;
    undefined field292_0x13f;
    undefined field293_0x140;
    undefined field294_0x141;
    undefined field295_0x142;
    undefined field296_0x143;
    undefined field297_0x144;
    undefined field298_0x145;
    undefined field299_0x146;
    undefined field300_0x147;
    undefined field301_0x148;
    undefined field302_0x149;
    undefined field303_0x14a;
    undefined field304_0x14b;
    undefined field305_0x14c;
    undefined field306_0x14d;
    undefined field307_0x14e;
    undefined field308_0x14f;
    undefined field309_0x150;
    undefined field310_0x151;
    undefined field311_0x152;
    undefined field312_0x153;
    undefined field313_0x154;
    undefined field314_0x155;
    undefined field315_0x156;
    undefined field316_0x157;
    undefined field317_0x158;
    undefined field318_0x159;
    undefined field319_0x15a;
    undefined field320_0x15b;
    undefined field321_0x15c;
    undefined field322_0x15d;
    undefined field323_0x15e;
    undefined field324_0x15f;
    undefined field325_0x160;
    undefined field326_0x161;
    undefined field327_0x162;
    undefined field328_0x163;
    undefined field329_0x164;
    undefined field330_0x165;
    undefined field331_0x166;
    undefined field332_0x167;
    undefined field333_0x168;
    undefined field334_0x169;
    undefined field335_0x16a;
    undefined field336_0x16b;
    undefined field337_0x16c;
    undefined field338_0x16d;
    undefined field339_0x16e;
    undefined field340_0x16f;
    undefined field341_0x170;
    undefined field342_0x171;
    undefined field343_0x172;
    undefined field344_0x173;
    undefined field345_0x174;
    undefined field346_0x175;
    undefined field347_0x176;
    undefined field348_0x177;
    undefined field349_0x178;
    undefined field350_0x179;
    undefined field351_0x17a;
    undefined field352_0x17b;
    undefined field353_0x17c;
    undefined field354_0x17d;
    undefined field355_0x17e;
    undefined field356_0x17f;
    undefined field357_0x180;
    undefined field358_0x181;
    undefined field359_0x182;
    undefined field360_0x183;
    undefined field361_0x184;
    undefined field362_0x185;
    undefined field363_0x186;
    undefined field364_0x187;
    undefined field365_0x188;
    undefined field366_0x189;
    undefined field367_0x18a;
    undefined field368_0x18b;
    undefined field369_0x18c;
    undefined field370_0x18d;
    undefined field371_0x18e;
    undefined field372_0x18f;
    undefined field373_0x190;
    undefined field374_0x191;
    undefined field375_0x192;
    undefined field376_0x193;
    undefined field377_0x194;
    undefined field378_0x195;
    undefined field379_0x196;
    undefined field380_0x197;
    undefined field381_0x198;
    undefined field382_0x199;
    undefined field383_0x19a;
    undefined field384_0x19b;
    undefined field385_0x19c;
    undefined field386_0x19d;
    undefined field387_0x19e;
    undefined field388_0x19f;
    undefined field389_0x1a0;
    undefined field390_0x1a1;
    undefined field391_0x1a2;
    undefined field392_0x1a3;
    undefined field393_0x1a4;
    undefined field394_0x1a5;
    undefined field395_0x1a6;
    undefined field396_0x1a7;
    undefined field397_0x1a8;
    undefined field398_0x1a9;
    undefined field399_0x1aa;
    undefined field400_0x1ab;
    undefined field401_0x1ac;
    undefined field402_0x1ad;
    undefined field403_0x1ae;
    undefined field404_0x1af;
    undefined field405_0x1b0;
    undefined field406_0x1b1;
    undefined field407_0x1b2;
    undefined field408_0x1b3;
    undefined field409_0x1b4;
    undefined field410_0x1b5;
    undefined field411_0x1b6;
    undefined field412_0x1b7;
    undefined field413_0x1b8;
    undefined field414_0x1b9;
    undefined field415_0x1ba;
    undefined field416_0x1bb;
    undefined field417_0x1bc;
    undefined field418_0x1bd;
    undefined field419_0x1be;
    undefined field420_0x1bf;
    undefined field421_0x1c0;
    undefined field422_0x1c1;
    undefined field423_0x1c2;
    undefined field424_0x1c3;
    undefined field425_0x1c4;
    undefined field426_0x1c5;
    undefined field427_0x1c6;
    undefined field428_0x1c7;
    undefined field429_0x1c8;
    undefined field430_0x1c9;
    undefined field431_0x1ca;
    undefined field432_0x1cb;
    undefined field433_0x1cc;
    undefined field434_0x1cd;
    undefined field435_0x1ce;
    undefined field436_0x1cf;
    undefined field437_0x1d0;
    undefined field438_0x1d1;
    undefined field439_0x1d2;
    undefined field440_0x1d3;
    undefined field441_0x1d4;
    undefined field442_0x1d5;
    undefined field443_0x1d6;
    undefined field444_0x1d7;
    undefined field445_0x1d8;
    undefined field446_0x1d9;
    undefined field447_0x1da;
    undefined field448_0x1db;
    undefined field449_0x1dc;
    undefined field450_0x1dd;
    undefined field451_0x1de;
    undefined field452_0x1df;
    undefined field453_0x1e0;
    undefined field454_0x1e1;
    undefined field455_0x1e2;
    undefined field456_0x1e3;
    undefined field457_0x1e4;
    undefined field458_0x1e5;
    undefined field459_0x1e6;
    undefined field460_0x1e7;
    undefined field461_0x1e8;
    undefined field462_0x1e9;
    undefined field463_0x1ea;
    undefined field464_0x1eb;
    undefined field465_0x1ec;
    undefined field466_0x1ed;
    undefined field467_0x1ee;
    undefined field468_0x1ef;
    undefined field469_0x1f0;
    undefined field470_0x1f1;
    undefined field471_0x1f2;
    undefined field472_0x1f3;
    undefined field473_0x1f4;
    undefined field474_0x1f5;
    undefined field475_0x1f6;
    undefined field476_0x1f7;
    undefined field477_0x1f8;
    undefined field478_0x1f9;
    undefined field479_0x1fa;
    undefined field480_0x1fb;
    undefined field481_0x1fc;
    undefined field482_0x1fd;
    undefined field483_0x1fe;
    undefined field484_0x1ff;
    undefined field485_0x200;
    undefined field486_0x201;
    undefined field487_0x202;
    undefined field488_0x203;
    undefined field489_0x204;
    undefined field490_0x205;
    undefined field491_0x206;
    undefined field492_0x207;
    undefined field493_0x208;
    undefined field494_0x209;
    undefined field495_0x20a;
    undefined field496_0x20b;
    undefined field497_0x20c;
    undefined field498_0x20d;
    undefined field499_0x20e;
    undefined field500_0x20f;
    undefined field501_0x210;
    undefined field502_0x211;
    undefined field503_0x212;
    undefined field504_0x213;
    undefined field505_0x214;
    undefined field506_0x215;
    undefined field507_0x216;
    undefined field508_0x217;
    undefined field509_0x218;
    undefined field510_0x219;
    undefined field511_0x21a;
    undefined field512_0x21b;
    undefined field513_0x21c;
    undefined field514_0x21d;
    undefined field515_0x21e;
    undefined field516_0x21f;
    undefined field517_0x220;
    undefined field518_0x221;
    undefined field519_0x222;
    undefined field520_0x223;
    undefined field521_0x224;
    undefined field522_0x225;
    undefined field523_0x226;
    undefined field524_0x227;
    undefined field525_0x228;
    undefined field526_0x229;
    undefined field527_0x22a;
    undefined field528_0x22b;
    undefined field529_0x22c;
    undefined field530_0x22d;
    undefined field531_0x22e;
    undefined field532_0x22f;
    undefined field533_0x230;
    undefined field534_0x231;
    undefined field535_0x232;
    undefined field536_0x233;
    undefined field537_0x234;
    undefined field538_0x235;
    undefined field539_0x236;
    undefined field540_0x237;
    undefined field541_0x238;
    undefined field542_0x239;
    undefined field543_0x23a;
    undefined field544_0x23b;
    undefined field545_0x23c;
    undefined field546_0x23d;
    undefined field547_0x23e;
    undefined field548_0x23f;
    undefined field549_0x240;
    undefined field550_0x241;
    undefined field551_0x242;
    undefined field552_0x243;
    undefined field553_0x244;
    undefined field554_0x245;
    undefined field555_0x246;
    undefined field556_0x247;
    undefined field557_0x248;
    undefined field558_0x249;
    undefined field559_0x24a;
    undefined field560_0x24b;
    undefined field561_0x24c;
    undefined field562_0x24d;
    undefined field563_0x24e;
    undefined field564_0x24f;
    undefined field565_0x250;
    undefined field566_0x251;
    undefined field567_0x252;
    undefined field568_0x253;
    undefined field569_0x254;
    undefined field570_0x255;
    undefined field571_0x256;
    undefined field572_0x257;
    undefined field573_0x258;
    undefined field574_0x259;
    undefined field575_0x25a;
    undefined field576_0x25b;
    undefined field577_0x25c;
    undefined field578_0x25d;
    undefined field579_0x25e;
    undefined field580_0x25f;
    undefined field581_0x260;
    undefined field582_0x261;
    undefined field583_0x262;
    undefined field584_0x263;
    undefined field585_0x264;
    undefined field586_0x265;
    undefined field587_0x266;
    undefined field588_0x267;
    undefined field589_0x268;
    undefined field590_0x269;
    undefined field591_0x26a;
    undefined field592_0x26b;
    undefined field593_0x26c;
    undefined field594_0x26d;
    undefined field595_0x26e;
    undefined field596_0x26f;
    undefined field597_0x270;
    undefined field598_0x271;
    undefined field599_0x272;
    undefined field600_0x273;
    undefined field601_0x274;
    undefined field602_0x275;
    undefined field603_0x276;
    undefined field604_0x277;
    undefined field605_0x278;
    undefined field606_0x279;
    undefined field607_0x27a;
    undefined field608_0x27b;
    undefined field609_0x27c;
    undefined field610_0x27d;
    undefined field611_0x27e;
    undefined field612_0x27f;
    undefined field613_0x280;
    undefined field614_0x281;
    undefined field615_0x282;
    undefined field616_0x283;
    undefined field617_0x284;
    undefined field618_0x285;
    undefined field619_0x286;
    undefined field620_0x287;
    undefined field621_0x288;
    undefined field622_0x289;
    undefined field623_0x28a;
    undefined field624_0x28b;
    undefined field625_0x28c;
    undefined field626_0x28d;
    undefined field627_0x28e;
    undefined field628_0x28f;
    undefined field629_0x290;
    undefined field630_0x291;
    undefined field631_0x292;
    undefined field632_0x293;
    undefined field633_0x294;
    undefined field634_0x295;
    undefined field635_0x296;
    undefined field636_0x297;
    undefined field637_0x298;
    undefined field638_0x299;
    undefined field639_0x29a;
    undefined field640_0x29b;
    undefined field641_0x29c;
    undefined field642_0x29d;
    undefined field643_0x29e;
    undefined field644_0x29f;
    undefined field645_0x2a0;
    undefined field646_0x2a1;
    undefined field647_0x2a2;
    undefined field648_0x2a3;
    undefined field649_0x2a4;
    undefined field650_0x2a5;
    undefined field651_0x2a6;
    undefined field652_0x2a7;
    undefined field653_0x2a8;
    undefined field654_0x2a9;
    undefined field655_0x2aa;
    undefined field656_0x2ab;
    undefined field657_0x2ac;
    undefined field658_0x2ad;
    undefined field659_0x2ae;
    undefined field660_0x2af;
    undefined field661_0x2b0;
    undefined field662_0x2b1;
    undefined field663_0x2b2;
    undefined field664_0x2b3;
    undefined field665_0x2b4;
    undefined field666_0x2b5;
    undefined field667_0x2b6;
    undefined field668_0x2b7;
    undefined field669_0x2b8;
    undefined field670_0x2b9;
    undefined field671_0x2ba;
    undefined field672_0x2bb;
    undefined field673_0x2bc;
    undefined field674_0x2bd;
    undefined field675_0x2be;
    undefined field676_0x2bf;
    undefined field677_0x2c0;
    undefined field678_0x2c1;
    undefined field679_0x2c2;
    undefined field680_0x2c3;
    undefined field681_0x2c4;
    undefined field682_0x2c5;
    undefined field683_0x2c6;
    undefined field684_0x2c7;
    undefined field685_0x2c8;
    undefined field686_0x2c9;
    undefined field687_0x2ca;
    undefined field688_0x2cb;
    undefined field689_0x2cc;
    undefined field690_0x2cd;
    undefined field691_0x2ce;
    undefined field692_0x2cf;
    undefined field693_0x2d0;
    undefined field694_0x2d1;
    undefined field695_0x2d2;
    undefined field696_0x2d3;
    undefined field697_0x2d4;
    undefined field698_0x2d5;
    undefined field699_0x2d6;
    undefined field700_0x2d7;
    undefined field701_0x2d8;
    undefined field702_0x2d9;
    undefined field703_0x2da;
    undefined field704_0x2db;
    undefined field705_0x2dc;
    undefined field706_0x2dd;
    undefined field707_0x2de;
    undefined field708_0x2df;
    undefined field709_0x2e0;
    undefined field710_0x2e1;
    undefined field711_0x2e2;
    undefined field712_0x2e3;
    undefined field713_0x2e4;
    undefined field714_0x2e5;
    undefined field715_0x2e6;
    undefined field716_0x2e7;
    undefined field717_0x2e8;
    undefined field718_0x2e9;
    undefined field719_0x2ea;
    undefined field720_0x2eb;
    undefined field721_0x2ec;
    undefined field722_0x2ed;
    undefined field723_0x2ee;
    undefined field724_0x2ef;
    undefined field725_0x2f0;
    undefined field726_0x2f1;
    undefined field727_0x2f2;
    undefined field728_0x2f3;
    undefined field729_0x2f4;
    undefined field730_0x2f5;
    undefined field731_0x2f6;
    undefined field732_0x2f7;
    undefined field733_0x2f8;
    undefined field734_0x2f9;
    undefined field735_0x2fa;
    undefined field736_0x2fb;
    undefined field737_0x2fc;
    undefined field738_0x2fd;
    undefined field739_0x2fe;
    undefined field740_0x2ff;
    undefined field741_0x300;
    undefined field742_0x301;
    undefined field743_0x302;
    undefined field744_0x303;
    undefined field745_0x304;
    undefined field746_0x305;
    undefined field747_0x306;
    undefined field748_0x307;
    uint CCR; // common configuration register
};

typedef struct struct_can_buffer struct_can_buffer, *Pstruct_can_buffer;

struct struct_can_buffer {
    uint can_id_standard;
    uint can_id_extended;
    byte can_ide;
    byte can_rtr;
    byte can_dlc;
    byte can_data1;
    byte can_data2;
    byte can_data3;
    byte can_data4;
    byte can_data5;
    byte can_data6;
    byte can_data7;
    byte can_data8;
    byte can_fmi;
};

typedef struct struct_can_filter_registers struct_can_filter_registers, *Pstruct_can_filter_registers;

struct struct_can_filter_registers {
    uint CAN_FMR;
    uint CAN_FM1R;
    uint field2_0x8;
    uint CAN_FS1R;
    uint field4_0x10;
    uint CAN_FFA1R;
    uint field6_0x18;
    uint CAN_FA1R;
    uint field8_0x20;
    uint field9_0x24;
    uint field10_0x28;
    uint field11_0x2c;
    uint field12_0x30;
    uint field13_0x34;
    uint field14_0x38;
    uint field15_0x3c;
    uint CAN_F0R1;
    uint CAN_F0R2;
    uint CAN_F1R1;
    uint CAN_F1R2;
    uint CAN_F2R1;
    uint CAN_F2R2;
    uint CAN_F3R1;
    uint CAN_F3R2;
    uint field24_0x60;
    uint field25_0x64;
    uint field26_0x68;
    uint field27_0x6c;
    uint field28_0x70;
    uint field29_0x74;
    uint field30_0x78;
    uint field31_0x7c;
    uint field32_0x80;
    uint field33_0x84;
    uint field34_0x88;
    uint field35_0x8c;
    uint CAN_F10R1;
    uint CAN_F10R2;
    uint field38_0x98;
    uint field39_0x9c;
    uint field40_0xa0;
    uint field41_0xa4;
    uint field42_0xa8;
    uint field43_0xac;
    uint field44_0xb0;
    uint field45_0xb4;
    uint CAN_F15R1;
    uint CAN_F15R2;
    uint CAN_F16R1;
    uint CAN_F16R2;
    uint field50_0xc8;
    uint field51_0xcc;
    uint field52_0xd0;
    uint field53_0xd4;
    uint field54_0xd8;
    uint field55_0xdc;
    uint CAN_F20R1;
    uint CAN_F20R2;
    uint CAN_F21R1;
    uint CAN_F21R2;
    uint field60_0xf0;
    uint field61_0xf4;
    uint field62_0xf8;
    uint field63_0xfc;
    uint field64_0x100;
    uint field65_0x104;
    uint CAN_F25R1;
    uint CAN_F25R2;
    uint field68_0x110;
    uint field69_0x114;
    uint CAN_F27R1;
    uint CAN_F27R2;
};

typedef struct struct_gpio_init_data struct_gpio_init_data, *Pstruct_gpio_init_data;

struct struct_gpio_init_data {
    uint gpio_value;
    byte gpio_moder;
    byte gpio_opseedr;
    byte gpio_otyper;
    byte gpio_pupdr;
};

typedef struct struct_rcc_registers struct_rcc_registers, *Pstruct_rcc_registers;

struct struct_rcc_registers {
    uint RCC_CR;
    uint RCC_CFGR;
    uint RCC_CIR;
    uint RCC_APB2RSTR;
    uint RCC_APB1RSTR;
    uint RCC_AHBENR;
    uint RCC_APB2ENR;
    uint RCC_APB1ENR;
    uint RCC_BDCR;
    uint RCC_CSR;
    uint RCC_AHBRSTR;
    uint RCC_CFGR2;
    uint RCC_CFGR3;
    uint RCC_CR2;
};

typedef struct NVIC NVIC, *PNVIC;

struct NVIC {
    uint ISER; // Interrupt Set Enable Register
    uint field1_0x4;
    uint field2_0x8;
    uint field3_0xc;
    uint field4_0x10;
    uint field5_0x14;
    uint field6_0x18;
    uint field7_0x1c;
    uint field8_0x20;
    uint field9_0x24;
    uint field10_0x28;
    uint field11_0x2c;
    uint field12_0x30;
    uint field13_0x34;
    uint field14_0x38;
    uint field15_0x3c;
    uint field16_0x40;
    uint field17_0x44;
    uint field18_0x48;
    uint field19_0x4c;
    uint field20_0x50;
    uint field21_0x54;
    uint field22_0x58;
    uint field23_0x5c;
    uint field24_0x60;
    uint field25_0x64;
    uint field26_0x68;
    uint field27_0x6c;
    uint field28_0x70;
    uint field29_0x74;
    uint field30_0x78;
    uint field31_0x7c;
    uint ICER; // Interrupt Clear Enable           Register
    uint field33_0x84;
    uint field34_0x88;
    uint field35_0x8c;
    uint field36_0x90;
    uint field37_0x94;
    uint field38_0x98;
    uint field39_0x9c;
    uint field40_0xa0;
    uint field41_0xa4;
    uint field42_0xa8;
    uint field43_0xac;
    uint field44_0xb0;
    uint field45_0xb4;
    uint field46_0xb8;
    uint field47_0xbc;
    uint field48_0xc0;
    uint field49_0xc4;
    uint field50_0xc8;
    uint field51_0xcc;
    uint field52_0xd0;
    uint field53_0xd4;
    uint field54_0xd8;
    uint field55_0xdc;
    uint field56_0xe0;
    uint field57_0xe4;
    uint field58_0xe8;
    uint field59_0xec;
    uint field60_0xf0;
    uint field61_0xf4;
    uint field62_0xf8;
    uint field63_0xfc;
    uint ISPR; // Interrupt Set-Pending Register
    uint field65_0x104;
    uint field66_0x108;
    uint field67_0x10c;
    uint field68_0x110;
    uint field69_0x114;
    uint field70_0x118;
    uint field71_0x11c;
    uint field72_0x120;
    uint field73_0x124;
    uint field74_0x128;
    uint field75_0x12c;
    uint field76_0x130;
    uint field77_0x134;
    uint field78_0x138;
    uint field79_0x13c;
    uint field80_0x140;
    uint field81_0x144;
    uint field82_0x148;
    uint field83_0x14c;
    uint field84_0x150;
    uint field85_0x154;
    uint field86_0x158;
    uint field87_0x15c;
    uint field88_0x160;
    uint field89_0x164;
    uint field90_0x168;
    uint field91_0x16c;
    uint field92_0x170;
    uint field93_0x174;
    uint field94_0x178;
    uint field95_0x17c;
    uint ICPR; // Interrupt Clear-Pending           Register
    uint field97_0x184;
    uint field98_0x188;
    uint field99_0x18c;
    uint field100_0x190;
    uint field101_0x194;
    uint field102_0x198;
    uint field103_0x19c;
    uint field104_0x1a0;
    uint field105_0x1a4;
    uint field106_0x1a8;
    uint field107_0x1ac;
    uint field108_0x1b0;
    uint field109_0x1b4;
    uint field110_0x1b8;
    uint field111_0x1bc;
    uint field112_0x1c0;
    uint field113_0x1c4;
    uint field114_0x1c8;
    uint field115_0x1cc;
    uint field116_0x1d0;
    uint field117_0x1d4;
    uint field118_0x1d8;
    uint field119_0x1dc;
    uint field120_0x1e0;
    uint field121_0x1e4;
    uint field122_0x1e8;
    uint field123_0x1ec;
    uint field124_0x1f0;
    uint field125_0x1f4;
    uint field126_0x1f8;
    uint field127_0x1fc;
    uint field128_0x200;
    uint field129_0x204;
    uint field130_0x208;
    uint field131_0x20c;
    uint field132_0x210;
    uint field133_0x214;
    uint field134_0x218;
    uint field135_0x21c;
    uint field136_0x220;
    uint field137_0x224;
    uint field138_0x228;
    uint field139_0x22c;
    uint field140_0x230;
    uint field141_0x234;
    uint field142_0x238;
    uint field143_0x23c;
    uint field144_0x240;
    uint field145_0x244;
    uint field146_0x248;
    uint field147_0x24c;
    uint field148_0x250;
    uint field149_0x254;
    uint field150_0x258;
    uint field151_0x25c;
    uint field152_0x260;
    uint field153_0x264;
    uint field154_0x268;
    uint field155_0x26c;
    uint field156_0x270;
    uint field157_0x274;
    uint field158_0x278;
    uint field159_0x27c;
    uint field160_0x280;
    uint field161_0x284;
    uint field162_0x288;
    uint field163_0x28c;
    uint field164_0x290;
    uint field165_0x294;
    uint field166_0x298;
    uint field167_0x29c;
    uint field168_0x2a0;
    uint field169_0x2a4;
    uint field170_0x2a8;
    uint field171_0x2ac;
    uint field172_0x2b0;
    uint field173_0x2b4;
    uint field174_0x2b8;
    uint field175_0x2bc;
    uint field176_0x2c0;
    uint field177_0x2c4;
    uint field178_0x2c8;
    uint field179_0x2cc;
    uint field180_0x2d0;
    uint field181_0x2d4;
    uint field182_0x2d8;
    uint field183_0x2dc;
    uint field184_0x2e0;
    uint field185_0x2e4;
    uint field186_0x2e8;
    uint field187_0x2ec;
    uint field188_0x2f0;
    uint field189_0x2f4;
    uint field190_0x2f8;
    uint field191_0x2fc;
    uint IPR0; // Interrupt Priority Register 0
    uint IPR1; // Interrupt Priority Register 1
    uint IPR2; // Interrupt Priority Register 2
    uint IPR3; // Interrupt Priority Register 3
    uint IPR4; // Interrupt Priority Register 4
    uint IPR5; // Interrupt Priority Register 5
    uint IPR6; // Interrupt Priority Register 6
    uint IPR7; // Interrupt Priority Register 7
};

typedef struct DBGMCU DBGMCU, *PDBGMCU;

struct DBGMCU {
    uint IDCODE; // MCU Device ID Code Register
    uint CR; // Debug MCU Configuration           Register
    uint APBLFZ; // APB Low Freeze Register
    uint APBHFZ; // APB High Freeze Register
};

typedef struct TIM3 TIM3, *PTIM3;

struct TIM3 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    uint SMCR; // slave mode control register
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register 1 (input           mode)
    uint CCMR2_Input; // capture/compare mode register 2 (input           mode)
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    undefined field12_0x30;
    undefined field13_0x31;
    undefined field14_0x32;
    undefined field15_0x33;
    uint CCR1; // capture/compare register 1
    uint CCR2; // capture/compare register 2
    uint CCR3; // capture/compare register 3
    uint CCR4; // capture/compare register 4
    undefined field20_0x44;
    undefined field21_0x45;
    undefined field22_0x46;
    undefined field23_0x47;
    uint DCR; // DMA control register
    uint DMAR; // DMA address for full transfer
};

typedef struct TIM2 TIM2, *PTIM2;

struct TIM2 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    uint SMCR; // slave mode control register
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register 1 (input           mode)
    uint CCMR2_Input; // capture/compare mode register 2 (input           mode)
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    undefined field12_0x30;
    undefined field13_0x31;
    undefined field14_0x32;
    undefined field15_0x33;
    uint CCR1; // capture/compare register 1
    uint CCR2; // capture/compare register 2
    uint CCR3; // capture/compare register 3
    uint CCR4; // capture/compare register 4
    undefined field20_0x44;
    undefined field21_0x45;
    undefined field22_0x46;
    undefined field23_0x47;
    uint DCR; // DMA control register
    uint DMAR; // DMA address for full transfer
};

typedef struct TIM1 TIM1, *PTIM1;

struct TIM1 {
    uint CR1; // control register 1
    uint CR2; // control register 2
    uint SMCR; // slave mode control register
    uint DIER; // DMA/Interrupt enable register
    uint SR; // status register
    uint EGR; // event generation register
    uint CCMR1_Input; // capture/compare mode register 1 (input           mode)
    uint CCMR2_Input; // capture/compare mode register 2 (input           mode)
    uint CCER; // capture/compare enable           register
    uint CNT; // counter
    uint PSC; // prescaler
    uint ARR; // auto-reload register
    uint RCR; // repetition counter register
    uint CCR1; // capture/compare register 1
    uint CCR2; // capture/compare register 2
    uint CCR3; // capture/compare register 3
    uint CCR4; // capture/compare register 4
    uint BDTR; // break and dead-time register
    uint DCR; // DMA control register
    uint DMAR; // DMA address for full transfer
};

typedef struct TSC TSC, *PTSC;

struct TSC {
    uint CR; // control register
    uint IER; // interrupt enable register
    uint ICR; // interrupt clear register
    uint ISR; // interrupt status register
    uint IOHCR; // I/O hysteresis control           register
    undefined field5_0x14;
    undefined field6_0x15;
    undefined field7_0x16;
    undefined field8_0x17;
    uint IOASCR; // I/O analog switch control           register
    undefined field10_0x1c;
    undefined field11_0x1d;
    undefined field12_0x1e;
    undefined field13_0x1f;
    uint IOSCR; // I/O sampling control register
    undefined field15_0x24;
    undefined field16_0x25;
    undefined field17_0x26;
    undefined field18_0x27;
    uint IOCCR; // I/O channel control register
    undefined field20_0x2c;
    undefined field21_0x2d;
    undefined field22_0x2e;
    undefined field23_0x2f;
    uint IOGCSR; // I/O group control status           register
    uint IOG1CR; // I/O group x counter register
    uint IOG2CR; // I/O group x counter register
    uint IOG3CR; // I/O group x counter register
    uint IOG4CR; // I/O group x counter register
    uint IOG5CR; // I/O group x counter register
    uint IOG6CR; // I/O group x counter register
};

typedef struct CRC CRC, *PCRC;

struct CRC {
    uint DR; // Data register
    uint IDR; // Independent data register
    uint CR; // Control register
    uint INIT; // Initial CRC value
};

typedef struct SYSCFG SYSCFG, *PSYSCFG;

struct SYSCFG {
    uint CFGR1; // configuration register 1
    undefined field1_0x4;
    undefined field2_0x5;
    undefined field3_0x6;
    undefined field4_0x7;
    uint EXTICR1; // external interrupt configuration register           1
    uint EXTICR2; // external interrupt configuration register           2
    uint EXTICR3; // external interrupt configuration register           3
    uint EXTICR4; // external interrupt configuration register           4
    uint CFGR2; // configuration register 2
};

typedef struct CRS CRS, *PCRS;

struct CRS {
    uint CR; // control register
    uint CFGR; // configuration register
    uint ISR; // interrupt and status register
    uint ICR; // interrupt flag clear register
};

typedef struct DMA DMA, *PDMA;

struct DMA {
    uint ISR; // DMA interrupt status register           (DMA_ISR)
    uint IFCR; // DMA interrupt flag clear register           (DMA_IFCR)
    uint CCR1; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR1; // DMA channel 1 number of data           register
    uint CPAR1; // DMA channel 1 peripheral address           register
    uint CMAR1; // DMA channel 1 memory address           register
    undefined field6_0x18;
    undefined field7_0x19;
    undefined field8_0x1a;
    undefined field9_0x1b;
    uint CCR2; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR2; // DMA channel 2 number of data           register
    uint CPAR2; // DMA channel 2 peripheral address           register
    uint CMAR2; // DMA channel 2 memory address           register
    undefined field14_0x2c;
    undefined field15_0x2d;
    undefined field16_0x2e;
    undefined field17_0x2f;
    uint CCR3; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR3; // DMA channel 3 number of data           register
    uint CPAR3; // DMA channel 3 peripheral address           register
    uint CMAR3; // DMA channel 3 memory address           register
    undefined field22_0x40;
    undefined field23_0x41;
    undefined field24_0x42;
    undefined field25_0x43;
    uint CCR4; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR4; // DMA channel 4 number of data           register
    uint CPAR4; // DMA channel 4 peripheral address           register
    uint CMAR4; // DMA channel 4 memory address           register
    undefined field30_0x54;
    undefined field31_0x55;
    undefined field32_0x56;
    undefined field33_0x57;
    uint CCR5; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR5; // DMA channel 5 number of data           register
    uint CPAR5; // DMA channel 5 peripheral address           register
    uint CMAR5; // DMA channel 5 memory address           register
    undefined field38_0x68;
    undefined field39_0x69;
    undefined field40_0x6a;
    undefined field41_0x6b;
    uint CCR6; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR6; // DMA channel 6 number of data           register
    uint CPAR6; // DMA channel 6 peripheral address           register
    uint CMAR6; // DMA channel 6 memory address           register
    undefined field46_0x7c;
    undefined field47_0x7d;
    undefined field48_0x7e;
    undefined field49_0x7f;
    uint CCR7; // DMA channel configuration register           (DMA_CCR)
    uint CNDTR7; // DMA channel 7 number of data           register
    uint CPAR7; // DMA channel 7 peripheral address           register
    uint CMAR7; // DMA channel 7 memory address           register
};

typedef struct astruct_gpio astruct_gpio, *Pastruct_gpio;

struct astruct_gpio {
    uint 1;
    uint 2;
};




void FUN_MAIN_WHILE_LOOP_08000c68(void)

{
  (*(code *)PTR_FUN_MAIN_LOOP_08000c68_1_080000cc)();
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_INT_RESET_080000d4(void)

{
  bool bVar1;
  
  bVar1 = (bool)isCurrentModePrivileged();
  if (bVar1) {
    setMainStackPointer(_FUN_INT_RESET_08000108);
  }
  if ((uint *)(*PTR_Reset_0800010c >> 0x18) == PTR_Reserved1_3_08000110) {
    PTR_RCC_APB2ENR_08000114->RCC_CR = DAT_00000001_08000118;
    *PTR_SYSCFG_0800011c = DAT_00000000_08000120;
  }
  (*(code *)PTR_FUN_RCC_CONFIG_08000b6c_1_08000124)();
                    // WARNING: Could not recover jumptable at 0x080000f8. Too many branches
                    // WARNING: Treating indirect jump as call
  (*(code *)PTR_LAB_080000c0_1_08000128)();
  return;
}



void FUN_INT_IRQ_LOOP_FOREVER_08000104(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



uint FUN_INT_RESET_08000108(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  undefined **ppuVar1;
  int caount;
  
  param_3 = param_3 & param_4 >> 0x20;
  caount = 3;
  ppuVar1 = &Reset;
  do {
    ppuVar1 = (undefined **)((int)ppuVar1 + -1);
    param_3 = param_3 << 8 | (uint)*(byte *)ppuVar1;
    caount = caount + -1;
  } while (-1 < caount);
  return param_3;
}



uint FUN_CAN_FILTER_MASK_HIGH_0800012c(struct_can_filter_config *can_filter)

{
  ushort *maskid;
  int i;
  uint value;
  
  i = 3;
  maskid = &can_filter->filter_maskid_high;
  do {
    maskid = (ushort *)((int)maskid + -1);
    value = value << 8 | (uint)*(byte *)maskid;
    i = i + -1;
  } while (-1 < i);
  return value;
}



void FUN_START_08000140(void)

{
  uint *mem_ptr;
  
                    // Is this some sort of initialisation for memory?
                    // Seems to be doing something with a couple of bytes at the end of the flash
                    // (values 2 & 3)???
                    // Trouble is there is no mem_ptr[3] defined...
  for (mem_ptr = (uint *)&UINT_8000CC4_08000ca4; mem_ptr < &UINT_00000002_08000cc4;
      mem_ptr = mem_ptr + 4) {
    (*(code *)mem_ptr[3])(*mem_ptr,mem_ptr[1],mem_ptr[2]);
  }
  FUN_MAIN_WHILE_LOOP_08000c68();
  FUN_GPIO_INIT_PA4_LED_CONFIG_080008e8(0);
  return;
}



void FUN_GPIO_INIT_PA4_LED_08000164(void)

{
  FUN_GPIO_INIT_PA4_LED_CONFIG_080008e8();
  return;
}



void FUN_CAN_GPIO_INIT_0800016c(void)

{
  CAN *can_register;
  struct_gpio_init_data gpio_config;
  struct_can_config can_config;
  struct_nvic_data nvic_config;
  struct_can_filter_config can_filter;
  ushort can_id_low_value;
  
                    // 00020000 => 00000000 00000010 00000000 00000000
                    // 
                    // Bit 17 IOPAEN: I/O port A clock enable
                    // Set and cleared by software.
                    // 0: I/O port A clock disabled
                    // 1: I/O port A clock enabled
  FUN_RCC_AHBENR_0800099c(0x20000);
                    // CAN Tx * Rx Alternate Functions
                    // https://www.st.com/resource/en/datasheet/stm32f042f6.pdf
                    // GPIOA AFR PA11 AF4 CAN Tx => 1011
                    // GPIOA AFR PA12 AF4 CAN Rx => 1100
  FUN_GPIO_AFRL_08000840(&Peripherals::GPIOA,0b00001011,4);
  FUN_GPIO_AFRL_08000840(&Peripherals::GPIOA,0b00001100,4);
                    // PA11 AF CAN Rx (Pull-down)
  gpio_config.gpio_value = 0b0000100000000000;
  gpio_config.gpio_moder = 2;
  gpio_config.gpio_opseedr = 3;
  gpio_config.gpio_otyper = 0;
  gpio_config.gpio_pupdr = 1;
  FUN_GPIO_CONFIG_080007d0(&Peripherals::GPIOA,&gpio_config);
                    // PA12 AF CAN Tx (Pull-down)
  gpio_config.gpio_value = 0b0001000000000000;
  gpio_config.gpio_moder = 2;
  gpio_config.gpio_opseedr = 3;
  gpio_config.gpio_otyper = 0;
  gpio_config.gpio_pupdr = 1;
  FUN_GPIO_CONFIG_080007d0(&Peripherals::GPIOA,&gpio_config);
                    // PA6 Output
                    // 
                    // Looks like it is possibly connect from PA6 to TJA042 Pin 8 (STB 8 Standby
                    // mode control input).  Makes sense as this will help reduce power.
                    // 
                    // STB Normal mode:
                    // A LOW level on pin STB selects Normal mode. In this mode, the transceiver can
                    // transmit and receive data via the bus lines CANH and CANL.
                    // The differential receiver converts the analog data on the bus lines into
                    // digital data which is output to pin RXD. The slopes of the output signals on
                    // the bus lines are controlled internally and are optimized in a way that
                    // guarantees the lowest possible EME.
                    // 
                    // Standby mode
                    // A HIGH level on pin STB selects Standby mode. In Standby mode, the
                    // transceiver is not able to transmit or correctly receive data via the bus
                    // lines. The transmitter and Normal-mode receiver blocks are switched off to
                    // reduce supply current, and only a low-power differential receiver monitors
                    // the bus lines for activity. The wake-up filter on the output of the low-power
                    // receiver does not latch bus dominant states, but ensures that only bus
                    // dominant and bus recessive states that persist longer than t fltr(wake)bus
                    // are reflected on pin RXD.
                    // In Standby mode, the bus lines are biased to ground to minimize the system
                    // supply current. The low-power receiver is supplied by VIO , and is capable of
                    // detecting CAN bus activity even if VIO is the only supply voltage available.
                    // When pin RXD goes LOW to signal a wake-up request, a transition to Normal
                    // mode will not be triggered until STB is forced LOW.
                    // 
                    // Note: on the PCB, PA5 is also routed to a missing chip (U6 Pin 10).
                    // 
  gpio_config.gpio_value = 0b01000000;
  gpio_config.gpio_moder = 1;
  gpio_config.gpio_opseedr = 3;
  gpio_config.gpio_otyper = 0;
  gpio_config.gpio_pupdr = 0;
  FUN_GPIO_CONFIG_080007d0(&Peripherals::GPIOA,&gpio_config);
                    // Make PA6 Output Low
                    // 
                    // STB Low: Normal Mode
  FUN_GPIO_BRR_0800086e(&Peripherals::GPIOA,0b01000000);
  nvic_config.nvic_bit_num = 0x1e;
  nvic_config.nvic_ipro_data = 1;
  nvic_config.write = 1;
  FUN_GPIO_NVIC_0800090c(&nvic_config);
  FUN_RCC_APB1ENR_080009b4(0x2000000,1);
  can_register = PTR_CAN_08000288;
  FUN_CAN_RCC_RESET_0800029c(PTR_CAN_08000288);
                    // Not sure why it sets default only to override with final values...?
  FUN_CAN_DEFAULTS_08000678(&can_config);
  can_config.time_triggered_mode = 0;
  can_config.auto_bus_off = 0;
  can_config._8_4_ = 0;
  can_config.mode = 0;
  can_config.sync_jump_width = 0;
  can_config.timeseg_1 = 8;
  can_config.timeseg_2 = 7;
  can_config.prescaler = 20;
  FUN_CAN_CONFIG_08000380(can_register,&can_config);
                    // List Mode, Dual 16 Bit Scale
  can_filter.filter_num = 0;
  can_filter.filter_mode = 1;
  can_filter.filter_scale = 0;
                    // STDID[10:0], RTR, IDE and EXTID[17:15]
                    // 
                    // 0xB820 => 10111000 00100000
                    // 
                    // ID => 10111000001 => 0x5c1
                    // 
  can_filter.filter_canid_high = (ushort)UINT_0000B820_0800028c;
                    // 0x0FFF => 111111111111
                    // 
                    // Can ID => 11111111111 => 0x7ff (used in all the low values
                    // 
                    // This seems to be a waste - why is 0x7ff listed 4 times, when it is not used
                    // ???
                    // They could have just used one filter config, as it provides 4 CanIds in the
                    // one list (0x5c1, 0x575, 0x436 & 0x439 => which match those in CAN MAIN LOOP)
                    // 
  can_id_low_value = (ushort)UINT_00000FFF_08000290;
                    // 0xAEA0 => 10101110 10100000
                    // 
                    // Top 11 bits:
                    // Can ID => 10101110101 => 0x575
                    // 
  can_filter.filter_maskid_high = (ushort)UINT_0000AEA0_08000294;
  can_filter.filter_fifo = 0;
  can_filter.filter_enabled = 1;
  can_filter.filter_canid_low = can_id_low_value;
  can_filter.filter_maskid_low = can_id_low_value;
  FUN_CAN_FILTER_080002b4(&can_filter);
  can_filter.filter_num = 1;
  can_filter.filter_mode = 1;
  can_filter.filter_scale = 0;
                    // 0x86C0 => 10000110 11000000 => CanID 0x436
  can_filter.filter_canid_high = (ushort)UINT_000086C0_08000298;
                    // 0x8720 => 10000111 00100000 => CanID 0x439
  can_filter.filter_maskid_high = can_filter.filter_canid_high + 0x60;
  can_filter.filter_fifo = 0;
  can_filter.filter_enabled = 1;
  can_filter.filter_canid_low = can_id_low_value;
  can_filter.filter_maskid_low = can_id_low_value;
  FUN_CAN_FILTER_080002b4(&can_filter);
                    // CAN_IER: Bit 1 FMPIE0: FIFO message pending interrupt enable
                    // 0: No interrupt generated when state of FMP[1:0] bits are not 00b.
                    // 1: Interrupt generated when state of FMP[1:0] bits are not 00b
  FUN_CAN_IER_SETBIT_08000370(can_register,2,1);
  return;
}



void FUN_CAN_RCC_RESET_0800029c(void)

{
                    // 02000000 => 00000010 00000000 00000000 00000000
                    // 
                    // Bit 25 CANRST: CAN interface reset
                    // Set and cleared by software.
                    // 0: No effect
                    // 1: Reset CAN interface
  FUN_CAN_RCC_APB1RSTR_SETBIT_080009cc(0x2000000);
  FUN_CAN_RCC_APB1RSTR_SETBIT_080009cc(0x2000000,0);
  return;
}



void FUN_CAN_FILTER_080002b4(struct_can_filter_config *can_filter)

{
  uint val;
  uint in_r2;
  uint filter_num_bit;
  struct_can_filter_registers *can_filter_register;
  
  can_filter_register = PTR_CAN_CAN_FMR_0800036c;
  filter_num_bit = 1 << can_filter->filter_num;
                    // CAN filter master register (CAN_FMR)
                    // 
                    // Bit 0 FINIT: Filter initialization mode
                    // Initialization mode for filter banks
                    // 0: Active filters mode.
                    // 1: Initialization mode for the filters.
  PTR_CAN_CAN_FMR_0800036c->CAN_FMR = PTR_CAN_CAN_FMR_0800036c->CAN_FMR | 1;
                    // Disable filter num
  can_filter_register->CAN_FA1R = can_filter_register->CAN_FA1R & ~filter_num_bit;
                    // Dual 16 bit filters
  if (can_filter->filter_scale == 0) {
    can_filter_register->CAN_FS1R = can_filter_register->CAN_FS1R & ~filter_num_bit;
                    // Check the order
                    // 
    (&can_filter_register->CAN_F0R1)[(uint)can_filter->filter_num * 2] =
         CONCAT22(can_filter->filter_maskid_low,can_filter->filter_canid_low);
    (&can_filter_register->CAN_F0R2)[(uint)can_filter->filter_num * 2] =
         CONCAT22(can_filter->filter_maskid_high,can_filter->filter_canid_high);
  }
                    // 32 bit filters
  if (can_filter->filter_scale == 1) {
    can_filter_register->CAN_FS1R = can_filter_register->CAN_FS1R | filter_num_bit;
    val = FUN_CAN_FILTER_MASK_HIGH_0800012c(can_filter);
    (&can_filter_register->CAN_F0R1)[(uint)can_filter->filter_num * 2] = val >> 16 | val << uVar4;
    val = FUN_CAN_FILTER_MASK_HIGH_0800012c
                    ((struct_can_filter_config *)&can_filter->filter_maskid_high);
    (&can_filter_register->CAN_F0R2)[(uint)can_filter->filter_num * 2] = val >> 16 | val << uVar7;
  }
  if (can_filter->filter_mode == 0) {
    val = can_filter_register->CAN_FM1R & ~filter_num_bit;
  }
  else {
    val = can_filter_register->CAN_FM1R | filter_num_bit;
  }
                    // Set filter mode
  can_filter_register->CAN_FM1R = val;
  if (can_filter->filter_fifo == 0) {
    can_filter_register->CAN_FFA1R = can_filter_register->CAN_FFA1R & ~filter_num_bit;
  }
                    // set FIFO
  if (can_filter->filter_fifo == 1) {
    can_filter_register->CAN_FFA1R = can_filter_register->CAN_FFA1R | filter_num_bit;
  }
  if (can_filter->filter_enabled == 1) {
                    // Enable filter num
    can_filter_register->CAN_FA1R = can_filter_register->CAN_FA1R | filter_num_bit;
  }
  can_filter_register->CAN_FMR = can_filter_register->CAN_FMR & 0xfffffffe;
  return;
}



void FUN_CAN_IER_SETBIT_08000370(CAN *can_register,uint bit_mask,int state)

{
  uint uVar1;
  
  if (state == 0) {
    uVar1 = can_register->CAN_IER & ~bit_mask;
  }
  else {
    uVar1 = can_register->CAN_IER | bit_mask;
  }
  can_register->CAN_IER = uVar1;
  return;
}



undefined4 FUN_CAN_CONFIG_08000380(CAN *can_register,struct_can_config *can_config)

{
  uint i;
  uint bit_mask;
  
                    // Bit 1 SLEEP: Sleep mode request: Disable
  can_register->CAN_MCR = can_register->CAN_MCR & 0xfffffffd;
                    // INRQ: Initialization request
                    // Software sets this bit to request the CAN hardware to enter initialization
                    // mode.
  can_register->CAN_MCR = can_register->CAN_MCR | 1;
  bit_mask = UINT_00ffffff_0800045c;
                    // Wait for INAK: Initialization acknowledge (or too many retries)
  for (i = 0; ((can_register->CAN_MSR & 1) == 0 && (i != UINT_00ffffff_0800045c)); i = i + 1) {
  }
  if ((can_register->CAN_MSR & 1) != 0) {
                    // Initiaisation mode so configure...
    if (can_config->time_triggered_mode == 1) {
      i = can_register->CAN_MCR | 0b10000000;
    }
    else {
      i = can_register->CAN_MCR & 0xffffff7f;
    }
    can_register->CAN_MCR = i;
    if (can_config->auto_bus_off == 1) {
      i = can_register->CAN_MCR | 0b01000000;
    }
    else {
      i = can_register->CAN_MCR & 0xffffffbf;
    }
    can_register->CAN_MCR = i;
    if (can_config->auto_wakeup == 1) {
      i = can_register->CAN_MCR | 0b00100000;
    }
    else {
      i = can_register->CAN_MCR & 0b11111111111111111111111111011111;
    }
    can_register->CAN_MCR = i;
    if (can_config->auto_retransmit == 1) {
      i = can_register->CAN_MCR | 0b00010000;
    }
    else {
      i = can_register->CAN_MCR & 0b11111111111111111111111111101111;
    }
    can_register->CAN_MCR = i;
    if (can_config->receiver_fifo_locked == 1) {
      i = can_register->CAN_MCR | 8;
    }
    else {
      i = can_register->CAN_MCR & 0b11111111111111111111111111110111;
    }
    can_register->CAN_MCR = i;
    if (can_config->tx_fifo_priority == 1) {
      i = can_register->CAN_MCR | 4;
    }
    else {
      i = can_register->CAN_MCR & 0b11111111111111111111111111111011;
    }
    can_register->CAN_MCR = i;
    can_register->CAN_BTR =
         (uint)can_config->mode << 30 | (uint)can_config->sync_jump_width << 24 |
         (uint)can_config->timeseg_1 << 16 | (uint)can_config->timeseg_2 << 20 |
         can_config->prescaler - 1;
                    // Reset CAN_MCR->INRQ and wait till CAN_INAK is 0
    can_register->CAN_MCR = can_register->CAN_MCR & 0xfffffffe;
    for (i = 0; ((can_register->CAN_MSR & 1) != 0 && (i != bit_mask)); i = i + 1) {
    }
    if ((can_register->CAN_MSR & 1) == 0) {
      return 1;
    }
  }
  return 0;
}



void FUN_CAN_RX_08000460(uint *can_base_register,int fifo,struct_can_buffer *rx_buffer)

{
  uint rx_ide;
  
                    // CAN receive FIFO mailbox identifier register (CAN_RIxR) (x = 0..1)
                    // Address offsets: 0x1B0 (0x6c), 0x1C0 (0x70)
                    // 
                    // CAN1 Base 0x40006400
                    // CAN2 Base 0x40006800
                    // Note: Offset * 4 (uint32): 0x6c = 0x1B0
                    // 0x6c => CAN_RI0R
                    // 0x6d => CAN_RDT0R
                    // 0x6e => CAN_RDL0R
                    // 0x6f => CAN_RDH0R
  rx_ide = can_base_register[fifo * 4 + 0x6c];
                    // Bit 2 IDE: Identifier extension
                    // This bit defines the identifier type of message in the mailbox.
                    // 0: Standard identifier.
                    // 1: Extended identifier.
  rx_buffer->can_ide = (byte)(rx_ide & 0b00000100);
  if ((rx_ide & 0b00000100) == 0) {
    rx_buffer->can_id_standard = can_base_register[fifo * 4 + 0x6c] >> 21;
  }
  else {
    rx_buffer->can_id_extended = can_base_register[fifo * 4 + 0x6c] >> 3;
  }
                    // Bit 1 RTR: Remote transmission request
                    // 0: Data frame
                    // 1: Remote frame
  rx_buffer->can_rtr = (byte)can_base_register[fifo * 4 + 0x6c] & 0b00000010;
                    // DLC
  rx_buffer->can_dlc = (byte)can_base_register[fifo * 4 + 0x6d] & 0b00001111;
                    // Bits 15:8 FMI[7:0]: Filter match index
                    // This register contains the index of the filter the message stored in the
                    // mailbox passed
                    // through.
  rx_buffer->can_fmi = (byte)(can_base_register[fifo * 4 + 0x6d] >> 8);
                    // Data
  rx_buffer->can_data1 = (byte)can_base_register[fifo * 4 + 0x6e];
  rx_buffer->can_data2 = (byte)(can_base_register[fifo * 4 + 0x6e] >> 8);
  rx_buffer->can_data3 = (byte)(can_base_register[fifo * 4 + 0x6e] >> 16);
  rx_buffer->can_data4 = (byte)(can_base_register[fifo * 4 + 0x6e] >> 24);
  rx_buffer->can_data5 = (byte)can_base_register[fifo * 4 + 0x6f];
  rx_buffer->can_data6 = (byte)(can_base_register[fifo * 4 + 0x6f] >> 8);
  rx_buffer->can_data7 = (byte)(can_base_register[fifo * 4 + 0x6f] >> 16);
  rx_buffer->can_data8 = (byte)(can_base_register[fifo * 4 + 0x6f] >> 24);
  if (fifo != 0) {
                    // CAN_RF1R: CAN receive FIFO 1 register
                    // Bit 5 RFOM0: Release FIFO 1 output mailbox
                    // Set by software to release the output mailbox of the FIFO
    can_base_register[4] = can_base_register[4] | 0b00100000;
    return;
  }
                    // CAN_RF0R: CAN receive FIFO 0 register
                    // Bit 5 RFOM0: Release FIFO 0 output mailbox
                    // Set by software to release the output mailbox of the FIFO
  can_base_register[3] = can_base_register[3] | 0b00100000;
  return;
}



void FUN_CAN_INT_MAIN_080004d8(void)

{
  struct_can_registers *can_base_register;
  int led_pa4_pin;
  uint can_id_modified;
  struct_can_buffer tx_buffer;
  struct_can_buffer rx_buffer;
  uint *sram_ptr;
  
  can_base_register = PTR_CAN_08000668;
  FUN_CAN_RX_08000460(&PTR_CAN_08000668->CAN_MCR,0,&rx_buffer);
  sram_ptr = PTR_DAT_20000000_08000670;
                    // If StdID == 0x5c1:
                    // 
                    // if
                    //  0x5c1 x [ 0x1e/0x1d X X X X X X X ] => 0x5c1 8 [ 0x1a X X X X X X X ]
                    // else
                    //  where (a) is sram[0]
                    //  0x5c1 x [ 0x22 X X X X X X X ] => 0x5c1 8 [ (a)   X X X X X X X ]
                    // else
                    //  0x5c1 x [ 0x23 X X X X X X X ] => 0x5c1 8 [ (a+1) X X X X X X X ]
                    // else
                    //  0x5c1 x [ 0xa  X X X X X X X ] => 0x5c1 8 [ 0xa   X X X X X X X ]
                    //  (a) = 0x22
                    //  (a+1) = 0x23
                    // else
                    //  0x5c1 x [ 0x28 X X X X X X X ] => 0x5c1 8 [ 0x28 X X X X X X X ]
                    //  (a) = 2, (a+1) = 3
                    // else
                    //  0x5c1 x [ X X X X X X X X ] => 0x5c1 8 [ X X X X X X X X ]
  if (rx_buffer.can_id_standard == UINT_000005c1_0800066c) {
    tx_buffer.can_id_standard = UINT_000005c1_0800066c;
    tx_buffer.can_rtr = 0;
    tx_buffer.can_ide = 0x0;
    tx_buffer.can_dlc = 8;
    if ((rx_buffer.can_data1 == 0x1e) || (rx_buffer.can_data1 == 0x1d)) {
      tx_buffer.can_data1 = 0x1a;
    }
    else if (rx_buffer.can_data1 == 0x22) {
      tx_buffer.can_data1 = *(byte *)PTR_DAT_20000000_08000670;
    }
    else if (rx_buffer.can_data1 == 0x23) {
      tx_buffer.can_data1 = *(byte *)(PTR_DAT_20000000_08000670 + 1);
    }
    else if (rx_buffer.can_data1 == 0xa) {
      *PTR_DAT_20000000_08000670 = 0x22;
      sram_ptr[1] = 0x23;
      tx_buffer.can_data1 = 0xa;
    }
    else {
      tx_buffer.can_data1 = rx_buffer.can_data1;
      if (rx_buffer.can_data1 == 0x28) {
        *PTR_DAT_20000000_08000670 = 0x2;
        sram_ptr[1] = 3;
        tx_buffer.can_data1 = 0x28;
      }
    }
    tx_buffer._12_4_ = 0x0;
    tx_buffer.can_data6 = 0x0;
    tx_buffer.can_data7 = 0x0;
    tx_buffer.can_data8 = 0x0;
    FUN_CAN_TX_08000698(&can_base_register->CAN_MCR,&tx_buffer);
                    // Toggle the PA4 LED
    led_pa4_pin = FUN_GPIO_ODR_08000860(&Peripherals::GPIOA,0b00010000);
    FUN_GPIO_SETPIN_08000876(&Peripherals::GPIOA,0b00010000,(uint)(led_pa4_pin == 0));
  }
                    // 0x575 => Reset WD Timer
  if (rx_buffer.can_id_standard == UINT_000005c1_0800066c - 0x4c) {
    FUN_IWDG_KR_AAAA_080008c0();
  }
                    // 0x436 8 [ 1 x x x x 6 x x ] => 0x436 6 [ 1 x x x x x 6 ]
                    //                             => 0x439 6 [ 1 x x x x x 6 ]
                    // 
                    // 
  can_id_modified = UINT_00000436_08000674 + 3;
  if ((rx_buffer.can_id_standard == UINT_00000436_08000674) && (rx_buffer.can_dlc == 8)) {
    tx_buffer.can_id_standard = UINT_00000436_08000674;
    tx_buffer.can_rtr = 0;
    tx_buffer.can_ide = 0;
    tx_buffer.can_dlc = 6;
    tx_buffer.can_data1 = rx_buffer.can_data1;
    tx_buffer.can_data6 = rx_buffer.can_data6;
    FUN_CAN_TX_08000698(&can_base_register->CAN_MCR,&tx_buffer);
    tx_buffer.can_rtr = 0;
    tx_buffer.can_ide = 0;
    tx_buffer.can_dlc = 6;
    tx_buffer.can_data1 = rx_buffer.can_data1;
    tx_buffer.can_data6 = rx_buffer.can_data6;
    tx_buffer.can_id_standard = can_id_modified;
    FUN_CAN_TX_08000698(&can_base_register->CAN_MCR,&tx_buffer);
  }
                    // 0x439 8 [ 1 x x x x 6 x x ] => 0x439 6 [ 1 x x x x x 6 ]
  if ((rx_buffer.can_id_standard == can_id_modified) && (rx_buffer.can_dlc == 8)) {
    tx_buffer.can_rtr = 0;
    tx_buffer.can_ide = 0;
    tx_buffer.can_dlc = 6;
    tx_buffer.can_data1 = rx_buffer.can_data1;
    tx_buffer.can_data6 = rx_buffer.can_data6;
    tx_buffer.can_id_standard = can_id_modified;
    FUN_CAN_TX_08000698(&can_base_register->CAN_MCR,&tx_buffer);
  }
  return;
}



void FUN_CAN_DEFAULTS_08000678(struct_can_config *can_config)

{
  can_config->time_triggered_mode = 0;
  can_config->auto_bus_off = 0;
  can_config->auto_wakeup = 0;
  can_config->auto_retransmit = 0;
  can_config->receiver_fifo_locked = 0;
  can_config->tx_fifo_priority = 0;
  can_config->mode = 0;
  can_config->sync_jump_width = 0;
  can_config->timeseg_1 = 3;
  can_config->timeseg_2 = 2;
  can_config->prescaler = 1;
  return;
}



int FUN_CAN_TX_08000698(uint *can_base_register,struct_can_buffer *tx_buffer)

{
  int can_mailbox;
  uint *can_register;
  
                    // Look for an empty mailbox
  can_mailbox = 0b0;
  if (-1 < (int)(can_base_register[2] << 5)) {
    if ((int)(can_base_register[2] << 4) < 0) {
      can_mailbox = 1;
    }
    else {
      if (-1 < (int)(can_base_register[2] << 3)) {
        return 4;
      }
      can_mailbox = 2;
    }
  }
  can_register = can_base_register + can_mailbox * 4 + 0x60;
  *can_register = *can_register & 1;
  if (tx_buffer->can_ide == 0) {
                    // CAN Id Standard
    *can_register =
         *can_register | (uint)tx_buffer->can_rtr |
         (uint)*(ushort *)&tx_buffer->can_id_standard << 21;
  }
  else {
                    // Can Id Extended
    *can_register =
         *can_register | (uint)tx_buffer->can_ide |
         (uint)tx_buffer->can_rtr | tx_buffer->can_id_extended << 3;
  }
  tx_buffer->can_dlc = tx_buffer->can_dlc & 0b00001111;
  can_base_register[can_mailbox * 4 + 0x61] = can_base_register[can_mailbox * 4 + 0x61] & 0xfffffff0
  ;
  can_base_register[can_mailbox * 4 + 0x61] =
       can_base_register[can_mailbox * 4 + 0x61] | (uint)tx_buffer->can_dlc;
  can_base_register[can_mailbox * 4 + 0x62] =
       *(int *)&tx_buffer->can_data2 << 8 | (uint)tx_buffer->can_data1;
  can_base_register[can_mailbox * 4 + 0x63] =
       *(int *)&tx_buffer->can_data6 << 8 | (uint)tx_buffer->can_data5;
  *can_register = *can_register | 1;
  return can_mailbox;
}



void FUN_CAN_INT_08000726(void)

{
  FUN_CAN_INT_MAIN_080004d8();
  return;
}



void FUN_CAN_INT_START_08000728(void)

{
  FUN_CAN_INT_MAIN_080004d8();
  return;
}



void FUN_EXTI_INT_0800072e(void)

{
  int iVar1;
  
  iVar1 = FUN_EXTI_READ_08000750(1);
  if (iVar1 != 0) {
    FUN_EXTI_WRITE_08000744(1);
  }
  return;
}



void FUN_EXTI_WRITE_08000744(uint data)

{
  PTR_EXTI_0800074c->PR = data;
  return;
}



bool FUN_EXTI_READ_08000750(uint bit_mask)

{
  return (PTR_EXTI_08000760->PR & bit_mask) != 0;
}



void FUN_GPIO_EXTI_08000764(struct_gpio_exti_data *exti_data)

{
  uint *exti_trigger_register;
  uint *value_ptr;
  EXTI *exti_registers;
  
  exti_registers = PTR_EXTI_080007cc;
                    // Interrupt mask register (EXTI_IMR)
                    // 
                    // Reset value: 0x0FF4 0000 (STM32F03x devices)
                    // 0x7FF4 0000 (STM32F04x devices)
                    // 
                    // Bits 31:0 IMx: Interrupt Mask on line x (x = 31 to 0)
                    // 0: Interrupt request from Line x is masked
                    // 1: Interrupt request from Line x is not masked
                    // 
                    // Example data:
                    //   exti_data.bit_mask = 1;
                    //   exti_data.offset = 0;
                    //   exti_data.trigger_register_offset = 12/0x0c (3 x 4 bytes); => Falling
                    // EXTI_FTSR
                    //   exti_data.enable = 1;
  if (exti_data->enable == 0) {
    value_ptr = (uint *)((int)&PTR_EXTI_080007cc->IMR + (uint)exti_data->offset);
                    // Setting masked bits to zero...?
                    // Presumably enabling them for IRQ?
    *value_ptr = *value_ptr & ~exti_data->bit_mask;
    return;
  }
                    // Presumably this is the enabling part...
                    // 
                    // Disable bit_mask
  PTR_EXTI_080007cc->IMR = PTR_EXTI_080007cc->IMR & ~exti_data->bit_mask;
                    // same as above?
  exti_registers->EMR = exti_registers->EMR & ~exti_data->bit_mask;
  value_ptr = (uint *)((int)&exti_registers->IMR + (uint)exti_data->offset);
                    // Turn the bit_mask on
  *value_ptr = *value_ptr | exti_data->bit_mask;
                    // Rising trigger selection register (EXTI_RTSR)
                    // 
                    // Cleared
  exti_registers->RTSR = exti_registers->RTSR & ~exti_data->bit_mask;
                    // Falling trigger selection register (EXTI_FTSR)
                    // 
                    // Cleared
  exti_registers->FTSR = exti_registers->FTSR & ~exti_data->bit_mask;
                    // Checks it is not: Software interrupt event register (EXTI_SWIER)
  if (exti_data->trigger_register_offset != 0x10) {
                    // Point exti_register to the offset trigger.
                    // Turn bit_mask on. 
    exti_trigger_register =
         (uint *)((int)&exti_registers->IMR + (uint)exti_data->trigger_register_offset);
    *exti_trigger_register = *exti_trigger_register | exti_data->bit_mask;
    return;
  }
  exti_registers->RTSR = exti_registers->RTSR | exti_data->bit_mask;
  exti_registers->FTSR = exti_registers->FTSR | exti_data->bit_mask;
  return;
}



void FUN_GPIO_CONFIG_080007d0
               (struct_gpio_registers *gpio_registers,struct_gpio_init_data *gpio_init_data)

{
  uint bit_num;
  uint bit_mask_low;
  uint bit_mask_high;
  
  bit_num = 0;
  do {
    bit_mask_low = 1 << (bit_num & 0xff);
    if ((gpio_init_data->gpio_value & bit_mask_low) == bit_mask_low) {
      if ((gpio_init_data->gpio_moder == 1) || (gpio_init_data->gpio_moder == 2)) {
        gpio_registers->GPIO_OSPEEDR = gpio_registers->GPIO_OSPEEDR & ~(3 << (bit_num << 1 & 0xff));
        gpio_registers->GPIO_OSPEEDR =
             (uint)gpio_init_data->gpio_opseedr << (bit_num << 1 & 0xff) |
             gpio_registers->GPIO_OSPEEDR;
        *(ushort *)&gpio_registers->GPIO_OTYPER =
             *(ushort *)&gpio_registers->GPIO_OTYPER & ~(ushort)bit_mask_low;
        *(ushort *)&gpio_registers->GPIO_OTYPER =
             *(ushort *)&gpio_registers->GPIO_OTYPER |
             (ushort)gpio_init_data->gpio_otyper << (bit_num & 0xff);
      }
      bit_mask_high = bit_num << 1;
      bit_mask_low = 3 << (bit_mask_high & 0xff);
      gpio_registers->GPIO_MODER = gpio_registers->GPIO_MODER & ~bit_mask_low;
      gpio_registers->GPIO_MODER =
           (uint)gpio_init_data->gpio_moder << (bit_mask_high & 0xff) | gpio_registers->GPIO_MODER;
      gpio_registers->GPIO_PUPDR = gpio_registers->GPIO_PUPDR & ~bit_mask_low;
      gpio_registers->GPIO_PUPDR =
           (uint)gpio_init_data->gpio_pupdr << (bit_mask_high & 0xff) | gpio_registers->GPIO_PUPDR;
    }
    bit_num = bit_num + 1;
  } while (bit_num < 16);
  return;
}



void FUN_GPIO_AFRL_08000840
               (struct_gpio_registers *gpio_register,uint bit_data,int alternate_function)

{
  uint index;
  uint bit_pos;
  
                    // GPIO alternate function low register (GPIOx_AFRL)
                    // 
                    // bit_mask consists of:
                    // Bits[2:0]: GPIO Pin (0-7)
                    // Bits[3]: index (Low = 0, High =1) 
                    // 
                    // Interesting way to mask lowest 3 bits and multiply by 4
  bit_pos = (bit_data << 29) >> 27;
                    // Note: the alternate GPIO functions table is found in the datasheet, not the
                    // manual, how stupid...
                    // index is just the top bit (3) to choose first Pins 0-7 (index 0) or Pins 8-15
                    // (index 1) - which is really just deciding b/w AFRL or AFRH
  index = bit_data >> 3;
  (&gpio_register->GPIO_AFRL)[index] = (&gpio_register->GPIO_AFRL)[index] & ~(0b00001111 << bit_pos)
  ;
  (&gpio_register->GPIO_AFRL)[index] =
       (&gpio_register->GPIO_AFRL)[index] | alternate_function << bit_pos;
  return;
}



bool FUN_GPIO_ODR_08000860(struct_gpio_registers *gpio_base_register,ushort bit_mask)

{
  return (*(ushort *)&gpio_base_register->GPIO_ODR & bit_mask) != 0;
}



void FUN_GPIO_BRR_0800086e(struct_gpio_registers *gpio_register,ushort value)

{
                    // GPIO port bit reset register (GPIOx_BRR) (x =A..F)
  *(ushort *)&gpio_register->GPIO_BRR = value;
  return;
}



void FUN_GPIO_BSRR_08000872(struct_gpio_registers *gpio_register,uint value)

{
                    // GPIO port bit set/reset register (GPIOx_BSRR) (x = A..F)
                    // 
                    // Base is setting, << 16 to reset
  gpio_register->GPIO_BSRR = value;
  return;
}



void FUN_GPIO_SETPIN_08000876(struct_gpio_registers *gpio_base_register,uint bit_mask,int state)

{
  if (state != 0) {
    gpio_base_register->GPIO_BSRR = bit_mask;
    return;
  }
  *(short *)&gpio_base_register->GPIO_BRR = (short)bit_mask;
  return;
}



void FUN_INT_LOOP_FOREVER_08000882(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_IWDG_KR_CCCC_08000884(void)

{
  PTR_IWDG_08000890->KR = UINT_0000CCCC_0800088c;
  return;
}



void FUN_IWDG_INIT_08000894(void)

{
                    // 0101010101010101 => Setup Key
  PTR_IWDG_080008b8->KR = UINT_00005555_080008b4;
                    // IWDG Prescaler register 
                    // Bits 2:0 PR[2:0]: Prescaler divider
                    // 6 => 110: divider /256
  FUN_IWDG_PR_080008d0(6);
                    // Reload register (IWDG_RLR)
                    // Bits11:0 RL[11:0]: Watchdog counter reload value
                    // 0x271 => 625
                    // 
                    // These values look like a 4sec IWDG timeout (256/40,000*625)...
  FUN_IWDG_RLR_080008dc(UINT_00000271_080008bc);
                    // 1010101010101010 => WD Reset Key
  FUN_IWDG_KR_AAAA_080008c0();
                    // 1100110011001100 => Start WG
  FUN_IWDG_KR_CCCC_08000884();
  return;
}



void FUN_IWDG_KR_AAAA_080008c0(void)

{
  PTR_IWDG_080008cc->KR = UINT_0000AAAA_080008c8;
  return;
}



void FUN_IWDG_PR_080008d0(uint value)

{
  PTR_IWDG_080008d8->PR = value;
  return;
}



void FUN_IWDG_RLR_080008dc(uint value)

{
  PTR_IWDG_080008e4->RLR = value;
  return;
}



void FUN_GPIO_INIT_PA4_LED_CONFIG_080008e8(void)

{
  struct_gpio_init_data gpio_init_data;
  
                    // Initialise PA4: Output, High Speed, push-pull, No pull-up, pull-down
  gpio_init_data.gpio_value = 0b00010000;
  gpio_init_data._4_4_ = 0x301;
  FUN_GPIO_CONFIG_080007d0(&Peripherals::GPIOA,&gpio_init_data);
  return;
}



void FUN_INT_NMI_RETURN_08000908(void)

{
  return;
}



void FUN_GPIO_NVIC_0800090c(struct_nvic_data *nvic_data)

{
  NVIC *nvic_register;
  uint int;
  
                    // nvic_bit_num / 4
                    // 
                    // nvic_ipro_data 0x3 (bottom 2 bits) * 32
  int = (uint)nvic_data->nvic_bit_num;
  if (nvic_data->write == 0) {
                    // Interrupt clear-enable register (ICER)
                    // 
                    //   nvic_config.nvic_bit_num = 30 0x1e 00011110;
                    //   nvic_config.2 = 1;
                    //   nvic_config.write = 1;
                    // 
                    //   nvic_config.nvic_bit_num = 5 0101;
                    //   nvic_config.2 = 0;
                    //   nvic_config.write = 1;
                    // 
                    // e000e100+(4*0x20) => e000e180 => Interrupt clear-enable register (ICER)
    nvic_register = (NVIC *)&PTR_NVIC_08000958->ICER;
  }
  else {
                    // Interrupt priority register (IPR0-IPR7)
                    // Figure out which IPRO register for the nvic_bit_num (i..e divide by 4)
                    // int = bottom 2 bits multiplied by 4
    int = (int << 30) >> 27;
                    // *16
    PTR_NVIC_IPR0_08000954[nvic_data->nvic_bit_num >> 2] =
         (((uint)nvic_data->nvic_ipro_data << 30) >> 24) << int |
         PTR_NVIC_IPR0_08000954[nvic_data->nvic_bit_num >> 2] & ~(0xff << int);
    int = (uint)nvic_data->nvic_bit_num;
    nvic_register = PTR_NVIC_08000958;
  }
  nvic_register->ISER = 1 << (int & 0x1f);
  return;
}



void FUN_POWER_SLEEP_MODES_0800095c(uint pwr_mode,int sleep_mode)

{
  uint value;
  uint *base_register;
  
                    // Power control register (PWR_CR)
                    // 
                    // Reset value: 0x0000 0000 (reset by wakeup from Standby mode)
                    // 
                    // Bit 1 PDDS: Power down deepsleep.
                    // This bit is set and cleared by software. It works together with the LPDS bit.
                    // 0: Enter Stop mode when the CPU enters Deepsleep. The regulator status
                    // depends on the LPDS bit.
                    // 1: Enter Standby mode when the CPU enters Deepsleep.
                    // 
                    // Bit 0 LPDS: Low-power deepsleep.
                    // This bit is set and cleared by software. It works together with the PDDS bit.
                    // 0: Voltage regulator on during Stop mode
                    // 1: Voltage regulator in low-power mode during Stop mode
                    // 
                    // Note: When a peripheral that can work in STOP mode requires a clock, the
                    // Power controller automatically switch the voltage regulator from Low-power
                    // mode to Normal mode and remains in this mode until the request disappears.
  PTR_PWR_08000990->CR = PTR_PWR_08000990->CR & 0b11111111111111111111111111111100 | pwr_mode;
  base_register = PTR_DAT_e000ed00_CPUID_08000994;
                    // System control register (SCR) (0xe000ed00[4] => 0xE000ED10)
                    // 
                    // The SCR controls features of entry to and exit from low power state.
                    // 
                    // Bit 2 SLEEPDEEP
                    // Controls whether the processor uses sleep or deep sleep as its low power
                    // mode:
                    // 0: Sleep
                    // 1: Deep sleep.
                    // Bit 1 SLEEPONEXIT
                    // Configures sleep-on-exit when returning from Handler mode to Thread mode.
                    // Setting this bit to 1 enables an interrupt-driven application to avoid
                    // returning to an empty main application.
                    // 0: Do not sleep when returning to Thread mode.
                    // 1: Enter sleep, or deep sleep, on return to Thread mode from an interrupt
                    // service routine.
                    // 
                    // Here we seem to besetting DeepSleep with a choice of:
                    // Interrupt(mode 1)
                    // Event (mode 2) OR
                    // Sleep on retun from Interrupt
  PTR_DAT_e000ed00_CPUID_08000994[4] = PTR_DAT_e000ed00_CPUID_08000994[4] | 0b00000100;
  if (sleep_mode == 1) {
    WaitForInterrupt();
  }
  else {
    if (sleep_mode != 2) {
                    // Set Sleep on exit of Interrupt
      value = base_register[4] | 2;
      goto LAB_08000980;
    }
    WaitForEvent();
  }
                    // Set to normal Sleep mode
  value = base_register[4] & 0b11111111111111111111111111111011;
LAB_08000980:
  base_register[4] = value;
  return;
}



void FUN_INT_PENDSV_RETURN_08000998(void)

{
  return;
}



void FUN_RCC_AHBENR_0800099c(uint bit_mask,int state)

{
  if (state == 0) {
    bit_mask = PTR_RCC_080009b0->RCC_AHBENR & ~bit_mask;
  }
  else {
    bit_mask = PTR_RCC_080009b0->RCC_AHBENR | bit_mask;
  }
  PTR_RCC_080009b0->RCC_AHBENR = bit_mask;
  return;
}



void FUN_RCC_APB1ENR_080009b4(uint bit_mask,int state)

{
  uint uVar1;
  
  if (state == 0) {
    uVar1 = PTR_RCC_080009c8->RCC_APB1ENR & ~bit_mask;
  }
  else {
    uVar1 = PTR_RCC_080009c8->RCC_APB1ENR | bit_mask;
  }
  PTR_RCC_080009c8->RCC_APB1ENR = uVar1;
  return;
}



void FUN_CAN_RCC_APB1RSTR_SETBIT_080009cc(uint bit_mask,int state)

{
  if (state == 0) {
    bit_mask = PTR_RCC_080009e0->APB1RSTR & ~bit_mask;
  }
  else {
    bit_mask = PTR_RCC_080009e0->APB1RSTR | bit_mask;
  }
  PTR_RCC_080009e0->APB1RSTR = bit_mask;
  return;
}



void FUN_RCC_APB2ENR_080009e4(uint bit_mask,int state)

{
  uint uVar1;
  
  if (state == 0) {
    uVar1 = PTR_RCC_080009f8->RCC_APB2ENR & ~bit_mask;
  }
  else {
    uVar1 = PTR_RCC_080009f8->RCC_APB2ENR | bit_mask;
  }
  PTR_RCC_080009f8->RCC_APB2ENR = uVar1;
  return;
}



void FUN_RCC_INIT_080009fc(void)

{
                    // Not sure why there is so much duplication in these RCC routines...
  FUN_RCC_CLEAR_08000a3c();
  FUN_RCC_CONFIG_08000b6c();
  FUN_SYSTICK_SOURCE_08000c30(0x24);
                    // 10000000 => 00010000 00000000 00000000 00000000
                    // 
                    // PWREN: 1: Power interface clock enabled
  FUN_RCC_APB1ENR_080009b4(0x10000000,1);
                    // 20000 => 00000000 00000010 00000000 00000000
                    // 
                    // IOPAEN: 1: I/O port A clock enabled
  FUN_RCC_AHBENR_0800099c(0x20000);
                    // 00040000 => 00000000 00000100 00000000 00000000
                    // 
                    // IOPBEN: 1: I/O port B clock enabled
  FUN_RCC_AHBENR_0800099c(0x40000);
                    // SYSCFGCOMPEN: 1: SYSCFG & COMP clock enabled
  FUN_RCC_APB2ENR_080009e4(1,1);
                    // PA11_PA12_RMP: 1: Remap (pin pair PA11/12 mapped instead of PA9/10)
  PTR_SYSCFG_08000a38->CFGR1 = PTR_SYSCFG_08000a38->CFGR1 | 0b00010000;
  return;
}



void FUN_RCC_CLEAR_08000a3c(void)

{
  struct_rcc_registers *rcc_register;
  
  rcc_register = PTR_RCC_08000a88;
                    // HSION: 1: HSI oscillator ON
  PTR_RCC_08000a88->RCC_CR = PTR_RCC_08000a88->RCC_CR | 1;
                    // RCC_CFGR: 08FFB80C => 00001000 11111111 10111000 00001100
                    // 
                    // Setting:
                    // PLLNODIV: 0: PLL is divided by 2 for MCO
                    // MCOPRE[2:0]: 000: MCO is divided by 1
                    // MCO[3:0]: 1000: Internal RC 48 MHz (HSI48) oscillator clock selected
                    // PLLMUL[3:0]: 1111: PLL input clock x 16
                    // PLLXTPRE: This bit is the same bit as bit PREDIV[0] from RCC_CFGR2
                    // PLLSRC[1:0]: 11: HSI48/PREDIV selected as PLL input clock
                    // ADCPRE: ADC prescaler Obsolete See ADC_CFGR2
                    // PPRE[2:0]; 0xx: HCLK not divided
                    // HPRE[3:0]: 0xxx: SYSCLK not divided
                    // SW[1:0]: 00: HSI selected as system clock
                    // 
                    // 
  rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & UINT_08FFB80C_08000a8c;
                    // FEF6FFFF => 11111110 11110110 11111111 11111111
                    // 
                    // Settings:
                    // PLLON: PLL enable: 0: PLL OFF
                    // CSSON: 0: Clock security system disabled (clock detector OFF).
                    // HSEBYP: HSE crystal oscillator bypass: 1: bypassed with external clock
                    // HSEON: HSE clock enable: 0: HSE oscillator OFF
                    // HSION: HSI clock enable: 1: HSI oscillator ON
                    // 
  rcc_register->RCC_CR = rcc_register->RCC_CR & UINT_FEF6FFFF_08000a90;
                    // fffbffff => 11111111 11111011 11111111 11111111
                    // 
                    // PLLON: PLL enable: 1: PLL ON
                    // HSEBYP: HSE crystal oscillator bypass : 0: not bypassed
                    // CSSON: 1: Clock security system enabled
                    // HSEON: 1: HSE oscillator ON
                    // 
  rcc_register->RCC_CR = rcc_register->RCC_CR & 0xfffbffff;
                    // ffc0ffff => 11111111 11000000 11111111 11111111
                    // 
                    // Clearing:
                    // PLLMUL: 0000: PLL input clock x 2
                    // PLLXTPRE: 0 PREDIV[0] from RCC_CFGR2
                    // PLLSRC: 00: HSI/2 selected as PLL input clock (PREDIV forced to divide by 2
                    // on STM32F04x devices)
  rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & 0xffc0ffff;
                    // 0xfffffff0 => 11111111 11111111 11111111 11110000
                    // 
                    // PREDIV division factor: 0000: PREDIV input clock not divided
  rcc_register->RCC_CFGR2 = rcc_register->RCC_CFGR2 & 0xfffffff0;
                    // FFF0FEAC => 11111111 11110000 11111110 10101100
                    // 
                    // USART3SW: 00: PCLK selected as USART3 clock source (default)
                    // USART2SW: 00: PCLK selected as USART2 clock source (default)
                    // ADCSW: ADC clock source selection Obsolete setting
                    // USART1SW: 00: PCLK selected as USART1 clock source (default)
                    // I2C1SW: 0: HSI clock selected as I2C1 clock source (default)
                    // 
  rcc_register->RCC_CFGR3 = rcc_register->RCC_CFGR3 & UINT_FFF0FEAC_08000a94;
                    // fffffffe => 11111111 11111111 11111111 11111110
                    // 
                    // HSI48ON: 1: HSI48 oscillator ON
                    // HSI14ON: 0: HSI14 oscillator OFF
  rcc_register->RCC_CR2 = rcc_register->RCC_CR2 & 0xfffffffe;
                    // Clock interrupt register (RCC_CIR)
                    // 
                    // Disable all clock related interrupts
                    // 
                    // Should really be 0xff000000 to maintain reserved pin state...
  rcc_register->RCC_CIR = 0;
  return;
}



void FUN_INT_SVCALL_RETURN_08000a98(void)

{
  return;
}



void FUN_SYSCFG_08000a9c(int bit_mask,uint bit_num)

{
  uint bit_pos;
  SYSCFG *syscfg_register;
  
  syscfg_register = PTR_SYSCFG_08000ac0;
                    // SYSCFG external interrupt configuration register 1
                    // (SYSCFG_EXTICR1)
                    // 
                    // Bits 15:0 EXTIx[3:0]: EXTI x configuration bits (x = 0 to 3)
                    // These bits are written by software to select the source input for the EXTIx
                    // external interrupt.
                    // x000: PA[x] pin
                    // x001: PB[x] pin
                    // x010: PC[x] pin
                    // x011: PD[x] pin
                    // x100: PE[x] pin
                    // x101: PF[x] pin
                    // 
                    // limit to 4:
                    // value = (bit_num & 0x00000011) * 4
                    // 
                    // Called with 0,0
  bit_pos = (bit_num << 30) >> 28;
  bit_num = bit_num & 0b11111111111111111111111111111100;
  *(uint *)((int)&PTR_SYSCFG_08000ac0->EXTICR1 + bit_num) =
       *(uint *)((int)&PTR_SYSCFG_08000ac0->EXTICR1 + bit_num) & ~(0xf << bit_pos);
  *(uint *)((int)&syscfg_register->EXTICR1 + bit_num) =
       *(uint *)((int)&syscfg_register->EXTICR1 + bit_num) | bit_mask << bit_pos;
  return;
}



void FUN_RCC_CONFIG_PLL_FLASH_08000ac4(void)

{
  int i;
  struct_rcc_registers *rcc_register;
  
  rcc_register = PTR_RCC_08000b60;
  i = 0;
                    // 00010000 => 00000000 00000001 00000000 00000000
                    // 
                    // HSEON: 1: HSE oscillator ON
                    // Wait for HSERDY
  PTR_RCC_08000b60->RCC_CR = PTR_RCC_08000b60->RCC_CR | 0x10000;
  do {
    i = i + 1;
    if ((rcc_register->RCC_CR & 0x20000) != 0) break;
  } while (i != 0x5000);
                    // HSERDY to top bit, then check for <0 ???
                    // 
                    // I think this is just checking for HSERDY bit set...
  if ((int)(rcc_register->RCC_CR << 14) < 0) {
                    // FLASH_ACR: 
                    // PRFTBE: 1: Prefetch is enabled
                    // LATENCY: 001: One wait state, if 24 MHz < SYSCLK ≤ 48 MHz
    PTR_Flash_08000b64->ACR = 0b00010001;
                    // No sure what the net 2 are doing - nothing...???
                    // 
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR;
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR;
                    // ffc07fff => 11111111 11000000 01111111 11111111
                    // 
                    // PLLMUL 0000: PLL input clock x 2
                    // PLLXTPRE 0
                    // PLLSRC0: HSI/2 selected as PLL input clock (PREDIV forced to divide by 2 on
                    // STM32F04x)
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & 0xffc07fff;
                    // Was: ffc07fff => 11111111 11000000 01111111 11111111 OR
                    // Now: 001d0000 => 00000000 00011101 00000000 00000000
                    // 
                    // PLLMUL: 0111: PLL input clock x 9
                    // PLLSRC: 10: HSE/PREDIV selected as PLL input clock
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR | 0x1d0000;
                    // Was: fffffff0 => 11111111 11111111 11111111 11110000
                    // Now: fffffff0 => 11111111 11111111 11111111 11110000
                    // 
                    // No change
                    // 
                    // PREDIV division factor: 0000: PREDIV input clock not divided
    rcc_register->RCC_CFGR2 = rcc_register->RCC_CFGR2 & 0xfffffff0;
                    // PREDIV: 0001: PREDIV input clock divided by 2
    rcc_register->RCC_CFGR2 = rcc_register->RCC_CFGR2 | 1;
                    // 010000000 => 00000001 00000000 00000000 00000000 OR
                    // 
                    // PLLON: 1: PLL ON
    rcc_register->RCC_CR = rcc_register->RCC_CR | 0x1000000;
    do {
                    // Wait for PLLRDY
    } while (-1 < (int)(rcc_register->RCC_CR << 6));
                    // fffffffc => 11111111 11111111 11111111 11111100
                    // 
                    // SW: 00: HSI selected as system clock
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & 0xfffffffc;
                    // SW: 10: PLL selected as system clock
    rcc_register->RCC_CFGR = rcc_register->RCC_CFGR | 2;
    do {
                    // Wait for SWS: 10: PLL used as system clock
    } while ((rcc_register->RCC_CFGR << 28) >> 30 != 2);
    return;
  }
  return;
}



void FUN_INT_SYSTICK_RETURN_08000b68(void)

{
  return;
}



void FUN_RCC_CONFIG_08000b6c(void)

{
  struct_rcc_registers *rcc_register;
  
  rcc_register = PTR_RCC_08000bc0;
                    // Bit 0 HSION: HSI clock enable
  PTR_RCC_08000bc0->RCC_CR = PTR_RCC_08000bc0->RCC_CR | 1;
                    // Was: 08FFB80C => 00001000 11111111 10111000 00001100
                    // Now: F8FFB80C => 11111000 11111111 10111000 00001100
                    // 
                    // PLLNODIV: 1: PLL is not divided for MCO
                    // MCOPRE: 111: MCO is divided by 128
  rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & UINT_F8FFB80C_08000bc4;
                    // Was: fffbffff => 11111111 11111011 11111111 11111111
                    // Now: FEF6FFFF => 11111110 11110110 11111111 11111111
                    // 
                    // Changes:
                    // PLLON: 0: PLL OFF
                    // CSSON: 0: Clock security system disabled (clock detector OFF).
                    // HSEON: 0: HSE oscillator OFF
                    // 
  rcc_register->RCC_CR = rcc_register->RCC_CR & UNIT_FEF6FFFF_08000bc8;
                    // Was: FEF6FFFF => 11111110 11110110 11111111 11111111
                    // Now: fffbffff => 11111111 11111011 11111111 11111111
                    // 
                    // PLLON: 1: PLL ON
                    // CSSON: 1: Clock security system enabled (clock detector ON if the HSE is
                    // ready, OFF if not).
                    // HSEBYP: 0: HSE crystal oscillator not bypassed
                    // HSEON: 1: HSE oscillator ON
  rcc_register->RCC_CR = rcc_register->RCC_CR & 0xfffbffff;
                    // Was: F8FFB80C => 11111000 11111111 10111000 00001100
                    // Now: FFC0FFFF => 11111111 11000000 11111111 11111111
                    // 
                    // 
                    // MCO: 0111: PLL clock selected (divided by 1 or 2, depending on PLLNODIV)
                    //      1000: Internal RC 48 MHz (HSI48) oscillator clock selected
                    //      (not sure which of these)
                    // 
                    // PLLMUL: 0000: PLL input clock x 2
                    // PLLXTPRE: 0 This bit is the same bit as bit PREDIV[0] from RCC_CFGR2
                    // PLLSRC: 00: HSI/2 selected as PLL input clock
                    // HPRE: 1000: SYSCLK divided by 2
                    // SW: 00: HSI selected as system clock
                    // 
                    // 
  rcc_register->RCC_CFGR = rcc_register->RCC_CFGR & 0xffc0ffff;
                    // Was: fffffff0 => 11111111 11111111 11111111 11110000
                    // Now: fffffff0 => 11111111 11111111 11111111 11110000
                    // 
                    // No change
  rcc_register->RCC_CFGR2 = rcc_register->RCC_CFGR2 & 0xfffffff0;
                    // Was: FFF0FEAC => 11111111 11110000 11111110 10101100
                    // Now: fffffeac => 11111111 11111111 11111110 10101100
                    // 
                    // USART3SW: 11: HSI clock selected as USART3 clock
                    // USART2SW: 11: HSI clock selected as USART2 clock
  rcc_register->RCC_CFGR3 = rcc_register->RCC_CFGR3 & 0xfffffeac;
                    // Was: fffffffe => 11111111 11111111 11111111 11111110
                    // Now: fffffffe => 11111111 11111111 11111111 11111110
                    // 
                    // No Change
  rcc_register->RCC_CR2 = rcc_register->RCC_CR2 & 0xfffffffe;
                    // No Change
  rcc_register->RCC_CIR = 0;
  FUN_RCC_CONFIG_PLL_FLASH_08000ac4();
  return;
}



void FUN_GPIO_INIT_08000bcc(void)

{
  struct_gpio_exti_data exti_config;
  struct_gpio_init_data gpio_config;
  struct_nvic_data nvic_config;
  
                    // PA0 Input
                    // 
                    // Presumably not used ???
                    // 
                    // Odd since the PCB does not seem to have any connections to PA0 ???
  gpio_config.gpio_value = 0b00000001;
  gpio_config.gpio_moder = 0;
  gpio_config.gpio_pupdr = 0;
  FUN_GPIO_CONFIG_080007d0(&Peripherals::GPIOA,&gpio_config);
  exti_config.bit_mask = 0b00000001;
  exti_config.offset = 0;
  exti_config.trigger_register_offset = 12;
  exti_config.enable = 1;
  FUN_GPIO_EXTI_08000764(&exti_config);
  nvic_config.nvic_bit_num = 5;
  nvic_config.nvic_ipro_data = 0;
  nvic_config.write = 1;
  FUN_GPIO_NVIC_0800090c(&nvic_config);
  FUN_SYSCFG_08000a9c(0);
  return;
}



void FUN_SYSTICK_SOURCE_08000c30(void)

{
                    // Bit 2 CLKSOURCE: Clock source selection
                    // Selects the timer clock source.
                    // 0: External reference clock
                    // 1: Processor clock
                    // SysTick control and status register (STK_CSR)
  PTR_DAT_e000e000_08000c3c[4] = PTR_DAT_e000e000_08000c3c[4] & 0b11111111111111111111111111111011;
  return;
}



void FUN_SYSTICK_CONFIG_08000c40(int bit_mask)

{
  uint *base_register;
  
                    // System Control Space 0xe000e000
                    // 
                    // E000    [0]     Base SCR
                    // E004    [1]     Interrupt Control Type Register
                    // E008    [2]     Auxiliary Control Register              ACTLR
                    // E00C    [3]
                    // E010    [4]     SysTick Control and Status Register     STCSR STK_CSR 
                    // E014    [5]     SysTick Reload Value Register           STRVR STK_RVR
                    // E018    [6]     SysTick Current Value Register          STCVR STK_CVR
                    // E01c    [7]     SysTick Calibration Value Register      STCR  STK_CALIB
                    // 
  base_register = PTR_DAT_e000e000_08000c64;
                    // SysTick reload value register (STK_RVR)
                    // 
                    // The STK_RVR specifies the start value to load into the STK_CVR.
                    // 
                    // Called with 0x32 => 50 => 0b00110010
                    // 
                    // So 0x32 * 0x1194 => 0x36ee8 => 225000
  PTR_DAT_e000e000_08000c64[5] = DAT_00001194_08000c60 * bit_mask;
                    // SysTick current value register (STK_CVR)
                    // 
                    // The STK_CVR contains the current value of the SysTick counter.
  base_register[6] = 0;
                    // SysTick control and status register (STK_CSR)
                    // 
                    // The SysTick CSR register enables the SysTick features.
  base_register[4] = 1;
  do {
                    // SysTick control and status register (STK_CSR)
                    // 
                    // Bit 0 ENABLE: Counter enable
                    // Enables the counter. When ENABLE is set to 1, the counter starts counting
                    // down. On reaching
                    // 0, it sets the COUNTFLAG to 1 and optionally asserts the SysTick depending on
                    // the value of
                    // TICKINT. It then loads the RELOAD value again, and begins counting.
                    // 0: Counter disabled
                    // 1: Counter enabled
    if ((base_register[4] & 1) == 0) break;
  } while (-1 < (int)(base_register[4] << 15));
                    // SysTick control and status register (STK_CSR)
  base_register[4] = 0;
                    // SysTick current value register (STK_CVR)
                    // 
                    // The STK_CVR contains the current value of the SysTick counter.
  base_register[6] = 0;
  return;
}



void FUN_MAIN_LOOP_08000c68(void)

{
  FUN_RCC_INIT_080009fc();
  FUN_GPIO_INIT_08000bcc();
  FUN_SYSTICK_CONFIG_08000c40(0b00110010);
                    // I think this is called with 0x1 & 0x1 as the parameters...?
                    // 
                    // So Stop Mode & Voltage Regulator is in low power mode AND
                    // DeepSleep with Wait for Interrupt
  FUN_POWER_SLEEP_MODES_0800095c(1);
                    // I think the uC stops here until a CAN interrupt.
                    // Apprently it needs to re-initialise RCC after waking up...
                    // 
                    // Might possibly be the IWDG waking it up, not a CAN interrupt...
  FUN_RCC_INIT_080009fc();
  FUN_GPIO_INIT_PA4_LED_08000164();
  FUN_CAN_GPIO_INIT_0800016c();
                    // Set PA4 (LED) High (Off ???)
  FUN_GPIO_BSRR_08000872(&Peripherals::GPIOA,0b00010000);
  FUN_IWDG_INIT_08000894();
                    // Set PA6 Low: TJA1042 STB Mode Normal
  FUN_GPIO_BRR_0800086e(&Peripherals::GPIOA,0b01000000);
  do {
                    // WARNING: Do nothing block with infinite loop
                    // Just let CAN interrupts drive the show.
                    // Each new CAN packet will reset the IWDG.
                    // 
                    // So if no new CAN packets in 4sec, IWDG will reset and it will go back into
                    // stop mode...
  } while( true );
}


