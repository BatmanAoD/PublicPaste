import QtQuick 2.5

Item {
    visible: false
    property alias red_rect: red_rect

    Rectangle {
        id: red_rect
        color: "red"
        x: 25; y: 25; width: 50; height: 50
        rotation: 30
    }
}
