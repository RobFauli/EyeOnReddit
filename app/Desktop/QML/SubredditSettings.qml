import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: subredditSettings
    anchors.fill: parent

    function format(n) {
        if (n % 1 === 0)
            return n + ".0"
        else
            return n
    }

    property string subname

    function save() {
        theReddit.getSubreddit(subname).scoreThreshold = parseFloat(scoreFactorInput.text)
        theReddit.getSubreddit(subname).commentsThreshold = parseFloat(numCommentsFactorInput.text)
    }

    Column {
        RowLayout {
            Layout.fillWidth: true
            Text {
                text: "Score factor: "
            }
            FloatInput {
                id: scoreFactorInput
                text: {
                    var prev = theReddit.getSubreddit(subname).scoreThreshold
                    return format(prev)
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Text {
                text: "Number of comments factor: "
            }
            FloatInput {
                id: numCommentsFactorInput
                text:  {
                    var prev = theReddit.getSubreddit(subname).commentsThreshold
                    return format(prev)
                }
            }
        }
    }
}
