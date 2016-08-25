import QtQuick 2.7
import QtQuick.Layouts 1.3
import myReddit 0.1

Item {
    id: subredditAlertView
    property Reddit reddit

    function update(subName) {
        subredditAlertsModel.clear()
        var subreddit = reddit.getSubreddit(subName)
        var importantPostIds = subreddit.importantPostIds
        for (var i = 0; i<importantPostIds.length; ++i) {
            var post = subreddit.getPost(importantPostIds[i])
            var data = {
                "title": post.title,
                "permalink": post.permalink
            }
            subredditAlertsModel.append(data)
        }
    }

    ListModel {
        id: subredditAlertsModel

    }

    ListView {
        id: subFrontPageView
        anchors.fill: parent
        clip: true

        spacing: 4

        model: subredditAlertsModel
        delegate: subFrontPageTitleDelegate
    }

    Component {
        id: subFrontPageTitleDelegate
        GridLayout {
            property int collapseAtWidth: 200
            width: ListView.view.width
            Layout.fillWidth: true
            Rectangle {
                Layout.row: 0
                Layout.column: 0
                Layout.fillWidth: true
                Layout.minimumHeight: titleText.contentHeight + 4
                Text {
                    id: titleText
                    clip: true
                    width: parent.width
                    padding: 8
                    anchors.verticalCenter: parent.verticalCenter
                    text: title
                    color: "blue"
                }
            }
            Button {
                id: openButton
                Layout.row: 0
                Layout.column: 1
                onClicked: {
                    var url = permalink
                    Qt.openUrlExternally(url)
                }
            }
        }
    }
}
