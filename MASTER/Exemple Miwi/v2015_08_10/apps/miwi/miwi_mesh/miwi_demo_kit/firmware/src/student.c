//STUDENT

#include "student.h"
#include "system.h"
#include "codes library.h"
#include "system_config.h"
#include "miwi/miwi_api.h"

void Student(void)
{
    uint8_t switch_val;
    LCD_Erase();
    sprintf((char *)&(LCDText), (char*)" STUDENT DEVICE ");
    
    while(true)
    {
        sprintf((char *)&(LCDText[16]), (char*)"Address: %02x%02x", myShortAddress.v[1], myShortAddress.v[0]);
        LCD_Update();
        switch_val = BUTTON_Pressed();
        if(switch_val == SW1)
        {
            LED1 = 1;
            MiApp_FlushTx();
            MiApp_WriteData(PROJECTOR_ON);
            MiApp_WriteData(myShortAddress.v[0]);
            MiApp_WriteData(myShortAddress.v[1]);
            MiApp_BroadcastPacket(false);
            delay_ms(500);
            LED1 = 0;
        }
        if(switch_val == SW2)
        {
            LED1 = 1;
            MiApp_FlushTx();
            MiApp_WriteData(PROJECTOR_OFF);
            MiApp_WriteData(myShortAddress.v[0]);
            MiApp_WriteData(myShortAddress.v[1]);
            MiApp_BroadcastPacket(false);
            delay_ms(500);
            LED1 = 0;
        }
    }
}
    	    


 
/*     
            
            
            
    while(true)
    {
        
        bool Run_Demo = true;
        bool Tx_Packet = true;
        uint8_t rssi = 0;
        uint8_t Pkt_Loss_Cnt = 0;
        MIWI_TICK tick1, tick2;
        uint8_t switch_val;
        uint8_t pktCmd = 0;

        //*******************************************************************
        // Dispaly Door Unlock Splach Screen
        //*******************************************************************
        LCD_Display((char *)"   Microchip       Door Unlock  ", 0, true);

        //*******************************************************************
        // Read Start tickcount
        //*******************************************************************	
        tick1 = MiWi_TickGet();

        while(Run_Demo)
        {	
            //*******************************************************************
            // Read current tickcount
            //*******************************************************************
            tick2 = MiWi_TickGet();

            // Send a Message
            //((MiWi_TickGetDiff(tick2,tick1) > (ONE_SECOND * TX_PKT_INTERVAL)))
            if((MiWi_TickGetDiff(tick2,tick1) > (ONE_MILLI_SECOND * 1000)))
            {
                //LCD_Erase();

                if(Tx_Packet)
                {	
                        //LCD_Display((char *)"Checking Signal Strength...", 0, true);

                    MiApp_FlushTx();

                    MiApp_WriteData(RANGE_PKT);
                    MiApp_WriteData(0x4D);
                    MiApp_WriteData(0x69);
                    MiApp_WriteData(0x57);
                    MiApp_WriteData(0x69);
                    MiApp_WriteData(0x20);
                    MiApp_WriteData(0x52);
                    MiApp_WriteData(0x6F);
                    MiApp_WriteData(0x63);
                    MiApp_WriteData(0x6B);
                    MiApp_WriteData(0x73);
                    MiApp_WriteData(0x21);

                    if( MiApp_UnicastConnection(ConnectionEntry, false) == false )
                        Pkt_Loss_Cnt++;
                    else
                        Pkt_Loss_Cnt = 0;

                    Tx_Packet = false;
                }

                else
                {	      	
                    if(Pkt_Loss_Cnt < 1)
                    {           		
                        if(rssi > 50) //200)
                        {
                            //sprintf((char *)&LCDText, (char*)" Unlock Door ?  SW1:YES   SW2:NO");
                            LED0 = 1;
                            LED1 = 0;
                            LED2 = 0;
                            /*
                            switch_val = BUTTON_Pressed();
                            if(switch_val == SW1)
                            {
                                LED0 = 1;
                                LED1 = 1;
                                LED2 = 1;
                            }
                            */
