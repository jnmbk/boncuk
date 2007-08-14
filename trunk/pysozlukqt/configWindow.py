# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'pysozlukqt/ui/config.ui'
#
# Created: Tue Aug 14 20:53:42 2007
#      by: PyQt4 UI code generator 4.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_configWindow(object):
    def setupUi(self, configWindow):
        configWindow.setObjectName("configWindow")
        configWindow.resize(QtCore.QSize(QtCore.QRect(0,0,315,203).size()).expandedTo(configWindow.minimumSizeHint()))
        configWindow.setWindowIcon(QtGui.QIcon("../icons/16x16/configure.png"))

        self.gridlayout = QtGui.QGridLayout(configWindow)
        self.gridlayout.setObjectName("gridlayout")

        self.tabWidget = QtGui.QTabWidget(configWindow)
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

        self.comboBox = QtGui.QComboBox(self.translation)
        self.comboBox.setObjectName("comboBox")
        self.hboxlayout.addWidget(self.comboBox)
        self.gridlayout1.addLayout(self.hboxlayout,0,0,1,1)

        spacerItem = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout1.addItem(spacerItem,1,0,1,1)
        self.tabWidget.addTab(self.translation,"")

        self.trayIcon = QtGui.QWidget()
        self.trayIcon.setObjectName("trayIcon")

        self.gridlayout2 = QtGui.QGridLayout(self.trayIcon)
        self.gridlayout2.setObjectName("gridlayout2")

        self.checkBox = QtGui.QCheckBox(self.trayIcon)
        self.checkBox.setObjectName("checkBox")
        self.gridlayout2.addWidget(self.checkBox,0,0,1,1)

        self.checkBox_2 = QtGui.QCheckBox(self.trayIcon)
        self.checkBox_2.setObjectName("checkBox_2")
        self.gridlayout2.addWidget(self.checkBox_2,1,0,1,2)

        self.checkBox_3 = QtGui.QCheckBox(self.trayIcon)
        self.checkBox_3.setObjectName("checkBox_3")
        self.gridlayout2.addWidget(self.checkBox_3,2,0,1,2)

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

        self.spinBox = QtGui.QSpinBox(self.advanced)
        self.spinBox.setMaximum(4)
        self.spinBox.setObjectName("spinBox")
        self.hboxlayout1.addWidget(self.spinBox)
        self.gridlayout3.addLayout(self.hboxlayout1,0,0,1,1)

        spacerItem2 = QtGui.QSpacerItem(20,40,QtGui.QSizePolicy.Minimum,QtGui.QSizePolicy.Expanding)
        self.gridlayout3.addItem(spacerItem2,1,0,1,1)
        self.tabWidget.addTab(self.advanced,"")
        self.gridlayout.addWidget(self.tabWidget,0,0,1,1)

        self.buttonBox = QtGui.QDialogButtonBox(configWindow)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.NoButton|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridlayout.addWidget(self.buttonBox,1,0,1,1)

        self.retranslateUi(configWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QObject.connect(self.buttonBox,QtCore.SIGNAL("accepted()"),configWindow.accept)
        QtCore.QObject.connect(self.buttonBox,QtCore.SIGNAL("rejected()"),configWindow.reject)
        QtCore.QMetaObject.connectSlotsByName(configWindow)
        configWindow.setTabOrder(self.buttonBox,self.tabWidget)
        configWindow.setTabOrder(self.tabWidget,self.checkBox)
        configWindow.setTabOrder(self.checkBox,self.checkBox_2)
        configWindow.setTabOrder(self.checkBox_2,self.checkBox_3)

    def retranslateUi(self, configWindow):
        configWindow.setWindowTitle(QtGui.QApplication.translate("configWindow", "Configuration", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("configWindow", "Method:", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBox.addItem(QtGui.QApplication.translate("configWindow", "Always Online", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBox.addItem(QtGui.QApplication.translate("configWindow", "Always Offline", None, QtGui.QApplication.UnicodeUTF8))
        self.comboBox.addItem(QtGui.QApplication.translate("configWindow", "Try Offline First", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.translation), QtGui.QApplication.translate("configWindow", "Translation", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBox.setText(QtGui.QApplication.translate("configWindow", "Enable Tray Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBox_2.setText(QtGui.QApplication.translate("configWindow", "Minimize to Tray on Close", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBox_3.setText(QtGui.QApplication.translate("configWindow", "Remember Last State", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.trayIcon), QtGui.QApplication.translate("configWindow", "Tray Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("configWindow", "Debug Level:", None, QtGui.QApplication.UnicodeUTF8))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.advanced), QtGui.QApplication.translate("configWindow", "Advanced", None, QtGui.QApplication.UnicodeUTF8))

