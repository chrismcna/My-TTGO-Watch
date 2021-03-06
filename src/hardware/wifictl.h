/****************************************************************************
 *   Tu May 22 21:23:51 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _WIFICTL_H
    #define _WIFICTL_H

    #include "TTGO.h"

    #define WIFICTL_DELAY               10
    #define NETWORKLIST_ENTRYS          20
    #define WIFICTL_LIST_FILE           "/wifilist.cfg"
    #define WIFICTL_CONFIG_FILE         "/wificfg.cfg"
    #define WIFICTL_JSON_CONFIG_FILE    "/wificfg.json"

    #define ESP_WPS_MODE                WPS_TYPE_PBC
    #define ESP_MANUFACTURER            "ESPRESSIF"
    #define ESP_MODEL_NUMBER            "ESP32"
    #define ESP_MODEL_NAME              "LILYGO T-WATCH2020 V1"
    #define ESP_DEVICE_NAME             "ESP STATION"

    struct networklist {
        char ssid[64]="";
        char password[64]="";
    };

    typedef struct {
        bool autoon = true;
        bool webserver = false;
    } wifictl_config_t;

    typedef void ( * WIFICTL_CALLBACK_FUNC ) ( EventBits_t event, char *msg );
    
    typedef struct {
        EventBits_t event;
        WIFICTL_CALLBACK_FUNC event_cb;
    } wifictl_event_t;

    #define WIFICTL_CONNECT                 _BV(0)
    #define WIFICTL_CONNECT_IP              _BV(1)
    #define WIFICTL_DISCONNECT              _BV(2)
    #define WIFICTL_ON                      _BV(3)
    #define WIFICTL_OFF                     _BV(4)
    #define WIFICTL_ACTIVE                  _BV(5)
    #define WIFICTL_ON_REQUEST              _BV(6)
    #define WIFICTL_OFF_REQUEST             _BV(7)
    #define WIFICTL_WPS_REQUEST             _BV(8)
    #define WIFICTL_WPS_SUCCESS             _BV(9)
    #define WIFICTL_WPS_FAILED              _BV(10)
    #define WIFICTL_SCAN                    _BV(11)
    #define WIFICTL_FIRST_RUN               _BV(12)

    /*
     * @brief setup wifi controller routine
     */
    void wifictl_setup( void );
    /*
     * @brief check if networkname known
     * 
     * @param   networkname network name to check
     */
    bool wifictl_is_known( const char* networkname );
    /*
     * @brief insert or add an new ssid/password to the known network list
     * 
     * @param ssid      pointer to an network name
     * @param password  pointer to the password
     * 
     * @return  true if was success or false if fail
     */
    bool wifictl_insert_network( const char *ssid, const char *password );
    /*
     * @brief delete ssid from network list
     * 
     * @param   ssid    pointer to an network name
     * 
     * @return  true if was success or false if fail
     */
    bool wifictl_delete_network( const char *ssid );
    /*
     * @brief switch on wifi
     */
    void wifictl_on( void );
    /*
     * @brief switch off wifi
     */
    void wifictl_off( void );
    void wifictl_set_event( EventBits_t bits );
    bool wifictl_get_event( EventBits_t bits );
    void wifictl_clear_event( EventBits_t bits );
    void wifictl_register_cb( EventBits_t event, WIFICTL_CALLBACK_FUNC blectl_event_cb );
    void wifictl_send_event_cb( EventBits_t event, char *msg );
    void wifictl_standby( void );
    void wifictl_wakeup( void );
    bool wifictl_get_autoon( void );
    void wifictl_set_autoon( bool autoon );
    void wifictl_start_wps( void );
    bool wifictl_get_webserver( void );
    void wifictl_set_webserver( bool webserver );

#endif // _WIFICTL_H