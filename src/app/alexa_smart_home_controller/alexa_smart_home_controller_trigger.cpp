/****************************************************************************
 *   Aug 22 16:36:11 2020
 *   Copyright  2020  Chris McNamee
 *   Email: chris.mcna@gmail.com
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
#include "config.h"
#include "HTTPClient.h"

#include "alexa_smart_home_controller.h"
#include "alexa_smart_home_controller_trigger.h"

#include "hardware/powermgm.h"
#include "hardware/json_psram_allocator.h"


int alexa_smart_home_controller_trigger_contact_sensor( alexa_smart_home_controller_config_t * alexa_smart_home_controller_config, char *endPointId) {
    char url[512]="";
    int httpcode = -1;

    
    snprintf( url, sizeof( url ), "http://%s/api/AlexaSmartHome/ContactSensorEvent/%s/DETECTED", MY_TTGO_WATCH_HOST, endPointId);

    HTTPClient http_client;

    http_client.useHTTP10( true );
    http_client.begin( url );
    http_client.addHeader("force-unsecure","true");
    http_client.addHeader("Authorization",alexa_smart_home_controller_config->apiKey);
    httpcode = http_client.GET();

 log_e("%s", alexa_smart_home_controller_config->apiKey );

    if ( httpcode != 200 ) {
        log_e("HTTPClient error %d %s", httpcode, url );
        http_client.end();
        return( -1 );
    }

    return( httpcode );
}

