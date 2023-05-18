import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    signal fileOpen
    signal exportDocx
    signal mainPage
    signal toolsPage
    signal help
    signal about

    RowLayout {
        anchors.fill: parent
        spacing: 20
        ToolButton {
            text: qsTr("文件")
            onClicked: fileOpen()
        }
        ToolButton {
            text: "导出"
            onClicked: exportDocx()
        }
        ToolButton {
            text: "主页"
            onClicked: mainPage()
            //            elide: Label.ElideRight
            //            horizontalAlignment: Qt.AlignHCenter
            //            verticalAlignment: Qt.AlignVCenter
            //            Layout.fillWidth: true
        }
        ToolButton {
            text: "工具"
            onClicked: toolsPage()
            //            elide: Label.ElideRight
            //            horizontalAlignment: Qt.AlignHCenter
            //            verticalAlignment: Qt.AlignVCenter
            //            Layout.fillWidth: true
        }
        ToolButton {
            text: qsTr("帮助")
            onClicked: help()
            //            onClicked: menu.open()
        }
        ToolButton {
            text: qsTr("关于")
            onClicked: about()
            //            onClicked: menu.open()
        }
    }
}
