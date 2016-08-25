import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Window {
    id: root
    title: "Eye on Reddit"
    visible: true
    width: 360
    height: 360

    Rectangle{
        anchors.fill: parent
//        Reddit {
//            id: myReddit
//            onPostAlert: {
//                tray.alert = true
//                var subreddit = getSubreddit(subname)
//                var post = subreddit.getPost(id)
//                tray.receivePostAlert(type, subname, post.title)
//                subreddit.setPostImportantStatus(id, true)
//            }
//        }

        RedditView {
            id: redditView
            reddit: myReddit
            width: parent.width
            height: parent.height - toolbar.height
            anchors.top: parent.top

            // For testing:
            Component.onCompleted: {
                myReddit.addSubreddit("news")
                myReddit.addSubreddit("globaloffensive")
                update()
            }
        }

        Rectangle {
            id: toolbar
            width: parent.width
            height: addButton.height
            anchors.bottom: parent.bottom
            RowLayout{
                anchors.fill: parent
                TextInput {
                    id: nameInput
                    Layout.fillWidth: true
                    height: addButton.height
                    leftPadding: 4

                    text: ""

                    Text {
                        id: hint
                        anchors.verticalCenter: parent.verticalCenter
                        leftPadding: parent.leftPadding
                        color: "lightgrey"
                        text: (parent.length == 0) ? "Input the name of a subreddit" : ""

                    }

                    Keys.onEnterPressed: addButton.clicked()
                    Keys.onReturnPressed: addButton.clicked()
                }

                Button {
                    id: addButton
                    text: "add"
                    onClicked: {
                        myReddit.addSubreddit(nameInput.text)
                        nameInput.text = ""
                        redditView.update()
                    }
                }
            }
        }
    }

}
