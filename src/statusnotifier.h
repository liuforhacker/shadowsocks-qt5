/*
 * Copyright (C) 2015 Symeon Huang <hzwhuang@gmail.com>
 *
 * shadowsocks-qt5 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * shadowsocks-qt5 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libQtShadowsocks; see the file LICENSE. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef STATUSNOTIFIER_H
#define STATUSNOTIFIER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QStringList>
#include "mainwindow.h"

#ifdef Q_OS_UNIX
#undef signals
extern "C"
{
#include <libappindicator/app-indicator.h>
#include <gtk/gtk.h>
}
#define signals public
#endif

class StatusNotifier : public QObject
{
    Q_OBJECT
public:
    explicit StatusNotifier(MainWindow &w, QObject *parent = 0);
    ~StatusNotifier();

    bool isUsingAppIndicator() const;

public slots:
    void activate();
    void showNotification(const QString &);
    void onWindowVisibleChanged(bool visible);

private:
#ifdef Q_OS_UNIX
    GtkWidget *minimiseRestoreGtkItem;
    void createAppIndicator();
#endif

    QMenu systrayMenu;
    QAction *minimiseRestoreAction;
    QSystemTrayIcon systray;
    MainWindow &window;

    bool useAppIndicator;

    void createSystemTray();

    //desktop environments that need application indicator
    static const QStringList appIndicatorDE;
};

#endif // STATUSNOTIFIER_H
