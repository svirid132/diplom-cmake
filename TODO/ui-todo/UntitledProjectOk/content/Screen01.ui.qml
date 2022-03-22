import QtQuick
import QtQuick.Controls
import UntitledProjectOk
import QtQuick.Studio.Components 1.0

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello UntitledProjectOk")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }

    Grid {
        id: grid
        height: parent.height

        columns: 2
        spacing: 2

        Label {
            id: label
            text: qsTr("Label")
        }

        TextField {
            id: textField
            placeholderText: qsTr("Text Field")
        }

        Label {
            id: label1
            text: qsTr("Label")
        }

        SpinBoxFloat {
            x: 50
            y: 50

        }
    }
}
