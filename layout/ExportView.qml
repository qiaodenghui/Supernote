import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import Supernote 1.0

Item {
    property int page: 0
    property int allPage: 0
    property int dialogStatus: 0
    property string exportPath: ""
    property string lang: "en_US"
    property int pageIndex: 0
    Connections {
        target: noteInfo
        function onProgress(value) {
            console.log("Connections onProgress value:" + value)
            page = value
            pageIndex = pageIndex + 1
        }
        function onResult(ret, docxPath) {
            console.log("Connections onResult ret:" + ret)
            exportPath = docxPath
            dialogStatus = 1
            progressViewLoader.sourceComponent = undefined
            progressViewLoader.sourceComponent = resultComponent
        }
        function onPageInfo(firstPage, all) {
            console.log("firstPage:" + firstPage + " all:" + all)
            allPage = all
            page = firstPage - 1
            pageIndex = 0
        }
    }

    function showView() {
        exportPath = ""
        dialogStatus = 0
        pageIndex = 0
        allPage = 0
        progressViewLoader.sourceComponent = selectComponent
        progressDialog.open()
    }

    Component {
        id: exportComponent
        Item {
            implicitWidth: 600
            implicitHeight: 300
            anchors.centerIn: parent
            Column {
                anchors.centerIn: parent
                Label {
                    id: progressLabel
                    font.bold: true
                    font.pixelSize: 15
                    width: 560
                    text: qsTr("Exporting page "+page)
                    horizontalAlignment: Text.AlignHCenter
                }
                spacing: 20
                ProgressBar {

                    id: control
                    from: 0
                    to: allPage
                    value: pageIndex
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

    Component {
        id: resultComponent
        Item {
            implicitWidth: 600
            implicitHeight: 300
            ColumnLayout {
                Layout.margins: 20
                anchors.fill: parent
                Item {
                    Layout.fillHeight: true
                }
                Label {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                    id: resultLabel
                    elide: Text.ElideMiddle
                    font.bold: true
                    font.pixelSize: 15
                    text: qsTr("Successfully exported to " + exportPath)
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
                            id: close
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
                                progressDialog.close()
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
                            id: confirmText
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
                                noteInfo.openExplorer(exportPath)
                                progressViewLoader.sourceComponent = undefined
                                progressDialog.close()
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: selectComponent
        ExportSetting {
            id: exportSetting
            width: 600
            height: 300
            Connections {
                target: exportSetting
                function onConfirm() {
                    console.log("exportSetting onConfirm")
                    progressViewLoader.sourceComponent = undefined
                    progressViewLoader.sourceComponent = exportComponent
                    noteInfo.startExport(exportSetting.format,
                                         exportSetting.pageRanges,
                                         exportSetting.lang)
                }
                function onCancel() {
                    console.log("exportSetting onCancel")
                    progressDialog.close()
                }
            }
        }
    }

    Popup {
        width: 600
        height: 300
        id: progressDialog
        closePolicy: Popup.NoAutoClose
        //        onRejected: progressViewLoader.sourceComponent = undefined
        //        onAccepted: {
        //            noteInfo.openExplorer(exportPath)
        //            progressViewLoader.sourceComponent = undefined
        //        }
        modal: false
        //        title: "Export To Docx"
        contentItem: Loader {
            id: progressViewLoader
        }
        //        footer: DialogButtonBox {
        //            Button {
        //                text: qsTr(dialogStatus == 0 ? "Cancel" : "Ok")
        //                DialogButtonBox.buttonRole: dialogStatus == 0 ? DialogButtonBox.RejectRole : DialogButtonBox.AcceptRole
        //            }
        //        }
    }
    //    Dialog {
    //        height: 300
    //        id: progressDialog
    //        closePolicy: Popup.NoAutoClose
    //        onRejected: progressViewLoader.sourceComponent = undefined
    //        onAccepted: {
    //            noteInfo.openExplorer(exportPath)
    //            progressViewLoader.sourceComponent = undefined
    //        }
    //        modal: true
    //        title: "Export To Docx"
    //        contentItem: Loader {
    //            id: progressViewLoader
    //        }
    //        footer: DialogButtonBox {
    //            Button {
    //                text: qsTr(dialogStatus == 0 ? "Cancel" : "Ok")
    //                DialogButtonBox.buttonRole: dialogStatus == 0 ? DialogButtonBox.RejectRole : DialogButtonBox.AcceptRole
    //            }
    //        }
    //    }
}
