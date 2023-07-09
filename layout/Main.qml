import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import Qt.labs.folderlistmodel
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id: rect
        width: 80
        height: 20
        color: "black"
        MouseArea{
            anchors.fill: parent
            onClicked:{
                fileDialog.open()
            }
        }

    }

    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        nameFilters: ["Note files (*.note)"]
        onAccepted: {
            noteInfo.notePath = urlToPath(fileDialog.selectedFile.toString())
            console.log("You chose: " + noteInfo.notePath)
        }
        function urlToPath(urlString) {
            var s
            if (urlString.startsWith("file:///")) {
                var k = urlString.charAt(9) === ':' ? 8 : 7
                s = urlString.substring(k)
            } else {
                s = urlString
            }
            return decodeURIComponent(s);
        }
    }
}

