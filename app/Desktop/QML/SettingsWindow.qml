import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Window {
    id: window
    title: "Eye on Reddit: Settings"
    visible: true
    height: 400
    width: 600
    
    Rectangle {
        id: menuArea
        anchors.left: parent.left
        width: parent.width*0.2
        height: parent.height

        ListModel {
            id: menuModel
            ListElement {
                title: "General"; collapseable: true
            }
            ListElement {
                title: "Appearance"; collapseable: true;
            }
            ListElement {
                title: "Subreddits"; collapseable: true;
            }
        }

        ListView {
            id: menu
            anchors.fill: parent

            model: menuModel
            delegate: menuDelegate
            highlight: menuHighlighter
        }

        Component {
            id: menuDelegate
            Rectangle {
                //property bool subsOpen: true
                property int itemHeight: text.contentHeight + 4
                property alias currentSubredditDelegate: sublistView.currentItem
                property alias currentSubredditCount: sublistView.count
                width: ListView.view.width
                height: sublistView.visible ? itemHeight + sublistView.count*textBox.height : itemHeight
                color: "transparent"
                Rectangle {
                    id: textBox
                    height: text.contentHeight + 4
                    width: parent.width
                    color: "transparent"
                    Text {
                        id: text
                        text: title
                        anchors.verticalCenter: parent.verticalCenter
                        padding: 4
                    }
                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            menu.currentIndex = index
                            pane.state = title
                        }
                    }
                }
                SublistView {
                    id: sublistView
                    width: parent.width
                    anchors.top: textBox.bottom
                    anchors.bottom: parent.bottom

                    onCurrentItemChanged: settingsLoader.reload()

                    visible: (menu.currentIndex === 2 && title === "Subreddits")
                }

            }
        }

        Component {
            id: menuHighlighter
            Rectangle {
                color: "lightgrey"
            }
        }
    }
    Rectangle {
        id: pane
        anchors.left: menuArea.right
        width: window.width - menuArea.width
        height: window.height
        state: "General"

        states: [
            State {
                name: "General"
                PropertyChanges { target: settingsLoader; source: "General" + "Settings.qml" }
            },
            State {
                name: "Appearance"
                PropertyChanges { target: settingsLoader; source: "Appearance" + "Settings.qml" }
            },
            State {
                name: "Subreddits"
                PropertyChanges { target: settingsLoader; source: "Subreddit" + "Settings.qml" }
            }
        ]

        Loader {
            id: settingsLoader
            anchors.fill: parent

            onLoaded: {
                if (pane.state === "Subreddits") {
                    if (menu.currentItem.currentSubredditCount > 0)
                        item.subname = menu.currentItem.currentSubredditDelegate.subname
                    else // If there are no subreddits
                        item.subname = ""
                }
            }

            function reload() {
                var oldSource = source
                source = ""
                source = oldSource
            }
        }

        Row {
            id: bottomBar
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            Button {
                text: "Cancel"
                onClicked: window.close()
            }
            Button {
                text: "Apply"
                onClicked: settingsLoader.item.save()
            }
            Button {
                text: "OK"
                onClicked: {
                    settingsLoader.item.save()
                    window.close()
                }
            }
        }
    }
}
