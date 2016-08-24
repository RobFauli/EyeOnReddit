import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import myReddit 0.1

Item {
    id: redditView
    property Reddit reddit

    ListModel {
        id: subredditListModel
    }
    function update() {
        subredditListModel.clear()
        var names = reddit.subredditNames
        for (var i = 0; i < names.length; ++i) {
            var name = names[i]
            var data = {
                "name": name,
            }
            subredditListModel.append(data)
        }
    }

    ListView {
        id: redditListView
        clip: true
        anchors.fill: parent
        model: subredditListModel
        delegate: subredditDelegate
    }
    
    Component {
        id: subredditDelegate
        GridLayout {
            id: column
            property bool expanded: false
            width: ListView.view.width
            Layout.fillWidth: true
            Text {
                id: subName
                Layout.row: 0
                Layout.column: 0
                Layout.columnSpan: 2
                Layout.fillWidth: true
                leftPadding: 4
                anchors.verticalCenter: removeButton.verticalCenter
                text: "/r/" + name
            }
            Button {
                id: collapseButton
                Layout.row: 0
                Layout.column: 2
                text: expanded ? "Collapse" : "Expand"
                onClicked: {
                    expanded = !expanded
                    if (expanded)
                        subredditAlertView.update(name)
                }
            }
            Button {
                id: removeButton
                Layout.row: 0
                Layout.column: 3
                text: "Remove"
                onClicked: {
                    reddit.removeSubreddit(name)
                    redditView.update()
                }
            }
            SubredditAlertView {
                id: subredditAlertView
                reddit: redditView.reddit
                Layout.row: 1
                Layout.columnSpan: 4
                Layout.minimumHeight: redditListView.height/3;
                Layout.maximumHeight: redditListView.height/2;
                //Layout.fillHeight: true
                Layout.fillWidth: true

                visible: expanded
            }
        }
    }
}
