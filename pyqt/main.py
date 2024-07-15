import sys

from PyQt5 import uic, QtCore
from PyQt5.QtWidgets import QApplication, QDialog,QMessageBox, QHeaderView
from PyQt5.QtWidgets import QMainWindow, QTableWidgetItem
from datetime import date
import sqlite3


class Notice(QDialog):
    def __init__(self):
        super().__init__()
        uic.loadUi('notice.ui', self)
        self.con = sqlite3.connect("AniList.db")
        self.setWindowFlag(QtCore.Qt.WindowStaysOnTopHint)
        self.pushButton.clicked.connect(self.ok)


    def ok(self):
        self.close()


class Dialog(QDialog):
    def __init__(self):
        super().__init__()
        uic.loadUi('calendar.ui', self)
        self.date = self.calendarWidget.selectedDate()
        self.calendarWidget.setMinimumDate(self.date)



class MyWidget(QMainWindow):
    def __init__(self, ):
        global now_date
        now_date = date.today().strftime('%d.%m.%Y')
        super().__init__()
        uic.loadUi('main.ui', self)
        self.con = sqlite3.connect("AniList.db")
        self.cur = self.con.cursor()
        self.widgets = {"Планы": [self.tableWidget_2, self.pushButton_2, self.comboBox_3, self.lineEdit_2,
                                  self.pushButton_6],
                        "Просмотрено": [self.tableWidget_3, self.pushButton_3, self.comboBox_5, self.lineEdit_3,
                                  self.pushButton_7],
                        "Ожидания": [self.tableWidget_4, self.pushButton_4, self.comboBox_6, self.lineEdit_4,
                                     self.pushButton_8]}
        self.tableWidget_1.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table_show("Планы")
        self.table_show("Просмотрено")
        self.table_show("Ожидания")

        self.pushButton.clicked.connect(self.add1)
        self.pushButton_1.clicked.connect(self.find)

        self.pushButton_2.clicked.connect(self.find_other)
        self.pushButton_3.clicked.connect(self.find_other)
        self.pushButton_4.clicked.connect(self.find_other)

        self.pushButton_6.clicked.connect(self.delete)
        self.pushButton_7.clicked.connect(self.delete)
        self.pushButton_8.clicked.connect(self.delete)

        self.notice_check()

    def notice_check(self):
        names = self.cur.execute(f"""
           SELECT 
           Name
           FROM
           Ожидания
           WHERE Date = '{now_date}'""").fetchall()
        if len(names) != 0:
            self.notice = Notice()
            self.notice.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
            self.notice.tableWidget.horizontalHeader().setMinimumSectionSize(0)
            self.notice.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
            self.notice.tableWidget.setRowCount(len(names))
            for i, row in enumerate(names):
                for j, elem in enumerate(row):
                    self.notice.tableWidget.setItem(i, j, QTableWidgetItem(str(elem)))
            self.notice.show()

            self.cur.execute(f"""
                DELETE from Ожидания 
                WHERE Date = '{now_date}'""").fetchall()
            self.con.commit()
            self.table_show("Ожидания")

    def add1(self):
        global now_date, items
        items = []
        name = self.comboBox_4.currentText()
        for item in self.tableWidget_1.selectedItems():
            items.append(item.text())

        try:
            if name == "Ожидания":
                self.dialog = Dialog()
                self.dialog.show()
                self.dialog.pushButton.clicked.connect(self.run_calendar)
            else:
                self.cur.execute(f"""
                                                    INSERT INTO '{name}'(Name, Genre,  Year, DateofAdd) values 
                                                    ('{items[0]}','{items[1]}', {items[2]}, '{now_date}')
                                                    """).fetchall()
                self.table_show(name)
                self.error1(f"'{items[0]}' успешно добавлено в '{name}'")
            self.con.commit()

        except IndexError:
            self.error1("Ничего не выбрано")
        except:
            self.error1(f"'{items[0]}' уже есть в '{name}'")

    def run_calendar(self):
        self.dialog.date = self.dialog.calendarWidget.selectedDate()
        self.cur.execute(f"""
                            INSERT INTO Ожидания (Name, Genre, Year, Date) 
                            values ('{items[0]}','{items[1]}', {items[2]}, '{self.dialog.date.toString("dd.MM.yyyy")}')
                            """).fetchall()
        self.con.commit()
        self.dialog.close()
        self.error1(f"'{items[0]}' успешно добавлено в 'Ожидания'")
        self.table_show("Ожидания")

    def error1(self, text):
        dlg = QMessageBox(self)
        dlg.setWindowTitle("Message")
        dlg.setText(text)
        dlg.exec()

    def table_show(self, name):
        self.widgets[name][0].horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.widgets[name][0].horizontalHeader().setMinimumSectionSize(0)
        self.widgets[name][0].horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        result = self.cur.execute(f"SELECT * FROM '{name}'").fetchall()
        self.widgets[name][0].setRowCount(len(result))
        for i, row in enumerate(result):
            for j, elem in enumerate(row):
                self.widgets[name][0].setItem(i, j, QTableWidgetItem(str(elem)))

    def cop(self):
        return {"По названию": "Name", "По жанру": "Genre", "По году выпуска": "Year",
               "По дате добавления": "DateofAdd",
               "По дате выхода новых серий": "Date",}

    def find(self):
        result = []
        text = ""
        if self.comboBox_2.currentText() == "Все":
            result = self.cur.execute(f"""
                                                        SELECT
                                                            AllAnime.Name,
                                                            Genre.Genre,
                                                            AllAnime.Year
                                                        FROM
                                                            AllAnime
                                                        LEFT JOIN Genre
                                                            ON AllAnime.Genre = Genre.ID
                                                        """).fetchall()
        elif self.lineEdit_1.text() != "":
            column = self.cop()[self.comboBox_2.currentText()]
            if column == "Name":
                text = self.lineEdit_1.text().capitalize()
            elif column == "Genre":
                column = "Genre.Genre"
                text = self.lineEdit_1.text().capitalize()
            else:
                text = self.lineEdit_1.text()
            result = self.cur.execute(f"""
                                            SELECT
                                                AllAnime.Name,
                                                Genre.Genre,
                                                AllAnime.Year
                                            FROM
                                                AllAnime
                                            LEFT JOIN Genre
                                                ON AllAnime.Genre = Genre.ID
                                            WHERE {column} LIKE '{text}%'
                                            """).fetchall()
        self.tableWidget_1.setRowCount(len(result))
        if len(result) == 0 and text != "":
            self.error1(f"'{text}' не найдено")
        for i, elem in enumerate(result):
            for j, val in enumerate(elem):
                self.tableWidget_1.setItem(i, j, QTableWidgetItem(str(val)))
        self.tableWidget_1.resizeColumnsToContents()
        self.tableWidget_1.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)

    def find_other(self):
        result = []
        button = QApplication.instance().sender()
        for titles in self.widgets.keys():
            if self.widgets[titles][1] == button:
                name = titles
                break
        if self.widgets[name][2].currentText() == "Все":
            result = self.cur.execute(f""" SELECT * from {name}""").fetchall()
            text = ""
        else:
            column = self.cop()[self.widgets[name][2].currentText()]
            text = self.widgets[name][3].text()
            if column == "Name" or column == "Genre":
                text1 = text.capitalize()
            else:
                text1 = text
            result = self.cur.execute(f""" SELECT * from {name}
                                                WHERE {column} LIKE '{text1}%'""").fetchall()
        if len(result) == 0 and text != "":
            self.error1(f"'{text}' не найдено")
        else:
            self.widgets[name][0].setRowCount(len(result))
            for i, elem in enumerate(result):
                for j, val in enumerate(elem):
                    self.widgets[name][0].setItem(i, j, QTableWidgetItem(str(val)))
            self.widgets[name][0].resizeColumnsToContents()
            self.widgets[name][0].horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)

    def delete(self):
        items = []
        button = QApplication.instance().sender()
        for text in self.widgets.keys():
            if self.widgets[text][4] == button:
                name = text
                break
        for item in self.widgets[name][0].selectedItems():
            items.append(item.text())
        try:
            valid = QMessageBox.question(
                self, '', f"Вы действительно хотите удалить '{items[0]}' из 'Планы'",
                QMessageBox.Yes, QMessageBox.No)
            if valid == QMessageBox.Yes:
                self.cur.execute(f"""DELETE from {name} WHERE name = '{items[0]}'""").fetchall()
                self.con.commit()
                self.table_show(name)
        except IndexError:
            self.error1("Ничего не выбрано")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MyWidget()
    ex.show()
    sys.exit(app.exec())