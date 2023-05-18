import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

MenuBar {
    signal updateNote
    signal convert
    signal help
    signal about
    signal changeLog

    Menu {
        contentWidth: 200
        title: qsTr("File")
        Action {
            text: qsTr("Open")
            onTriggered: fileDialog.open()
        }
        Action {
            text: qsTr("Export")
            onTriggered: exportView.showView()
            enabled: noteInfo.totalPage > 0 ? true : false
        }
    }
    Menu {
        implicitWidth: 100
        id: menuTools
        title: qsTr("Tools")
        Action {
            text: qsTr("Update Note")
            id: actionUpdateNote
            onTriggered: updateNote()
            enabled: noteInfo.totalPage > 0 ? true : false
        }
        Action {
            text: qsTr("Convert to Rel-note")
            id: actionConvert
            onTriggered: convert()
            enabled: noteInfo.totalPage > 0 ? true : false
        }
    }
    Menu {
        implicitWidth: 100
        title: qsTr("Help")
        Action {
            text: qsTr("About")
            onTriggered: dialog.open()
        }
        Action {
            text: qsTr("change log")
            onTriggered: changeLog()
        }
    }
}
