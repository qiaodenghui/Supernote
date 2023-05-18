import QtQuick
import Assistant 1.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs

Window {
//    id: root
    width: 640
    height: 480
    visible: true
    minimumHeight: 480
    minimumWidth: 640
    color: "#373250"
    title: qsTr("Supernote Assistant")

    Export{
        id:exportObj
        appKey: ""
        hmacKey: ""
        pageRange: ""
        notePath: ""
    }

    FirstView{
        id:firstView
        visible: true
        onButtonClicked:function(appKey,hmacKey) {
            exportObj.appKey = appKey
            exportObj.hmacKey = hmacKey
            firstView.visible=false
            secondView.visible=true
        }
    }

    SecondView{
        id:secondView
        visible: false
        onLast:{
            exportObj.notePath = ""
            exportObj.pageRange = ""
            firstView.visible=true
            secondView.visible=false
        }
        onConfirm:{
            exportObj.notePath = secondView.mNotePath
            exportObj.pageRange = secondView.mPageRange
           var ret= exportObj.startExport(1);
        }
        onOpen:{
            fileDialog.open()
        }
    }



    FileDialog {
        id: fileDialog

        title: "Please choose a file"
        nameFilters: ["Note files (*.note)"]
        onAccepted: {

            secondView.mNotePath= fileDialog.selectedFile.toString().replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            console.log("You chose: " + secondView.mNotePath)
        }
    }

}
