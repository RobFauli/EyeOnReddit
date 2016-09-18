import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: appearanceSettings
    anchors.fill: parent

    function save() {
        return
    }

    RowLayout {
        Layout.fillWidth: true
        Text {
            text: "Appearance settings are not available yet."
        }
    }
}
