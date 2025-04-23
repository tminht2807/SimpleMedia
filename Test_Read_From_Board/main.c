#include "device_registers.h" /* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"

#define SW2 12
#define SW3 13
#define POTEN 14

#define PTD0 0
#define PTD16 15
#define PTD15 16


#define RED_LED 15
#define GREEN_LED 16

uint8_t adcResult;

void NVIC_Init(void){
    // Enable IRQ for PORTC interrupts in NVIC
	S32_NVIC->ISER[PORTC_IRQn >> 5] = (1 << (PORTC_IRQn & 0x1F));
}

void LPUART1_init(void)  /* Init. summary: 9600 baud, 1 stop bit, 8 bit format, no parity */
{
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;    /* Ensure clk disabled for config */
	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(3)    /* Clock Src = 3 (FIRCDIV2_CLK) */
                            	 |  PCC_PCCn_CGC_MASK;     /* Enable clock for LPUART1 regs */

	LPUART1->BAUD = LPUART_BAUD_SBR(26)  	/* Initialize for 115200 baud, 1 stop: */
                	|LPUART_BAUD_OSR(15);  	/* SBR=26: baud divisor = 48M/115200/16 = 26 */
											/* OSR=15: Over sampling ratio = 15+1=16 */
											/* SBNS=0: One stop bit */
											/* BOTHEDGE=0: receiver samples only on rising edge */
											/* M10=0: Rx and Tx use 7 to 9 bit data characters */
											/* RESYNCDIS=0: Resync during rec'd data word supported */
											/* LBKDIE, RXEDGIE=0: interrupts disable */
											/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
											/* MAEN1, MAEN2,  MATCFG=0: Match disabled */

	LPUART1->CTRL =	LPUART_CTRL_RE_MASK
					|LPUART_CTRL_TE_MASK;   	/* Enable transmitter & receiver, no parity, 8 bit char: */
												/* RE=1: Receiver enabled */
												/* TE=1: Transmitter enabled */
												/* PE,PT=0: No hw parity generation or checking */
												/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
												/* DOZEEN=0: LPUART enabled in Doze mode */
												/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
												/* TxDIR=0: TxD pin is input if in single-wire mode */
												/* TXINV=0: TRansmit data not inverted */
												/* RWU,WAKE=0: normal operation; rcvr not in statndby */
												/* IDLCFG=0: one idle character */
												/* ILT=0: Idle char bit count starts after start bit */
												/* SBK=0: Normal transmitter operation - no break char */
												/* LOOPS,RSRC=0: no loop back */
}

void PORT_init (void)
{
	// PORT C
	PCC->PCCn[PCC_PORTC_INDEX ]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTC */

	// Configure PORTC Pin 12 (SW2) as GPIO with interrupt
	PORTC->PCR[SW2] = PORT_PCR_MUX(1)       // Set MUX to GPIO
					| PORT_PCR_IRQC(9)   // Enable interrupt on rising edge
					| PORT_PCR_PE_MASK
					| PORT_PCR_PS_MASK;
	// Configure PORTC Pin 13 (SW3) as GPIO with interrupt
	PORTC->PCR[SW3] = PORT_PCR_MUX(1)       // Set MUX to GPIO
					| PORT_PCR_IRQC(9)   // Enable interrupt on rising edge
					| PORT_PCR_PE_MASK
					| PORT_PCR_PS_MASK;
	// Configure PORTC Pin 14 (potentiometer) as GPIO with interrupt
	PORTC->PCR[POTEN] = PORT_PCR_MUX(1)       // Set MUX to GPIO
					| PORT_PCR_PE_MASK
					| PORT_PCR_PS_MASK;

	PORTC->PCR[6]|=PORT_PCR_MUX(2);	/* Port C6: MUX = ALT2, UART1 RX */
	PORTC->PCR[7]|=PORT_PCR_MUX(2);   /* Port C7: MUX = ALT2, UART1 TX */

	// Set the pins as inputs in the GPIO module
	PTC->PDDR &= ~((1 << SW2) | (1 << SW3) | (1 << POTEN)); // Clear bits 12 and 13 for input

	PORTC->ISFR = ((1 << SW2) | (1 << SW3));

	// PORT D
	PCC->PCCn[PCC_PORTD_INDEX]|=PCC_PCCn_CGC_MASK;   /* Enable clock for PORTD */
	PORTD->PCR[RED_LED] = PORT_PCR_MUX(1);  /* Port D15: MUX = GPIO */
	PORTD->PCR[GREEN_LED] = PORT_PCR_MUX(1);  /* Port D16: MUX = GPIO */
	PORTD->PCR[PTD0] = PORT_PCR_MUX(1);  /* Port D16: MUX = GPIO */

	PTD->PDDR |= 1<< RED_LED	    /* Port D15: Data Direction = output */
				| 1 << PTD0
				| 1<< GREEN_LED ;    /* Port D16: Data Direction = output */
}

