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

import QtQuick 1.1
import com.meego 1.0
import com.meego.extras 1.0
import net.venemo.ircchatter 1.0

Page {
    id: settingsPage
    tools: ToolBarLayout {
        visible: true

        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: appWindow.pageStack.pop()
        }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            onClicked: (commonMenu.status == DialogStatus.Closed) ? commonMenu.open() : commonMenu.close()
        }
    }

    onStatusChanged: {
        if (status == PageStatus.Active)
            prereleaseDialog.open();
    }

    Flickable {
        id: settingsFlickable
        anchors.fill: parent

        interactive: true
        contentWidth: parent.width
        contentHeight: settingsColumn.height + 30
        clip: true

        Column {
            id: settingsColumn
            spacing: 10
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20

            /*TitleLabel {
                text: "Display"
            }
            Label {
                text: "Misc events"
                width: parent.width
                height: miscEventsSwitch.height
                verticalAlignment: Text.AlignVCenter

                Switch {
                    id: miscEventsSwitch
                    anchors.right: parent.right
                    checked: true
                }
            }
            Label {
                text: "Timestamps"
                width: parent.width
                height: timestampsSwitch.height
                verticalAlignment: Text.AlignVCenter

                Switch {
                    id: timestampsSwitch
                    anchors.right: parent.right
                    checked: true
                }
            }
            Label {
                text: "Font size"
                width: parent.width
                height: fontSizeTumblerButton.height
                verticalAlignment: Text.AlignVCenter

                TumblerButton {
                    id: fontSizeTumblerButton
                    anchors.right: parent.right
                    text: "24"
                    width: 140

                    onClicked: fontSizeSelectionDialog.open()
                }
            }
            TitleLabel {
                text: "Send notifications for"
            }
            Label {
                text: "Messages in queries"
                width: parent.width
                height: messagesInQueriesSwitch.height
                verticalAlignment: Text.AlignVCenter

                Switch {
                    id: messagesInQueriesSwitch
                    anchors.right: parent.right
                    checked: true
                }
            }
            Label {
                text: "Messages containing your nick"
                width: parent.width
                height: messagesInQueriesSwitch.height
                verticalAlignment: Text.AlignVCenter

                Switch {
                    id: messagesContainingYourNickSwitch
                    anchors.right: parent.right
                    checked: true
                }
            }
            TitleLabel {
                text: "Configuration"
            }
            Button {
                width: parent.width - 100
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Configure servers"
            }*/
            TitleLabel {
                text: "User Configuration"
            }
            Label {
                text: "Part Message"
            }
            TextField {
                id: partField
                width: parent.width
                text: appSettings.partMessage
                inputMethodHints: Qt.ImhNoPredictiveText
            }
            Binding {
                target: appSettings
                property: "partMessage"
                value: partField.text
            }
            Label {
                text: "Kick Message"
            }
            TextField {
                id: kickField
                width: parent.width
                text: appSettings.partMessage
                inputMethodHints: Qt.ImhNoPredictiveText
            }
            Binding {
                target: appSettings
                property: "kickMessage"
                value: kickField.text
            }
        }
    }
    ScrollDecorator {
        flickableItem: settingsFlickable
    }

    WorkingSelectionDialog {
        id: fontSizeSelectionDialog
        model: ListModel { }
        titleText: "Font size"
        searchFieldVisible: false
        Component.onCompleted: {
            for (var i = 10; i <= 40; i++)
                model.append({ name: i + " pixels", pixelSize: i });
        }
    }
}
