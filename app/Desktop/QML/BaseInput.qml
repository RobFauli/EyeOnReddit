import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Rectangle {
    id: input

    property alias text: digitInput.text
    property alias validator: digitInput.validator
    signal wheelMoved(real angle)

    width: digitInput.contentWidth + 6
    height: digitInput.contentHeight + 2

    border.color: "gray"
    color: "lightgray"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onWheel: {
            wheelMoved(wheel.angleDelta.y)
        }
    }

    TextInput {
        id: digitInput
        anchors.centerIn: parent

        text: "BaseInput"

        selectByMouse: true
    }
}

