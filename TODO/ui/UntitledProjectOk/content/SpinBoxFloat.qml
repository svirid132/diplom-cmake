import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    SpinBox {
        id: spinbox
        from: 0
        value: 110
        to: 100 * 100
        stepSize: 100
        anchors.centerIn: parent
        editable: true

        property int decimals: 2
        property real realValue: value / 100

        validator: DoubleValidator {
            bottom: Math.min(spinbox.from, spinbox.to)
            top:  Math.max(spinbox.from, spinbox.to)
        }

        textFromValue: function(value, locale) {
            return Number(value / 100).toLocaleString(locale, 'f', spinbox.decimals)
        }

        valueFromText: function(text, locale) {
            console.log(Number.fromLocaleString(locale, text) * 100);
            return Number.fromLocaleString(locale, text) * 100
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}
}
##^##*/
