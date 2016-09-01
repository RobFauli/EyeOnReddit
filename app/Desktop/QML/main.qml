import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Window {
    id: window
    title: "Eye on Reddit"
    visible: true
    width: 360
    height: 360

    // @disable-check M16
    onClosing: {
        var xcoord = x
        var ycoord = y
        settings.setValue("x", xcoord)
        settings.setValue("y", ycoord)
        settings.sync()

        // Hide window when user closes it
        close.accepted = false
        hide();
    }

    x: settings.value("x")
    y: settings.value("y")


    Rectangle {
        id: root
        anchors.fill: parent
        
        Rectangle {
            id: topToolbar
            anchors.top: parent.top
            height: settingsButton.height
            width: parent.width
            color: "grey"
            
            Button {
                id: settingsButton
                text: "Settings"
                radius: 0
                hoverEnabled: true
                basecolor: containsMouse ? "lightgrey" : "grey"
                border.color: basecolor
                
                onClicked: {
                    var component = Qt.createComponent("SettingsWindow.qml")
                    if (component.status != Component.Ready) {
                        if (component.status == Component.Error)
                            console.debug("Error: " + component.errorString()) 
                        return;
                    }
                    var settingsWindow = component.createObject(
                        root, {"x": window.x + window.width/8, "y": window.y + window.height/6})
                    settingsWindow.show()
                }
            }
        }

        RedditView {
            id: redditView
            objectName: "redditView"
            reddit: theReddit
            width: parent.width
            anchors.top: topToolbar.bottom
            anchors.bottom: bottomToolbar.top

            Component.onCompleted: {
                update()
            }
        }

        Rectangle {
            id: bottomToolbar
            width: parent.width
            height: addButton.height
            anchors.bottom: parent.bottom
            RowLayout {
                anchors.fill: parent
                Rectangle {
                    height: addButton.height
                    Layout.fillWidth: true
                    border.color: "grey"
                    TextInput {
                        id: nameInput
                        leftPadding: 4
                        anchors.fill: parent

                        text: ""

                        Text {
                            id: hint
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: parent.leftPadding
                            color: "grey"
                            text: (parent.length == 0) ? "Input the name of a subreddit" : ""

                        }
                        
                        selectByMouse: true

                        Keys.onEnterPressed: addButton.clicked()
                        Keys.onReturnPressed: addButton.clicked()
                    }
                }

                Button {
                    id: addButton
                    text: "add"
                    onClicked: {
                        theReddit.addSubreddit(nameInput.text)
                        nameInput.text = ""
                        redditView.update()
                    }
                }
            }
        }
    }

}