/*
                        }

                        else //if(switch_val == SW2)
                        {
                            //*******************************************************************
                            // Send Exit Demo Request Packet and exit Door Unlock
                            //*******************************************************************
                            LED0 = 0;
                            LED1 = 0;
                            LED2 = 1;
                            MiApp_FlushTx();    
                            MiApp_WriteData(EXIT_PKT);
                            MiApp_UnicastConnection(ConnectionEntry, false);


                            tick1 = MiWi_TickGet();
                            // Wait for ACK Packet
                            while(Run_Demo)
                            {
                                if(MiApp_MessageAvailable())
                                {
                                    if(rxMessage.Payload[0] == ACK_PKT)          
                                        Run_Demo = false;

                                    MiApp_DiscardMessage();
                                }
                                if ((MiWi_TickGetDiff(tick2,tick1) > (ONE_SECOND * EXIT_DEMO_TIMEOUT)))
                                    Run_Demo = false;

                                tick2 = MiWi_TickGet();
                            }    
                        }    
                    }



                        /*
                        else if(rssi < 201)
                        {
                            sprintf((char *)&LCDText, (char*)" Get Closer to      the Door    ");
                            LED0 = 0;
                            LED1 = 1;
                            LED2 = 0;
                            switch_val = BUTTON_Pressed();
                            if((switch_val == SW1) || (switch_val == SW2))
                            {
                                //*******************************************************************
                                // Send Exit Demo Request Packet and exit Door Unlock
                                //******************************************************************
                                MiApp_FlushTx();    
                                MiApp_WriteData(EXIT_PKT);
                                MiApp_UnicastConnection(ConnectionEntry, false);

                                LCD_BacklightON();
                                LCD_Display((char *)"   Exiting....     Door Unlock  ", 0, true);
                                LCD_BacklightOFF();

                                tick1 = MiWi_TickGet();
                                // Wait for ACK Packet
                                while(Run_Demo)
                                {
                                    if(MiApp_MessageAvailable())
                                    {
                                        if(rxMessage.Payload[0] == ACK_PKT)          
                                            Run_Demo = false;

                                        MiApp_DiscardMessage();
                                    }
                                    if ((MiWi_TickGetDiff(tick2,tick1) > (ONE_SECOND * EXIT_DEMO_TIMEOUT)))
                                        Run_Demo = false;

                                    tick2 = MiWi_TickGet();
                                }    
                            }    
                        }

                        // Convert to dB
                        //rssi = RSSIlookupTable[rssi];
                        //sprintf((char *)&(LCDText[16]), (char*)"Rcv RSSI: %03d", rssi);
                    }  

                    */
/*
                    LCD_Update();
                    Tx_Packet = true;

                } 	     
                //*******************************************************************
                // Read New Start tickcount
                //*******************************************************************
                tick1 = MiWi_TickGet(); 

            }

            // Check if Message Available
            if(MiApp_MessageAvailable())
            {
                pktCmd = rxMessage.Payload[0];
                if(pktCmd == EXIT_PKT)
                {
                MiApp_DiscardMessage();
                MiApp_FlushTx();
                MiApp_WriteData(ACK_PKT);
                MiApp_UnicastConnection(ConnectionEntry, false);
                Run_Demo = false;
                LCD_BacklightON();
                LCD_Display((char *)"   Exiting....     Door Unlock  ", 0, true);
                LCD_BacklightOFF();


                }
                else if(rxMessage.Payload[0] == RANGE_PKT)
                {
                    // Get RSSI value from Recieved Packet
                    rssi = rxMessage.PacketRSSI;
                    #if defined(MRF89XA)
                        rssi = rssi<<1;
                    #endif
                    // Disguard the Packet so can recieve next
                    MiApp_DiscardMessage();
                }
                else
                    MiApp_DiscardMessage(); 
            }

            /*
            // Check if  Switch Pressed
            switch_val = BUTTON_Pressed();

            if((switch_val == SW1) || (switch_val == SW2))
            {
                /*******************************************************************
                // Send Exit Demo Request Packet and exit Door Unlock
                /*******************************************************************
                MiApp_FlushTx();    
                MiApp_WriteData(EXIT_PKT);
                MiApp_UnicastConnection(ConnectionEntry, false);

                LCD_BacklightON();
                LCD_Display((char *)"   Exiting....     Door Unlock  ", 0, true);
                LCD_BacklightOFF();

                tick1 = MiWi_TickGet();
                // Wait for ACK Packet
                while(Run_Demo)
                {
                    if(MiApp_MessageAvailable())
                    {
                        if(rxMessage.Payload[0] == ACK_PKT)          
                            Run_Demo = false;

                        MiApp_DiscardMessage();
                    }
                    if ((MiWi_TickGetDiff(tick2,tick1) > (ONE_SECOND * EXIT_DEMO_TIMEOUT)))
                        Run_Demo = false;

                    tick2 = MiWi_TickGet();
                }    
            }*//*
        }
    }
}
    	  
*/