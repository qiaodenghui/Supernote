import QtQuick 2.15
import Supernote 1.0

import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtQuick.Dialogs

ApplicationWindow {
    property real viewZoom: 1.0
    property int currentPage: 0
    property bool isEditor: false
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
    Component {
        id: noteViewDelegate
        Item {
            id: noteItem
            width: root.width
            height: 1872 * viewZoom
            NoteView {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.centerIn: parent
                width: 1404 * viewZoom
                height: 1874 * viewZoom
                pageIndex: index + 1
                notePath: noteInfo.notePath
                zoom: viewZoom
                onPageIndexChanged: {
                    if (currentPage === 0) {
                        currentPage = 1
                    }
                }
            }
        }
    }
    ListView {

        id: listView
        anchors.fill: parent
        model: noteInfo.totalPage
        contentWidth: 1404 * viewZoom

        snapMode: ListView.NoSnap
        highlightMoveDuration: 0
        highlightMoveVelocity: -1

        // 去除回弹效果
        boundsBehavior: Flickable.StopAtBounds
        delegate: noteViewDelegate

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
            size: listView.height / listView.contentHeight

            stepSize: listView.height / listView.contentHeight * 0.2
            onPositionChanged: {
                console.log("current position = " + position)
                if (isEditor) {
                    console.log("---isEditor--- ")
                    return
                }
                var value = position * noteInfo.totalPage / (1.0 - size)

                console.log("value = " + value)
                var p = value.toFixed(0)
                currentPage = Number(p) + 1
                if (currentPage > noteInfo.totalPage) {
                    currentPage = noteInfo.totalPage
                }

                console.log("currentPage = " + currentPage)
            }
        }
        MouseArea {
            id: mapMouseArea
            anchors.fill: parent
            preventStealing: false
            hoverEnabled: false
            onWheel: wheel => {
                         if (wheel.modifiers & Qt.ControlModifier) {
                             console.log("x:" + wheel.angleDelta.y)
                             if (wheel.angleDelta.y < 0) {
                                 console.log("sacle:" + viewZoom)
                                 if (viewZoom > 0.3) {
                                     viewZoom -= 0.1
                                     console.log("sacle:" + viewZoom)
                                 }
                             } else {
                                 if (viewZoom < 1.0) {
                                     console.log("sacle:" + viewZoom)
                                     viewZoom += 0.1
                                     console.log("sacle:" + viewZoom)
                                 }
                             }
                         } else {
                             isEditor = false
                             if (wheel.angleDelta.y < 0) {

                                 vbar.increase()
                             } else {
                                 vbar.decrease()
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
                if (currentPage > 1) {
                    isEditor = true
                    var value = vbar.position - (1.0 - vbar.size) / noteInfo.totalPage
                    if (value < 0) {
                        value = 0
                    }
                    vbar.position = value
                    --currentPage
                }
            }
            onNextPage: {
                if (currentPage < noteInfo.totalPage) {
                    isEditor = true
                    var value = vbar.position + (1.0 - vbar.size) / noteInfo.totalPage
                    if (value + vbar.size > 1.0) {
                        value = 1.0 - vbar.size
                    }
                    vbar.position = value
                    ++currentPage
                }
            }
            onFirstPage: {
                console.log("onFirstPage")
                isEditor = false
                vbar.position = 0
            }
            onEndPage: {
                console.log("onEndPage")
                isEditor = false
                vbar.position = 1.0 - vbar.size
            }
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
                    var urlString=drop.urls[i].toString()
                    var str;
                    if (urlString.startsWith("file:///")) {
                        var k = urlString.charAt(9) === ':' ? 8 : 7
                        str=decodeURIComponent(urlString.substring(k))
                    } else {
                         str = decodeURIComponent(urlString);
                    }
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
