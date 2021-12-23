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
        visible: true
        Text {
            id: topRectText
            text: ""
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: timerCountRect
        width: 60
        height: 30
        border.color: "black"
        border.width: 1
        anchors.top: topRect.top
        anchors.left: topRect.right
        anchors.leftMargin: 50
        Text {
            id: timerCountText
            text: qsTr("Count 0")
            anchors.centerIn: parent
        }
    }

    Connections {
        target: obj
        function onTimerChanged(count) {
            timerCountText.text = "Count " + count
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
                timer.start()
            }
        }
    }

    Timer {
        id: timer
        interval: 100
        running: false
        repeat: false
        onTriggered: {
            topRectText.text = obj.getStr()
        }
    }

    Timer {
        id: countTimer
        interval: 10000
        running: true
        repeat: true
        onTriggered: {
            obj.timerCount()
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
            clientA.qmlSignal(inputBox.text)
            timer.start()
        }
    }
}
