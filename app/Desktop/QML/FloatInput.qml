import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

// The filename DoubleInput.qml was ambiguous.
BaseInput {
    property alias bottomValue: doubleValidator.bottom
    property alias topValue: doubleValidator.top

    validator: DoubleValidator {
        id: doubleValidator
        bottom: 0.1; top: 99.0
        notation: DoubleValidator.StandardNotation
        decimals: 1
    }
    onWheelMoved: {
        var nextNumber = parseFloat(text) + angle/(Math.abs(angle) * 10)
        if (nextNumber < doubleValidator.bottom || nextNumber > doubleValidator.top)
            return
        var precision = nextNumber.toString().split('.')[0].length + 1
        var next = (nextNumber).toPrecision(precision).toString()
        if (nextNumber % 1 === 0)
            text = next + ".0"
        else
            text = next
    }
}
