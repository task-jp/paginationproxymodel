import QtQuick 2.12
import QtQuick.Controls 2.5
import PaginationProxyModel 2.15

ApplicationWindow {
    width: 320
    height: 480
    visible: true
    title: 'PaginationProxyModel'

    ListModel {
        id: items
        readonly property int countPerPage: 10
        readonly property int pageCount: Math.floor((items.count + items.countPerPage - 1) / items.countPerPage)
        Component.onCompleted: {
            for (var i = 0; i < 21; i++)
                items.append( { "text": 'Item at %1'.arg(i) })
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Repeater {
            model: items.pageCount
            Item {
                id: delegate
                property int index: model.index
                ListView {
                    id: listView
                    anchors.fill: parent
                    interactive: false
                    model: PaginationProxyModel {
                        source: items
                        page: delegate.index
                        countPerPage: items.countPerPage
                    }
                    delegate: Text {
                        width: ListView.view.width
                        height: ListView.view.height / items.countPerPage
                        text: model.text
                        verticalAlignment: Qt.AlignVCenter
                    }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        Repeater {
            model: items.pageCount
            TabButton {
                text: qsTr("Page %1").arg(model.modelData)
            }
        }
    }
}
