import QtQuick
import Supernote 1.0

import QtQuick.Controls
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    width: 1400
    height: 900
    visible: true
    title: qsTr("Supernote")
    color: "lightgray"
    NoteInfo {
        id: noteInfo
    }

    Connections {
        target: noteInfo
        function onHasNewVversion() {
            console.log("Connections onHasNewVversion" )

        }
    }
    menuBar: NoteMenuBar {}

    ExportView {
        id: exportView
        width: 600
        height: 300
        anchors.centerIn: parent
    }

    ScrollView {
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.interactive: true
        ScrollBar.vertical.interactive: true
        width: parent.width
        height: parent.height
        anchors {
            fill: parent
        }
        ListView {
            property alias count: noteInfo.totalPage
            id: listView
            anchors {
                fill: parent
                margins: 20
            }
            model: count
            contentWidth: 1406

            // 去除回弹效果
            boundsBehavior: Flickable.StopAtBounds
            delegate: Rectangle {
                width: listView.width
                height: 1874
                color: "lightgray"
                NoteView {
                    id: noteView
                    width: 1406
                    height: 1874
                    pageIndex: index + 1
                    notePath: noteInfo.notePath
                    anchors.centerIn: parent
                }
            }
            spacing: 20
            Layout.alignment: Qt.AlignHCenter
        }
    }

    footer: ToolBar {
        id: toolBar
        width: parent.width
        height: 32
        FooterView {
            pageInfo: "" + (listView.currentIndex + 1) + " / " + noteInfo.totalPage
            height: parent.height
            id: footerView
            onLastPage: {
                if (listView.currentIndex > 0) {
                    changePage(listView.currentIndex - 1)
                }
            }
            onNextPage: {
                if (listView.currentIndex < noteInfo.totalPage - 1) {
                    changePage(listView.currentIndex + 1)
                }
            }
            onFirstPage: {
                console.log("onFirstPage")
                changePage(0)
            }
            onEndPage: {
                console.log("onEndPage")
                changePage(noteInfo.totalPage - 1)
            }
        }
    }

    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        nameFilters: ["Note files (*.note)"]
        onAccepted: {

            noteInfo.notePath = fileDialog.selectedFile.toString().replace(
                        /^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/, "")
            console.log("You chose: " + noteInfo.notePath)
        }
    }
    Dialog {
        id: dialog
        closePolicy: Popup.NoAutoClose
        anchors.centerIn: parent
        width: 300
        height: 150
        modal: true
        standardButtons: Dialog.Ok
        Label {
            id: label
            anchors.centerIn: parent
            text: qsTr("this is Note APP version is 1.0.0")
        }
        background: Rectangle {
            border.width: 1 //border.color: "#B2B2B2"
            radius: 4
            anchors.fill: parent
        }
    }

    DropArea {
        anchors.fill: parent
        onDropped: function droppedOpen(drop) {
            if (drop.hasUrls) {
                for (var i = 0; i < drop.urls.length; i++) {
                    var str = drop.urls[i].toString().slice(8)
                    if (str.toLowerCase().endsWith(".note")) {
                        console.log(str)
                        noteInfo.notePath = str
                        break
                    }
                }
            }
        }
    }

    function changePage(page) {

        // 1.先取消动画
        listView.highlightMoveDuration = 0

        // 2.改变页码
        listView.currentIndex = page

        // 3.恢复动画
        listView.highlightMoveDuration = 400
    }
}
