/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "npc_dialog/npcdialog.h"
#include "music_player.h"

////////////////////////New files templates///////////////////////////

void MainWindow::on_actionNewNPC_config_triggered()
{

    NpcDialog * npcList = new NpcDialog(&configs);
    npcList->setWindowFlags (Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    npcList->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, npcList->size(), qApp->desktop()->availableGeometry()));
    npcList->setState(0, 1);
    npcList->setWindowTitle(tr("Create new NPC.txt configuration file"));
    if(npcList->exec()==QDialog::Accepted)
    {
        npcedit *child = createNPCChild();
        child->newFile( npcList->selectedNPC);
        child->show();
    }

}



void MainWindow::on_actionNewLevel_triggered()
{
    leveledit *child = createLvlChild();
    child->newFile(configs, LvlOpts);
    child->show();
    updateMenus(true);
    SetCurrentLevelSection(0);
    on_actionSelect_triggered();
    setDoorsToolbox();
    setLayersBox();

    if(autoPlayMusic) ui->actionPlayMusic->setChecked(true);
    LvlMusPlay::musicForceReset=true; //reset musics
    on_actionPlayMusic_triggered(ui->actionPlayMusic->isChecked());
}


void MainWindow::on_actionNewWorld_map_triggered()
{
    QMessageBox::information(this, "Comming soon", "World map editor in this version is not implemented", QMessageBox::Ok);
}
