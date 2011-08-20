// This file is part of IRC Chatter, the first IRC Client for MeeGo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2011, Timur Kristóf <venemo@fedoraproject.org>
// Copyright (C) 2011, Hiemanshu Sharma <mail@theindiangeek.in>

#include <QtCore>

#include "appsettings.h"

#define APPSETTING_SETTINGSVERSION "SettingsVersion"
#define APPSETTING_SERVERSETTINGS "ServerSettings"
#define APPSETTING_USERNICKNAME "UserNickname"
#define APPSETTING_USERIDENT "UserIdent"
#define APPSETTING_USERREALNAME "UserRealName"
#define APPSETTING_PARTMESSAGE "PartMessage"
#define APPSETTING_KICKMESSAGE "KickMessage"
#define APPSETTING_FONTSIZE "FontSize"

AppSettings::AppSettings(QObject *parent) :
    QObject(parent),
    _areSettingsDeleted(false),
    _serverSettings(new QObjectListModel<ServerSettings>(this))
{
    // Checking for settings version

    int savedSettingsVersion = _backend.value(APPSETTING_SETTINGSVERSION, 0).toInt();

    if (savedSettingsVersion < APPSETTINGS_VERSION)
    {
        // Clearing all settings if the saved version is different than current one
        _backend.clear();
        _backend.setValue(APPSETTING_SETTINGSVERSION, APPSETTINGS_VERSION);

        _areSettingsDeleted = true;
        emit areSettingsDeletedChanged();
    }
    else
    {
        // Deserializing server settings

        QByteArray array = _backend.value(APPSETTING_SERVERSETTINGS).toByteArray();
        QDataStream stream(array);
        int n;
        stream >> n;
        for (int i = 0; i < n; i++)
        {
            ServerSettings *server = new ServerSettings((QObject*)this);
            stream >> (*server);
            _serverSettings->addItem(server);
        }
    }
}

QString AppSettings::userNickname() const
{
    return _backend.value(APPSETTING_USERNICKNAME).toString();
}

void AppSettings::setUserNickname(const QString &value)
{
    _backend.setValue(APPSETTING_USERNICKNAME, value);
}

QString AppSettings::userIdent() const
{
    return _backend.value(APPSETTING_USERIDENT).toString();
}

void AppSettings::setUserIdent(const QString &value)
{
    _backend.setValue(APPSETTING_USERIDENT, value);
}

QString AppSettings::userRealName() const
{
    return _backend.value(APPSETTING_USERREALNAME).toString();
}

void AppSettings::setUserRealName(const QString &value)
{
    _backend.setValue(APPSETTING_USERREALNAME, value);
}

QString AppSettings::kickMessage() const
{
    return _backend.value(APPSETTING_KICKMESSAGE).toString();
}

void AppSettings::setKickMessage(const QString &value)
{
    _backend.setValue(APPSETTING_KICKMESSAGE, value);
}

QString AppSettings::partMessage() const
{
    return _backend.value(APPSETTING_PARTMESSAGE).toString();
}

void AppSettings::setPartMessage(const QString &value)
{
    _backend.setValue(APPSETTING_PARTMESSAGE, value);
}

quint16 AppSettings::fontSize() const
{
    return _backend.value(APPSETTING_FONTSIZE).toUInt();
}

void AppSettings::setFontSize(const quint16 &value)
{
    _backend.value(APPSETTING_FONTSIZE, value);
}

QObjectListModel<ServerSettings> *AppSettings::serverSettings()
{
    return _serverSettings;
}

void AppSettings::saveServerSettings()
{
    QByteArray array;
    QBuffer buffer(&array);
    QDataStream stream(&buffer);
    buffer.open(QBuffer::WriteOnly);
    stream << _serverSettings->rowCount();
    foreach (ServerSettings *server, _serverSettings->getList())
        stream << (*server);
    buffer.close();
    _backend.setValue(APPSETTING_SERVERSETTINGS, array);
}

void AppSettings::appendServerSettings(ServerSettings *server)
{
    _serverSettings->addItem(server);
}

int AppSettings::serverSettingsCount() const
{
    return _serverSettings->rowCount();
}
