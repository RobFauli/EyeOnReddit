import QtQuick 2.5
import QtQuick.Controls 2.0

ApplicationWindow {
    id: window
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello Android")
        anchors.centerIn: parent
    }
}
