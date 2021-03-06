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

#include <mainwindow.h>
#include <common_features/grid.h>
#include <common_features/item_rectangles.h>
#include <editing/edit_level/level_edit.h>
#include <PGE_File_Formats/file_formats.h>
#include <main_window/dock/lvl_events_box.h>

#include "../lvl_history_manager.h"
#include "../lvl_item_placing.h"

static long eventID=0;
void LvlScene::setEventSctSizeResizer(long event, bool enabled, bool accept)
{
    if(event >= 0)
        eventID = event;

    if( (enabled) && (m_resizeBox==nullptr) )
    {
        m_mw->on_actionSelect_triggered(); //Reset mode

        int x = m_data->events[eventID].sets[m_data->CurSection].position_left;
        int y = m_data->events[eventID].sets[m_data->CurSection].position_top;
        int w = m_data->events[eventID].sets[m_data->CurSection].position_right;
        int h = m_data->events[eventID].sets[m_data->CurSection].position_bottom;

        m_resizeBox = new ItemResizer( QSize(abs(x-w), abs(y-h)), Qt::yellow, 32 );
        this->addItem(m_resizeBox);
        m_resizeBox->setPos(x, y);
        m_resizeBox->type=1;
        m_resizeBox->_minSize = QSizeF(800, 600);
        this->setFocus(Qt::ActiveWindowFocusReason);
        //DrawMode=true;
        //MainWinConnect::pMainWin->activeLvlEditWin()->changeCursor(leveledit::MODE_Resizing);
        SwitchEditingMode(MODE_Resizing);
        m_mw->resizeToolbarVisible(true);
    }
    else
    {
        if(m_resizeBox != nullptr)
        {
            if(accept)
            {
                #ifdef _DEBUG_
                WriteToLog(QtDebugMsg, QString("SECTION RESIZE -> to %1 x %2").arg(pResizer->_width).arg(pResizer->_height));
                #endif
                long l = m_resizeBox->pos().x();
                long t = m_resizeBox->pos().y();
                long r = l + m_resizeBox->_width;
                long b = t + m_resizeBox->_height;
                //long oldL = LvlData->events[eventID].sets[LvlData->CurSection].position_left;
                //long oldR = LvlData->events[eventID].sets[LvlData->CurSection].position_right;
                //long oldT = LvlData->events[eventID].sets[LvlData->CurSection].position_top;
                //long oldB = LvlData->events[eventID].sets[LvlData->CurSection].position_bottom;
                QList<QVariant> sizeData;
                sizeData.push_back((qlonglong)m_data->CurSection);
                sizeData.push_back((qlonglong)m_data->events[eventID].sets[m_data->CurSection].position_top);
                sizeData.push_back((qlonglong)m_data->events[eventID].sets[m_data->CurSection].position_right);
                sizeData.push_back((qlonglong)m_data->events[eventID].sets[m_data->CurSection].position_bottom);
                sizeData.push_back((qlonglong)m_data->events[eventID].sets[m_data->CurSection].position_left);
                sizeData.push_back((qlonglong)t);
                sizeData.push_back((qlonglong)r);
                sizeData.push_back((qlonglong)b);
                sizeData.push_back((qlonglong)l);
                m_history->addChangeEventSettings(m_data->events[eventID].meta.array_id, HistorySettings::SETTING_EV_SECSIZE, QVariant(sizeData));

                m_data->events[eventID].sets[m_data->CurSection].position_left = l;
                m_data->events[eventID].sets[m_data->CurSection].position_right = r;
                m_data->events[eventID].sets[m_data->CurSection].position_top = t;
                m_data->events[eventID].sets[m_data->CurSection].position_bottom = b;

                //addResizeSectionHistory(LvlData->CurSection, oldL, oldT, oldR, oldB, l, t, r, b);

                //ChangeSectionBG(LvlData->sections[LvlData->CurSection].background);
                //drawSpace();
                m_data->meta.modified = true;
                m_mw->dock_LvlEvents->eventSectionSettingsSync();
            }
            delete m_resizeBox;
            m_resizeBox = NULL;
            m_mw->on_actionSelect_triggered();
            m_mw->resizeToolbarVisible(false);
        }
        m_busyMode=false;
    }
}


