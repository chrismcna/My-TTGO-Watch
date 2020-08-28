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
#include "alexa_smart_home_controller_setup.h"

#include "gui/mainbar/mainbar.h"
#include "gui/statusbar.h"
#include "gui/keyboard.h"

lv_obj_t *alexa_smart_home_controller_setup_tile = NULL;
lv_style_t alexa_smart_home_controller_setup_style;

lv_obj_t *alexa_smart_home_controller_api_key_textfield = NULL;

LV_IMG_DECLARE(exit_32px);

static void exit_alexa_smart_home_controller_setup_event_cb( lv_obj_t * obj, lv_event_t event );
static void alexa_smart_home_controller_textarea_event_cb( lv_obj_t * obj, lv_event_t event );


void alexa_smart_home_controller_setup_setup( uint32_t tile_num ) {

    alexa_smart_home_controller_config_t * alexa_smart_home_controller_config = alexa_smart_home_controller_get_config();

    alexa_smart_home_controller_setup_tile = mainbar_get_tile_obj( tile_num );
    lv_style_copy( &alexa_smart_home_controller_setup_style, mainbar_get_style() );

    lv_style_set_bg_color( &alexa_smart_home_controller_setup_style, LV_OBJ_PART_MAIN, LV_COLOR_GRAY);
    lv_style_set_bg_opa( &alexa_smart_home_controller_setup_style, LV_OBJ_PART_MAIN, LV_OPA_100);
    lv_style_set_border_width( &alexa_smart_home_controller_setup_style, LV_OBJ_PART_MAIN, 0);
    lv_obj_add_style( alexa_smart_home_controller_setup_tile, LV_OBJ_PART_MAIN, &alexa_smart_home_controller_setup_style );

    lv_obj_t *exit_cont = lv_obj_create( alexa_smart_home_controller_setup_tile, NULL );
    lv_obj_set_size( exit_cont, lv_disp_get_hor_res( NULL ) , 40);
    lv_obj_add_style( exit_cont, LV_OBJ_PART_MAIN, &alexa_smart_home_controller_setup_style  );
    lv_obj_align( exit_cont, alexa_smart_home_controller_setup_tile, LV_ALIGN_IN_TOP_MID, 0, 10 );

    lv_obj_t *exit_btn = lv_imgbtn_create( exit_cont, NULL);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_RELEASED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_PRESSED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_RELEASED, &exit_32px);
    lv_imgbtn_set_src( exit_btn, LV_BTN_STATE_CHECKED_PRESSED, &exit_32px);
    lv_obj_add_style( exit_btn, LV_IMGBTN_PART_MAIN, &alexa_smart_home_controller_setup_style );
    lv_obj_align( exit_btn, exit_cont, LV_ALIGN_IN_TOP_LEFT, 10, 0 );
    lv_obj_set_event_cb( exit_btn, exit_alexa_smart_home_controller_setup_event_cb );
    
    lv_obj_t *exit_label = lv_label_create( exit_cont, NULL);
    lv_obj_add_style( exit_label, LV_OBJ_PART_MAIN, &alexa_smart_home_controller_setup_style  );
    lv_label_set_text( exit_label, "Alexa setup");
    lv_obj_align( exit_label, exit_btn, LV_ALIGN_OUT_RIGHT_MID, 5, 0 );

    lv_obj_t *alexa_smart_home_controller_api_key_cont = lv_obj_create( alexa_smart_home_controller_setup_tile, NULL );
    lv_obj_set_size(alexa_smart_home_controller_api_key_cont, lv_disp_get_hor_res( NULL ) , 40);
    lv_obj_add_style( alexa_smart_home_controller_api_key_cont, LV_OBJ_PART_MAIN, &alexa_smart_home_controller_setup_style  );
    lv_obj_align( alexa_smart_home_controller_api_key_cont, exit_cont, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20 );
    lv_obj_t *crypto_ticker_symbol_label = lv_label_create( alexa_smart_home_controller_api_key_cont, NULL);
    lv_obj_add_style( crypto_ticker_symbol_label, LV_OBJ_PART_MAIN, &alexa_smart_home_controller_setup_style  );
    lv_label_set_text( crypto_ticker_symbol_label, "Api Key");
    lv_obj_align( crypto_ticker_symbol_label, alexa_smart_home_controller_api_key_cont, LV_ALIGN_IN_LEFT_MID, 5, 0 );
    alexa_smart_home_controller_api_key_textfield = lv_textarea_create( alexa_smart_home_controller_api_key_cont, NULL);
    lv_textarea_set_text( alexa_smart_home_controller_api_key_textfield, alexa_smart_home_controller_config->apiKey );
    lv_textarea_set_pwd_mode( alexa_smart_home_controller_api_key_textfield, false);
    lv_textarea_set_one_line( alexa_smart_home_controller_api_key_textfield, true);
    lv_textarea_set_cursor_hidden( alexa_smart_home_controller_api_key_textfield, true);
    lv_obj_set_width( alexa_smart_home_controller_api_key_textfield, LV_HOR_RES /4 * 2 );
    lv_obj_align( alexa_smart_home_controller_api_key_textfield, alexa_smart_home_controller_api_key_cont, LV_ALIGN_IN_RIGHT_MID, -5, 0 );
    lv_obj_set_event_cb( alexa_smart_home_controller_api_key_textfield, alexa_smart_home_controller_textarea_event_cb );


}





static void exit_alexa_smart_home_controller_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       
                                    keyboard_hide();
                                    alexa_smart_home_controller_config_t * alexa_smart_home_controller_config = alexa_smart_home_controller_get_config();
                                    strlcpy( alexa_smart_home_controller_config->apiKey, lv_textarea_get_text( alexa_smart_home_controller_api_key_textfield ), sizeof( alexa_smart_home_controller_config->apiKey ) );
                                    alexa_smart_home_controller_save_config();
                                    alexa_smart_home_controller_jump_to_main();
                                    break;
    }
}



static void alexa_smart_home_controller_textarea_event_cb( lv_obj_t * obj, lv_event_t event ) {
    if( event == LV_EVENT_CLICKED ) {
        keyboard_set_textarea( obj );
    }
}