import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: generalSettings
    anchors.fill: parent
    RowLayout {
        Layout.fillWidth: true
        Rectangle {
            height: text.contentHeight
            Layout.minimumWidth: text.contentWidth
            Text {
                id: text
                anchors.centerIn: parent
                text: "Refresh interval: lala"
            }
        }
        IntegerInput {
            id: input
        }
    }
}
