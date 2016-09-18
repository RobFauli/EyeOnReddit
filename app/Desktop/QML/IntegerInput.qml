import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

BaseInput {
    property alias bottomValue: intValidator.bottom
    property alias topValue: intValidator.top

    validator: IntValidator {
        id: intValidator
        bottom: 1; top: 60
    }
    onWheelMoved: {
        text = parseFloat(text) + angle/(Math.abs(angle))
    }
}
