/****************************************************************************
 *   Aug 3 12:17:11 2020
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
#include "config.h"
#include <TTGO.h>

#include "alexa_smart_home_controller.h"
#include "alexa_smart_home_controller_main.h"
#include "alexa_smart_home_controller_setup.h"
#include "alexa_smart_home_controller_trigger.h"

#include "gui/mainbar/app_tile/app_tile.h"
#include "gui/mainbar/main_tile/main_tile.h"
#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"

#include "hardware/json_psram_allocator.h"

alexa_smart_home_controller_config_t alexa_smart_home_controller_config;

uint32_t alexa_smart_home_controller_main_tile_num;
uint32_t alexa_smart_home_controller_setup_tile_num;

// app icon container
lv_obj_t *alexa_smart_home_controller_icon_cont = NULL;
lv_obj_t *alexa_smart_home_controller_icon = NULL;
lv_obj_t *alexa_smart_home_controller_icon_info = NULL;

// widget icon container
lv_obj_t *alexa_smart_home_controller_widget_cont = NULL;
lv_obj_t *alexa_smart_home_controller_widget_icon = NULL;
lv_obj_t *alexa_smart_home_controller_widget_icon_info = NULL;
lv_obj_t *alexa_smart_home_controller_widget_label = NULL;

// declare you images or fonts you need
LV_IMG_DECLARE(example_app_64px);
LV_IMG_DECLARE(example_app_48px);
LV_IMG_DECLARE(info_1_16px);

// declare callback functions
static void enter_alexa_smart_home_controller_event_cb( lv_obj_t * obj, lv_event_t event );
static void enter_alexa_smart_home_controller_widget_event_cb( lv_obj_t * obj, lv_event_t event );


void alexa_smart_home_controller_load_config( void );

// setup routine for example app
void alexa_smart_home_controller_setup( void ) {

    alexa_smart_home_controller_load_config();

    // register 2 vertical tiles and get the first tile number and save it for later use
    alexa_smart_home_controller_main_tile_num = mainbar_add_app_tile( 1, 2 );
    alexa_smart_home_controller_setup_tile_num = alexa_smart_home_controller_main_tile_num + 1;

    // create an app icon, label it and get the lv_obj_t icon container
    alexa_smart_home_controller_icon_cont = app_tile_register_app( "alexa");
    // set your own icon and register her callback to activate by an click
    // remember, an app icon must have an size of 64x64 pixel with an alpha channel
    // use https://lvgl.io/tools/imageconverter to convert your images and set "true color with alpha" to get fancy images
    // the resulting c-file can put in /app/examples/images/
    alexa_smart_home_controller_icon = lv_imgbtn_create( alexa_smart_home_controller_icon_cont, NULL );
    lv_imgbtn_set_src( alexa_smart_home_controller_icon, LV_BTN_STATE_RELEASED, &example_app_64px);
    lv_imgbtn_set_src( alexa_smart_home_controller_icon, LV_BTN_STATE_PRESSED, &example_app_64px);
    lv_imgbtn_set_src( alexa_smart_home_controller_icon, LV_BTN_STATE_CHECKED_RELEASED, &example_app_64px);
    lv_imgbtn_set_src( alexa_smart_home_controller_icon, LV_BTN_STATE_CHECKED_PRESSED, &example_app_64px);
    lv_obj_reset_style_list( alexa_smart_home_controller_icon, LV_OBJ_PART_MAIN );
    lv_obj_align( alexa_smart_home_controller_icon , alexa_smart_home_controller_icon_cont, LV_ALIGN_IN_TOP_LEFT, 0, 0 );
    lv_obj_set_event_cb( alexa_smart_home_controller_icon, enter_alexa_smart_home_controller_event_cb );

    // make app icon drag scroll the mainbar
    mainbar_add_slide_element(alexa_smart_home_controller_icon);

    // set an small info indicator at your app icon to inform the user about the state or news
    alexa_smart_home_controller_icon_info = lv_img_create( alexa_smart_home_controller_icon_cont, NULL );
    lv_img_set_src( alexa_smart_home_controller_icon_info, &info_1_16px );
    lv_obj_align( alexa_smart_home_controller_icon_info, alexa_smart_home_controller_icon_cont, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );
    lv_obj_set_hidden( alexa_smart_home_controller_icon_info, false );

    // init main and setup tile, see alexa_smart_home_controller_main.cpp and alexa_smart_home_controller_setup.cpp
    alexa_smart_home_controller_main_setup( alexa_smart_home_controller_main_tile_num );
    alexa_smart_home_controller_setup_setup( alexa_smart_home_controller_setup_tile_num );

#ifdef alexa_smart_home_controller_WIDGET
    // get an widget container from main_tile
    // remember, an widget icon must have an size of 64x64 pixel
    // total size of the container is 64x80 pixel, the bottom 16 pixel is for your label
    alexa_smart_home_controller_widget_cont = main_tile_register_widget();


    
    static const char * btnm_map[] = {"Bed", "\n",
                                        "Living", ""};
    alexa_smart_home_controller_widget_icon = lv_btnmatrix_create( alexa_smart_home_controller_widget_cont, NULL );
    lv_btnmatrix_set_map(alexa_smart_home_controller_widget_icon, btnm_map);
    lv_obj_set_size(alexa_smart_home_controller_widget_icon, 64, 64);
    
    
    
    lv_obj_reset_style_list( alexa_smart_home_controller_widget_icon, LV_OBJ_PART_MAIN );
    lv_obj_align( alexa_smart_home_controller_widget_icon , alexa_smart_home_controller_widget_cont, LV_ALIGN_IN_TOP_LEFT, 0, 0 );
    lv_obj_set_event_cb( alexa_smart_home_controller_widget_icon, enter_alexa_smart_home_controller_widget_event_cb );

    // make widget icon drag scroll the mainbar
    mainbar_add_slide_element(alexa_smart_home_controller_widget_icon);

    // set an small info icon at your widget icon to inform the user about the state or news
    alexa_smart_home_controller_widget_icon_info = lv_img_create( alexa_smart_home_controller_widget_cont, NULL );
    lv_img_set_src( alexa_smart_home_controller_widget_icon_info, &info_1_16px );
    lv_obj_align( alexa_smart_home_controller_widget_icon_info, alexa_smart_home_controller_widget_cont, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );
    lv_obj_set_hidden( alexa_smart_home_controller_widget_icon_info, false );

    // label your widget
    alexa_smart_home_controller_widget_label = lv_label_create( alexa_smart_home_controller_widget_cont , NULL);
    lv_label_set_text( alexa_smart_home_controller_widget_label, "Alexa");
    lv_obj_reset_style_list( alexa_smart_home_controller_widget_label, LV_OBJ_PART_MAIN );
    lv_obj_align( alexa_smart_home_controller_widget_label, alexa_smart_home_controller_widget_cont, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
#endif // alexa_smart_home_controller_WIDGET
}

uint32_t alexa_smart_home_controller_get_app_main_tile_num( void ) {
    return( alexa_smart_home_controller_main_tile_num );
}

uint32_t alexa_smart_home_controller_get_app_setup_tile_num( void ) {
    return( alexa_smart_home_controller_setup_tile_num );
}

void alexa_smart_home_controller_jump_to_main( void ) {
    statusbar_hide( true );
    alexa_smart_home_controller_hide_app_icon_info( true );
    #ifdef alexa_smart_home_controller_WIDGET
        alexa_smart_home_controller_hide_widget_icon_info( true );
    #endif
    mainbar_jump_to_tilenumber( alexa_smart_home_controller_main_tile_num, LV_ANIM_ON );
}

void alexa_smart_home_controller_jump_to_setup( void ) {
    statusbar_hide( true );
    mainbar_jump_to_tilenumber( alexa_smart_home_controller_setup_tile_num, LV_ANIM_ON );    
}


/*
 *
 */
