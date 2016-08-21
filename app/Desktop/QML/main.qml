import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import myReddit 0.1

ApplicationWindow {
    id: root
    title: "IntelliReddit"
    visible: true
    width: 360
    height: 360

    Rectangle{
        anchors.fill: parent
        Reddit {
            id: myReddit
        }

        RedditView {
            id: redditView
            reddit: myReddit
            anchors.fill: parent

            // For testing:
            Component.onCompleted: {
                myReddit.addSubreddit("news")
                myReddit.addSubreddit("globaloffensive")
                update()
            }
        }

        ToolBar {
            width: parent.width
            anchors.bottom: parent.bottom
            RowLayout{
                anchors.fill: parent
                TextField {
                    id: nameInput
                    placeholderText: "subname"
                }

                ToolButton {
                    text: "add"
                    onClicked: {
                        myReddit.addSubreddit(nameInput.text)
                        redditView.update()
                    }
                }
            }
        }
    }

}
