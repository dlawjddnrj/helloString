import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("ClientA")
    objectName: "clientA"
    id: clientA

    signal qmlSignal(string getStr)

    Rectangle {
        id: topRect
        width: 100
        height: 30
        border.color: "black"
        border.width: 1
        anchors.bottom: borderRect.top
        anchors.bottomMargin: 20
        anchors.left: borderRect.left
        anchors.leftMargin: 50
        visible: false
        Text {
            id: topRectText
            text: "Send to Enter"
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: borderRect
        width: 200
        height: 100
        border.color: "green"
        border.width: 5
        anchors.centerIn: parent

        TextInput {
            id: inputBox
            objectName: "inputBoxObj"
            anchors.centerIn: parent
            text: "send to Message"
            visible: true
            onAccepted: {
                clientA.qmlSignal(inputBox.text)
//                inputBox.clear()
            }
        }
    }

    Button {
        id: pushButton
        anchors.left: borderRect.right
        anchors.leftMargin: 30
        anchors.top: borderRect.top
        anchors.topMargin: 27
        text: "Send"
        onClicked: {
            console.log("TEST !!!")
            clientA.qmlSignal(inputBox.text)
//            inputBox.clear()
        }
    }
}
