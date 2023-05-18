import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    property string mNotePath
    property string mPageRange: pageRange.text

    signal confirm()
    signal last()
    signal open()

    id: secondViewRoot
    visible: false
    anchors.centerIn: parent

    ColumnLayout{
        anchors.centerIn: parent
        RowLayout{
            id: row1
            Layout.fillWidth: true
            TextField {
                id: notePath
                Layout.fillWidth: true
                focus: true
                text: mNotePath
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
                font.family: "微软雅黑"
                color: "white" //"#B2B2B2"
                cursorVisible: true
                selectByMouse: true //是否可以选择文本
                selectionColor: "#999999"//选中背景颜色
                placeholderText: qsTr("请输入或选择文件")
                width: 280; height: 48
                background: Rectangle {
                    border.width: 0; //border.color: "#B2B2B2"
                    radius: 4; color: "#FFFFFF" //"transparent"
                    opacity: 0.05
                    implicitHeight: 40; implicitWidth: 280
                }
            }

            //打开文件
            Rectangle {
                id: openButtonRect
                Layout.fillWidth: true
                width: 80
                height: 40
                color: "#FF5362"
                radius: 4
                Text {
                    id: openText
                    width: parent.width
                    height: 22
                    color: "#FFFFFF"
                    font.pixelSize: 16
                    font.family: "微软雅黑"
                    anchors.centerIn: parent
                    text: qsTr("打开")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    id: openMouse
                    anchors.fill: parent;
                    onClicked:open()
                }
            }
        }

        RowLayout{
            id: noteInfo
            Layout.fillWidth: true

        }

        //note path
        TextField {
            Layout.fillWidth: true
            Layout.topMargin: 20
            id: pageRange
            focus: false
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
            font.family: "微软雅黑"
            color: "white" //"#B2B2B2"
            cursorVisible: false
            selectByMouse: true //是否可以选择文本
            selectionColor: "#999999"//选中背景颜色
            placeholderText: qsTr("请输入页码例如：1-10")
            height: 40
            width: 280
            background: Rectangle {
                border.width: 0; //border.color: "#B2B2B2"
                radius: 4; color: "#FFFFFF" //"transparent"
                opacity: 0.05
                implicitHeight: 40
                implicitWidth: 280
            }
        }

        RowLayout{
            spacing: 10
            Layout.topMargin: 20

            //返回按钮
            Rectangle {
                id: lastButtonRect
                width: 280
                height: 40
                color: "#FF5362"
                radius: 4
                Text {
                    id: lastText
                    width: parent.width
                    height: 22
                    color: "#FFFFFF"
                    font.pixelSize: 16
                    font.family: "微软雅黑"
                    anchors.centerIn: parent
                    text: qsTr("上一步")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    id: lastMouse
                    anchors.fill: parent;
                    onClicked:last()
                }
            }

            //确认按钮
            Rectangle {
                id: confirmButtonRect
                width: 280
                height: 40
                Layout.alignment: Qt.AlignCenter
                color: "#FF5362"
                radius: 4
                Text {
                    id: confirmText
                    width: parent.width; height: 22
                    color: "#FFFFFF"
                    font.pixelSize: 16
                    font.family: "微软雅黑"
                    anchors.centerIn: parent
                    text: qsTr("确认")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    id: confirmMouse
                    anchors.fill: parent;
                    onClicked:confirm()
                }
            }
        }
    }
}