static void enter_alexa_smart_home_controller_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                        alexa_smart_home_controller_jump_to_main();
                                        break;
    }    
}

/*
 *
 */
static void enter_alexa_smart_home_controller_widget_event_cb( lv_obj_t * obj, lv_event_t event ) {

    if (event == LV_EVENT_SHORT_CLICKED || event == LV_EVENT_LONG_PRESSED)
    {
        const char * txt = lv_btnmatrix_get_active_btn_text(obj);

        if(event == LV_EVENT_SHORT_CLICKED)
        {
            if(strcmp(txt, "Bed") == 0) alexa_smart_home_controller_trigger_contact_sensor(alexa_smart_home_controller_get_config(), "58478514-d038-4985-96ff-c3b3cf432259");
            else if(strcmp(txt, "Living") == 0) alexa_smart_home_controller_trigger_contact_sensor(alexa_smart_home_controller_get_config(), "0b522170-c898-4635-969e-8ebb1639d6b0");
            
        }
        else if(event == LV_EVENT_LONG_PRESSED)
        {
            if(strcmp(txt, "Bed") == 0) alexa_smart_home_controller_trigger_contact_sensor(alexa_smart_home_controller_get_config(), "ee7c6810-242f-4256-95b3-1c9e49dff30b");
            else if(strcmp(txt, "Living") == 0) alexa_smart_home_controller_trigger_contact_sensor(alexa_smart_home_controller_get_config(), "44edbf35-ecb3-43e6-a6f8-ae3577a277c3");
        }
    }
    
}

