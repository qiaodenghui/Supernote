import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    title: qsTr("update")
    width: 600
    height: 300
    maximumWidth: 600
    maximumHeight: 300
    minimumWidth: 600
    minimumHeight: 300
    id: updateWindow
    visible: true
    property int currentValue: 0
    property int totalValue: 100
    property string errorMsg: ""
    Connections {
        target: appManager
        function onDownloadFinished() {

        }
        function onDownloadProgress(value,total) {
             console.log("onDownloadProgress:"+value+"  "+total)
            currentValue=value
            totalValue=total
        }
        function onDownloadError(msg) {
            console.log("error msg:"+msg)
            errorMsg=msg
            updateLoader.sourceComponent=undefined
            updateLoader.sourceComponent=updateErrorTips
        }
    }


    Loader {
        id: updateLoader
        sourceComponent: updateTips
    }

    Component {
        id: updateTips
        Item {
            implicitWidth: 600
            implicitHeight: 300
            anchors.centerIn: parent
            ColumnLayout {
                Layout.margins: 20
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    elide: Text.ElideMiddle
                    font.bold: true
                    font.pixelSize: 15
                    text: qsTr("New version detected, whether to update immediately?")
                    horizontalAlignment: Text.AlignHCenter
                }
                Item {
                    Layout.fillHeight: true
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.margins: 20

                    //close
                    Rectangle {
                        width: 200
                        height: 30
                        Layout.alignment: Qt.AlignCenter
                        color: "gray"
                        radius: 4
                        Text {
                            width: parent.width
                            height: 22
                            color: "#FFFFFF"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                            text: qsTr("Close")
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("close end")
                                updateLoader.sourceComponent = undefined
                                updateWindow.close()
                            }
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    //Confirm
                    Rectangle {
                        width: 200
                        height: 30
                        Layout.alignment: Qt.AlignCenter
                        color: "gray"
                        radius: 4
                        Text {
                            width: parent.width
                            height: 22
                            color: "#FFFFFF"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                            text: qsTr("Confirm")
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("confirmMouse end")
                                appManager.updateNow()
                                updateLoader.sourceComponent = undefined
                                updateLoader.sourceComponent = updateProgress
                            }
                        }
                    }
                }
                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }



    Component {
        id: updateErrorTips
        Item {
            implicitWidth: 600
            implicitHeight: 300
            anchors.centerIn: parent
            ColumnLayout {
                Layout.margins: 20
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                }
                Label {

                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    elide: Text.ElideMiddle
                    font.bold: true
                    font.pixelSize: 15
                    horizontalAlignment: Text.AlignHCenter
                    text: errorMsg
                }
                Item {
                    Layout.fillHeight: true
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.margins: 20

                    Item {
                        Layout.fillWidth: true
                    }

                    //Confirm
                    Rectangle {
                        width: 200
                        height: 30
                        Layout.alignment: Qt.AlignCenter
                        color: "gray"
                        radius: 4
                        Text {
                            width: parent.width
                            height: 22
                            color: "#FFFFFF"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                            text: qsTr("Confirm")
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("confirmMouse end")
                                updateLoader.sourceComponent = undefined
                                updateWindow.close()
                            }
                        }
                    }
                }
                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }
    Component {
        id: updateProgress
        Item {
            implicitWidth: 600
            implicitHeight: 300
            anchors.centerIn: parent
            Column {
                anchors.centerIn: parent
                Label {
                    font.bold: true
                    font.pixelSize: 15
                    width: 560
                    text: qsTr("downloading")
                    horizontalAlignment: Text.AlignHCenter
                }
                spacing: 20
                ProgressBar {

                    id: control
                    from: 0
                    to: totalValue
                    value: currentValue
                    padding: 2

                    background: Rectangle {
                        implicitWidth: 560
                        implicitHeight: 20
                        color: "#e6e6e6"
                        radius: 10
                    }

                    contentItem: Item {
                        implicitWidth: 560
                        implicitHeight: 20

                        Rectangle {
                            width: control.visualPosition * parent.width
                            height: parent.height
                            radius: height / 2
                            color: "#17a81a"
                        }
                    }
                }
            }
        }
    }
}
