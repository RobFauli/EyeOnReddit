import QtQuick 2.7
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: root

    property alias text: buttonText.text

    width: buttonText.contentWidth + 4
    height: buttonText.contentHeight + 2
    
    signal clicked
    
    Text{
        id: buttonText
        anchors.centerIn: parent
        text: "Open"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
