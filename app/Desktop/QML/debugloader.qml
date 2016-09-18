import QtQuick 2.7

Loader {
    id: loader
    objectName: "loader"
    active: true
    source: "SettingsWindow.qml"

    signal reloading()

    function reload()
    {
        var oldSource = source
        source = '';
        reloading()
        source = oldSource

        console.debug('Reloaded QML!')
    }
    Shortcut {
        sequence: "F5"
        context: Qt.ApplicationShortcut
        onActivated: loader.reload()
    }
    Shortcut {
        sequence: "ESC"
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}

