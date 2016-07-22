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
#ifndef CUSTOMCOUNTER_H
#define CUSTOMCOUNTER_H

#include <QVector>
#include <QString>

#include <GlobalDefines>

class CustomCounter
{
public:
    CustomCounter();
    CustomCounter(const CustomCounter &c);
    ~CustomCounter();
    ItemTypes::itemTypes type;
    QVector<long > items;
    QString name;
    int windowType;
};

#endif // CUSTOMCOUNTER_H
