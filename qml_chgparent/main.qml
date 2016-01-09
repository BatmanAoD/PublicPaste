import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1


ApplicationWindow {
    id:  winRoot
    
    property alias persistent: persistent
    Persistent {
        id: persistent
    }
    
    TabView {
        width: 100
        height: 100
        
        Tab {
            title: "tab1"
            anchors.fill: parent

            Tab1 {
                anchors.fill: parent
            }
        }

        Tab {
            title: "tab2"
            anchors.fill: parent
            
            Tab2 {
                anchors.fill: parent
            }
        }
    }
}
