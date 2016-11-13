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

    function refresh() {
        var seconds = theReddit.getSubreddit(subname).updateInterval
        var minutes = Math.floor(seconds/60)
        seconds = seconds % 60
        intervalMinutesInput.text = minutes
        intervalSecondsInput.text = seconds
    }
    onSubnameChanged: refresh()

    function save() {
        if (subname != "") {
            theReddit.getSubreddit(subname).updateInterval
                    = parseInt(intervalMinutesInput) * 60 + parseInt(intervalSecondsInput)
            theReddit.getSubreddit(subname).scoreThreshold = parseFloat(scoreFactorInput.text)
            theReddit.getSubreddit(subname).commentsThreshold = parseFloat(numCommentsFactorInput.text)
        } else {
            console.debug("Tried to save subreddit, but subname was empty so did nothing. "
                          + "There may be that there are no subreddits. \n")
        }
    }

    Loader {
        sourceComponent: (subname != "") ? settingsColumn : nosubsColumn
    }

    Component {
        id: nosubsColumn
        Column {
            SettingsHeadline { text: "You have not added any subreddits." }
        }
    }

    Component {
        id: settingsColumn
        Column {
            SettingsHeadline { text: "Settings for /r/" + subname + ":" }
            RowLayout {
                Layout.fillWidth: true
                Text { text: "Update interval: " }
                IntegerInput {
                    id: intervalMinutesInput;
                    bottomValue: 0; topValue: 99
                    width: 30
                }
                Text { text: "m" }
                IntegerInput {
                    id: intervalSecondsInput;
                    bottomValue: 0; topValue: 59
                    width: 30
                }
                Text { text: "s" }
            }

            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "Score factor: "
                }
                FloatInput {
                    id: scoreFactorInput
                    width: 30
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
                    width: 30
                    text:  {
                        var prev = theReddit.getSubreddit(subname).commentsThreshold
                        return format(prev)
                    }
                }
            }
        }
    }
}
