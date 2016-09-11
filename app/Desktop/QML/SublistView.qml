import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Layouts 1.3
import myReddit 0.1

Item {
    property alias currentIndex: sublistView.currentIndex
    property alias currentItem: sublistView.currentItem
    property alias count: sublistView.count

    function update() {
        sublistModel.clear()
        var names = theReddit.subredditNames;
        for (var i = 0; i < names.length; ++i)
            sublistModel.append({"name": names[i]});
        sublistView.currentIndex = 0
    }
    ListModel {
        id: sublistModel
    }
    ListView {
        id: sublistView
        anchors.fill: parent
        
        model: sublistModel
        delegate: sublistDelegate
        highlight: sublistHighlighter
        
        clip: true
        focus: true
        
        Component.onCompleted: parent.update()
    }
    Component {
        id: sublistDelegate
        Item {
            property string subName: name
            width: ListView.view.width
            height: text.contentHeight + 4
            Text {
                id: text
                text: "/r/" + name
                leftPadding: 4
            }
            MouseArea {
                anchors.fill: parent
                onClicked: sublistView.currentIndex = index
            }
        }
    }
    Component {
        id: sublistHighlighter
        Rectangle {
            width: sublistView.width
            height: sublistDelegate.height
            color: "lightblue"
        }
    }
}
