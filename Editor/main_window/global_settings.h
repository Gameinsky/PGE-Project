/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014-2016 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <QString>
#include <QMdiArea>

struct EditingSettings
{
    EditingSettings();
    //Common
    bool animationEnabled;
    bool collisionsEnabled;
    bool grid_snap;
    bool grid_override;
    QSize customGrid;
    bool grid_show;
    //World map only
    bool semiTransparentPaths;
};

struct SETTINGS_ItemDefaults {
    int npc_direction;
    int npc_generator_type;
    int npc_generator_delay;
    int warp_type;
    bool classicevents_tabs_layviz;
    bool classicevents_tabs_laymov;
    bool classicevents_tabs_autoscroll;
    bool classicevents_tabs_secset;
    bool classicevents_tabs_common;
    bool classicevents_tabs_buttons;
    bool classicevents_tabs_trigger;
};

struct SETTINGS_TestSettings {
    bool xtra_god;
    bool xtra_flyup;
    bool xtra_chuck;
    bool xtra_debug;
    bool xtra_showFPS;
    bool xtra_physdebug;
    bool xtra_worldfreedom;
    int  numOfPlayers;
    int  p1_char;
    int  p1_state;
    int  p1_vehicleID;
    int  p1_vehicleType;
    int  p2_char;
    int  p2_state;
    int  p2_vehicleID;
    int  p2_vehicleType;
};

struct SETTINGS_ScreenGrabSettings {
    enum GrabSize{
        GRAB_Fit,
        GRAB_Custom
    };
    int sizeType;
    int width;
    int height;
};

class GlobalSettings
{
public:
    static EditingSettings  LvlOpts;
    static SETTINGS_ItemDefaults LvlItemDefaults;

    //! Testing settings
    static SETTINGS_TestSettings testing;
    static SETTINGS_ScreenGrabSettings screenGrab;

    //! Current language
    static QString locale;
    //! Max limit of animated elements (on exciding, animation will be paused)
    static long animatorItemsLimit;//If level map have too many items, animation will be stopped

    //Paths
    //! Recent file-save path for Levels and World maps
    static QString savePath;
    //! Recent file-save path for NPC.txt files
    static QString savePath_npctxt;
    //! Recent open path
    static QString openPath;

    //External tools
    //! Path to SoX utility
    static QString tools_sox_bin_path;

    //Music player
    //! Play music automatically on file open
    static bool autoPlayMusic;
    //! Music volume
    static int  musicVolume;
    //! Recent state of the music playing button
    static bool recentMusicPlayingState;

    //Toolboxes visibly states
    static bool LevelItemBoxVis;
    static bool LevelSectionBoxVis;
    static bool LevelDoorsBoxVis;
    static bool LevelLayersBoxVis;
    static bool LevelEventsBoxVis;
    static bool LevelSearchBoxVis;

    static bool WorldItemBoxVis;
    static bool WorldSettingsToolboxVis;
    static bool WorldSearchBoxVis;

    static bool TilesetBoxVis;
    static bool DebuggerBoxVis;
    static bool BookmarksBoxVis;
    static bool VariablesBoxVis;

    // Editor flags
    //! Enalbe middle-mouse group duplicating feature
    static bool MidMouse_allowDuplicate;
    //! Enalbe middle-mouse quick-grabbing-for-place feature
    static bool MidMouse_allowSwitchToPlace;
    //! Enalbe middle-mouse switch to drag mode feature
    static bool MidMouse_allowSwitchToDrag;

    //Placing mode flahs
    static bool Placing_dontShowPropertiesBox;

    //!Max Limit if history elements
    static int  historyLimit;

    //!Last active file type state
    static int  lastWinType;

    static QMdiArea::ViewMode       MainWindowView;
    static QTabWidget::TabPosition  LVLToolboxPos;
    static QTabWidget::TabPosition  WLDToolboxPos;
    static QTabWidget::TabPosition  TSTToolboxPos;
    static QString                  currentTheme;

    static bool ShowTipOfDay;
};

class ConfStatus
{
//Configuration status
public:
    static long total_blocks;
    static long total_bgo;
    static long total_bg;
    static long total_npc;

    static long total_wtile;
    static long total_wpath;
    static long total_wscene;
    static long total_wlvl;

    static long total_music_lvl;
    static long total_music_wld;
    static long total_music_spc;

    static long total_sound;

    static QString configName;
    static QString defaultTheme;
    static QString configPath;

    static QString configDataPath;
    #ifdef _WIN32
    static QString SmbxEXE_Name;
    static bool    SmbxTest_By_Default;
    #endif
};

#endif // GLOBAL_SETTINGS_H
