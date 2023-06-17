import QtQuick
import Supernote 1.0

import QtQuick.Controls
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

ApplicationWindow {
    property real viewZoom: 1.0
    property int currentPage: 0
    property int y: 0
    id: root
    width: 1400
    height: 900
    visible: true
    title: qsTr("Supernote")
    color: "lightgray"
    Connections {
        target: appManager
        function onVersionChanged() {
            console.log("--Connections onVersionChanged")
            var component = Qt.createComponent("UpdateWindow.qml")
            var window = component.createObject(root)
            window.show()
        }
        function onUpdateVersion() {
            console.log("--Connections onUpdateVersion")
        }
    }

    menuBar: NoteMenuBar {}

    ExportView {
        id: exportView
        width: 600
        height: 300
        anchors.centerIn: parent
    }

    ListView {

        id: listView
        anchors.fill: parent
        model: noteInfo.totalPage
        contentWidth: 1406 * viewZoom
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0
        highlightMoveVelocity: -1
        cacheBuffer: 0

        Component.onCompleted: {
            onContentItemChanged: {
                console.log("onContentItemChanged")
            }
            onContentXChanged: {
                console.log("onContentXChanged:" + contentX)
            }
        }

        //        highlightRangeMode:ListView.ApplyRange
        //                        highlightRangeMode: ListView.StrictlyEnforceRange

        // 去除回弹效果
        boundsBehavior: Flickable.StopAtBounds
        delegate: Item {
            width: root.width
            height: 1872 * viewZoom

            NoteView {
                id: noteView
                anchors.centerIn: parent
                width: 1404 * viewZoom
                height: 1874 * viewZoom
                pageIndex: index + 1
                notePath: noteInfo.notePath
                //                    Layout.alignment: Qt.AlignHCenter
                //                    anchors.centerIn: parent
                zoom: viewZoom
                onPageIndexChanged: {
                    if (currentPage === 0) {
                        currentPage = index + 1
                    }
                }
            }
        }
        onContentYChanged: {
            var t = indexAt(0, contentY)
            if (t !== -1) {
                currentPage = t + 1
            }

            console.log("onContentYChanged:" + contentY + " t:" + t)
        }

        reuseItems: false
        onCurrentIndexChanged: {
            console.log("current index = " + listView.currentIndex)
        }
        spacing: 20

        flickableDirection: Flickable.AutoFlickIfNeeded
        ScrollBar.horizontal: ScrollBar {
            id: hbar
            active: vbar.active
            policy: ScrollBar.AlwaysOn
        }
        ScrollBar.vertical: ScrollBar {
            id: vbar
            active: hbar.active
            policy: ScrollBar.AlwaysOn
        }
        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            preventStealing: false
            hoverEnabled: false
            onWheel: wheel => {
                         if (wheel.modifiers & Qt.ControlModifier) {
                             console.log("x:" + wheel.angleDelta.y)
//                             if (wheel.angleDelta.y < 0) {
//                                 console.log("sacle:" + viewZoom)
//                                 if (viewZoom > 0.3) {
//                                     viewZoom -= 0.1
//                                     console.log("sacle:" + viewZoom)
//                                 }
//                             } else {
//                                 if (viewZoom < 1.0) {
//                                     console.log("sacle:" + viewZoom)
//                                     viewZoom += 0.1
//                                     console.log("sacle:" + viewZoom)
//                                 }
//                             }
                             wheel.accepted = true
                         } else {

                             var value = 0
                             if (wheel.angleDelta.y < 0) {
                                 value = listView.contentY + 40
                                 if (value + root.height > listView.contentHeight) {
                                     value = listView.contentHeight - root.height
                                 }
                                 listView.contentY = value
                             } else {
                                 value = listView.contentY - 40
                                 if (value < 0) {
                                     value = 0
                                 }
                                 listView.contentY = value
                             }
                             wheel.accepted = true
                         }
                     }
        }
    }
    footer: ToolBar {

        id: toolBar
        width: parent.width
        height: 32
        FooterView {
            pageInfo: "" + currentPage + " / " + noteInfo.totalPage
            height: parent.height
            id: footerView
            onLastPage: {
                if (listView.currentIndex > 0) {
                    listView.currentIndex = listView.currentIndex - 1
                }
            }
            onNextPage: {
                if (listView.currentIndex < noteInfo.totalPage - 1) {
                    listView.currentIndex = listView.currentIndex + 1
                }
            }
            onFirstPage: {
                console.log("onFirstPage")
                listView.currentIndex = 0
            }
            onEndPage: {
                console.log("onEndPage")
                listView.currentIndex = noteInfo.totalPage - 1
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

    Dialog {
        id: updateDialog
        closePolicy: Popup.NoAutoClose
        anchors.centerIn: parent
        width: 300
        height: 150
        modal: true
        standardButtons: Dialog.Ok
        Label {
            anchors.centerIn: parent
            text: qsTr("this is Note APP version is 1.0.0")
        }
        background: Rectangle {
            border.width: 1 //border.color: "#B2B2B2"
            radius: 4
            anchors.fill: parent
        }
    }
}
