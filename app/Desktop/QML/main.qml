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

        RedditView {
            id: redditView
            objectName: "redditView"
            reddit: theReddit
            width: parent.width
            height: parent.height - toolbar.height
            anchors.top: parent.top

            Component.onCompleted: {
                update()
            }
        }

        Rectangle {
            id: toolbar
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
