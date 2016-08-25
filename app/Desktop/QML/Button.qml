import QtQuick 2.7
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: root

    property alias text: buttonText.text

    width: 80
    height: buttonText.contentHeight + 2

    // Default look:
    property color basecolor: "lightgrey"
    color: mouseArea.containsPress ? Qt.lighter(basecolor) : basecolor
    border.color: Qt.lighter(basecolor)
    radius: 5

    
    signal clicked
    
    Text{
        id: buttonText
        anchors.centerIn: parent
        text: "Button"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
