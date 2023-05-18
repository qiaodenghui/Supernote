import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    property string pageInfo: ""
    signal nextPage()
    signal lastPage()
    signal firstPage()
    signal endPage()
    RowLayout {
        anchors.fill: parent
        spacing: 0
        ToolButton {
            id: left
            height: 16
            width: 16
            icon.source: "../images/arrow_left.png"
            onClicked: {
                lastPage()
            }
        }
        ToolButton {
            id: doubleLeft
            icon.source: "../images/double_arrow_left.png"
            width: 16
            height: 16
            onClicked: firstPage()
        }
        Rectangle{
            width: 100
            height:parent.height
            Label {
                color: noteInfo.totalPage>0? "black":"gray"
                text: pageInfo
                elide: Label.ElideRight
                anchors.centerIn: parent
            }
        }
        ToolButton {
            id: doubleRight
            icon.source: "../images/double_arrow_right.png"
            width: 16
            height: 16
            onClicked: endPage()
        }
        ToolButton {
            id: right
            icon.source:"../images/arrow_right.png"
            width: 32
            height: 32
            onClicked: {
                nextPage()
            }
        }

    }
}