void ADC0_init(void){
	PCC->PCCn[PCC_ADC0_INDEX] &=~ PCC_PCCn_CGC_MASK;  /* Disable clock to change PCS */
	PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(3); /* PCS=1: Select FIRCDIV2 		*/
	PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_CGC_MASK;   /* Enable bus clock in ADC 	*/

	/*!
	* ADC0 Initialization:
	* ===================================================
	*/
	ADC0->SC1[0] |= ADC_SC1_ADCH_MASK;	/* ADCH=1F: Module is disabled for conversions	*/
											/* AIEN=0: Interrupts are disabled 			*/
	ADC0->CFG1 |= ADC_CFG1_ADIV_MASK
				|ADC_CFG1_MODE(1);	/* ADICLK=0: Input clk=ALTCLK1=	*/
										/* ADIV=0: Prescaler=1 					*/
										/* MODE=1: 12-bit conversion 				*/

	ADC0->CFG2 = ADC_CFG2_SMPLTS(12);	/* SMPLTS=12(default): sample time is 13 ADC clks 	*/
	ADC0->SC2 = 0x00000000;         	/* ADTRG=0: SW trigger 							*/
										/* ACFE,ACFGT,ACREN=0: Compare func disabled		*/
										/* DMAEN=0: DMA disabled 							*/
										/* REFSEL=0: Voltage reference pins= VREFH, VREEFL */
	ADC0->SC3 = 0x00000000;       	/* CAL=0: Do not start calibration sequence 		*/
										/* ADCO=0: One conversion performed 				*/
										/* AVGE,AVGS=0: HW average function disabled 		*/
}

void convertAdcChan(uint16_t adcChan){
	/*!
	 * For SW trigger mode, SC1[0] is used
	 * ===================================================
	 */
	ADC0->SC1[0]&=~ADC_SC1_ADCH_MASK;	      	/* Clear prior ADCH bits 	*/
	ADC0->SC1[0] = ADC_SC1_ADCH(adcChan);   	/* Initiate Conversion		*/
}

uint8_t adc_complete(void){
	return ((ADC0->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT); 	/* Wait for completion */
}

void LPUART1_transmit_char(uint8_t send) {    /* Function to Transmit single Char */
	while((LPUART1->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT==0);
	/* Wait for transmit buffer to be empty */
	LPUART1->DATA=send;              /* Send data */
}

void read_adc_chx(void){
	uint32_t adc_result = 0;
	adc_result = ADC0->R[0];      							/* For SW trigger mode, R[0] is used 	*/
	uint8_t temp = ((adc_result * 62) / 4095); 		// max is 62 = 0x3E, spare 2 bits
	adcResult = temp;								// 0011 1110
}

void delay_ms(uint32_t milliseconds) {
    uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 4000; j++) {  // Adjust loop count for approximate timing
            __asm__("NOP");  // No operation (to prevent compiler optimization)
        }
    }
}

void PORTC_IRQHandler(void){
    static uint8_t flag_btn13 = 0;

    // Check if the interrupt was triggered by SW2 (PortC Pin 12)
    if (PORTC->ISFR & (1 << SW2))    { // SW2 play pause
        PORTC->ISFR |= (1 << SW2); // Clear interrupt flag for Pin 12
        // Handle SW2 interrupt
        LPUART1_transmit_char(0xBF);				// 1011 1111  // PlayPause
        PTD->PTOR |= 1 << RED_LED;
    }

    // Check if the interrupt was triggered by SW3 (PortC Pin 13)
    if(PORTC->ISFR & (1 << 13)) {
            PORTC->ISFR |= (1 << 13);

            if (flag_btn13 == 0) {
                flag_btn13 = 1;
                delay_ms(1000);
                if (PORTC->ISFR & (1 << 13)) { // double click Prev media feature
                    PORTC->ISFR |= (1 << 13);
                    PTD->PTOR |= 1 << PTD0;
                    LPUART1_transmit_char(0x3F); // 0011 1111
                } else {						// normal click Next media feature
                	LPUART1_transmit_char(0x7F); // 0111 1111
                    PTD->PTOR |= 1 << GREEN_LED;
                }
                flag_btn13 = 0;
            }
        }
}


int main(void){
	// Set FIRCDIV2 clock
	SCG->FIRCCFG = SCG_FIRCCFG_RANGE(1);     // Set FIRC range to 48 MHz
	SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN_MASK; // Enable FIRC
	while (!(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK)) {
		// Wait for FIRC to stabilize
	}
	// Enable FIRCDIV2
	SCG->FIRCDIV = SCG_FIRCDIV_FIRCDIV2(1);  // Divide by 1 (you can adjust the divider value)

	uint8_t before = 0;

	NVIC_Init();
	PORT_init();           /* Configure ports */
	LPUART1_init();        /* Initialize LPUART @ 9600*/
	ADC0_init();
	/*!
	* Infinite for:
	* ========================
	*/
	for(;;)
	{
		convertAdcChan(12);                   /* Convert Channel AD12 to pot on EVB 	*/
		while(adc_complete()==0){}            /* Wait for conversion complete flag 	*/
		read_adc_chx();       /* Get channel's conversion results in mv */

		if (adcResult != before){
			LPUART1_transmit_char(adcResult);  		/* Transmit prompt character*/
//			adcResult &= 0x3F;    // clear first 2 bits
			before = adcResult;
		}

//		adcResult &= 0xC0;

		delay_ms(200);
	}
}


