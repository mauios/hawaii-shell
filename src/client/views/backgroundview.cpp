/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>
#include <QtGui/QScreen>
#include <QtGui/qpa/qplatformnativeinterface.h>
#include <QtQuick/QQuickItem>

#include <HawaiiShell/Package>
#include <HawaiiShell/PluginLoader>

#include "backgroundview.h"
#include "shellmanager.h"

BackgroundView::BackgroundView(ShellUi *corona, QScreen *screen)
    : QQuickView(new QWindow(screen))
    , m_settings(new ShellSettings(this))
{
    // Transparent color
    setColor(Qt::transparent);

    // Set custom window type
    setFlags(Qt::BypassWindowManagerHint);

    // Create platform window
    create();

    // Set surface role
    setSurfaceRole();

    // React to background change
    connect(m_settings, &ShellSettings::backgroundChanged,
            this, &BackgroundView::loadPlugin);

    // Resize view to actual size and thus resize the root object
    setResizeMode(QQuickView::SizeRootObjectToView);

    // Set geometry and react to screen geometry changes
    setGeometry(screen->geometry());
    connect(screen, &QScreen::geometryChanged,
            this, static_cast<void (QWindow::*)(const QRect &)>(&QWindow::setGeometry));
    connect(this, &BackgroundView::screenChanged, [=](QScreen *screen) {
        setGeometry(screen->geometry());
        setSurfaceRole();
    });

    // Load QML source file
    setSource(QUrl::fromLocalFile(corona->package().filePath(
                                      "views", QStringLiteral("Background.qml"))));

    // Debugging message
    qDebug() << "-> Created BackgroundView with geometry"
             << geometry();
}

void BackgroundView::loadPlugin()
{
    // Load background plugin package
    Hawaii::Shell::Package package =
            Hawaii::Shell::PluginLoader::instance()->loadPackage(
                Hawaii::Shell::PluginLoader::BackgroundPlugin);
    package.setPath(m_settings->background());

    // If the package is invalid try with the default plugin
    if (!package.isValid())
        package.setPath(QStringLiteral("org.hawaii.backgrounds.wallpaper"));

    // Now load the QML component
    QString mainScript = package.filePath("mainscript");
    rootObject()->setProperty("sourceUrl", QUrl::fromLocalFile(mainScript));
}

void BackgroundView::setSurfaceRole()
{
    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();

    struct ::wl_output *output = static_cast<struct ::wl_output *>(
                native->nativeResourceForScreen("output", screen()));
    struct ::wl_surface *surface = static_cast<struct ::wl_surface *>(
                native->nativeResourceForWindow("surface", this));

    ShellManager::instance()->shellInterface()->set_background(output, surface);
}

#include "moc_backgroundview.cpp"
