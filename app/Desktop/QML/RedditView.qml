import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Item {
    id: redditView
    property Reddit reddit
    signal postAlert(string subname, string id)
    signal clearAllAlerts()

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
                color: subredditAlertView.count ? "red" : "black"
            }
            Button {
                id: collapseButton
                Layout.row: 0
                Layout.column: 2
                text: expanded ? "Collapse" : "Expand"
                onClicked: expanded = !expanded
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
                subname: name

                Layout.row: 1
                Layout.columnSpan: 4
                Layout.minimumHeight: (count < 4) ? minHeight(count) : minHeight(4)
                Layout.maximumHeight: (count == 0) ? 0 : redditListView.height/2;
                Layout.fillWidth: true

                visible: expanded

                Component.onCompleted: {
                    redditView.postAlert.connect(update)
                    redditView.clearAllAlerts.connect(cleared)
                }

                onCleared: {
                    expanded = false
                    reddit.getSubreddit(subname).clearImportantPosts()
                    fetchImportantPosts()
                    tray.setAlert(reddit.anyAlerts())
                }

                function minHeight(n) {
                    var delegateHeight = contentHeight / count
                    return (n * delegateHeight + 0.5 * delegateHeight)
                }

            }
        }
    }
}
