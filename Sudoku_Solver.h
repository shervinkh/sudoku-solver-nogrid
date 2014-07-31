/*
 * Sudoku Solver Class Defination
 * Author: ShervinKH145
 * Date: 1391/2/17
 * Version: 1.1
 * License:
 *  This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SUDOKU_SOLVER_H_
#define SUDOKU_SOLVER_H_

#include <QObject>
#include <QLineEdit>

class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QPushButton;
class QWidget;
class QMainWindow;
class QSpacerItem;

class Sudoku_Solver : public QObject
{
	Q_OBJECT

	private:
		quint8 table[9][9];
		QLineEdit le[9][9];
		bool blacklist_row[9][9];
		bool blacklist_col[9][9];
		bool blacklist_squ[3][3][9];

		QSpacerItem *horizontalSpacer1;
		QSpacerItem *horizontalSpacer2;
		QSpacerItem *horizontalSpacer3;
		QSpacerItem *horizontalSpacer4;
		QSpacerItem *horizontalSpacer5;
		QSpacerItem *horizontalSpacer6;
		QSpacerItem *horizontalSpacer7;
		QSpacerItem *horizontalSpacer8;

		QLabel *title;
		QHBoxLayout *titleBox;

		QGridLayout *grid;

		QPushButton *solveButton;
		QPushButton *resetButton;
		QHBoxLayout *solveBox;

		QLabel *status;
		QLabel *stat;
		QHBoxLayout *statusBox;

		QVBoxLayout *total;

		QWidget *wid;

		void updateGrid();
		bool Solve(int x, int y);

	public:
		Sudoku_Solver();
		QWidget* widget() {return wid;}

		private slots:
			void SolvePuzzle();
		void reset();
		void setTable(const QString &str);

};

#endif
