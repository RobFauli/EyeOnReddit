import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import myReddit 0.1

Item {
    id: subFrontpageView
    property Reddit reddit

    ListModel {
        id: subFrontpageListModel

    }

    function update(name) {
        var sub = reddit.getSubreddit(name)
        var titles = sub.frontpageTitles
        var domains = sub.frontpageDomains
        var scores = sub.frontpageScores
        var num_comments = sub.frontpageCommentCounts
        for (var i = 0; i < titles.length; ++i) {
            var data = {
                "title": titles[i],
                "domain": domains[i],
                "score": scores[i],
                "num_comments": num_comments[i],
            }
            subFrontpageListModel.append(data)
        }
    }

    ListView {
        id: subFrontPageView
        anchors.fill: parent
        clip: true

        model: subFrontpageListModel
        delegate: Text {
            text: title
        }
    }
}
