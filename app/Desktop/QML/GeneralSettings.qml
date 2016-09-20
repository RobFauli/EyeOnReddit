import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: generalSettings
    anchors.fill: parent

    function refresh() {
        var seconds = theReddit.initialUpdateInterval
        var minutes = Math.floor(seconds/60)
        seconds = seconds % 60
        intervalMinutesInput.text = minutes.toString()
        intervalSecondsInput.text = seconds.toString()
    }
    Component.onCompleted: refresh()

    function save() {

    }

    Column {
        SettingsHeadline {
            text: "Initial settings for newly added subreddits:"
        }

        // Set the initial update intervals for newly added subreddits:
        RowLayout {
            Layout.fillWidth: true
            Text { text: "Update interval: " }
            IntegerInput {
                id: intervalMinutesInput
                bottomValue: 0; topValue: 99
                width: 30
            }
            Text { text: "m" }
            IntegerInput {
                id: intervalSecondsInput
                bottomValue:(parseInt(intervalMinutesInput.text) === 0) ? 1 : 0
                topValue: 59
                width: 30
            }
            Text { text: "s"}
        }
    }
}
