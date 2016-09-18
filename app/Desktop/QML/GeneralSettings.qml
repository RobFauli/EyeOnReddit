import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: generalSettings
    anchors.fill: parent

    function save() {

    }

    RowLayout {
        Layout.fillWidth: true
        Text {
            text: "General settings are not available yet."
        }

        /*
        Text {
            Layout.minimumWidth: contentWidth
            text: "Default refresh interval for subreddits: "
        }
        IntegerInput {
            id: input
        }
        Text {
            text: "seconds"
        }
        */
    }
}
