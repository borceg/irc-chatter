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
// Copyright (C) 2011-2012, Timur Kristóf <venemo@fedoraproject.org>
// Copyright (C) 2011, Hiemanshu Sharma <mail@theindiangeek.in>

#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QDataStream>

#include "helpers/util.h"

#ifndef DEFAULT_SERVER
#define DEFAULT_SERVER "irc.freenode.net"
#endif

#ifndef DEFAULT_CHANNELS
#define DEFAULT_CHANNELS "#irc-chatter"
#endif

class ServerSettings : public QObject
{
    Q_OBJECT
    GENPROPERTY_F(QString, _serverUrl, serverUrl, setServerUrl, serverUrlChanged)
    Q_PROPERTY(QString serverUrl READ serverUrl WRITE setServerUrl NOTIFY serverUrlChanged)
    GENPROPERTY_F(quint16, _serverPort, serverPort, setServerPort, serverPortChanged)
    Q_PROPERTY(quint16 serverPort READ serverPort WRITE setServerPort NOTIFY serverPortChanged)
    GENPROPERTY_F(bool, _serverSSL, serverSSL, setServerSSL, serverSSLChanged)
    Q_PROPERTY(bool serverSSL READ serverSSL WRITE setServerSSL NOTIFY serverSSLChanged)
    GENPROPERTY_F(QString, _serverPassword, serverPassword, setServerPassword, serverPasswordChanged)
    Q_PROPERTY(QString serverPassword READ serverPassword WRITE setServerPassword NOTIFY serverPasswordChanged)
    GENPROPERTY_F(QStringList, _autoJoinChannels, autoJoinChannels, setAutoJoinChannels, autoJoinChannelsChanged)
    Q_PROPERTY(QStringList autoJoinChannels READ autoJoinChannels WRITE setAutoJoinChannels NOTIFY autoJoinChannelsChanged)
    Q_PROPERTY(QString autoJoinChannelsInPlainString READ autoJoinChannelsInPlainString WRITE setAutoJoinChannelsInPlainString NOTIFY autoJoinChannelsChanged)
    GENPROPERTY_F(QString, _userNickname, userNickname, setUserNickname, userNicknameChanged)
    Q_PROPERTY(QString userNickname READ userNickname WRITE setUserNickname NOTIFY userNicknameChanged)
    GENPROPERTY_F(QString, _userIdent, userIdent, setUserIdent, userIdentChanged)
    Q_PROPERTY(QString userIdent READ userIdent WRITE setUserIdent NOTIFY userIdentChanged)
    GENPROPERTY_F(QString, _userRealName, userRealName, setUserRealName, userRealNameChanged)
    Q_PROPERTY(QString userRealName READ userRealName WRITE setUserRealName NOTIFY userRealNameChanged)
    GENPROPERTY_F(bool, _shouldConnect, shouldConnect, setShouldConnect, shouldConnectChanged)
    Q_PROPERTY(bool shouldConnect READ shouldConnect WRITE setShouldConnect NOTIFY shouldConnectChanged)

    GENPROPERTY_F(bool, _isConnecting, isConnecting, setIsConnecting, isConnectingChanged)
    Q_PROPERTY(bool isConnecting READ isConnecting WRITE setIsConnecting NOTIFY isConnectingChanged)
    GENPROPERTY_F(bool, _isConnected, isConnected, setIsConnected, isConnectedChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)

    friend QDataStream &operator>>(QDataStream &stream, ServerSettings &server);

public:
    explicit ServerSettings(QObject *parent = 0, const QString &url = DEFAULT_SERVER, const quint16 &port = 6667, bool ssl = false, const QString &password = QString(), const QStringList &autoJoinChannels = QStringList());
    QString autoJoinChannelsInPlainString() const;
    void setAutoJoinChannelsInPlainString(const QString &value);
    void addAutoJoinChannel(const QString &channelName);
    void removeAutoJoinChannel(const QString &channelName);
    void save();

signals:
    void serverUrlChanged();
    void serverPasswordChanged();
    void autoJoinChannelsChanged();
    void serverPortChanged();
    void serverSSLChanged();
    void userNicknameChanged();
    void userIdentChanged();
    void userRealNameChanged();
    void shouldConnectChanged();

    void isConnectingChanged();
    void isConnectedChanged();

private slots:
    void backendAsksForPassword(QString *password);

};

QDataStream &operator<<(QDataStream &stream, const ServerSettings &server);
QDataStream &operator>>(QDataStream &stream, ServerSettings &server);

#endif // SERVERSETTINGS_H
