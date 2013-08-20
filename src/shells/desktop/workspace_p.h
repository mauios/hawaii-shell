/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef WORKSPACE_P_H
#define WORKSPACE_P_H

struct hawaii_workspace;
struct hawaii_workspace_listener;

class Workspace;

class WorkspacePrivate
{
    Q_DECLARE_PUBLIC(Workspace)
public:
    WorkspacePrivate();

    void initialize(hawaii_workspace *workspace, bool active);

    Workspace *q_ptr;
    bool active;
    hawaii_workspace *workspace;

private:
    void handleActivated(hawaii_workspace *workspace);
    void handleDeactivated(hawaii_workspace *workspace);

    static const hawaii_workspace_listener m_listener;
};

#endif // WORKSPACE_P_H
