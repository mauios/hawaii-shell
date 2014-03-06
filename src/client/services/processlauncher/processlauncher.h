/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2012-2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef PROCESSLAUNCHER_H
#define PROCESSLAUNCHER_H

#include <QtCore/QObject>

class ProcessLauncher : public QObject
{
    Q_OBJECT
public:
    ProcessLauncher(QObject *parent = 0);

    constexpr static const char *name() { return "ProcessLauncher"; }

public Q_SLOTS:
    bool launch(const QString &program,
                const QStringList &arguments = QStringList());
};

#endif // PROCESSLAUNCHER_H
