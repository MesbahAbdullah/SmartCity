/*********************************************************/
/* Author      : Mosbah Abdallah                         */
/* Date        : 28 JAN 2021                             */
/* Version     : V01                                     */
/*********************************************************/
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_h
void ESP8266_VidInit(void);
u8   ESP8266_u8ValidateCmd();
void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password );

#endif // !ESP_INTERFACE_H
