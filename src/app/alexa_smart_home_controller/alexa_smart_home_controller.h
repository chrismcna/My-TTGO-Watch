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
#ifndef _alexa_smart_home_controller_H
    #define _alexa_smart_home_controller_H

    #include <TTGO.h>

    #define alexa_smart_home_controller_WIDGET // uncomment if an widget need

    #define alexa_smart_home_controller_JSON_CONFIG_FILE "/alexa.json"

    typedef struct
    {
        char apiKey[33] = "";
    } alexa_smart_home_controller_config_t;

    void alexa_smart_home_controller_setup(void);
    void alexa_smart_home_controller_hide_app_icon_info(bool show);
    void alexa_smart_home_controller_hide_widget_icon_info(bool show);
    uint32_t alexa_smart_home_controller_get_app_setup_tile_num(void);
    uint32_t alexa_smart_home_controller_get_app_main_tile_num(void);
    void alexa_smart_home_controller_jump_to_main( void ) ;
    void alexa_smart_home_controller_jump_to_setup( void );

    alexa_smart_home_controller_config_t *alexa_smart_home_controller_get_config(void);

    void alexa_smart_home_controller_save_config( void );

#endif // _alexa_smart_home_controller_H