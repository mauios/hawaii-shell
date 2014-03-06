/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013-2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QCoreApplication>

#include "lockscreenview.h"
#include "sessionmanager.h"
#include "shellmanager.h"

SessionManager::SessionManager(QObject *parent)
    : QObject(parent)
{
}

void SessionManager::logout()
{
    ShellManager::instance()->shellInterface()->quit();
}

void SessionManager::lock()
{
    ShellManager::instance()->shellInterface()->lock();
}

void SessionManager::unlock()
{
    ShellManager::instance()->shellInterface()->unlock();

    // Close the lock screen, this will unmap the window and
    // save some resources
    ShellManager::instance()->corona()->closeLockScreen();
}

#include "moc_sessionmanager.cpp"
