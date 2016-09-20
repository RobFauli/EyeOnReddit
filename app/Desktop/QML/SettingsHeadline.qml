import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

RowLayout {
    property alias text: textComponent.text
    Text {
        id: textComponent
        font.underline: true
        font.pointSize: 13
        bottomPadding: 5
    }
}
