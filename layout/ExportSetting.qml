import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    property alias lang:control.currentValue
    property alias pageRanges: pageRange.text
    property string format:"TXT"
    signal confirm()
    signal cancel();

    ColumnLayout {
        anchors.fill: parent
        spacing: 20
        anchors.topMargin: 20
        Text {
            font.bold: true
            font.pixelSize: 25
            Layout.fillWidth: true
            text: "导出设置"
            horizontalAlignment: Text.Center
        }

        RowLayout {
            Layout.topMargin: 30
            Layout.fillWidth: true
            //                    anchors.fill: parent
            spacing: 10
            Text {
                leftPadding: 20
                text: "导出语言："
            }

            ComboBox {
                id: control
                leftPadding: 10
                textRole: "key"
                valueRole: "value"
                model: LangModel {}
                delegate: ItemDelegate {
                    //呈现标准视图项 以在各种控件和控件中用作委托
                    width: control.width

                    implicitHeight: 30
                    contentItem: Text {
                        text: key //即model中的数据
                        color: "black"
                        font: control.font
                        verticalAlignment: Text.AlignVCenter
                    }
                }
                contentItem: Text {
                    //界面上显示出来的文字
                    //                        topPadding: 5
                    //                        bottomPadding: 5
                    leftPadding: 5 //左部填充为5
                    text: control.displayText //表示ComboBox上显示的文本
                    font: control.font //文字大小
                    color: control.pressed ? "orange" : "black" //文字颜色
                    verticalAlignment: Text.AlignVCenter //文字位置
                }
                background: Rectangle {
                    //背景项
                    implicitWidth: 120
                    implicitHeight: 20
                    color: "gray"
                    border.width: 1
                    radius: 2
                }
                popup: Popup {
                    //弹出项
                    y: control.height
                    width: control.width
                    height: 100
                    padding: 1
                    focus: true

                    //istView具有一个模型和一个委托。模型model定义了要显示的数据
                    contentItem: ListView {
                        //显示通过ListModel创建的模型中的数据
                        focus: true
                        clip: true
                        model: control.popup.visible ? control.delegateModel : null
                        highlightRangeMode: ListView.StrictlyEnforceRange
                        anchors.fill: parent
                    }
                    background: Rectangle {
                        border.color: "gray"
                        radius: 2
                    }
                }

                onAccepted: {
                    console.log("onAccepted: key:"+currentText);
                    console.log("onAccepted: value:"+currentValue);
                }

                onActivated: {
                    console.log("onActivated: key:"+currentText);
                    console.log("onActivated: value:"+currentValue);
                }
            }
            Item {
                //                    implicitWidth: 100
                Layout.fillWidth: true
            }

            Text {
                text: "导出格式："
            }

            ButtonGroup {
                id: group
                exclusive: true
                buttons: col.children
            }
            Row {
                id: col
                spacing: 30
                CheckBox {
                    id: ch1
                    checked: true
                    text: qsTr("TXT")
                    onCheckedChanged: {
                          if (checked) {
                             format="TXT"
                          }
                      }
                }
                CheckBox {
                    id: ch2
                    text: qsTr("WORD")
                    onCheckedChanged: {
                          if (checked) {
                            format="WORD"
                          }
                      }
                }
                leftPadding: 10
                rightPadding: 20
            }
        }

        TextField {
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            id: pageRange
            focus: true
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12
            font.family: "微软雅黑"
            color: "black" //"#B2B2B2"
            cursorVisible: false
            selectByMouse: true //是否可以选择文本
            selectionColor: "#FFFFFF" //选中背景颜色
            placeholderText: qsTr("请输入页码例如：1-10")
            height: 40
            background: Rectangle {
                border.width: 0 //border.color: "#B2B2B2"
                radius: 4
                color: "#000000" //"transparent"
                opacity: 0.05
                implicitHeight: 30
                implicitWidth: 280
            }
        }

        RowLayout {
            spacing: 10
            Layout.fillWidth: true
            Layout.topMargin: 20
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            //返回按钮
            Rectangle {
                id: lastButtonRect
                width: 200
                height: 30
                color: "gray"
                radius: 4
                Text {
                    id: lastText
                    width: parent.width
                    height: 22
                    color: "#FFFFFF"
                    font.pixelSize: 16
                    font.family: "微软雅黑"
                    anchors.centerIn: parent
                    text: qsTr("Cancel")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    id: lastMouse
                    anchors.fill: parent
                    onClicked:{
                         console.log("confirmMouse cancel");
                        cancel()
                    }
                }
            }
            Item {
                Layout.fillWidth: true
            }
            //确认按钮
            Rectangle {
                id: confirmButtonRect
                width: 200
                height: 30
                Layout.alignment: Qt.AlignCenter
                color: "gray"
                radius: 4
                Text {
                    id: confirmText
                    width: parent.width
                    height: 22
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
                    anchors.fill: parent
                    onClicked:{
                        console.log("confirmMouse confirm");
                        confirm()
                    }
                }
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
