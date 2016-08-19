import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
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
            id: reddit
            onSubredditNamesChanged: {
            }
        }

        ListModel {
            id: subredditListModel
        }

        ListView {
            anchors.fill: parent
            model: subredditListModel
            delegate: Text {
                text: name
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
                        reddit.addSubreddit(nameInput.text)
                        subredditListModel.clear()
                        for (var i = 0; i < reddit.subredditNames.length; ++i) {
                            var data = {
                                "name": reddit.subredditNames[i]
                            }
                            subredditListModel.append(data)
                            console.log(subredditListModel.rowCount())
                        }

                    }
                }
            }
        }
    }

}