/*
 *
 */
void alexa_smart_home_controller_hide_app_icon_info( bool show ) {
    if ( alexa_smart_home_controller_icon_info == NULL )
        return;
    
    lv_obj_set_hidden( alexa_smart_home_controller_icon_info, show );
    lv_obj_invalidate( lv_scr_act() );
}

/*
 *
 */
void alexa_smart_home_controller_hide_widget_icon_info( bool show ) {
    if ( alexa_smart_home_controller_widget_icon_info == NULL )
        return;

    lv_obj_set_hidden( alexa_smart_home_controller_widget_icon_info, show );
    lv_obj_invalidate( lv_scr_act() );
}




alexa_smart_home_controller_config_t *alexa_smart_home_controller_get_config( void ) {
    return( &alexa_smart_home_controller_config );
}

/*
 *
 */
void alexa_smart_home_controller_save_config( void ) {
  

    fs::File file = SPIFFS.open( alexa_smart_home_controller_JSON_CONFIG_FILE, FILE_WRITE );

    if (!file) {
        log_e("Can't open file: %s!", alexa_smart_home_controller_JSON_CONFIG_FILE );
    }
    else {
        SpiRamJsonDocument doc( 1000 );

        doc["apiKey"] = alexa_smart_home_controller_config.apiKey;

        if ( serializeJsonPretty( doc, file ) == 0) {
            log_e("Failed to write config file");
        }
        doc.clear();
    }
    file.close();
}

/*
 *
 */
void alexa_smart_home_controller_load_config( void ) {
    if ( SPIFFS.exists( alexa_smart_home_controller_JSON_CONFIG_FILE ) ) {        
        fs::File file = SPIFFS.open( alexa_smart_home_controller_JSON_CONFIG_FILE, FILE_READ );
        if (!file) {
            log_e("Can't open file: %s!", alexa_smart_home_controller_JSON_CONFIG_FILE );
        }
        else {
            int filesize = file.size();
            SpiRamJsonDocument doc( filesize * 2 );

            DeserializationError error = deserializeJson( doc, file );
            if ( error ) {
                log_e("update check deserializeJson() failed: %s", error.c_str() );
            }
            else {
                strlcpy( alexa_smart_home_controller_config.apiKey, doc["apiKey"], sizeof( alexa_smart_home_controller_config.apiKey ) );
            }        
            doc.clear();
        }
        file.close();
    }

}