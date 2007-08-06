# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainWindow.ui'
#
# Created: Mon Aug  6 09:28:40 2007
#      by: PyQt4 UI code generator 4.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(QtCore.QSize(QtCore.QRect(0,0,400,300).size()).expandedTo(MainWindow.minimumSizeHint()))
        MainWindow.setWindowIcon(QtGui.QIcon("/usr/share/icons/hicolor/scalable/apps/pysozluk-qt.svg"))

        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")

        self.gridlayout = QtGui.QGridLayout(self.centralwidget)
        self.gridlayout.setMargin(9)
        self.gridlayout.setSpacing(6)
        self.gridlayout.setObjectName("gridlayout")

        self.lineEdit = QtGui.QLineEdit(self.centralwidget)
        self.lineEdit.setObjectName("lineEdit")
        self.gridlayout.addWidget(self.lineEdit,1,1,1,1)

        self.label = QtGui.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.gridlayout.addWidget(self.label,1,0,1,1)

        self.pushButton = QtGui.QPushButton(self.centralwidget)
        self.pushButton.setIcon(QtGui.QIcon("data/icons/16x16/find.png"))
        self.pushButton.setObjectName("pushButton")
        self.gridlayout.addWidget(self.pushButton,1,2,1,1)

        self.textBrowser = QtGui.QTextBrowser(self.centralwidget)
        self.textBrowser.setObjectName("textBrowser")
        self.gridlayout.addWidget(self.textBrowser,0,0,1,3)
        MainWindow.setCentralWidget(self.centralwidget)

        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0,0,400,29))
        self.menubar.setObjectName("menubar")

        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")

        self.menuHelp = QtGui.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        MainWindow.setMenuBar(self.menubar)

        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.actionHelp = QtGui.QAction(MainWindow)
        self.actionHelp.setObjectName("actionHelp")

        self.actionAbout_Pysozluk_Qt = QtGui.QAction(MainWindow)
        self.actionAbout_Pysozluk_Qt.setIcon(QtGui.QIcon("data/icons/16x16/pysozluk-qt.png"))
        self.actionAbout_Pysozluk_Qt.setObjectName("actionAbout_Pysozluk_Qt")

        self.actionAbout_Qt = QtGui.QAction(MainWindow)
        self.actionAbout_Qt.setObjectName("actionAbout_Qt")

        self.actionOffline = QtGui.QAction(MainWindow)
        self.actionOffline.setCheckable(True)
        self.actionOffline.setChecked(True)
        self.actionOffline.setObjectName("actionOffline")

        self.actionSave = QtGui.QAction(MainWindow)
        self.actionSave.setIcon(QtGui.QIcon("data/icons/16x16/filesave.png"))
        self.actionSave.setObjectName("actionSave")

        self.actionQuit = QtGui.QAction(MainWindow)
        self.actionQuit.setIcon(QtGui.QIcon("data/icons/16x16/exit.png"))
        self.actionQuit.setObjectName("actionQuit")

        self.actionConfigure = QtGui.QAction(MainWindow)
        self.actionConfigure.setIcon(QtGui.QIcon("data/icons/16x16/configure.png"))
        self.actionConfigure.setObjectName("actionConfigure")
        self.menuFile.addAction(self.actionConfigure)
        self.menuFile.addAction(self.actionSave)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionQuit)
        self.menuHelp.addAction(self.actionAbout_Pysozluk_Qt)
        self.menuHelp.addAction(self.actionAbout_Qt)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)
        MainWindow.setTabOrder(self.lineEdit,self.textBrowser)
        MainWindow.setTabOrder(self.textBrowser,self.pushButton)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "Pysozluk-Qt", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("MainWindow", "Keyword:", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButton.setText(QtGui.QApplication.translate("MainWindow", "&Search", None, QtGui.QApplication.UnicodeUTF8))
        self.textBrowser.setHtml(QtGui.QApplication.translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'Sans Serif\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.menuFile.setTitle(QtGui.QApplication.translate("MainWindow", "&File", None, QtGui.QApplication.UnicodeUTF8))
        self.menuHelp.setTitle(QtGui.QApplication.translate("MainWindow", "&Help", None, QtGui.QApplication.UnicodeUTF8))
        self.actionHelp.setText(QtGui.QApplication.translate("MainWindow", "&Index", None, QtGui.QApplication.UnicodeUTF8))
        self.actionHelp.setShortcut(QtGui.QApplication.translate("MainWindow", "F1", None, QtGui.QApplication.UnicodeUTF8))
        self.actionAbout_Pysozluk_Qt.setText(QtGui.QApplication.translate("MainWindow", "About &Pysozluk-Qt", None, QtGui.QApplication.UnicodeUTF8))
        self.actionAbout_Qt.setText(QtGui.QApplication.translate("MainWindow", "About &Qt", None, QtGui.QApplication.UnicodeUTF8))
        self.actionOffline.setText(QtGui.QApplication.translate("MainWindow", "&Offline", None, QtGui.QApplication.UnicodeUTF8))
        self.actionOffline.setShortcut(QtGui.QApplication.translate("MainWindow", "Ctrl+M", None, QtGui.QApplication.UnicodeUTF8))
        self.actionSave.setText(QtGui.QApplication.translate("MainWindow", "&Save", None, QtGui.QApplication.UnicodeUTF8))
        self.actionSave.setShortcut(QtGui.QApplication.translate("MainWindow", "Ctrl+S", None, QtGui.QApplication.UnicodeUTF8))
        self.actionQuit.setText(QtGui.QApplication.translate("MainWindow", "&Quit", None, QtGui.QApplication.UnicodeUTF8))
        self.actionQuit.setShortcut(QtGui.QApplication.translate("MainWindow", "Alt+F4", None, QtGui.QApplication.UnicodeUTF8))
        self.actionConfigure.setText(QtGui.QApplication.translate("MainWindow", "&Configure PySozluk-Qt", None, QtGui.QApplication.UnicodeUTF8))

