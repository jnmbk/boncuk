# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/config.ui'
#
# Created: Wed Aug 15 11:38:55 2007
#      by: PyQt4 UI code generator 4.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_ConfigWindow(object):
    def setupUi(self, ConfigWindow):
        ConfigWindow.setObjectName("ConfigWindow")
        ConfigWindow.setWindowModality(QtCore.Qt.WindowModal)
        ConfigWindow.resize(QtCore.QSize(QtCore.QRect(0,0,315,203).size()).expandedTo(ConfigWindow.minimumSizeHint()))
        ConfigWindow.setWindowIcon(QtGui.QIcon("../icons/16x16/configure.png"))

        self.gridlayout = QtGui.QGridLayout(ConfigWindow)
        self.gridlayout.setObjectName("gridlayout")

        self.tabWidget = QtGui.QTabWidget(ConfigWindow)
        self.tabWidget.setObjectName("tabWidget")

        self.translation = QtGui.QWidget()
        self.translation.setObjectName("translation")

        self.gridlayout1 = QtGui.QGridLayout(self.translation)
        self.gridlayout1.setObjectName("gridlayout1")

        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setObjectName("hboxlayout")

        self.label_2 = QtGui.QLabel(self.translation)
        self.label_2.setObjectName("label_2")
        self.hboxlayout.addWidget(self.label_2)

        self.translation_method = QtGui.QComboBox(self.translation)
        self.translation_method.setObjectName("translation_method")
        self.hboxlayout.addWidget(self.translation_method)
        self.gridlayout1.addLayout(self.hboxlayout,0,0,1,1)

        spacerItem = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout1.addItem(spacerItem,1,0,1,1)
        self.tabWidget.addTab(self.translation,"")

        self.trayIcon = QtGui.QWidget()
        self.trayIcon.setObjectName("trayIcon")

        self.gridlayout2 = QtGui.QGridLayout(self.trayIcon)
        self.gridlayout2.setObjectName("gridlayout2")

        self.trayIcon_enable = QtGui.QCheckBox(self.trayIcon)
        self.trayIcon_enable.setObjectName("trayIcon_enable")
        self.gridlayout2.addWidget(self.trayIcon_enable,0,0,1,1)

        self.trayIcon_minimizeOnClose = QtGui.QCheckBox(self.trayIcon)
        self.trayIcon_minimizeOnClose.setObjectName("trayIcon_minimizeOnClose")
        self.gridlayout2.addWidget(self.trayIcon_minimizeOnClose,1,0,1,2)

        self.trayIcon_startMinimized = QtGui.QCheckBox(self.trayIcon)
        self.trayIcon_startMinimized.setObjectName("trayIcon_startMinimized")
        self.gridlayout2.addWidget(self.trayIcon_startMinimized,2,0,1,2)

        spacerItem1 = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout2.addItem(spacerItem1,3,1,1,1)
        self.tabWidget.addTab(self.trayIcon,"")

        self.advanced = QtGui.QWidget()
        self.advanced.setObjectName("advanced")

        self.gridlayout3 = QtGui.QGridLayout(self.advanced)
        self.gridlayout3.setObjectName("gridlayout3")

        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setObjectName("hboxlayout1")

        self.label = QtGui.QLabel(self.advanced)
        self.label.setObjectName("label")
        self.hboxlayout1.addWidget(self.label)

        self.advanced_debugLevel = QtGui.QSpinBox(self.advanced)
        self.advanced_debugLevel.setMaximum(4)
        self.advanced_debugLevel.setObjectName("advanced_debugLevel")
        self.hboxlayout1.addWidget(self.advanced_debugLevel)
        self.gridlayout3.addLayout(self.hboxlayout1,0,0,1,1)

        spacerItem2 = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout3.addItem(spacerItem2,1,0,1,1)
        self.tabWidget.addTab(self.advanced,"")
        self.gridlayout.addWidget(self.tabWidget,0,0,1,1)

        self.buttonBox = QtGui.QDialogButtonBox(ConfigWindow)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.NoButton|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridlayout.addWidget(self.buttonBox,1,0,1,1)

        self.retranslateUi(ConfigWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QObject.connect(self.buttonBox,QtCore.SIGNAL("accepted()"),ConfigWindow.accept)
        QtCore.QObject.connect(self.buttonBox,QtCore.SIGNAL("rejected()"),ConfigWindow.reject)
        QtCore.QMetaObject.connectSlotsByName(ConfigWindow)
        ConfigWindow.setTabOrder(self.buttonBox,self.tabWidget)
        ConfigWindow.setTabOrder(self.tabWidget,self.trayIcon_enable)
        ConfigWindow.setTabOrder(self.trayIcon_enable,self.trayIcon_minimizeOnClose)
        ConfigWindow.setTabOrder(self.trayIcon_minimizeOnClose,self.trayIcon_startMinimized)

    def retranslateUi(self, ConfigWindow):
        ConfigWindow.setWindowTitle(QtGui.QApplication.translate("ConfigWindow", "Configuration", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("ConfigWindow", "Method:", None, QtGui.QApplication.UnicodeUTF8))
        self.translation_method.addItem(QtGui.QApplication.translate("ConfigWindow", "Try Offline First", None, QtGui.QApplication.UnicodeUTF8))
        self.translation_method.addItem(QtGui.QApplication.translate("ConfigWindow", "Always Offline", None, QtGui.QApplication.UnicodeUTF8))
        self.translation_method.addItem(QtGui.QApplication.translate("ConfigWindow", "Always Online", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.translation), QtGui.QApplication.translate("ConfigWindow", "Translation", None, QtGui.QApplication.UnicodeUTF8))
        self.trayIcon_enable.setText(QtGui.QApplication.translate("ConfigWindow", "Enable Tray Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.trayIcon_minimizeOnClose.setText(QtGui.QApplication.translate("ConfigWindow", "Minimize to Tray on Close", None, QtGui.QApplication.UnicodeUTF8))
        self.trayIcon_startMinimized.setText(QtGui.QApplication.translate("ConfigWindow", "Start Minimized", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.trayIcon), QtGui.QApplication.translate("ConfigWindow", "Tray Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("ConfigWindow", "Debug Level:", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.advanced), QtGui.QApplication.translate("ConfigWindow", "Advanced", None, QtGui.QApplication.UnicodeUTF8))

