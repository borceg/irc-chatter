
// This file is part of IRC Chatter, the first IRC Client for MeeGo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2012, Timur Kristóf <venemo@fedoraproject.org>

#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

class Notifier : public QObject
{
    Q_OBJECT

public:
    explicit Notifier(QObject *parent = 0);
    
public slots:
    void notify(const QString &text);
    
};

#endif // NOTIFIER_H
